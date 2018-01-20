//
//  DeviceStateManager.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/25.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "DeviceStateManager.h"

#import "CELightsTableViewCell.h"

@implementation DeviceStateManager
{
    NSMutableArray *_checkInfoArr;  //记录正在设备的查询信息，存的是 {deviceId:checkCount}
    NSMutableArray *_lastDeviceIds; //上一次查询的设备Id数组
}

+ (DeviceStateManager *)shareInstance {
    static DeviceStateManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[DeviceStateManager alloc] init];
    });
    return manager;
}

/*
 检查设备当前连接状态
 
 处于连接状态的判定:
 发送查询指令到该设备，能获取到信息说明处于连接状态
 未处于连接状态的判定:
 当发送了3次查询指令到设备，依旧未获取到信息则判定当前未连接
 
 指令每隔3s发送一次，时间间隔不可太低，切记切记，如有解决不了的问题，可尝试重启手机 *_*
 
 每次查询时获取该tableView当前屏幕显示出的所有设备，
 当下一次查询时与上一次查询的设备们不一致时不理会，即只查当前显示的设备

 */
- (void)checkDeviceStateWith:(NSMutableArray *)deviceIds
                       block:(void(^)(NSNumber *devicId))block {
        
    if (deviceIds.count == 0) {
        return;
    }
    
    NSLog(@"这次查询的设备为: %@",deviceIds);
    
    if (!_checkInfoArr) {
        _checkInfoArr = @[].mutableCopy;
    }
    
    //查询超过3次的设备视为离线状态
    for (NSMutableDictionary *mDic in _checkInfoArr) {
        NSInteger index = [mDic[@"index"] integerValue];
        if (index > 3) {
            
            NSNumber *deviceId = mDic[@"deviceId"];
            [UDManager saveDeviceOnlineState:deviceId online:NO];
            
            if (block) {
                block(deviceId);
            }
        }
    }
    
    //删除被跳过的设备
    NSMutableArray *prepareDeleteArr = @[].mutableCopy;
    for (NSMutableDictionary *mDic in _checkInfoArr) {
        
        NSNumber *deviceId = mDic[@"deviceId"];
        if (![deviceIds containsObject:deviceId]) {
            [prepareDeleteArr addObject:mDic];
        }
    }
    
    for (NSMutableDictionary *mDic in prepareDeleteArr) {
        [_checkInfoArr removeObject:mDic];
    }
    
    NSLog(@"不需要继续查询的设备: %@",prepareDeleteArr);
    
    //查看是否有新的设备需要查询，有则添加进checkInfoArr
    NSMutableArray *newAddDeviceIds = [self getNeedlessWith:deviceIds arr2:_lastDeviceIds];
    if (newAddDeviceIds.count != 0) {
        
        for (NSNumber *newDiviceId in newAddDeviceIds) {
            NSMutableDictionary *mDic = @{}.mutableCopy;
            [mDic setValue:newDiviceId forKey:@"deviceId"];
            [mDic setValue:@(1) forKey:@"index"];
            
            if (![_checkInfoArr containsObject:mDic]) {
                [_checkInfoArr addObject:mDic];
            }
        }
        
    }
    
    NSLog(@"正在查询中的设备信息: %@",_checkInfoArr);
    
    //所有查询设备的查询次数加1
    for (NSMutableDictionary *mDic in _checkInfoArr) {
        NSInteger index = [mDic[@"index"] integerValue];
        index++;
        [mDic setValue:@(index) forKey:@"index"];
    }
    
    //统一发送查询指令
    for (NSNumber *deviceId in deviceIds) {
        NSLog(@"正在发送查询设备: %@ 的指令",deviceId);
        
        [[LightModelApi sharedInstance] getState:deviceId
                                         success:^(NSNumber * _Nullable deviceId, UIColor * _Nullable color, NSNumber * _Nullable powerState, NSNumber * _Nullable colorTemperature, NSNumber * _Nullable supports) {
                                             
                                             NSArray *dataArr = @[
                                                                  deviceId,
                                                                  powerState,
                                                                  colorTemperature,
                                                                  ];
                                             NSLog(@"dataArr: %@",dataArr);
                                             
                                             NSInteger temperature = [self compatibilityDeviceTemperatureToOpposite:deviceId temperature:[colorTemperature integerValue]];
                                             
//                                             NSInteger temperature = [colorTemperature integerValue];
                                             
                                             [UDManager savePowerStateWith:deviceId power:[powerState boolValue]];
                                             [UDManager saveTemperatureWith:deviceId temperature:temperature];
                                             [UDManager saveDeviceOnlineState:deviceId online:YES];
                                             
                                             //将该设备的查询次数置0
                                             for (NSMutableDictionary *mDic in _checkInfoArr) {
                                                 NSNumber *getDiviceId = mDic[@"deviceId"];
                                                 if ([getDiviceId isEqualToNumber:deviceId]) {
                                                     [mDic setValue:@(1) forKey:@"index"];
                                                     break;
                                                 }
                                             }
                                             
                                             if (block) {
                                                 block(deviceId);
                                             }
                                             
                                         } failure:^(NSError * _Nullable error) {
                                             
                                         }];
    }
    
    _lastDeviceIds = deviceIds.mutableCopy;
    
    NSLog(@"---------------------------------------------");
    
}

