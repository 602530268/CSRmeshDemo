//
//  CEPasscodeVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/26.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEPasscodeVC.h"
#import "ChangePasscodeView.h"
#import "AlertControllerManager.h"

@interface CEPasscodeVC ()
{
    NSString *_currentPasscode;
}

@property(nonatomic,strong) ChangePasscodeView *passcodeView;

@end

@implementation CEPasscodeVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initData];
    [self createUI];
}

#pragma mark - UI
- (void)createUI {
    
    self.view.backgroundColor = BaseNavColor;
    
    [self navUI];
    [self createPasscodeView];
}

- (void)navUI {
    self.title = @"change passcode";
    
    self.navigationController.navigationBar.translucent = NO;
    self.navigationController.navigationBar.barTintColor = BaseBackgroundColor;
    self.navigationController.navigationBar.titleTextAttributes = @{NSForegroundColorAttributeName:[UIColor whiteColor],
                                                                    NSFontAttributeName : [UIFont fontWithName:@"Montserrat-Regular" size:20]
                                                                    };
    self.navigationController.navigationBar.tintColor = [UIColor lightGrayColor];
    
    UIBarButtonItem *saveBarBtnItem = [[UIBarButtonItem alloc] initWithTitle:@"save" style:(UIBarButtonItemStylePlain) target:self action:@selector(saveBarBtnItemEvent)];
    self.navigationItem.rightBarButtonItem = saveBarBtnItem;
    
    WeakSelf(weakSelf)
    if (_currentPasscode) {
        [self customBackBarBtnItemTo:^{
            [weakSelf backBarBtnItemEvent];
        }];
    }

}

- (void)createPasscodeView {
    
    _passcodeView = [[ChangePasscodeView alloc] init];
    _passcodeView.backgroundColor = [UIColor clearColor];
    _passcodeView.passcode = nil;
    [self.view addSubview:_passcodeView];
    [_passcodeView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.top.equalTo(@(150));
        make.width.equalTo(self.view).multipliedBy(0.8);
        make.height.equalTo(@(120));
    }];
    
    if (_currentPasscode) {
        _passcodeView.passcode = _currentPasscode;
    }
}

#pragma mark - Data
- (void)initData {
    _currentPasscode = [[NSUserDefaults standardUserDefaults] valueForKey:UD_Passcode];
}

#pragma mark - Interaction Event
- (void)saveBarBtnItemEvent {
    NSLog(@"save");
    
    [[[UIApplication sharedApplication] keyWindow] endEditing:YES];
    
    if (_passcodeView.passcode.length == 4) {
        
        if (_currentPasscode) {

            [AlertControllerManager alertWithTitle:@"Change Password"
                                           message:@"Are you sure you want to reset your password?"
                                             style:UIAlertControllerStyleAlert
                                      actionTitles:@[@"YES",
                                                     @"NO"]
                                      actionStyles:@[@(UIAlertActionStyleDefault),
                                                     @(UIAlertActionStyleDefault)]
                                            target:self
                                          handlers:^(NSInteger index) {
                                              if (index == 0) {
                                                  _currentPasscode = _passcodeView.passcode;
                                                  [self savePasscode];
                                              }
                                          }];
        }else {
            _currentPasscode = _passcodeView.passcode;
            [self savePasscode];
        }
        
    }
}

- (void)savePasscode {
    
    CSRPlaceEntity *placeEntity = [NSEntityDescription insertNewObjectForEntityForName:@"CSRPlaceEntity"
                                                 inManagedObjectContext:[CSRDatabaseManager sharedInstance].managedObjectContext];
    placeEntity.passPhrase = _currentPasscode;
    
    CCLog(@"保存组网密码: %@",_passcodeView.passcode);
    
    //先保存密码
    [[NSUserDefaults standardUserDefaults] setValue:_passcodeView.passcode forKey:UD_Passcode];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    [[CSRDevicesManager sharedInstance] setNetworkPassPhrase:_passcodeView.passcode];   //当即修改组网密码
    [[CSRDatabaseManager sharedInstance] saveContext];  
    [[CSRAppStateManager sharedInstance] setupPlace];
    
    [self backBarBtnItemEvent];
}

- (void)backBarBtnItemEvent {
    
    [[[UIApplication sharedApplication] keyWindow] endEditing:YES];
    [self dismissViewControllerAnimated:YES completion:nil];
}

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
