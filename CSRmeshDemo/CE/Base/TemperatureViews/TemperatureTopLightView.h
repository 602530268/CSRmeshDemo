//
//  TemperatureTopLightView.h
//  Test_1
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 double. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SwitchImgView.h"

@interface TemperatureTopLightView : UIView

@property (weak, nonatomic) IBOutlet UILabel *nameLbl;
@property (weak, nonatomic) IBOutlet UILabel *belongAreasLbl;
@property (weak, nonatomic) IBOutlet UILabel *connectStateLbl;

@property (weak, nonatomic) IBOutlet UIView *powerconsumesView;
@property (weak, nonatomic) IBOutlet UIButton *wattBtn;
@property (weak, nonatomic) IBOutlet UIButton *voltBtn;
@property (weak, nonatomic) IBOutlet UIButton *milliampereBtn;
@property (weak, nonatomic) IBOutlet UIButton *kilowattBtn;

@property (weak, nonatomic) IBOutlet SwitchImgView *switchImgView;
@property (weak, nonatomic) IBOutlet UIImageView *rightArrowImgView;
@property (weak, nonatomic) IBOutlet UIImageView *leftArrowImgView;

@property(nonatomic,copy) void (^switchPowerCallback)();
@property(nonatomic,copy) void (^leftArrowEventCallback)();
@property(nonatomic,copy) void (^rightArrowEventCallback)();

@end
