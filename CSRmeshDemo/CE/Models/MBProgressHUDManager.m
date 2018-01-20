//
//  MBProgressHUDManager.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/28.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "MBProgressHUDManager.h"
#import "MBProgressHUD.h"

@implementation MBProgressHUDManager

+ (MBProgressHUD *)showWith:(UIViewController *)vc {
    return [self showWith:vc title:nil];
}

+ (MBProgressHUD *)showWith:(UIViewController *)vc title:(NSString *)title  {
    MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:vc.navigationController.view animated:YES];
    hud.bezelView.style = MBProgressHUDBackgroundStyleSolidColor;
    hud.bezelView.color = [[UIColor blackColor] colorWithAlphaComponent:0.8f];
    hud.label.text = title;
    hud.label.textColor = [UIColor whiteColor];
    hud.activityIndicatorColor = [UIColor whiteColor];
    
    return hud;
}

+ (void)hideWith:(UIViewController *)vc {
    
    if (vc) {
        [MBProgressHUD hideHUDForView:vc.navigationController.view animated:YES];
    }
}

@end
