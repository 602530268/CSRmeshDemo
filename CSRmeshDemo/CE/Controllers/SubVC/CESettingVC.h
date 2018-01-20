//
//  CESettingVC.h
//  CSRmeshDemo
//
//  Created by double on 2017/10/23.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "BaseUIViewController.h"

@interface CESettingVC : BaseUIViewController

@property(nonatomic,assign) BOOL belongArea;

@property(nonatomic,strong) CSRDeviceEntity *deviceEntity;
@property(nonatomic,strong) CSRAreaEntity *areaEntity;

@end
