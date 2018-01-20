//
//  CommandManager.m
//  CSRmeshDemo
//
//  Created by double on 2017/8/28.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CommandManager.h"
#import "MingleManager.h"
#import "AlertControllerManager.h"

#define SendCommandIntervalTime 0.025

@interface CommandManager ()

@property(nonatomic,strong) CSRmeshDevice *selectDevice;
@property(nonatomic,strong) NSNumber *deviceId;

@end

@implementation CommandManager
{
    NSNumber *_deviceID;
    CGFloat _rgbBrightness;
}

+ (CommandManager *)shareInstance {
    static CommandManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[CommandManager alloc] init];
        [manager initData];
        manager.canSend = YES;
//        [manager timeLoop];
    });
    return manager;
}

- (void)initData {
    _rgbInfo = @{@"R":@(1.0f),@"G":@(1.0f),@"B":@(1.0f)};
    _rgbBrightness = 1.0;
    
}

- (void)sendPower:(BOOL)power {
    
    if (![self checkCanSendCommand]) return;
    
//    CSRmeshDevice *device = self.selectDevice;
//
//    if (device == nil) {
//        //all lights 关灯方式，可统一，不过为了兼容性，还是尽量能sendData就sendData
//        [[PowerModelApi sharedInstance] setPowerState:@(0) state:@(power) success:nil failure:nil];
//    }else {
//        [device setPower:power];
//    }
    [[PowerModelApi sharedInstance] setPowerState:self.deviceId state:@(power) success:nil failure:nil];

    
    //有些灯型不兼容，会出现关闭不完全现象，弃用
//    NSData *data = [CSRUtilities scanDataString:[NSString stringWithFormat:@"06%02x%02x",0,power?1:0]];
//    [[DataModelApi sharedInstance] sendData:self.deviceId data:data success:nil failure:nil];
    [UDManager savePowerStateWith:self.deviceId power:power];
    
    [self recordSendCommandOfDate];
    
    //需求: 快速操作“ON”、“OFF”的时候，速度过快间隔时间小于0.5秒时弹出“操作过快”的提示框。
    static BOOL show = NO;
    static NSNumber *lastDevcieId = nil;
    if (show == YES && lastDevcieId && [self.deviceId isEqualToNumber:lastDevcieId]) {
        UIViewController *vc = [BaseCommond getCurrentVC];
        if (![vc isKindOfClass:[UIAlertController class]]) {
            [AlertControllerManager alertWithTitle:nil
                                           message:@"Please do not operate frequently."
                                             style:UIAlertControllerStyleAlert
                                      actionTitles:@[@"OK"]
                                      actionStyles:@[@(UIAlertActionStyleDefault)]
                                            target:vc
                                          handlers:^(NSInteger index) {
                                          }];
        }
        show = NO;
        lastDevcieId = nil;
    }else {
        show = YES;
        lastDevcieId = self.deviceId;
    }
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.25f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        show = NO;
        lastDevcieId = nil;
    });

}

/*
 @{R:value,G:value,B:value}
 */
- (void)sendRGBCommandWithRGBInfo:(NSDictionary *)rgbInfo {
    
    if (![self checkCanSendCommand]) return;
    
    _rgbInfo = rgbInfo;
    
    if (!_rgbInfo) {
        _rgbInfo = @{@"R":@(1.0f),@"G":@(1.0f),@"B":@(1.0f)};
    }else {
        _rgbInfo = rgbInfo;
    }
    
    if (![rgbInfo.allKeys containsObject:@"R"] || ![rgbInfo.allKeys containsObject:@"G"] || ![rgbInfo.allKeys containsObject:@"B"]) {
        NSLog(@"rgbInfo is error");
        return;
    }
    
    CGFloat red = [_rgbInfo[@"R"] floatValue];
    CGFloat green = [_rgbInfo[@"G"] floatValue];
    CGFloat blue = [_rgbInfo[@"B"] floatValue];
    
    red = red * _rgbBrightness;
    green = green * _rgbBrightness;
    blue = blue * _rgbBrightness;
    
//    UIColor *brightnessColor = [UIColor colorWithRed:red green:green blue:blue alpha:1.0];
//    [[LightModelApi sharedInstance] setColor:self.deviceId color:brightnessColor duration:@0 success:nil failure:nil];
    
    [UDManager savePowerStateWith:self.deviceId power:YES];
    [self recordSendCommandOfDate];
    
//    CSRmeshDevice *device = [[CSRDevicesManager sharedInstance] selectedDevice];
//    if (device) {
//        [device setColorWithRed:red green:green blue:blue];
//    }else {
//
//        UIColor *brightnessColor = [UIColor colorWithRed:red green:green blue:blue alpha:1.0];
//        [[LightModelApi sharedInstance] setColor:self.deviceId color:brightnessColor duration:@0 success:nil failure:nil];
//    }

    UIColor *brightnessColor = [UIColor colorWithRed:red green:green blue:blue alpha:1.0];
    [[LightModelApi sharedInstance] setColor:self.deviceId color:brightnessColor duration:@0 success:nil failure:nil];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        NSLog(@"_rgbInfo: %@",_rgbInfo);
        NSLog(@"color: %@",brightnessColor);
    });
}

- (void)sendRGBCommandWithColor:(UIColor *)color {
    NSDictionary *rgbInfo = [BaseCommond getRGBDictionaryByColor:color];
    [[CommandManager shareInstance] sendRGBCommandWithRGBInfo:rgbInfo];
}

/*
 0-1
 */
