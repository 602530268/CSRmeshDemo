//
//  CEUpdateVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/28.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEUpdateVC.h"

@interface CEUpdateVC ()

@end

@implementation CEUpdateVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self createUI];
}

#pragma mark - UI
- (void)createUI {
    [self navUI];
}

- (void)navUI {
    WeakSelf(weakSelf)
    [self customBackBarBtnItemTo:^{
        [weakSelf.navigationController popViewControllerAnimated:YES];
    }];
}

#pragma mark - Data

#pragma mark - Interaction Event

#pragma mark - Trigger Event

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
