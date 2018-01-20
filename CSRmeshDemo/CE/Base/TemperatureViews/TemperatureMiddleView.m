
//
//  TemperatureMiddleView.m
//  Test_1
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 double. All rights reserved.
//

#import "TemperatureMiddleView.h"

@implementation TemperatureMiddleView
{
    NSArray *_temImgViews;
}

- (void)awakeFromNib {
    [super awakeFromNib];
    
    self.backgroundColor = BaseBackgroundColor;
    
    self.temsContainerView.backgroundColor = [UIColor clearColor];

    self.brightnessSlider.minimumTrackTintColor = [UIColor clearColor];
    self.brightnessSlider.maximumTrackTintColor = [UIColor clearColor];
    
    [self.brightnessSlider addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapBrightnessSlider:)]];
    [self.brightnessSlider addTarget:self action:@selector(brightnessSliderTouchEvent) forControlEvents:UIControlEventTouchUpInside];
    [self.brightnessSlider addTarget:self action:@selector(brightnessSliderTouchEvent) forControlEvents:UIControlEventTouchUpOutside];
    [self.brightnessSlider addTarget:self action:@selector(brightnessSliderTouchEvent) forControlEvents:UIControlEventTouchDown];
    
    _temImgViews = @[self.temImgView0,
                         self.temImgView1,
                         self.temImgView2,
                         self.temImgView3,
                         self.temImgView4,
                         self.temImgView5];
    
    for (UIImageView *imgView in _temImgViews) {
        
        imgView.userInteractionEnabled = YES;
        [imgView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapTemperatureEvent:)]];
    }
    
    self.temImgView0.highlighted = YES;
    
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

//索引点击事件
- (void)tapTemperatureEvent:(UITapGestureRecognizer *)sender {
    
    for (int i = 0; i < _temImgViews.count; i++) {
        
        UIImageView *imgView = _temImgViews[i];
        if (imgView == sender.view) {
            imgView.highlighted = YES;
            
            NSInteger temperature = [self getTemperatureByIndex:i];
            _selectIndex = i;
            if (_temperatureIndexCallback) {
                _temperatureIndexCallback(i, temperature);
            }
        }else {
            imgView.highlighted = NO;
        }
    }
}

#pragma mark - Setters
- (void)setSelectIndex:(NSInteger)selectIndex {
    
    _selectIndex = selectIndex;
    for (int i = 0; i < _temImgViews.count; i++) {
        
        UIImageView *imgView = _temImgViews[i];
        if (i == _selectIndex) {
            imgView.highlighted = YES;
        }else {
            imgView.highlighted = NO;
        }
    }
}

#pragma mark - APIs(public)
- (NSInteger)getSelectIndex {
    NSInteger index = 0;
    switch (_temperature) {
        case 2700:
            index = 0;
            break;
        case 3000:
            index = 1;
            break;
        case 3500:
            index = 2;
            break;
        case 4000:
            index = 3;
            break;
        case 4500:
            index = 4;
            break;
        case 5000:
            index = 5;
            break;
            
        default:
            break;
    }
    return index;
}

- (NSInteger)getTemperature {
    NSInteger temperature = 0;
    switch (_selectIndex) {
        case 0:
            temperature = 2700;
            break;
        case 1:
            temperature = 3000;
            break;
        case 2:
            temperature = 3500;
            break;
        case 3:
            temperature = 4000;
            break;
        case 4:
            temperature = 4500;
            break;
        case 5:
            temperature = 5000;
            break;
            
        default:
            break;
    }
    return temperature;
}

#pragma mark - APIs(private)
//根据指定索引获取色温值
- (NSInteger)getTemperatureByIndex:(NSInteger)index {
    
    _temperature = 2700;
    
    switch (index) {
        case 0 :
            _temperature = 2700;
            break;
        case 1:
            _temperature = 3000;
            break;
        case 2:
            _temperature = 3500;
            break;
        case 3:
            _temperature = 4000;
            break;
        case 4:
            _temperature = 4500;
            break;
        case 5:
            _temperature = 5000;
            break;
        default:
            break;
    }
    
    return _temperature;
}




@end
