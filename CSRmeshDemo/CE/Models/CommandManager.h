//
//  CommandManager.h
//  CSRmeshDemo
//
//  Created by double on 2017/8/28.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

/*
 命令管理器
 */

#import <Foundation/Foundation.h>

//mesh灯情景模式
typedef NS_ENUM(NSInteger,MeshSceneModeType) {
    MeshSceneModeTypeNone,
    MeshSceneModeTypeGradient = 1,   //渐变
    MeshSceneModeTypeRainbow = 2,    //彩虹
    MeshSceneModeTypeBreath = 4, //呼吸
    MeshSceneModeTypeFlash = 8,  //闪烁
};

@interface CommandManager : NSObject

@property(nonatomic,assign) BOOL canSend;  //是否允许发送命令
@property(nonatomic,strong) NSDate *lastSendOfDate;    //最后一次发送指令的时间
@property(nonatomic,strong) NSDictionary *rgbInfo;

+ (CommandManager *)shareInstance;

//开关
- (void)sendPower:(BOOL)power;

/*
 RGB设置
 @{R:value,G:value,B:value}
 */
- (void)sendRGBCommandWithRGBInfo:(NSDictionary *)rgbInfo;
- (void)sendRGBCommandWithColor:(UIColor *)color;

/*
 0-1
 */
- (void)sendRGBBirghtness:(CGFloat)brightness rgbInfo:(NSDictionary *)rgbInfo;

/*
 3000-6500
 */
- (void)sendTemperature:(NSInteger)temperature;
/*
 0-1
 */
- (void)sendTemperatureBrightness:(CGFloat)brightness;

/*
 MeshSceneModeType
 */
- (void)sendCommandSceneMode:(MeshSceneModeType)type;

//查询耗电量，只需要查询RGB设备，命令为16
- (void)inquirePowerRate;

@end
