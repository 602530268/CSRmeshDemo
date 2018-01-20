//
//  UDManager.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/21.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "UDManager.h"

/*
 创建一个名为kLightInfo的dictionary,里面存放所有device的info
 每个device的info都作为一个dictionary,里面存有对应信息
 格式为:
     kLightInfo:{
     device1:{}
     device2:{}
     ...
     }
 */

static NSString *kLIGHTINFO = @"kLIGHTINFO";    //大包
static NSString *kDeviceId = @"kDeviceId%@";    //每个device对应的小包名

static NSString *kDhmKey = @"kDhmKey";  //dhmKey值
static NSString *kLightPowerState = @"kLightPowerState";    //开关
static NSString *kLightCurrnetType = @"kLightCurrnetType";  //当前类型 (Tem/RGB)
static NSString *kTemperature = @"kTemperature";    //色温值
static NSString *kTemperatureIndex = @"kTemperatureIndex";  //色温按钮索引
static NSString *kTemperatureBrightness = @"kTemperatureBrightness";    //色温亮度
static NSString *kRgbIndex = @"kRgbIndex";  //RGB索引
static NSString *kRgbBrightness = @"kRgbBrightness";    //RGB亮度值
static NSString *kDeviceOriginName = @"kDeviceOriginName";  //设备原始名称
static NSString *kDeviceVersion = @"kDeviceVersion";   //设备版本
static NSString *kDeviceOnlineState = @"kDeviceOnlineState";  //设备在线状态
static NSString *kDeviceUUIDString = @"kDeviceUUIDString";   //设备连接时的UUID
static NSString *kDeviceCodingId = @"kDeviceCodingId"; //设备编码ID
static NSString *kPowerConsumption = @"kPowerConsumption";   //设备耗电量

@implementation UDManager

#pragma mark - Save
//保存dhmKey值，该key值为删除设备必须参数，但在重启程序后会被清空，所以需要手动保存
+ (void)saveDhmKeyWith:(NSNumber *)deviceId dhmKey:(NSData *)dhmKey {
    
    NSString *dhmKeyString = [BaseCommond converDataToHexString:dhmKey];
    [self saveUdWith:deviceId obj:dhmKeyString key:kDhmKey];
    
    if (!dhmKeyString) {
        NSLog(@"%@设备的dhmKey值不存在!",deviceId);
    }
}

//保存当前开关状态
+ (void)savePowerStateWith:(NSNumber *)deviceId power:(BOOL)power {
    NSNumber *number = power ? @(1) : @(0);
    [self saveUdWith:deviceId obj:number key:kLightPowerState];
}

//保存当前状态 默认: CEDeviceTypeTemperature
+ (void)saveCurrentTypeWith:(NSNumber *)deviceId type:(DeviceType)type {
    [self saveUdWith:deviceId obj:@(type) key:kLightCurrnetType];
}

//保存当前色温值 0-6000
+ (void)saveTemperatureWith:(NSNumber *)deviceId temperature:(NSInteger)temperature {
    [self saveUdWith:deviceId obj:@(temperature) key:kTemperature];
}

//保存色温按钮索引
+ (void)saveTemperatureIndexWith:(NSNumber *)deviceId index:(NSInteger)index {
    [self saveUdWith:deviceId obj:@(index) key:kTemperatureIndex];
}

//保存当前色温亮度值 0-255
+ (void)saveTemperatureBrightnessWith:(NSNumber *)deviceId brightness:(NSInteger)brightness {
    [self saveUdWith:deviceId obj:@(brightness) key:kTemperatureBrightness];
}

//保存当前RGB索引，index: 0-14
+ (void)saveRGBWith:(NSNumber *)deviceId index:(NSInteger)index {
    [self saveUdWith:deviceId obj:@(index) key:kRgbIndex];
}

//保存当前RGB亮度 0-1
+ (void)saveRGBBrigrtnessWith:(NSNumber *)deviceId brightness:(CGFloat)brightness {
    [self saveUdWith:deviceId obj:@(brightness) key:kRgbBrightness];
}

