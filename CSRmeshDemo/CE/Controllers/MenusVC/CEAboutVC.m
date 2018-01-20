//
//  CEAboutVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/27.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEAboutVC.h"
#import "UINavigationController+Smooth.h"

@interface CEAboutVC ()

@property(nonatomic,strong) UIImageView *imgView;
@property(nonatomic,strong) UILabel *bottomDetailLabel;

@end

@implementation CEAboutVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.navBarBgAlpha = 0;
    [self createUI];
}

#pragma mark - UI
- (void)createUI {
    [self navUI];
    [self createControls];
}

- (void)navUI {
    WeakSelf(weakSelf)
    [self customBackBarBtnItemTo:^{
        [weakSelf.navigationController popViewControllerAnimated:YES];
    }];
}

- (void)createControls {
    
    _imgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"CE_brand"]];
    _imgView.contentMode = UIViewContentModeScaleAspectFit;
    [self.view addSubview:_imgView];
    [_imgView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.view);
        make.width.equalTo(self.view).multipliedBy(0.65);
        make.height.equalTo(@(60));
    }];
    
    NSString *version = [NSString stringWithFormat:@"Version %@",[[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"]];
    NSString *company = @"Elec-tech Solid State Lighting (hk) Limited";
    _bottomDetailLabel = [[UILabel alloc] init];
//    _bottomDetailLabel.text = @"Version 1.0.6\nCopyright@ 2016 lgloo Technologies,Inc.\nAll Rights Reserved";
    _bottomDetailLabel.text = [NSString stringWithFormat:@"%@\n%@.\nAll Rights Reserved",version,company];
    _bottomDetailLabel.textAlignment = NSTextAlignmentCenter;
    _bottomDetailLabel.textColor = [UIColor whiteColor];
    _bottomDetailLabel.numberOfLines = 0;
    [self.view addSubview:_bottomDetailLabel];
    [_bottomDetailLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.right.equalTo(self.view);
        make.bottom.equalTo(self.view).offset(-20);
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
