//
//  DeviceDataHandle.h
//  CSRmeshDemo
//
//  Created by double on 2017/7/21.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 设备数据处理
 */

@interface DeviceDataHandle : NSObject

//根据设备的编码获取名字，没有编码的在硬件上默认为Light
+ (NSString *)getDeviceNameWith:(NSString *)shortName;

//获取设备当前应该显示的图片
+ (UIImage *)getImageWithDeviceId:(NSNumber *)deviceId;

+ (UIImage *)getImgWith:(NSNumber *)deviceId Type:(DeviceType)type;

//更新子设备的UD数据
+ (void)updateSubDevicesData:(NSNumber *)areaId;

//16/14号命令查询耗电量及功率电流数据的处理
+ (NSDictionary *)handlePowerConsumptionAndOtherWith:(NSNumber *)deviceId data:(NSData *)data type:(DeviceType)type;

//制造功率等假数据
+ (NSDictionary *)fakeDataForPowerConsumptionWith:(NSNumber *)deviceId type:(DeviceType)type size:(NSInteger)size;

@end
