//
//  ColorBottomView.m
//  CSRmeshDemo
//
//  Created by double on 2017/9/1.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "ColorBottomView.h"

@implementation ColorBottomView
{
    NSMutableArray *_itemsArr;
    UIButton *_lastTapBtn;
    NSArray *_rgbInfoArr;
}

- (void)awakeFromNib {
    [super awakeFromNib];

    if (!_itemsArr) {
        [self createControls];
    }

    //默认设置
    _rgbInfoArr = [self rgbInfoArr];
}

- (void)createControls {
    
    _itemSize = _itemSize == 0 ? 44 : _itemSize;
    
    _itemsArr = @[].mutableCopy;
    
    //如果是iPad的话，item的尺寸就为父视图的一半
    NSString *deviceType = [UIDevice currentDevice].model;

    for (int i = 0; i < self.colorItemsContainerView.subviews.count; i++) {
        
        UIView *subView = self.colorItemsContainerView.subviews[i];
        
        UIImage *normal = [UIImage imageNamed:[NSString stringWithFormat:@"color_%d",i]];
        UIImage *select = [UIImage imageNamed:[NSString stringWithFormat:@"color_%d_tick",i]];
        UIImageView *imgView = [[UIImageView alloc] initWithImage:normal highlightedImage:select];
        imgView.contentMode = UIViewContentModeScaleAspectFit;
        [subView addSubview:imgView];
        
        [imgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(subView);
            
            if([deviceType containsString:@"iPad"]) {
                make.size.equalTo(subView).multipliedBy(0.5);
            }else {
                make.width.height.equalTo(@(_itemSize));
            }
            
        }];
        
        imgView.userInteractionEnabled = YES;
        [imgView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapItemEvent:)]];
        
        [_itemsArr addObject:imgView];
        
//        if (i == 0) {
//            imgView.highlighted = YES;
//        }
    }
    
}

- (void)tapItemEvent:(UITapGestureRecognizer *)sender {
    
    NSInteger index = 0;
    
    for (int i = 0; i < _itemsArr.count; i++) {
        UIImageView *imgView = _itemsArr[i];
        
        if (imgView == sender.view) {
            index = i;
            imgView.highlighted = YES;
        }else {
            imgView.highlighted = NO;
        }
    }
    
    _selectIndex = index;
    if (_rgbInfoCallback && _rgbInfoArr.count > index) {
        NSDictionary *rgbInfo = _rgbInfoArr[index];
        
        CGFloat r = [rgbInfo[@"R"] floatValue] / 255.0;
        CGFloat g = [rgbInfo[@"G"] floatValue] / 255.0;
        CGFloat b = [rgbInfo[@"B"] floatValue] / 255.0;
        
        rgbInfo = @{@"R":@(r),@"G":@(g),@"B":@(b)};
        
        _rgbInfoCallback(index,rgbInfo);
    }

}

#pragma mark - Setters
- (void)setSelectIndex:(NSInteger)selectIndex {
    
    if (selectIndex < 0) {
        return;
    }
    
    _selectIndex = selectIndex;
    for (int i = 0; i < _itemsArr.count; i++) {
        
        UIButton *btn = _itemsArr[i];
        if (i == _selectIndex) {
            btn.highlighted = YES;
        }else {
            btn.highlighted = NO;
        }
    }
    
//    _rgbInfo = _rgbInfoArr[_selectIndex];
    
    NSDictionary *rgbInfo = _rgbInfoArr[_selectIndex];
    
    CGFloat r = [rgbInfo[@"R"] floatValue] / 255.0;
    CGFloat g = [rgbInfo[@"G"] floatValue] / 255.0;
    CGFloat b = [rgbInfo[@"B"] floatValue] / 255.0;
    
    _rgbInfo = @{@"R":@(r),@"G":@(g),@"B":@(b)};
}

#pragma mark - APIs(private)
- (NSArray *)rgbInfoArr {
//    NSArray *rgbsArr = @[@{@"R":@(1),@"G":@(0),@"B":@(0)},
//                    @{@"R":@(1),@"G":@(1),@"B":@(0)},
//                    @{@"R":@(1),@"G":@(0.2706),@"B":@(0)},
//                    @{@"R":@(1),@"G":@(0.549),@"B":@(0)},
//                    @{@"R":@(0.458),@"G":@(1),@"B":@(0)},
//                    @{@"R":@(0),@"G":@(1),@"B":@(0)},
//                    @{@"R":@(0),@"G":@(1),@"B":@(1)},
//                    @{@"R":@(0.56),@"G":@(1),@"B":@(0)},
//                    @{@"R":@(0.196),@"G":@(0.804),@"B":@(0.196)},
//                    @{@"R":@(0.118),@"G":@(0.5647),@"B":@(1)},
//                    @{@"R":@(0),@"G":@(0),@"B":@(1)},
//                    @{@"R":@(1),@"G":@(0),@"B":@(1)},
//                    @{@"R":@(1),@"G":@(0.186),@"B":@(0.15)},
//                    @{@"R":@(0.45),@"G":@(0),@"B":@(1)},
//                    @{@"R":@(0.5118),@"G":@(0.1687),@"B":@(0.88627)}];
    
    //后期经过改动的数值，兼容灯型，与上面标准数值不同
    NSArray *rgbsArr = @[@{@"R":@(255),@"G":@(0),@"B":@(0)},
                      @{@"R":@(255),@"G":@(127),@"B":@(0)},
                      @{@"R":@(255),@"G":@(15),@"B":@(0)},
                      @{@"R":@(255),@"G":@(30),@"B":@(0)},
                      @{@"R":@(125),@"G":@(255),@"B":@(0)},
                      
                      @{@"R":@(0),@"G":@(255),@"B":@(0)},
                      @{@"R":@(0),@"G":@(255),@"B":@(255)},
                      @{@"R":@(0),@"G":@(255),@"B":@(10)},
                      @{@"R":@(0),@"G":@(255),@"B":@(30)},
                      @{@"R":@(0),@"G":@(150),@"B":@(255)},
                      
                      @{@"R":@(0),@"G":@(0),@"B":@(255)},
                      @{@"R":@(255),@"G":@(0),@"B":@(235)},
                      @{@"R":@(255),@"G":@(0),@"B":@(100)},
                      @{@"R":@(150),@"G":@(0),@"B":@(255)},
                      @{@"R":@(80),@"G":@(0),@"B":@(255)}];
    
    return rgbsArr;
}

- (NSDictionary *)getRgbInfoWith:(NSInteger)index {
    
    NSArray *rgbs = [self rgbInfoArr];
    if (rgbs.count >= index && index > -1) {
        return rgbs[index];
    }
    return nil;
}



@end
