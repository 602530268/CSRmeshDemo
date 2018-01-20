//
//  CEHomeSelectorView.h
//  CSRmeshDemo
//
//  Created by double on 2017/7/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CEHomeSelectorView : UIView

@property(nonatomic,strong) NSArray *itemsArr;
@property(nonatomic,assign) NSInteger selectIndex;  //default 0
@property(nonatomic,strong) UIColor *bgColor;
@property(nonatomic,strong) UIColor *titleColor;

@property(nonatomic,copy) void (^tapSelectorCallback)(NSInteger index);

- (instancetype)initWithFrame:(CGRect)frame itemsArr:(NSArray <NSString *> *)itemsArr;

@end
