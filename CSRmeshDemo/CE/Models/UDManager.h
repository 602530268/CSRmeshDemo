//
//  UDManager.h
//  CSRmeshDemo
//
//  Created by double on 2017/7/21.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 灯有两种类型状态，
 默认为色温状态，此时可调节色温值和亮度值；
 另外一种为RGB状态，即彩灯状态，可调节RGB值和亮度值，注意这里的亮度值和色温状态的亮度值是不一样的
 */
typedef NS_ENUM(NSInteger,DeviceType) {
    DeviceTypeTemperature,  //色温类型
    DeviceTypeRGB,  //RGB类型
};

@interface UDManager : NSObject

#pragma mark - Save
//保存dhmKey值，该key值为删除设备必须参数，但在重启程序后会被清空，所以需要手动保存
+ (void)saveDhmKeyWith:(NSNumber *)deviceId dhmKey:(NSData *)dhmKey;

//保存当前开关状态
+ (void)savePowerStateWith:(NSNumber *)deviceId power:(BOOL)power;

//保存当前状态 默认: DeviceTypeTemperature
+ (void)saveCurrentTypeWith:(NSNumber *)deviceId type:(DeviceType)type;

//保存当前色温值 0-6000
+ (void)saveTemperatureWith:(NSNumber *)deviceId temperature:(NSInteger)temperature;

//保存色温按钮索引
+ (void)saveTemperatureIndexWith:(NSNumber *)deviceId index:(NSInteger)index;

//保存当前色温亮度值 0-255
+ (void)saveTemperatureBrightnessWith:(NSNumber *)deviceId brightness:(NSInteger)brightness;

//保存当前RGB索引，index: 0-14
+ (void)saveRGBWith:(NSNumber *)deviceId index:(NSInteger)index;

//保存当前RGB亮度 0-1
+ (void)saveRGBBrigrtnessWith:(NSNumber *)deviceId brightness:(CGFloat)brightness;

//保存设备原始名称
+ (void)saveDeviceOriginNameWith:(NSNumber *)deviceId originName:(NSString *)originName;

//保存设备版本号
+ (void)saveDeviceVersionWith:(NSNumber *)deviceId version:(NSString *)version;

//保存设备在线状态
+ (void)saveDeviceOnlineState:(NSNumber *)deviceId online:(BOOL)online;

//保存设备连接时的UUID
+ (void)saveDeviceUUIDStringWith:(NSNumber *)deviceId uuid:(NSString *)uuid;

//保存设备编码ID
+ (void)saveDeviceCodingIdWith:(NSNumber *)deviceId codingId:(NSString *)codingId;

//保存设备获取到的耗电量
+ (void)savePowerConsumptionWith:(NSNumber *)deviceId powerConsumption:(CGFloat)powerConsumption;

#pragma mark - Get
+ (NSData *)getDhmKeyWith:(NSNumber *)deviceId;

+ (BOOL)getPowerStateWith:(NSNumber *)deviceId;

+ (DeviceType)getDeviceTypeWith:(NSNumber *)deviceId;

+ (NSInteger)getTemperatureWith:(NSNumber *)deviceId;

+ (NSInteger)getTemperatureIndexWith:(NSNumber *)deviceId;

+ (NSInteger)getTemperatureBrightnessWith:(NSNumber *)deviceId;

+ (NSInteger)getRGBIndexWith:(NSNumber *)deviceId;

+ (CGFloat)getRGBBrightnessWith:(NSNumber *)deviceId;

+ (NSString *)getDeviceOriginName:(NSNumber *)deviceId;

+ (NSString *)getDeviceVersion:(NSNumber *)deviceId;

+ (BOOL)getDeviceOnlingState:(NSNumber *)deviceId;

+ (NSString *)getDeviceUUIDString:(NSNumber *)deviceId;

+ (NSString *)getDeviceCodingId:(NSNumber *)deviceId;

+ (CGFloat)getPowerConsumption:(NSNumber *)deviceId;

#pragma mark - Remove
//删除该device的所有信息
+ (void)removeInfoWith:(NSNumber *)deviceId;


@end
