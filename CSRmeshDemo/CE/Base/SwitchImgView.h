//
//  SwitchImgView.h
//  Test_1
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 double. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SwitchImgView : UIImageView

@property(nonatomic,copy) void(^switchCallback)();


@end
