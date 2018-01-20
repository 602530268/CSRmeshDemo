//
//  UITextField+DisableCopy.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/27.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "UITextField+DisableCopy.h"

@implementation UITextField (DisableCopy)

//禁用所有输入框功能按钮
- (BOOL)canPerformAction:(SEL)action withSender:(id)sender {
    UIMenuController *menuController = [UIMenuController sharedMenuController];
    if (menuController) {
        [UIMenuController sharedMenuController].menuVisible = NO;
    }
    return NO;
}


@end
