//
//  DeleteDeviceManager.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "DeleteDeviceManager.h"
#import "AreaDetailManager.h"
#import "BridgeStateManager.h"

@implementation DeleteDeviceManager
{
    //单灯
    CSRDeviceEntity *_deviceEntity;
    CSRmeshDevice *_device;
    
    void (^_success)();
    void (^_fail)();
    
    //多灯
    NSMutableArray <CSRDeviceEntity *> *_lights;
    CSRAreaEntity *_areaEntity;
    void (^_finish)();
}

#pragma mark - APIs (public)
+ (DeleteDeviceManager *)shareInstance {
    static DeleteDeviceManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[DeleteDeviceManager alloc] init];
        [manager registerNotify];
    });
    
    return manager;
}

//删除单灯
- (void)deleteDevice:(CSRDeviceEntity *)deviceEntity
             success:(void (^)())success
                fail:(void (^)())fail {
    
    _success = success;
    _fail = fail;
    
    if (!deviceEntity) {
        NSLog(@"设备不存在，无法删除");
        if (_fail) {
            _fail();
        }
        return;
    }
    
    //开始删除
    CSRmeshDevice *device = [[CSRDevicesManager sharedInstance] getDeviceFromDeviceId:deviceEntity.deviceId];
    
    NSLog(@"删除的设备ID为: %@,%@",deviceEntity.deviceId,device.deviceId);
    
    CSRPlaceEntity *placeEntity = [CSRAppStateManager sharedInstance].selectedPlace;
    
    UIViewController *vc = [BaseCommond getCurrentVC];
    if (![CSRUtilities isStringEmpty:placeEntity.passPhrase]) {
        
        if (device.deviceId) {
            BOOL online = [UDManager getDeviceOnlingState:device.deviceId];
            if (online) {
                [[CSRDevicesManager sharedInstance] initiateRemoveDevice:device];
            }else { //离线状态的话，只能强制删除
                [self showForceAlert:deviceEntity];
            }
        }else {
            NSLog(@"没有发现该设备");
            if (_fail) {
                _fail();
            }
            return;
        }
        
        
    } else {
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Alert!!"
                                                                                 message:@"You should be place owner to associate a device"
                                                                          preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK"
                                                           style:UIAlertActionStyleDefault
                                                         handler:^(UIAlertAction *action) {
                                                             
                                                         }];
        
        [alertController addAction:okAction];
        [vc presentViewController:alertController animated:YES completion:nil];
        
    }
}

//删除多盏灯
- (void)deleteMoreLights:(NSMutableArray <CSRDeviceEntity *>*)lights
              areaEntity:(CSRAreaEntity *)areaEntity
                  finish:(void(^)())finish {
    
    self.deleteArea = YES;
    
    _lights = lights;
    _areaEntity = areaEntity;
    _finish = finish;
    
    NSMutableArray *devices = lights.mutableCopy;
    for (int i = 0; i < devices.count; i++) {

        CSRDeviceEntity *deviceEntity = devices[i];
        [self deleteDevice:deviceEntity success:nil fail:nil];
        
        [_lights removeObject:deviceEntity];
    }
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        if (areaEntity) {
            [[AreaDetailManager shareInstance] deleteAreaWith:areaEntity finish:^{
                [self checkBridgeConnectAndRemainingLights];
            }];
        }else {
            [self checkBridgeConnectAndRemainingLights];
        }
    });
}

////延迟一小会检查状态
//- (void)checkStateByDelayTime {
//    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//        [self checkBridgeConnectAndRemainingLights];
//    });
//}

//检测当前桥连接bool和当前剩余灯数量count
- (void)checkBridgeConnectAndRemainingLights {
    
    //剩余灯数量
    _lights = [CSRAppStateManager sharedInstance].selectedPlace.devices.allObjects.mutableCopy;
    NSInteger count = _lights.count;
    
    //桥连接状态
    if ([BridgeStateManager shareInstance].bridgeConnnected == NO) {
        
        if (count == 0) {   //桥断开且设备为0时回调完成
            [self deleteMoreLightFinish];
            return;
        }
        
        CCLog(@"当前桥连接断开，说明桥被删除，等待3s后重新检测");
        [self performSelector:@selector(checkBridgeConnectAndRemainingLights) withObject:nil afterDelay:3.0f];
        return;
    }
    
    if (count == 0) {
        [self deleteMoreLightFinish];
        return;
    }else {
        CCLog(@"剩余灯数量不为0，继续删除操作,剩余等数量为: %ld",(long)count);
        [self deleteMoreLights:_lights areaEntity:_areaEntity finish:_finish];
    }
}