//保存设备原始名称
+ (void)saveDeviceOriginNameWith:(NSNumber *)deviceId originName:(NSString *)originName {
    [self saveUdWith:deviceId obj:originName key:kDeviceOriginName];
}

//保存设备版本号
+ (void)saveDeviceVersionWith:(NSNumber *)deviceId version:(NSString *)version {
    [self saveUdWith:deviceId obj:version key:kDeviceVersion];
}

//保存设备在线状态
+ (void)saveDeviceOnlineState:(NSNumber *)deviceId online:(BOOL)online {
    [self saveUdWith:deviceId obj:@(online) key:kDeviceOnlineState];
}

//保存设备连接时的UUID
+ (void)saveDeviceUUIDStringWith:(NSNumber *)deviceId uuid:(NSString *)uuid {
    [self saveUdWith:deviceId obj:uuid key:kDeviceUUIDString];

    NSLog(@"saveDeviceUUIDStringWith:%@,%@",deviceId,uuid);
}

//保存设备编码ID
+ (void)saveDeviceCodingIdWith:(NSNumber *)deviceId codingId:(NSString *)codingId {
    [self saveUdWith:deviceId obj:codingId key:kDeviceCodingId];
}

//保存设备获取到的耗电量
+ (void)savePowerConsumptionWith:(NSNumber *)deviceId powerConsumption:(CGFloat)powerConsumption {
    [self saveUdWith:deviceId obj:@(powerConsumption) key:kPowerConsumption];
}

#pragma mark - Get
+ (NSData *)getDhmKeyWith:(NSNumber *)deviceId {
    NSString *obj = [self getUDWith:deviceId key:kDhmKey];
    return [BaseCommond converHexStrToData:obj];
}

+ (BOOL)getPowerStateWith:(NSNumber *)deviceId {
    
    NSNumber *obj = [self getUDWith:deviceId key:kLightPowerState];
    if (!obj) {
        return YES; //默认为开灯状态
    }
    return [obj integerValue];
}

+ (DeviceType)getDeviceTypeWith:(NSNumber *)deviceId {
    NSNumber *obj = [self getUDWith:deviceId key:kLightCurrnetType];
    if (!obj) {
        return DeviceTypeTemperature;
    }
    return [obj integerValue];
}

+ (NSInteger)getTemperatureWith:(NSNumber *)deviceId {
    
    NSNumber *obj = [self getUDWith:deviceId key:kTemperature];
    if (!obj) {
        return 2700;
    }
    
    return [obj integerValue];
}

+ (NSInteger)getTemperatureIndexWith:(NSNumber *)deviceId {
    
    NSNumber *obj = [self getUDWith:deviceId key:kTemperatureIndex];
    if (!obj) {
        return 0;
    }
    
    return [obj integerValue];
}

+ (NSInteger)getTemperatureBrightnessWith:(NSNumber *)deviceId {
     
    NSNumber *obj = [self getUDWith:deviceId key:kTemperatureBrightness];
    if (!obj) {
        return 255;
    }
    
    return [obj integerValue];
}

+ (NSInteger)getRGBIndexWith:(NSNumber *)deviceId {
    
    NSNumber *obj = [self getUDWith:deviceId key:kRgbIndex];
    if (!obj) {
        return -1;
    }
    
    return [obj integerValue];
}

+ (CGFloat)getRGBBrightnessWith:(NSNumber *)deviceId {
    
    NSNumber *obj = [self getUDWith:deviceId key:kRgbBrightness];
    if (!obj) {
        return 1.0;
    }
    
    return [obj floatValue];
}

+ (NSString *)getDeviceOriginName:(NSNumber *)deviceId {
    NSString *obj = [self getUDWith:deviceId key:kDeviceOriginName];
    if (!obj || ![obj isKindOfClass:[NSString class]]) {
        return @"not name";
    }
    return obj;
}

