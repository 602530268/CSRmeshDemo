//
//  DeviceDataHandle.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/21.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "DeviceDataHandle.h"
#import "MingleManager.h"

@implementation DeviceDataHandle

//根据设备的编码获取名字，没有编码的在硬件上默认为Light
+ (NSString *)getDeviceNameWith:(NSString *)shortName {
    
    NSDictionary *deviceTypes = @{
                                  @"53185141": @"4” CE Downlight",
                                  @"53186141": @"5/6” CE Downlight",
                                  @"54682141": @"14” CE Flushmount",
                                  @"54683141": @"Ecosmart A19",
                                  @"54684141": @"Ecosmart BR30",
                                  @"54685141": @"Ecosmart 5/6\" Downlight",
                                  @"54685143": @"5/6\" Color Changing Downlight",
                                  @"53185142": @"4\" Color Changing Downlight",

                                  @"53184444": @"4” CE Downlight",
                                  @"53185555": @"5/6” CE Downlight",
                                  };
    
    NSString *deviceName = deviceTypes[shortName];
    if (deviceName) {
        return deviceName;
    }
    
    return shortName;
}

//获取显示img
+ (UIImage *)getImageWithDeviceId:(NSNumber *)deviceId {
    
    DeviceType type = [UDManager getDeviceTypeWith:deviceId];
    return [self getImgWith:deviceId Type:type];
}

