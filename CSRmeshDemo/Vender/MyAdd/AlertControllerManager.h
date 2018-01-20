//
//  AlertControllerManager.h
//  BLK_iTag
//
//  Created by double on 2017/8/7.
//  Copyright © 2017年 double. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface AlertControllerManager : NSObject

/*
 title:             标题
 messag:            内容
 style:             弹窗类型
 actionTitles:      actitions标题数组
 actionStyles:      actions类型
 handlers:          回调
 target:            调用者
 */
+ (void)alertWithTitle:(NSString *)title
               message:(NSString *)message
                 style:(UIAlertControllerStyle)style
          actionTitles:(NSArray *)actionTitles
          actionStyles:(NSArray *)actionStyles
                target:(UIViewController *)target
              handlers:(void(^)(NSInteger index))handlers;

@end
