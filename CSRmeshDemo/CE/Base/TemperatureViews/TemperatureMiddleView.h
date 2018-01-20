//
//  TemperatureMiddleView.h
//  Test_1
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 double. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface TemperatureMiddleView : UIView

@property (weak, nonatomic) IBOutlet UILabel *titleLbl;

@property (weak, nonatomic) IBOutlet UILabel *brightnessLbl;
@property (weak, nonatomic) IBOutlet UIImageView *sliderBgImgView;
@property (weak, nonatomic) IBOutlet UISlider *brightnessSlider;

@property (weak, nonatomic) IBOutlet UILabel *temperatureLbl;

@property (weak, nonatomic) IBOutlet UIView *temsContainerView;
@property (weak, nonatomic) IBOutlet UIImageView *temImgView0;
@property (weak, nonatomic) IBOutlet UIImageView *temImgView1;
@property (weak, nonatomic) IBOutlet UIImageView *temImgView2;
@property (weak, nonatomic) IBOutlet UIImageView *temImgView3;
@property (weak, nonatomic) IBOutlet UIImageView *temImgView4;
@property (weak, nonatomic) IBOutlet UIImageView *temImgView5;
@property(nonatomic,assign) NSInteger selectIndex;  //设置色温控件索引
@property(nonatomic,assign) NSInteger temperature;  //色温值

@property(nonatomic,copy) void (^brightnessSliderValueChangeCallback)(CGFloat value);   //亮度slider回调
@property(nonatomic,copy) void (^temperatureIndexCallback)(NSInteger index, NSInteger temperature); //色温控件回调
@property(nonatomic,copy) void (^brightnessSliderTouchEventCallback)(); //slider点击、抬起事件，用于UD存储

- (NSInteger)getSelectIndex;
- (NSInteger)getTemperature;

@end
