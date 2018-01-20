//
//  TemperatureTopAreaView.h
//  CSRmeshDemo
//
//  Created by double on 2017/8/28.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SwitchImgView.h"

@interface TemperatureTopAreaView : UIView

@property (weak, nonatomic) IBOutlet UILabel *nameLbl;
@property (weak, nonatomic) IBOutlet UILabel *numbersLbl;
@property (weak, nonatomic) IBOutlet SwitchImgView *switchImgView;
@property (weak, nonatomic) IBOutlet UIImageView *rightArrowImgView;
@property (weak, nonatomic) IBOutlet UIImageView *leftArrowImgView;

@property(nonatomic,copy) void (^rightArrowEventCallback)();
@property(nonatomic,copy) void (^leftArrowEventCallback)();


@end