+ (UIImage *)getImgWith:(NSNumber *)deviceId Type:(DeviceType)type {
    
    if ([UDManager getPowerStateWith:deviceId] == NO) {
        return [[UIImage imageNamed:@"circle_empty"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    }
    
    if (type == DeviceTypeTemperature) {
        NSInteger temperature = [UDManager getTemperatureWith:deviceId];
        switch (temperature) {
            case 2700:
                return [UIImage imageNamed:@"temperatureState_0"];
                break;
            case 3000:
                return [UIImage imageNamed:@"temperatureState_1"];
                break;
            case 3500:
                return [UIImage imageNamed:@"temperatureState_2"];
                break;
            case 4000:
                return [UIImage imageNamed:@"temperatureState_3"];
                break;
            case 4500:
                return [UIImage imageNamed:@"temperatureState_4"];
                break;
            case 5000:
                return [UIImage imageNamed:@"temperatureState_5"];
                break;
                
            default:
                break;
        }
    }else if (type == DeviceTypeRGB) {
        NSInteger index = [UDManager getRGBIndexWith:deviceId];
        
        if (index == -1) {
            return [UIImage imageNamed:@"colorState_white"];
        }else {
            NSString *imgString = [NSString stringWithFormat:@"colorState%ld",index];
            return [UIImage imageNamed:imgString];
        }
    }
    
    return [UIImage imageNamed:@"temperatureState_0"];
}

//更新子设备的UD数据
+ (void)updateSubDevicesData:(NSNumber *)areaId {
    
    BOOL isAllLight = NO;
    
    if (!areaId) {
        areaId = @(0);
    }
    
    if ([areaId isEqualToNumber:@(0)]) {
        isAllLight = YES;
    }

    if (isAllLight) {
        NSArray *allDevices = [[CSRDevicesManager sharedInstance] getMeshDevicesArray];
        for (CSRmeshDevice *device in allDevices) {
            [DeviceDataHandle saveDataWith:device.deviceId areaId:areaId];
        }
    }else {
        CSRAreaEntity *areaEntity = nil;
        
        NSMutableArray *areas = [[[CSRAppStateManager sharedInstance].selectedPlace.areas allObjects] mutableCopy];
        for (CSRAreaEntity *area in areas) {
            if ([area.areaID isEqualToNumber:areaId]) {
                areaEntity = area;
                break;
            }
        }
        
        if (!areaEntity) return;
        
        NSSet *devicesSet = areaEntity.devices;
        for (CSRDeviceEntity *deviceEntity in devicesSet) {
            [DeviceDataHandle saveDataWith:deviceEntity.deviceId areaId:areaId];
        }
    }
}

//16/14号命令查询耗电量及功率电流数据的处理
+ (NSDictionary *)handlePowerConsumptionAndOtherWith:(NSNumber *)deviceId data:(NSData *)data type:(DeviceType)type  {
    NSLog(@"获取耗电量数据: %@",data);
    
    NSString *dataString = [CSRUtilities hexStringFromData:data];
    if (dataString.length < 10) {
        NSLog(@"data格式不正确，无法解析耗电量数据");
        return nil;
    }
    
    NSString *powerConsumptionString = [dataString substringWithRange:NSMakeRange(0, 8)];  //功率
    NSString *sizeString = [dataString substringWithRange:NSMakeRange(8, 2)];   //尺寸
    
    powerConsumptionString = [NSString stringWithFormat:@"%lu",strtoul([powerConsumptionString UTF8String], 0, 16)];
    sizeString = [NSString stringWithFormat:@"%lu",strtoul([sizeString UTF8String], 0, 16)];
    
    CGFloat powerConsumption = [powerConsumptionString floatValue];
    NSInteger size = [sizeString integerValue];
    
    NSInteger base = 11;    //功率,11 是测试人员测试数据的标准，根据不同尺寸，功率应该进行相应转换
    switch (size) {
        case 14:
            base = 25;
            break;
        case 56:
            base = 11;
            break;
        case 4:
            base = 10;
            break;
            
        default:
            break;
    }
    
    powerConsumption = powerConsumption * base/255.0/1000.0/60.0;   //公式转换成 千瓦时 kwh
    NSLog(@"耗电量为: %fkwh",powerConsumption);
    
    //制造电压电流等假数据
    NSMutableDictionary *fakeDataInfo = [self fakeDataForPowerConsumptionWith:deviceId type:type size:size].mutableCopy;
    [fakeDataInfo setValue:[NSString stringWithFormat:@"%0.3fkwh",powerConsumption] forKey:@"powerConsumption"];
    
    [UDManager savePowerConsumptionWith:deviceId powerConsumption:powerConsumption];
    
    return fakeDataInfo;
}

//制造功率等假数据
+ (NSDictionary *)fakeDataForPowerConsumptionWith:(NSNumber *)deviceId type:(DeviceType)type size:(NSInteger)size {
    
    CGFloat base = 11;    //功率,11 是测试人员测试数据的标准，根据不同尺寸，功率应该进行相应转换
    
    //现在按照14彩灯做基准，就是base=22,
    switch (size) {
        case 14:
            base = 22;
            break;
        case 56:
            base = 11;
            break;
        case 4:
            base = 10;
            break;
            
        default:
            break;
    }
    
    //后来添加的两款cw灯，单独兼容
    NSString *coding = [UDManager getDeviceCodingId:deviceId];
    if ([coding isEqualToString:@"53184444"] ||
        [coding isEqualToString:@"53185555"]) {
        base = 22;
    }
    
    NSDictionary *baseData = [self baseData];   //基于11瓦特的灯型的0-100亮度的测试数据
    
    NSInteger brightness = 100; //亮度值，0-100
    if (type == DeviceTypeTemperature) {
        brightness = ([UDManager getTemperatureBrightnessWith:deviceId] / 255.0) * 100;
    }else {
        brightness = [UDManager getRGBBrightnessWith:deviceId] * 100;
    }
    
    //如果为关灯状态，亮度取0
    BOOL power = [UDManager getPowerStateWith:deviceId];
    if (power == NO) {
        brightness = 0;
    }
    
    NSString *stringByTestData = baseData[[NSString stringWithFormat:@"%ld",(long)brightness]];
    NSArray *handleArr = [stringByTestData componentsSeparatedByString:@","];
    if (handleArr.count != 2) {
        NSLog(@"data格式不正确，无法解析数据");
        return nil;
    }
    
    CGFloat ampereByTestData = [handleArr[1] floatValue];;
    
    CGFloat volt = 118.0 + (arc4random() % 21) / 10.0;  //伏特,118-122之间获取随机数，浮动单位0.1
    CGFloat ampere = ampereByTestData - 0.05 + (arc4random() % 6)/100.0; //安培,在测试数据中获取，并且浮动+-0.05，浮动单位0.01
    
    CGFloat watt = volt * ampere / 1000;
    watt *= (base / 11);
    ampere *= (base / 11);
    
    //兼容和需求
//    if ([MingleManager isRGBLight:deviceId]) {
    
        //最多显示10w，RGB最多显示5w
        if (type == DeviceTypeTemperature) {
            watt /= 2.0f;
            ampere /= 2.0f;
        }else {
            watt /= 4.0f;
            ampere /= 4.0f;
        }
//    }
    
    CCLog(@"watt: %f,volt: %f, ampere: %f",watt,volt,ampere);
    
    NSMutableDictionary *info = [NSMutableDictionary dictionaryWithCapacity:0];
    [info setValue:[NSString stringWithFormat:@"%0.3fW",watt] forKey:@"watt"];
    [info setValue:[NSString stringWithFormat:@"%0.1fV",volt] forKey:@"volt"];
    [info setValue:[NSString stringWithFormat:@"%.0fmA",ampere] forKey:@"ampere"];
    
    CGFloat powerConsumption = [UDManager getPowerConsumption:deviceId];
    if (powerConsumption > 0) {
        [info setValue:[NSString stringWithFormat:@"%0.3fkwh",powerConsumption] forKey:@"powerConsumption"];
    }
    return info;
}

#pragma mark - APIs(private)
+ (void)saveDataWith:(NSNumber *)deviceId areaId:(NSNumber *)areaId {
    
    BOOL power = [UDManager getPowerStateWith:areaId];
    DeviceType type = [UDManager getDeviceTypeWith:areaId];
    
    [UDManager savePowerStateWith:deviceId power:power];
    [UDManager saveCurrentTypeWith:deviceId type:type];
    
    if (type == DeviceTypeTemperature) {
        
        NSInteger temperature = [UDManager getTemperatureWith:areaId];
        NSInteger brightness = [UDManager getTemperatureBrightnessWith:areaId];
        NSInteger index = [UDManager getTemperatureIndexWith:areaId];
        
        [UDManager saveTemperatureWith:deviceId temperature:temperature];
        [UDManager saveTemperatureBrightnessWith:deviceId brightness:brightness];
        [UDManager saveTemperatureIndexWith:deviceId index:index];

    }else {
        NSInteger index = [UDManager getRGBIndexWith:areaId];
        CGFloat brightness = [UDManager getRGBBrightnessWith:areaId];
        
        [UDManager saveRGBWith:deviceId index:index];
        [UDManager saveRGBBrigrtnessWith:deviceId brightness:brightness];
    }
    
}

//基于11功率的灯型进行测试的测试数据，假的
+ (NSDictionary *)baseData {
    return @{@"0":@"0.3576,2.98",
             @"1":@"0.3576,2.98",
             @"2":@"0.3576,2.98",
             @"3":@"0.3576,2.98",@"4":@"0.3576,2.98",@"5":@"1.199,9.992",@"6":@"1.282,10.686",@"7":@"1.392,11.596",@"8":@"1.446,12.052",@"9":@"1.532,12.768",@"10":@"1.578,13.146",@"11":@"1.695,14.127",@"12":@"1.764,14.703",@"13":@"1.877,15.639",@"14":@"1.962,16.352",@"15":@"2.06,17.167",@"16":@"2.086,17.381",@"17":@"2.231,18.592",@"18":@"2.328,19.402",@"19":@"2.363,19.692",@"20":@"2.467,20.557",@"21":@"2.578,21.483",@"22":@"2.69,22.421",@"23":@"2.768,23.067",@"24":@"2.86,23.835",@"25":@"2.879,23.992",@"26":@"2.931,24.423",@"27":@"2.956,24.633",@"28":@"3.136,26.13",@"29":@"3.184,25.532",@"30":@"3.279,27.327",@"31":@"3.328,27.733",@"32":@"3.429,28.575",@"33":@"3.438,28.653",@"34":@"3.478,28.983",@"35":@"3.58,29.833",@"36":@"3.682,30.683",@"37":@"3.787,31.562",@"38":@"3.843,32.023",@"39":@"3.996,33.298",@"40":@"4.155,34.626",@"41":@"4.209,35.077",@"42":@"4.262,35.517",@"43":@"4.366,36.387",@"44":@"4.42,36.83",@"45":@"4.533,37.774",@"46":@"4.64,38.671",@"47":@"4.772,39.763",@"48":@"4.902,40.854",@"49":@"5.109,42.575",@"50":@"5.178,43.15",@"51":@"5.313,44.273",@"52":@"5.379,44.822",@"53":@"5.45,45.419",@"54":@"5.658,47.15",@"55":@"5.73,47.75",@"56":@"5.869,48.905",@"57":@"5.937,49.427",@"58":@"6.073,50.608",@"59":@"6.202,51.685",@"60":@"6.4,53.337",@"61":@"6.464,53.867",@"62":@"6.59,54.915",@"63":@"6.653,55.442",@"64":@"6.779,56.488",@"65":@"7.031,58.59",@"66":@"7.091,59.092",@"67":@"7.277,60.641",@"68":@"7.4,61.667",@"69":@"7.583,63.19",@"70":@"7.645,63.708",@"71":@"7.772,64.762",@"72":@"7.831,65.258",@"73":@"7.952,66.267",@"74":@"8.076,67.3",@"75":@"8.133,67.778",@"76":@"8.257,68.808",@"77":@"8.384,69.867",@"78":@"8.571,71.425",@"79":@"8.631,71.925",@"80":@"8.754,72.95",@"81":@"8.878,73.983",@"82":@"9.01,75.083",@"83":@"9.071,75.589",@"84":@"9.133,76.108",@"85":@"9.257,77.142",@"86":@"9.32,77.667",@"87":@"9.444,78.7",@"88":@"9.641,80.341",@"89":@"9.767,81.392",@"90":@"9.832,81.933",@"91":@"9.961,83.01",@"92":@"10.09,84.083",@"93":@"10.22,85.167",@"94":@"10.449,87.075",@"95":@"10.446,87.05",@"96":@"10.64,88.667",@"97":@"10.636,88.633",
             @"98":@"10.828,90.233",
             @"99":@"10.895,90.792",
             @"100":@"10.895,90.792",};
}

@end