+ (NSString *)getDeviceVersion:(NSNumber *)deviceId {
    NSString *obj = [self getUDWith:deviceId key:kDeviceVersion];
    if (!obj || ![obj isKindOfClass:[NSString class]]) {
        return nil;
    }
    return obj;
}

+ (BOOL)getDeviceOnlingState:(NSNumber *)deviceId {
    NSNumber *obj = [self getUDWith:deviceId key:kDeviceOnlineState];
    if (!obj) {
        return YES; //默认在线
    }
    return [obj boolValue];
}

+ (NSString *)getDeviceUUIDString:(NSNumber *)deviceId {
    NSString *obj = [self getUDWith:deviceId key:kDeviceUUIDString];
    
    NSLog(@"getDeviceUUIDString:%@,%@",deviceId,obj);
    
    return obj;
}

+ (NSString *)getDeviceCodingId:(NSNumber *)deviceId {
    NSString *obj = [self getUDWith:deviceId key:kDeviceCodingId];
    
    return obj;
}

+ (CGFloat)getPowerConsumption:(NSNumber *)deviceId {
    NSNumber *obj = [self getUDWith:deviceId key:kPowerConsumption];
    
    if (!obj) {
        return -1;
    }
    
    return [obj floatValue];
}

#pragma mark - Remove
//删除该device的所有信息
+ (void)removeInfoWith:(NSNumber *)deviceId {
    
    NSAssert(deviceId, @"deviceId != nil");
    
    if (!deviceId) {
        deviceId = @(0);
    }
    
    NSMutableDictionary *allLights = [self getAllDevicesInfo].mutableCopy;
    NSString *deviceKey = [NSString stringWithFormat:kDeviceId,deviceId];
    if ([allLights.allKeys containsObject:deviceKey]) {
        [allLights removeObjectForKey:deviceKey];
        [self saveAllDevicesInfo:allLights];
    }
}

#pragma mark - APIs (private)
//保存allLights的存放地址
+ (void)saveAllDevicesInfo:(NSMutableDictionary *)devicesInfo {
    [[NSUserDefaults standardUserDefaults] setObject:devicesInfo forKey:kLIGHTINFO];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

//获取allLights的存放地址
+ (NSDictionary *)getAllDevicesInfo {
    if (![[NSUserDefaults standardUserDefaults] objectForKey:kLIGHTINFO]) {
        [[NSUserDefaults standardUserDefaults] setObject:@{} forKey:kLIGHTINFO];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
    return [[NSUserDefaults standardUserDefaults] objectForKey:kLIGHTINFO];
}

//general
+ (void)saveUdWith:(NSNumber *)deviceId obj:(NSObject *)obj key:(NSString *)key {
    
    NSAssert(obj, @"obj != nil");
    
    if (!deviceId) {
        deviceId = @(0);
    }
    
    NSMutableDictionary *allLights = [self getAllDevicesInfo].mutableCopy;
    NSString *deviceKey = [NSString stringWithFormat:kDeviceId,deviceId];
    NSMutableDictionary *deviceinfo = [[allLights objectForKey:deviceKey] mutableCopy];
    if (!deviceinfo) {
        deviceinfo = @{}.mutableCopy;
    }
    
    [deviceinfo setObject:obj forKey:key];
    [allLights setObject:deviceinfo forKey:deviceKey];
    
    [self saveAllDevicesInfo:allLights];
}

//general
+ (id)getUDWith:(NSNumber *)deviceId key:(NSString *)key {
    
    NSAssert(key, @"key != nil");
    
    if (!deviceId) {
        deviceId = @(0);
    }
    
    NSString *deviceKey = [NSString stringWithFormat:kDeviceId,deviceId];
    NSMutableDictionary *deviceInfo = [[self getAllDevicesInfo] objectForKey:deviceKey];
    
    return [deviceInfo objectForKey:key];
}


@end
