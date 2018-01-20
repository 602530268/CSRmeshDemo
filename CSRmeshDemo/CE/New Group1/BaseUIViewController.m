//
//  BaseUIViewController.m
//  CSRmeshDemo
//
//  Created by double on 2017/6/26.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "BaseUIViewController.h"
#import "UINavigationController+Smooth.h"

@interface BaseUIViewController ()
{
    void(^_backBtnCallback)();
}

@end

@implementation BaseUIViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.view.backgroundColor = BaseBackgroundColor;
    self.navBarBgAlpha = 1.0f;
}

#pragma mark - APIs (Public)
- (void)setBars:(NSArray *)bars leftOrRight:(BOOL)leftOrRight {
    
    NSMutableArray *mBars = @[].mutableCopy;
    for (int i = 0; i < bars.count; i++) {
        id bar = bars[i];
        UIBarButtonItem *barBtnItem;
        
        if ([bar isKindOfClass:[NSString class]]) {
            barBtnItem = [[UIBarButtonItem alloc] initWithTitle:bar style:UIBarButtonItemStylePlain target:self action:@selector(barBtnItemsEvent:)];
        }else if ([bar isKindOfClass:[UIImage class]]) {
            barBtnItem = [[UIBarButtonItem alloc] initWithImage:bar style:UIBarButtonItemStylePlain target:self action:@selector(barBtnItemsEvent:)];
        }else if ([bar isKindOfClass:[UIView class]]) {
            
            UIView *getView = (UIView *)bar;
            getView.userInteractionEnabled = YES;
            [getView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(barBtnItemsEvent:)]];
            barBtnItem = [[UIBarButtonItem alloc] initWithCustomView:bar];
        }
        
        [mBars addObject:barBtnItem];
        
    }
    
    if (leftOrRight == NO) {
        self.navigationItem.leftBarButtonItems = [NSArray arrayWithArray:mBars];
    }else {
        self.navigationItem.rightBarButtonItems = [NSArray arrayWithArray:mBars];
    }
}

- (void)customBackBarBtnItemTo:(void (^)())block {
    
    _backBtnCallback = block;
    
    //定制返回按钮，会与原生有些出入，将就
    UIView * bgView = [[UIView alloc] initWithFrame:CGRectMake(0, 25, 80, 40)];
    UIImageView * backImgView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 10, 19, 19)];
    backImgView.image = [UIImage imageNamed:@"nav_back"];
    [bgView addSubview:backImgView];
    
    UILabel * backLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, 10, 60, 20)];
    backLabel.text = @"Back";
    backLabel.font = [UIFont fontWithName:@"MontSerrat-Regular" size:16];
    [backLabel setTextColor:[UIColor lightGrayColor]];
    [bgView addSubview:backLabel];
    
    UIButton * btn = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn addTarget:self action:@selector(backBarBtnItemEvent) forControlEvents:UIControlEventTouchUpInside];
    btn.frame = CGRectMake(0, 0, 80, 40);
    [bgView addSubview:btn];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:bgView];
}

#pragma mark - APIs (Private)
- (void)barBtnItemsEvent:(UIBarButtonItem *)sender {
    NSInteger index = -1;
    BOOL leftOrRight = false;
    
    for (int i = 0; i < self.navigationItem.leftBarButtonItems.count; i++) {
        UIBarButtonItem *leftBar = self.navigationItem.leftBarButtonItems[i];
        if (leftBar == sender) {
            index = i;
            leftOrRight = NO;
        }
    }
    
    for (int i = 0; i < self.navigationItem.rightBarButtonItems.count; i++) {
        UIBarButtonItem *rightBar = self.navigationItem.rightBarButtonItems[i];
        if (rightBar == sender) {
            index = i;
            leftOrRight = YES;
        }
    }
     
    
    if (_barBtnItemEvent && index != -1) {
        _barBtnItemEvent(leftOrRight,index);
    }
}

- (void)backBarBtnItemEvent {
    if (_backBtnCallback) {
        _backBtnCallback();
    }
}

- (void)dealloc {
    NSLog(@"dealloc: %@",NSStringFromClass([self class]));
//    NSLog(@"dealloc: %@",self);
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

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
