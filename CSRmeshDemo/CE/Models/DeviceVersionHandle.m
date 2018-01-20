//
//  DeviceVersionHandle.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/25.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "DeviceVersionHandle.h"

@implementation DeviceVersionHandle

//获取设备版本
+ (void)getDeviceVersionWith:(NSNumber *)deviceId
                     finish:(void(^)(NSString *version))finish {
    
    NSString *deviceVersionOfUD = [UDManager getDeviceVersion:deviceId];

    if (deviceVersionOfUD) {
        finish(deviceVersionOfUD);
        return;
    }
    
    if ([CSRMeshUserManager sharedInstance].bearerType == CSRBearerType_Bluetooth) {
        
        [[FirmwareModelApi sharedInstance] getVersionInfo:deviceId
                                                  success:^(NSNumber *deviceId, NSNumber *versionMajor, NSNumber *versionMinor) {
                                                      
                                                      NSString *deviceVersion = [NSString stringWithFormat:@"%@.%@", versionMajor, versionMinor];
                                                      
                                                      [UDManager saveDeviceVersionWith:deviceId version:deviceVersion];
                                                      finish(deviceVersion);
                                                      
                                                  } failure:^(NSError *error) {
                                                      NSLog(@"error :%@", error);
                                                      finish(@"N/A");
                                                  }];
    }
}

@end
