//
//  CEHomeSelectorView.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEHomeSelectorView.h"
#import "Masonry.h"

@implementation CEHomeSelectorView
{
    NSMutableArray *_btnsArr;
    UIView *_arrowView; //三角箭头
}

- (instancetype)initWithFrame:(CGRect)frame itemsArr:(NSArray <NSString *> *)itemsArr {
    if (self = [super initWithFrame:frame]) {
        
        self.backgroundColor = [UIColor clearColor];
        self.clipsToBounds = YES;
        _itemsArr = itemsArr;
        _bgColor = [UIColor whiteColor];
        _titleColor = [UIColor blackColor];
        _selectIndex = 0;
        [self setItemsArr:_itemsArr];
        [self createArrowView];
    }
    return self;
}

#pragma mark - Setters
- (void)setItemsArr:(NSArray *)itemsArr {
    
    if (!itemsArr || itemsArr.count == 0) {
        return;
    }
    
    _itemsArr = itemsArr;
    
    [self.subviews makeObjectsPerformSelector:@selector(removeFromSuperview)];
    
    _btnsArr = @[].mutableCopy;
    for (int i = 0; i < itemsArr.count; i++) {
        UIButton *btn = [[UIButton alloc] initWithFrame:CGRectZero];
        [btn setTitle:itemsArr[i] forState:UIControlStateNormal];
        [btn setTitleColor:_titleColor forState:UIControlStateNormal];
        btn.backgroundColor = _bgColor;
        [btn addTarget:self action:@selector(selectItemEvent:) forControlEvents:UIControlEventTouchUpInside];
        btn.tag = 1000 + i;
        [self addSubview:btn];
        if (i != _selectIndex) {
            [btn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateNormal];
        }
        
        [_btnsArr addObject:btn];
    }
    
    [_btnsArr mas_distributeViewsAlongAxis:MASAxisTypeHorizontal withFixedSpacing:0 leadSpacing:0 tailSpacing:0];
    [_btnsArr mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self);
        make.height.equalTo(self);
    }];
}

#pragma mark - APis (Private)
- (void)createArrowView {
    
    if (_arrowView) {
        return;
    }
    _arrowView = [[UIView alloc] initWithFrame:CGRectZero];
    _arrowView.backgroundColor = BaseBackgroundColor;
    _arrowView.transform = CGAffineTransformMakeRotation(M_PI_4);
    [self addSubview:_arrowView];
    [self changeArrowViewPosition];
}

- (void)changeItemsTitleColor {
    for (UIButton *btn in _btnsArr) {
        if (btn.tag - 1000 != _selectIndex) {
            [btn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateNormal];
        }else {
            [btn setTitleColor:_titleColor forState:UIControlStateNormal];
        }
    }
}

- (void)changeArrowViewPosition {
    if (!_btnsArr && _btnsArr.count == 0) {
        return;
    }
    
    for (int i = 0; i < _btnsArr.count; i++) {
        if (i == _selectIndex) {
            UIButton *btn = (UIButton *)_btnsArr[i];
            
            [UIView animateWithDuration:AnimationTimeByDefault animations:^{
                [_arrowView mas_remakeConstraints:^(MASConstraintMaker *make) {
                    make.bottom.equalTo(self).offset(6.0f);
                    make.centerX.equalTo(btn);
                    make.width.height.equalTo(@12.0f);
                }];
                
                [self layoutIfNeeded];
            }];
            break;
        }
    }
}

- (void)selectItemEvent:(UIButton *)sender {
    _selectIndex = sender.tag - 1000;
    [self changeItemsTitleColor];
    [self changeArrowViewPosition];
    
    if (_tapSelectorCallback) {
        _tapSelectorCallback(_selectIndex);
    }

}

@end
