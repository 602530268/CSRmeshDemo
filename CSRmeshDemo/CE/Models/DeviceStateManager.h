//
//  DeviceStateManager.h
//  CSRmeshDemo
//
//  Created by double on 2017/10/25.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

/*
 设备状态管理器
 */

#import <Foundation/Foundation.h>

@interface DeviceStateManager : NSObject

+ (DeviceStateManager *)shareInstance;

/*
 检查设备当前连接状态
 该过程能获取到设备的开关、色温值，所以顺带进行存储
 block回调后自行判断状态
 */
- (void)checkDeviceStateWith:(NSMutableArray *)deviceIds
                       block:(void(^)(NSNumber *devicId))block;

/*
 检查灯组状态
 获取灯组内第一盏灯的状态更新即可
 */
- (void)checkAreaStateWith:(NSMutableArray *)areas
                     block:(void(^)(NSNumber *areaId))block;

@end