/*
 检查灯组状态
 获取灯组内第一盏灯的状态更新即可
 */
- (void)checkAreaStateWith:(NSMutableArray <CSRAreaEntity *>*)areas
                     block:(void(^)(NSNumber *areaId))block {
    //牛逼哄哄的线程锁
    @synchronized (self) {
        
        //先看距离上一次发送指令的时间和当前时间是否超过1s，小于的话就这次的发送就放弃了，防止命令满天飞导致其他问题
        NSDate *lastDate = [CommandManager shareInstance].lastSendOfDate;
        NSDate *currentDate = [NSDate date];
        if ([currentDate timeIntervalSince1970] - [lastDate timeIntervalSince1970] < 1) {
            NSLog(@"刚刚发送完数据，取消这一次的查询指令");
            return;
        }
        
        //获取当前设备组里的一个灯，将其状态赋予给灯组，会有不精确的情况，将就
        
        for (CSRAreaEntity *areaEntity in areas) {
            NSArray *devices = areaEntity.devices.allObjects.mutableCopy;
            CSRDeviceEntity *deviceEntity = devices.firstObject;
            
            if (deviceEntity != nil) {
                BOOL devicePower = [UDManager getPowerStateWith:deviceEntity.deviceId];
                NSInteger temperature = [UDManager getTemperatureWith:deviceEntity.deviceId];
                NSInteger index = [UDManager getTemperatureIndexWith:deviceEntity.deviceId];
                
                [UDManager savePowerStateWith:areaEntity.areaID power:devicePower];
                [UDManager saveTemperatureWith:areaEntity.areaID temperature:temperature];
                [UDManager saveTemperatureIndexWith:areaEntity.areaID index:index];
                
                if (block) {
                    block(areaEntity.areaID);
                }

            }
        }
        
        
    }
}

#pragma mark - APIs(private)
//取arr1比arr2多余的元素
- (NSMutableArray *)getNeedlessWith:(NSMutableArray *)arr1 arr2:(NSMutableArray *)arr2 {
    __block NSMutableArray *differentArr = @[].mutableCopy;
    
    [arr1 enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        NSNumber *number1 = obj;//[obj objectAtIndex:idx];
        __block BOOL isHave = NO;
        [arr2 enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            if ([number1 isEqual:obj]) {
                isHave = YES;
                *stop = YES;
            }
        }];
        if (!isHave) {
            [differentArr addObject:obj];
        }
    }];
    
    return differentArr;
}

//兼容某些灯型的相反的色温标准
- (NSInteger)compatibilityDeviceTemperatureToOpposite:(NSNumber *)deviceId temperature:(NSInteger)temperature {
    
    NSInteger newTemperature = temperature;
    
    NSString *codingId = [UDManager getDeviceCodingId:deviceId];

    if ([codingId isEqualToString:@"54685143"] ||
        [codingId isEqualToString:@"53185142"] ||
        [codingId isEqualToString:@"53184444"] ||
        [codingId isEqualToString:@"53185555"]
        ) {
        switch (temperature) {
            case 2700:
                newTemperature = 5000;
                break;
            case 3000:
                newTemperature = 4500;
                break;
            case 3500:
                newTemperature = 4000;
                break;
            case 4000:
                newTemperature = 3500;
                break;
            case 4500:
                newTemperature = 3000;
                break;
            case 5000:
                newTemperature = 2700;
                break;
            default:
                break;
        }
    }
    
    return newTemperature;
}

@end
