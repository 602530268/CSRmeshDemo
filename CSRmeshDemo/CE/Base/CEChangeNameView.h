//
//  CEChangeNameView.h
//  CSRmeshDemo
//
//  Created by double on 2017/10/24.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CEChangeNameView : UIView

@property(nonatomic,strong) UILabel *titleLbl;
@property(nonatomic,strong) UITextField *textField;
@property(nonatomic,strong) UIButton *determineBtn;
@property(nonatomic,strong) UIButton *cancelBtn;
@property(nonatomic,copy) void (^newNameCallback)(NSString *name);

- (instancetype)initWithFrame:(CGRect)frame superView:(UIView *)superView;

@end
