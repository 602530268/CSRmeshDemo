//
//  CELightsVC.h
//  CSRmeshDemo
//
//  Created by double on 2017/7/18.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "BaseUIViewController.h"

@interface CELightsVC : BaseUIViewController

@property(nonatomic,copy) void (^hasNotDeviceCallback)(BOOL flag);  //设备清空后回调

@end
