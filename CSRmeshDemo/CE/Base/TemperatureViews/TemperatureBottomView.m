//
//  TemperatureBottomView.m
//  Test_1
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 double. All rights reserved.
//

#import "TemperatureBottomView.h"

@implementation TemperatureBottomView
{
    NSArray *_btns;
}

- (void)awakeFromNib {
    [super awakeFromNib];
    
    _btns = @[self.wakeBtn,self.sleepBtn,self.concentrateBtn,self.relaxBtn];
}

- (IBAction)btnsEvent:(id)sender {
    
    if (sender == self.wakeBtn) {
        _mode = SceneModeWake;
    }else if (sender == self.sleepBtn) {
        _mode = SceneModeSleep;
    }else if (sender == self.concentrateBtn) {
        _mode = SceneModeConcentrate;
    }else if (sender == self.relaxBtn) {
        _mode = SceneModeRelax;
    }
    
    //赋予点击效果
    for (UIButton *btn in _btns) {
        if (btn == sender) {
            btn.alpha = 0.6f;
        }else {
            btn.alpha = 1.0f;;
        }
    }
    
    [self controlsEventCallback];
}

- (void)controlsEventCallback {
    if (_sceneModeBtnEventCallback) {
        _sceneModeBtnEventCallback(_mode);
    }
}

@end
