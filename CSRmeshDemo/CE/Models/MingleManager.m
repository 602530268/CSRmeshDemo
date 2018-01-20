//
//  MingleManager.m
//  CSRmeshDemo
//
//  Created by chencheng on 2017/11/24.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "MingleManager.h"

@implementation MingleManager

//所有灯型都是 Ecosmart 厂商的
+ (BOOL)allLightsIsEcosmart {
    
    /*
     @"54683141": @"Ecosmart A19",
     @"54684141": @"Ecosmart BR30",
     @"54685141": @"Ecosmart 5/6\" Downlight",
     */
    
    NSArray *allDevices = [self allDevices];
    for (CSRDeviceEntity *deviceEntity in allDevices) {
        NSString *codingId = [UDManager getDeviceCodingId:deviceEntity.deviceId];
        if (![codingId isEqualToString:@"54683141"] &&
            ![codingId isEqualToString:@"54683141"] &&
            ![codingId isEqualToString:@"54683141"]) {
            return NO;
        }
    }
    
    return YES;
}

//是否是RGB类型的灯
+ (BOOL)isRGBLight:(NSNumber *)deviceId {
    
    NSString *codingId = [UDManager getDeviceCodingId:deviceId];
    if ([codingId isEqualToString:@"54685143"] ||
        [codingId isEqualToString:@"53185142"]) {
        return YES;
    }
    
    return NO;
}

//该灯组是否拥有RGB灯
+ (BOOL)containRGBLightWithArea:(CSRAreaEntity *)areaEntity {
    
    NSMutableArray *devices = nil;
    
    if (areaEntity == nil) {
        devices = [CSRAppStateManager sharedInstance].selectedPlace.devices.allObjects.mutableCopy;
    }else {
        devices = areaEntity.devices.allObjects.mutableCopy;
    }
    
    for (CSRDeviceEntity *deviceEntity in devices) {
        NSString *codingId = [UDManager getDeviceCodingId:deviceEntity.deviceId];
        if ([codingId isEqualToString:@"54685143"] ||
            [codingId isEqualToString:@"53185142"]) {
            return YES;
        }
    }
    
    return NO;
}

//属于老三款灯
+ (BOOL)isOldLights:(NSNumber *)deviceId {
    
    NSString *codingId = [UDManager getDeviceCodingId:deviceId];
    if ([codingId isEqualToString:@"53185141"] ||
        [codingId isEqualToString:@"53186141"] ||
        [codingId isEqualToString:@"54682141"] ||
        
        [codingId isEqualToString:@"53184444"] ||
        [codingId isEqualToString:@"53185555"]) {
        return YES;
    }
    
    return NO;
}

//所有灯型都是

/*
 @"53185141": @"4” CE Downlight",
 @"53186141": @"5/6” CE Downlight",
 @"54682141": @"14” CE Flushmount",
 
 @"54683141": @"Ecosmart A19",
 @"54684141": @"Ecosmart BR30",
 @"54685141": @"Ecosmart 5/6\" Downlight",
 
 @"54685143": @"5/6\" Color Changing Downlight",
 @"53185142": @"4\"Color Changing Downlight",
 */
/*
 UI显示方案:
 灯组内存在一盏灯型是Ecosmart系列，导航栏的商标显示为 Ecosmart，否则显示默认
 灯组内灯型存在一盏RGB灯，灯组页面显示RGB页面箭头，否则不显示
 
 指令类:
 不同灯型之间发现查询功率的指令不同，需要整理一下，目前猜测RGB灯的查询指令是16号，中间3款灯型的14号，前3个没有查询功能，麻烦嵌入式确认一下
 */

//加灯页面，点击灯，灯闪烁一次是mesh2.1的新功能，经过测试，20s后才能继续闪烁，命令的发送是直达框架底层，没有办法修改，或者保持原来的需求，取消闪烁功能

# pragma mark - API(private) -
+ (NSArray *)allDevices {
    return [[[CSRAppStateManager sharedInstance].selectedPlace.devices allObjects] mutableCopy];
}

@end