//删除多盏灯完成
- (void)deleteMoreLightFinish {
    if (_finish) {
        _finish();
    }
    
    _lights = nil;
    _areaEntity = nil;
    _finish = nil;
    _deleteArea = NO;
    
    [self checkToResetAllLightData];

    CCLog(@"剩余灯数量为0，删除完成");
}

#pragma mark - APIs(private)
- (void)registerNotify {
    
//    return;
    //当设备离线时，需要10s才能回调强制删除的通知，太久了，直接判断手动存储的设备离线状态就行
    //移除设备成功后回调，删除存储信息
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(deleteStatus:)
                                                 name:kCSRDeviceManagerDeviceFoundForReset
                                               object:nil];
}

-(void)deleteStatus:(NSNotification *)notification {
    
    NSNumber *num = notification.userInfo[@"boolFlag"];
    NSNumber *deviceId = notification.userInfo[@"deviceId"];
    
    if (!deviceId) {
        return;
    }
    
    NSMutableArray *devices = [[[CSRAppStateManager sharedInstance].selectedPlace.devices allObjects] mutableCopy];
    CSRDeviceEntity *deviceEntity = nil;
    for (CSRDeviceEntity *deviceE in devices) {
        if ([deviceE.deviceId isEqualToNumber:deviceId]) {
            deviceEntity = deviceE;
            break;
        }
    }
    
    if (!deviceEntity) return;
    
    if ([num boolValue] == NO) {
        [self showForceAlert:deviceEntity];
    } else {
        [self delectDataBase:deviceEntity];
    }
}

- (void)delectDataBase:(CSRDeviceEntity *)deviceEntity {
    
    [UDManager removeInfoWith:deviceEntity.deviceId];

    if(deviceEntity) {

        [[CSRAppStateManager sharedInstance].selectedPlace removeDevicesObject:deviceEntity];
        [[CSRDatabaseManager sharedInstance].managedObjectContext deleteObject:deviceEntity];
        [[CSRDatabaseManager sharedInstance] saveContext];
    }else {
        NSLog(@"没有device数据可删!");
    }
    NSNumber *deviceNumber = [[CSRDatabaseManager sharedInstance] getNextFreeIDOfType:@"CSRDeviceEntity"];
    [[CSRDevicesManager sharedInstance] setDeviceIdNumber:deviceNumber];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self finish];
    });
    
}

//强制删除
- (void)showForceAlert:(CSRDeviceEntity *)deviceEntity {
    
    if (_deleteArea == YES) {
        [self delectDataBase:deviceEntity];
        return;
    }
    
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Device"
                                                                             message:[NSString stringWithFormat:@"Device wasn't found. Do you want to delete %@ anyway?", _device.name]
                                                                      preferredStyle:UIAlertControllerStyleAlert];
    [alertController.view setTintColor:[CSRUtilities colorFromHex:kColorBlueCSR]];
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"No"
                                                           style:UIAlertActionStyleCancel
                                                         handler:^(UIAlertAction *action) {
                                                             if (_fail) {
                                                                 _fail();
                                                             }
                                                         }];
    
    UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"Yes"
                                                       style:UIAlertActionStyleDefault
                                                     handler:^(UIAlertAction *action) {
                                                         
                                                         [self delectDataBase:deviceEntity];

                                                         }];
    [alertController addAction:okAction];
    [alertController addAction:cancelAction];
    
    UIViewController *vc = [BaseCommond getCurrentVC];
    [vc presentViewController:alertController animated:YES completion:nil];
    
}

- (void)finish {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        //删除设备完成
        if (_success) {
            [self checkToResetAllLightData];
            
            _success();
            
            _success = nil;
            _fail = nil;
            _device = nil;
            _deviceEntity = nil;
        }
    });
}

//检查是否重置allLight的数据
- (void)checkToResetAllLightData {
    NSInteger deviceCount = [CSRAppStateManager sharedInstance].selectedPlace.devices.count;
    if (deviceCount == 0) {
        [UDManager removeInfoWith:@(0)];
    }
}

////safe机制,保证deleteArea会重置
//- (void)setDeleteArea:(BOOL)deleteArea {
//    _deleteArea = deleteArea;
//    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.1f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//        _deleteArea = NO;
//    });
//}

@end
