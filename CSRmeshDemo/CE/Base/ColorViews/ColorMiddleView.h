//
//  ColorMiddleView.h
//  CSRmeshDemo
//
//  Created by double on 2017/9/1.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ColorMiddleView : UIView

@property (weak, nonatomic) IBOutlet UILabel *titleLbl;
@property (weak, nonatomic) IBOutlet UILabel *brightnessLbl;
@property (weak, nonatomic) IBOutlet UILabel *colorControlLbl;
@property (weak, nonatomic) IBOutlet UIImageView *sliderBgImgView;
@property (weak, nonatomic) IBOutlet UISlider *brightnessSlider;

@property(nonatomic,copy) void (^brightnessSliderValueChangeCallback)(CGFloat value);
@property(nonatomic,copy) void (^brightnessSliderTouchEventCallback)(); //slider点击、抬起事件，用于UD存储

@end
