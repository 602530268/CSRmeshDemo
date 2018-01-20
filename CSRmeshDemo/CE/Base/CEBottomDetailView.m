//
//  CEBottomDetailView.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/23.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEBottomDetailView.h"

@implementation CEBottomDetailView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        
        [self createControls];
    }
    return self;
}

- (void)createControls {
    
    _tipLabel = [[UILabel alloc] init];
    _tipLabel.text = @"select multiple lights\nto connecting";
    _tipLabel.numberOfLines = 2;
    _tipLabel.textAlignment = NSTextAlignmentCenter;
    _tipLabel.textColor = [UIColor lightGrayColor];
    [self addSubview:_tipLabel]; 
    [_tipLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self);
    }]; 
    
    _connectBtn = [[UIButton alloc] init];
    [_connectBtn setTitle:@"sync 0 light" forState:UIControlStateNormal];
    [_connectBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    [_connectBtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
    _connectBtn.backgroundColor = [UIColor colorWithRed:229/255. green:143/255. blue:0/255. alpha:1.0];
    _connectBtn.layer.cornerRadius = 20.0f;
    _connectBtn.layer.masksToBounds = YES;
    [_connectBtn addTarget:self action:@selector(connectBtnEvent:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:_connectBtn];
    [_connectBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self);
        make.bottom.equalTo(self).offset(-15);
        make.width.equalTo(@250.0);
        make.height.equalTo(@40.0);
    }];
    
    _connectDetailLabel = [[UILabel alloc] init];
    _connectDetailLabel.text = @"Light\nAssociating 0%";
    _connectDetailLabel.numberOfLines = 2;
    _connectDetailLabel.textColor = [UIColor lightGrayColor];
    _connectDetailLabel.textAlignment = NSTextAlignmentCenter;
    [self addSubview:_connectDetailLabel];
    [_connectDetailLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(_connectBtn.mas_top).offset(-20);
        make.centerX.equalTo(_connectBtn);
    }];
    
    _progressView = [[UIProgressView alloc] init];
    [self addSubview:_progressView];
    [_progressView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(_connectDetailLabel.mas_top);
        make.centerX.equalTo(self);
        make.width.equalTo(self).offset(-60);
    }];
}

#pragma mark - Interaction Event
- (void)connectBtnEvent:(UIButton *)sender {
    if (_btnCallback) {
        _btnCallback();
    }
}

@end
