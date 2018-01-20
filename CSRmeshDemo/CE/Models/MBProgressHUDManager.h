//
//  MBProgressHUDManager.h
//  CSRmeshDemo
//
//  Created by double on 2017/10/28.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MBProgressHUDManager : NSObject

+ (MBProgressHUD *)showWith:(UIViewController *)vc;

+ (MBProgressHUD *)showWith:(UIViewController *)vc title:(NSString *)title;

+ (void)hideWith:(UIViewController *)vc;

@end
