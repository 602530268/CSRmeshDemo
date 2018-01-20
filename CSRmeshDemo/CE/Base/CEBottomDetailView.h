//
//  CEBottomDetailView.h
//  CSRmeshDemo
//
//  Created by double on 2017/10/23.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CEBottomDetailView : UIView

@property(nonatomic,strong) UILabel *tipLabel;
@property(nonatomic,strong) UIButton *connectBtn;
@property(nonatomic,strong) UIProgressView *progressView;
@property(nonatomic,strong) UILabel *connectDetailLabel;

@property(nonatomic,copy) void (^btnCallback)();

@end
