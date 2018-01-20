//
//  AlertControllerManager.m
//  BLK_iTag
//
//  Created by double on 2017/8/7.
//  Copyright © 2017年 double. All rights reserved.
//

#import "AlertControllerManager.h"

@implementation AlertControllerManager

+ (void)alertWithTitle:(NSString *)title
               message:(NSString *)message
                 style:(UIAlertControllerStyle)style
          actionTitles:(NSArray *)actionTitles
          actionStyles:(NSArray *)actionStyles
                target:(UIViewController *)target
              handlers:(void(^)(NSInteger index))handlers {
    
    NSAssert(actionTitles.count == actionStyles.count, @"actionTitles和actionStyles要保持一致");
    
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:style];
    
    for (int i = 0; i < actionTitles.count; i++) {
        UIAlertAction *action = [UIAlertAction actionWithTitle:actionTitles[i] style:[actionStyles[i] integerValue] handler:^(UIAlertAction * _Nonnull action) {
            
            if (handlers) {
                handlers(i);
            }
        }];
        [alertController addAction:action];
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [target presentViewController:alertController animated:YES completion:nil];
    });
    
}


@end
