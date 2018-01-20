//
//  SwitchImgView.m
//  Test_1
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 double. All rights reserved.
//

#import "SwitchImgView.h"

@implementation SwitchImgView
{
    UIImage *_onImage;
    UIImage *_offImage;
    
    BOOL _isAnimating;  //正在播放动画,一开始打算有动画效果的，目前弃用
}

- (void)awakeFromNib {
    [super awakeFromNib];
    
    self.contentMode = UIViewContentModeScaleAspectFit;
    
    _offImage = [[UIImage imageNamed:@"circle_empty"] imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal];
    
    self.image = _offImage;
    
    self.userInteractionEnabled = YES;
    [self addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(switchPower)]];
}

- (void)switchPower {
    
    if (_switchCallback) {
        _switchCallback();
    }
}


@end
