//
//  ColorMiddleView.m
//  CSRmeshDemo
//
//  Created by double on 2017/9/1.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "ColorMiddleView.h"

@implementation ColorMiddleView

- (void)awakeFromNib {
    [super awakeFromNib];
    
    //点击、滑动、抬起都会触发事件
    [self.brightnessSlider addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapBrightnessSlider:)]];
    [self.brightnessSlider addTarget:self action:@selector(brightnessSliderTouchEvent) forControlEvents:UIControlEventTouchUpInside];
    [self.brightnessSlider addTarget:self action:@selector(brightnessSliderTouchEvent) forControlEvents:UIControlEventTouchUpOutside];
    [self.brightnessSlider addTarget:self action:@selector(brightnessSliderTouchEvent) forControlEvents:UIControlEventTouchDown];
    
    self.brightnessSlider.minimumTrackTintColor = [UIColor clearColor];
    self.brightnessSlider.maximumTrackTintColor = [UIColor clearColor];
    
    //设置最大最小值
    self.brightnessSlider.maximumValue = 1.0f;
    self.brightnessSlider.minimumValue = 0.15f;
}

- (IBAction)brightnessValueChangeEvent:(UISlider *)sender {

    [self brightnessSliderValueChangeEvent];
}

//单击事件
- (void)tapBrightnessSlider:(UITapGestureRecognizer *)sender {
    CGPoint touchPoint = [sender locationInView:sender.view];
    CGFloat touchRange = touchPoint.x / CGRectGetWidth(sender.view.bounds);
    CGFloat value = (self.brightnessSlider.maximumValue - self.brightnessSlider.minimumValue) * touchRange;
    value += self.brightnessSlider.minimumValue;
    
    self.brightnessSlider.value = value;
    
    [self brightnessSliderValueChangeEvent];
    [self brightnessSliderTouchEvent];
}

//用于值改变发送命令，频繁
- (void)brightnessSliderValueChangeEvent {
    if (_brightnessSliderValueChangeCallback) {
        _brightnessSliderValueChangeCallback(self.brightnessSlider.value);
    }
}

//用于UD存储，不频繁
- (void)brightnessSliderTouchEvent {
    if (_brightnessSliderTouchEventCallback) {
        _brightnessSliderTouchEventCallback();
    }
}





@end
