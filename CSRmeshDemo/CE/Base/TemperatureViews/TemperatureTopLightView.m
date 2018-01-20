//
//  TemperatureTopLightView.m
//  Test_1
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 double. All rights reserved.
//

#import "TemperatureTopLightView.h"

@implementation TemperatureTopLightView

- (void)awakeFromNib {
    [super awakeFromNib];
    
    self.backgroundColor = BaseBackgroundColor;
    
    self.belongAreasLbl.layer.cornerRadius = CGRectGetHeight(self.belongAreasLbl.bounds)/2;
    self.belongAreasLbl.layer.masksToBounds = YES;
    
    self.powerconsumesView.backgroundColor = [UIColor clearColor];
    
    self.rightArrowImgView.userInteractionEnabled = YES;
    self.leftArrowImgView.userInteractionEnabled = YES;
    
    [self.rightArrowImgView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(arrowImgViewEvent:)]];
    [self.leftArrowImgView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(arrowImgViewEvent:)]];
    
}

//- (void)switchPower {
//
//    if (_switchPowerCallback) {
//        _switchPowerCallback();
//    }
//}

- (void)arrowImgViewEvent:(UITapGestureRecognizer *)sender {
    
    if (self.rightArrowImgView.hidden == NO) {
        
        if (_rightArrowEventCallback) {
            _rightArrowEventCallback();
        }
    }else if(self.leftArrowImgView.hidden == NO) {
        if (_leftArrowEventCallback) {
            _leftArrowEventCallback();
        }
    }
    
}


@end
