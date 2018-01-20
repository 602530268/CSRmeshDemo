//
//  CEHomeVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/17.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEHomeVC.h"
#import "CEAddNewLightVC.h"
#import "CELightsVC.h"
#import "CEAreasVC.h"
#import "CEPasscodeVC.h"
#import "CEUpdateVC.h"
#import "CEAboutVC.h"
#import "CEMoreLightsVC.h"
#import "CESupportVC.h"
#import "OTAUViewController.h"
#import "CEQAVC.h"

#import "CEHomeSelectorView.h"
#import "KxMenu.h"

#import "UINavigationController+Smooth.h"
#import "SharePlaceManager.h"
#import "AlertControllerManager.h"

@interface CEHomeVC ()
{
    NSInteger _vcCount;   //装载的Controller数量
    UIView *_settingItem;   //标记设置按钮视图
    
    CELightsVC *_lightsVC;
    CEAreasVC *_areasVC;    
}

@property(nonatomic,strong) CEHomeSelectorView *selectorView;
@property(nonatomic,strong) UIScrollView *vcScrollView;

@end

@implementation CEHomeVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initData];
    [self createUI];

}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.navBarBgAlpha = 1.0f;
    [self checkTotalAssociatedDevices];

}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
}

- (void)viewWillLayoutSubviews {
    [super viewWillLayoutSubviews];
    _vcScrollView.contentSize = CGSizeMake(SCREEN_WIDTH * _vcCount, 0);
}

#pragma mark - UI
- (void)createUI {
    
    self.navigationController.navigationBar.barTintColor = BaseNavColor;
    self.view.backgroundColor = BaseBackgroundColor;
    
    [self navUI];
    [self createNoDataView];
    [self createSegmentView];
    [self createVcScrollView];
}

- (void)navUI {

    self.navigationController.navigationBar.tintColor = [UIColor lightGrayColor];   //item颜色
    self.navigationController.navigationBar.shadowImage = [UIImage new];    //导航栏底部黑线

    UIImageView *titleView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"CE_brand"]];
    titleView.contentMode = UIViewContentModeScaleAspectFit;
    self.navigationItem.titleView = titleView;
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 11.0) {
        
        UIImageView *settingImgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"Setting"]];
        settingImgView.frame = CGRectMake(0, 0, 20, 20);
        settingImgView.contentMode = UIViewContentModeScaleAspectFit;
        [settingImgView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(settingBarBtnItemEvent)]];
        settingImgView.userInteractionEnabled = YES;

        UIView *settingView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 20, 20)];
        [settingView addSubview:settingImgView];

        UIBarButtonItem *settingBarBtnItem = [[UIBarButtonItem alloc] initWithCustomView:settingView];
        self.navigationItem.rightBarButtonItem = settingBarBtnItem;
        
        _settingItem = settingView;
        
    }else {
        UIImageView *settingImgView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"Setting"]];
        settingImgView.frame = CGRectMake(0, 0, 20, 20);
        settingImgView.contentMode = UIViewContentModeScaleAspectFit;
        UIView *settingView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 44, 44)];
        settingView.userInteractionEnabled = YES;
        [settingView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(settingBarBtnItemEvent)]];
        [settingView addSubview:settingImgView];
        [settingImgView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(settingView);
            make.width.height.equalTo(@20.0f);
        }];
        
        UIBarButtonItem *settingBarBtnItem = [[UIBarButtonItem alloc] initWithCustomView:settingView];
        self.navigationItem.rightBarButtonItem = settingBarBtnItem;
        
        _settingItem = settingView;
    }
    

}

- (void)createNoDataView {
    UIImageView *noDataView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"No_Data"]];
    [self.view addSubview:noDataView];
    noDataView.contentMode = UIViewContentModeScaleAspectFit;
    [noDataView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.view);
        make.width.height.equalTo(@300);
    }];
    noDataView.userInteractionEnabled = YES;
    [noDataView addGestureRecognizer:[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(addNewLightEvent)]];
}

- (void)createVcScrollView {
    self.automaticallyAdjustsScrollViewInsets = NO;
    
    _vcScrollView = [[UIScrollView alloc] initWithFrame:CGRectZero];
    _vcScrollView.backgroundColor = [UIColor clearColor];
    _vcScrollView.scrollEnabled = NO;
    [self.view addSubview:_vcScrollView];
    [_vcScrollView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(_selectorView.mas_bottom);
        make.left.right.bottom.equalTo(self.view);
    }];
    
    CELightsVC *lightsVC = [[CELightsVC alloc] init];
    CEAreasVC *areasVC = [[CEAreasVC alloc] init];
    NSArray *vcArr = @[lightsVC,areasVC];
    _vcCount = vcArr.count;
    
    _lightsVC = lightsVC;
    _areasVC = areasVC;
    
    _vcScrollView.contentSize = CGSizeMake(SCREEN_WIDTH * vcArr.count, 0);
    
    for (int i = 0; i < vcArr.count; i++) {
        
        UIViewController *vc = vcArr[i];
        [self addChildViewController:vc];
        
        vc.automaticallyAdjustsScrollViewInsets = NO;
        vc.view.backgroundColor = BaseBackgroundColor;
        [_vcScrollView addSubview:vc.view];
        
        [vc.view mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(_vcScrollView).offset(SCREEN_WIDTH * i);
            make.top.bottom.equalTo(_vcScrollView);
            make.width.equalTo(_vcScrollView);
            make.height.equalTo(_vcScrollView);
        }];
    }
    
    WeakSelf(weakSelf)
    lightsVC.hasNotDeviceCallback = ^(BOOL flag) {
        [weakSelf hasAssociatedDevice:flag];
    };
    
}

