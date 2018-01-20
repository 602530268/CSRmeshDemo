//
//  DeviceVersionHandle.h
//  CSRmeshDemo
//
//  Created by double on 2017/10/25.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

/*
 设备版本管理
 */

#import <Foundation/Foundation.h>

@interface DeviceVersionHandle : NSObject

//获取设备版本
+ (void)getDeviceVersionWith:(NSNumber *)deviceId
                      finish:(void(^)(NSString *version))finish;

@end
