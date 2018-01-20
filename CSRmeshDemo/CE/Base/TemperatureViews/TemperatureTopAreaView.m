//
//  TemperatureTopAreaView.m
//  CSRmeshDemo
//
//  Created by double on 2017/8/28.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "TemperatureTopAreaView.h"

@implementation TemperatureTopAreaView

- (void)awakeFromNib {
    [super awakeFromNib];
    
    self.rightArrowImgView.userInteractionEnabled = YES;
    self.leftArrowImgView.userInteractionEnabled = YES;
    
    [self.rightArrowImgView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(arrowImgViewEvent:)]];
    [self.leftArrowImgView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(arrowImgViewEvent:)]];
}

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
