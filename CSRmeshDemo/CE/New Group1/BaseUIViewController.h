//
//  BaseUIViewController.h
//  CSRmeshDemo
//
//  Created by double on 2017/6/26.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BaseUIViewController : UIViewController

@property(nonatomic,copy) void (^barBtnItemEvent)(BOOL leftOrTight, NSInteger index);   //leftOrTight = NO 为left,leftOrTight = YES 为Right

- (void)setBars:(NSArray *)bars leftOrRight:(BOOL)leftOrRight;

- (void)customBackBarBtnItemTo:(void(^)())block;

@end
