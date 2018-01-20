//
//  BaseContaints.h
//  CSRmeshDemo
//
//  Created by double on 2017/6/26.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#ifndef BaseContaints_h
#define BaseContaints_h

#define SCREEN_WIDTH [UIScreen mainScreen].bounds.size.width
#define SCREEN_HEIGHT [UIScreen mainScreen].bounds.size.height

#define StateBarHeight [[UIApplication sharedApplication] statusBarFrame].size.height   //状态栏高度
#define NavBarHeight self.navigationController.navigationBar.frame.size.height  //导航栏高度
#define StateBarAndNavBarHeight (StateBarHeight + NavBarHeight) //状态栏加导航栏
#define ScreenViewHeight (SCREEN_HEIGHT - StateBarAndNavBarHeight)  //除去状态栏和导航栏后的高度

#define WeakSelf(weakSelf) __weak typeof(self) weakSelf = self;

#define COLOR(RED,GREEN,BLUE,ALPHA) [UIColor colorWithRed:RED/255.0 green:GREEN/255.0 blue:BLUE/255.0 alpha:ALPHA];

//Notify
#define Notify_ChangeHomeSegment @"Notify_ChangeHomeSegment"    //改变首页segment时
#define Notify_UpdateOfExportFile @"Notify_UpdateOfExportFile"    //导入共享文件后刷新UI
#define Notify_ReceivePowerConsumptionData @"Notify_ReceivePowerConsumptionData"  //收到设备回调的耗电量数据

//UserDefault
#define UD_Passcode @"UD_Passcode"  //组网密码
#define UD_FirstInstall @"UD_FirstInstall"    //第一次更新

#endif /* BaseContaints_h */
