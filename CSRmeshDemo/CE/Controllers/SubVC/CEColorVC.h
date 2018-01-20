//
//  CEColorVC.h
//  CSRmeshDemo
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "BaseUIViewController.h"

@interface CEColorVC : BaseUIViewController

@property(nonatomic,strong) CSRDeviceEntity *deviceEntity;
@property(nonatomic,strong) CSRAreaEntity *areaEntity;

@property(nonatomic,assign) BOOL belongArea;    //属于灯组页面

@end
