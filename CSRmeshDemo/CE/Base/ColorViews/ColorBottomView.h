//
//  ColorBottomView.h
//  CSRmeshDemo
//
//  Created by double on 2017/9/1.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ColorBottomView : UIView

@property (weak, nonatomic) IBOutlet UIView *colorItemsContainerView;
@property(nonatomic,assign) CGFloat itemSize;   //default 44

@property(nonatomic,assign) NSInteger selectIndex;  //设置RGB控件索引
@property(nonatomic,strong) NSDictionary *rgbInfo;

@property(nonatomic,copy) void(^rgbInfoCallback)(NSInteger index,NSDictionary *rgbInfo);

- (NSDictionary *)getRgbInfoWith:(NSInteger)index;  //根据所以获取rgbInfo

@end