- (void)sendRGBBirghtness:(CGFloat)brightness rgbInfo:(NSDictionary *)rgbInfo {
    
    _rgbBrightness = brightness;
    _rgbBrightness = _rgbBrightness > 1.0f ? 1.0f : _rgbBrightness;
    _rgbBrightness = _rgbBrightness < 0 ? 0 : _rgbBrightness;
    
    [[CommandManager shareInstance] sendRGBCommandWithRGBInfo:_rgbInfo];
}

/*
 3000-6500
 */
- (void)sendTemperature:(NSInteger)temperature {
    
    if (![self checkCanSendCommand]) return;
    
    NSString *tempertureString = [BaseCommond ToHex:temperature:1];
    NSString *dataString = [NSString stringWithFormat:@"07%02x%@",1,tempertureString];
    NSData *data = [CSRUtilities scanDataString:dataString];
    
//    NSString *dataString = [NSString stringWithFormat:@"90"];
//    NSData *data = [CSRUtilities scanDataString:dataString];
    
    [[DataModelApi sharedInstance] sendData:self.deviceId data:data success:nil failure:nil];
    [self recordSendCommandOfDate];
}
/*
 0-1
 */
static int currentLever = 0;
static int pocketNumberLevel = 0;
static int lastTemperatureBrightness = -1;
- (void)sendTemperatureBrightness:(CGFloat)brightness {
    
    if (![self checkCanSendCommand]) return;
    
    brightness *= 255.0;
    currentLever = brightness;
    
    if (lastTemperatureBrightness == currentLever) {
        return;
    }
    
    NSLog(@"brightness: %f",brightness);
    
    NSString *dataString = [NSString stringWithFormat:@"05%02x%02x",pocketNumberLevel,currentLever];
    NSData *data = [CSRUtilities scanDataString:dataString];
    
    [[DataModelApi sharedInstance] sendData:self.deviceId data:data success:nil failure:nil];
    
    lastTemperatureBrightness = currentLever;
    pocketNumberLevel++;
    if (pocketNumberLevel >= 255) {
        pocketNumberLevel = 0;
    }
    
    [self recordSendCommandOfDate];
}

- (void)sendCommandSceneMode:(MeshSceneModeType)type {
    if (![self checkCanSendCommand]) return;
    
    static MeshSceneModeType lastSceneModeCommand;
    
    NSInteger sceneModeCommand = type;
    
    if (lastSceneModeCommand == type) {
        sceneModeCommand = 0;
    }
    
    lastSceneModeCommand = sceneModeCommand;
    
    NSString *command = [NSString stringWithFormat:@"%02x%02x%02ld",20,00,sceneModeCommand];
    NSLog(@"command: %@",command);
    
    NSData *commandData = [CSRUtilities scanDataString:command];
    [[DataModelApi sharedInstance]sendData:self.deviceId data:commandData success:nil failure:nil];
    [UDManager savePowerStateWith:self.deviceId power:YES];
}

//查询耗电量，只需要查询RGB设备，命令为16
- (void)inquirePowerRate {
    if (![self checkCanSendCommand]) return;
    
    @synchronized (self) {
        //先看距离上一次发送指令的时间和当前时间是否超过2s，小于的话就这次的发送就放弃了，防止命令满天飞导致其他问题
        NSDate *lastDate = [CommandManager shareInstance].lastSendOfDate;
        NSDate *currentDate = [NSDate date];
        if ([currentDate timeIntervalSince1970] - [lastDate timeIntervalSince1970] < 2.0f) {
            NSLog(@"刚刚发送完数据，取消这一次的查询指令");
            return;
        }
        
        if ([MingleManager isRGBLight:self.deviceId] == NO) {
            NSLog(@"该灯型没有查询耗电量功能,不发送命令");
        }
        
        NSString *commandNumber = @"16";
        if ([MingleManager isOldLights:self.deviceId]) {
            commandNumber = @"14";
        }
        
        NSData *data = [CSRUtilities scanDataString:commandNumber];
        [[DataModelApi sharedInstance] sendData:self.deviceId data:data success:nil failure:nil];
        CCLog(@"发送查询耗电量指令...");
    }
    
}

#pragma mark - Setter/Getter
- (CSRmeshDevice *)selectDevice {
    _selectDevice = [CSRDevicesManager sharedInstance].selectedDevice;
    
    return _selectDevice;
}

- (NSNumber *)deviceId {
    _deviceId = self.selectDevice ? self.selectDevice.deviceId : @(0);
    
    return _deviceId;
}

- (void)setRgbInfo:(NSDictionary *)rgbInfo {
    if (rgbInfo) {
        _rgbInfo = rgbInfo;
    }else {
        _rgbInfo = @{@"R":@(1.0f),@"G":@(1.0f),@"B":@(1.0f)};
    }
}

#pragma mark - APIs (Private)
//判断是否允许发送命令，因为命令间的发送必须大于NormalCommandTime,如果strong为YES，则不管时间限制
- (BOOL)checkCanSendCommand {
    
    BOOL tmp = _canSend;
    if (_canSend) {
        _canSend = NO;
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(SendCommandIntervalTime * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            _canSend = YES;
        });
    }
    
    return tmp;
}

//记录时间
- (void)recordSendCommandOfDate {
    @synchronized (self) {
       _lastSendOfDate = [NSDate date];
    }
}

//要加锁
- (NSDate *)lastSendOfDate {
    @synchronized (self) {
        return _lastSendOfDate;
    }
}


@end