- (void)createSegmentView {
    
    _selectorView = [[CEHomeSelectorView alloc] initWithFrame:CGRectZero itemsArr:@[@"all lights",@"groups"]];
    [self.view addSubview:_selectorView];
    [_selectorView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.view).offset(StateBarAndNavBarHeight);
        make.left.right.equalTo(self.view);
        make.height.equalTo(@45.0);
    }];
    
    WeakSelf(weakSelf)
    _selectorView.tapSelectorCallback = ^(NSInteger index) {
        [UIView animateWithDuration:AnimationTimeByDefault animations:^{
            [weakSelf.vcScrollView setContentOffset:CGPointMake(SCREEN_WIDTH * index, 0)];
        }];
        
        [[NSNotificationCenter defaultCenter] postNotificationName:Notify_ChangeHomeSegment object:nil userInfo:@{@"index":@(index)}];
    };
    
}

#pragma mark - Data
- (void)initData {
    [self registerNotify];
}

- (void)registerNotify {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(updateOfExportFile) name:Notify_UpdateOfExportFile object:nil];
}

#pragma mark - Notifications
- (void)updateOfExportFile {
    
    NSLog(@"接收到共享文件,更新UI");
    
    //返回到首页
    __block UIViewController *vc = [BaseCommond getCurrentVC];
    if ([vc isKindOfClass:[UIAlertController class]]) {
        [vc dismissViewControllerAnimated:NO completion:^{
            
            vc = [BaseCommond getCurrentVC];
        }];
    }
}

#pragma mark - Interaction Event
- (void)addNewLightEvent {

    CEAddNewLightVC *addNewLightVC = [[CEAddNewLightVC alloc] init];
    [self.navigationController pushViewController:addNewLightVC animated:YES];
}

- (void)settingBarBtnItemEvent {
    
    NSLog(@"setting");
    [self showKxMenu];
}


#pragma mark - Trigger Event
- (void)checkTotalAssociatedDevices {
    NSInteger deviceCount = [CSRAppStateManager sharedInstance].selectedPlace.devices.count;
    [self hasAssociatedDevice:deviceCount == 0 ? NO : YES];
}

- (void)hasAssociatedDevice:(BOOL)has {
    dispatch_async(dispatch_get_main_queue(), ^{
        _selectorView.hidden = !has;
        _vcScrollView.hidden = !has;
    });
}

//展示设置菜单
- (void)showKxMenu {
    NSArray *menuItems =
    @[
      [KxMenuItem menuItem:@"password"
                     image:[UIImage imageNamed:@"password"]
                    target:self
                    action:@selector(pushPasswordVC)],
      
      //double modified
      [KxMenuItem menuItem:@"update"
                     image:[UIImage imageNamed:@"update"]
                    target:self
                    action:@selector(pushUpdateVC)],
      
      [KxMenuItem menuItem:@"about"
                     image:[UIImage imageNamed:@"about"]
                    target:self
                    action:@selector(pushAboutVC)],
      
      [KxMenuItem menuItem:@"get more lights"
                     image:[UIImage imageNamed:@"get_more_lights"]
                    target:self
                    action:@selector(pushGetMoreLightsVC)],
      
      [KxMenuItem menuItem:@"help & support"
                     image:[UIImage imageNamed:@"support"]
                    target:self
                    action:@selector(pushSupportVC)],
      
      [KxMenuItem menuItem:@"Share Profile"
                     image:[UIImage imageNamed:@"share"]
                    target:self
                    action:@selector(pushShareVC)],
      
      [KxMenuItem menuItem:@"Q&A"
                     image:nil
                    target:self
                    action:@selector(pushQAVC)],
      ];
    
    //获取相对屏幕的位置
    UIWindow * window=[[[UIApplication sharedApplication] delegate] window];
    CGRect rect= [_settingItem convertRect: _settingItem.frame toView:window];
    
    [KxMenu showMenuInView:self.navigationController.view
                  fromRect:rect
                 menuItems:menuItems];
    
}

- (void)pushPasswordVC {
    
    CEPasscodeVC *passcodeVC = [[CEPasscodeVC alloc] init];
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:passcodeVC];
    [self presentViewController:nav animated:YES completion:nil];
}

- (void)pushUpdateVC {
    
    UIStoryboard *mainStoryBoard = [UIStoryboard storyboardWithName:@"OTAU" bundle:nil];
    [self presentViewController:[mainStoryBoard instantiateInitialViewController] animated:YES completion:nil];
    
    return;
    CEUpdateVC *updateVC = [[CEUpdateVC alloc] init];
    [self.navigationController pushViewController:updateVC animated:YES];
}

- (void)pushAboutVC {
    CEAboutVC *aboutVC = [[CEAboutVC alloc] init];
    [self.navigationController pushViewController:aboutVC animated:YES];
}

- (void)pushGetMoreLightsVC {
    CEMoreLightsVC *moreLightsVC = [[CEMoreLightsVC alloc] init];
    [self.navigationController pushViewController:moreLightsVC animated:YES];
}

- (void)pushSupportVC {
    CESupportVC *supportVC = [[CESupportVC alloc] init];
    [self.navigationController pushViewController:supportVC animated:YES];
}

- (void)pushShareVC {
    [[SharePlaceManager shareInstance] exportPlaceTo:self];
}

- (void)pushQAVC {
    CEQAVC *vc = [[CEQAVC alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}

#pragma mark - Other
- (void)dealloc {
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
