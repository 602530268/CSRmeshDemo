//
//  CELightsVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/18.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CELightsVC.h"
#import "CELightsTableViewCell.h"
#import "CEAddNewLightVC.h"
#import "CETemperatureVC.h"
#import "CEPasscodeVC.h"

#import "DeleteDeviceManager.h"
#import "DeviceDataHandle.h"
#import "DeviceStateManager.h"
#import "AlertControllerManager.h"
#import <objc/runtime.h>

static NSInteger additionalNum = 1; //加上一个Add new Light
static NSTimeInterval _checkTimeInterval = 3.0f;

@interface CELightsVC ()<UITableViewDataSource,UITableViewDelegate>
{
    NSMutableArray *_devices;   //设备列表
    NSMutableArray *_deleteDevices; //要删除的设备列表
    
    NSTimer *_checkDeviceStateTimer;    //定时查询设备状态，时间间隔为3s，不建议低于该值
    
    //这里是添加的需求，提示一个弹窗，短时间内一直显示
    UIView *_maskView;  //遮罩view，用于第一次安装时遮盖弹窗短时间不允许点击
    NSTimer *_maskTimer;    //遮罩时间
    id _alertAction1;
    id _alertAction2;
    BOOL _showMasked;   //记录已显示过
}

@property(nonatomic,strong) UITableView *lightsTableView;

@property (nonatomic) UIActivityIndicatorView *spinner;

@end

@implementation CELightsVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initData];
    [self createUI];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self registerNotification];
    [self refreshDevices];

    [self openCheckDeviceStateTimer];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    [self checkFirstInstall];
    [self checkAreaPassword];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [self stopCheckTimer];
}

#pragma mark - UI
- (void)createUI {
    [self createLightsTableView];
}

- (void)navUI {

}

- (void)createLightsTableView {
    _lightsTableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
    _lightsTableView.dataSource = self;
    _lightsTableView.delegate = self;
    _lightsTableView.backgroundColor = BaseBackgroundColor;
    _lightsTableView.separatorColor = [UIColor clearColor];
    _lightsTableView.rowHeight = 100.0f;
    _lightsTableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    [self.view addSubview:_lightsTableView];
    [_lightsTableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.left.right.bottom.equalTo(self.view);
    }];
    
    [_lightsTableView registerNib:[UINib nibWithNibName:NSStringFromClass([CELightsTableViewCell class]) bundle:[NSBundle mainBundle]] forCellReuseIdentifier:LightsTableViewCellIdentifier];
}

#pragma mark - Data
- (void)initData {
    _devices = @[].mutableCopy;
    _deleteDevices = @[].mutableCopy;
    
    [self refreshDevices];
}

- (void)registerNotification {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(didAssociateDeviceNotificationInListView:)
                                                 name:kCSRmeshManagerDidAssociateDeviceNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(didGetDeviceNotificationInListView:)
                                                 name:kCSRmeshManagerDidGetDeviceInfoNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(refreshDevices)
                                                 name:NSManagedObjectContextObjectsDidChangeNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(refreshDevicesForChangeHomePage:)
                                                 name:Notify_ChangeHomeSegment
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(refreshDevices)
                                                 name:Notify_UpdateOfExportFile
                                               object:nil];
}

- (void)removeNotification {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kCSRmeshManagerDidAssociateDeviceNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:kCSRmeshManagerDidGetDeviceInfoNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:Notify_UpdateOfExportFile object:nil];
}

#pragma mark - Interaction Event

#pragma mark - Trigger Event
- (void)refreshDevices {
    [_devices removeAllObjects];
    _devices = [[[CSRAppStateManager sharedInstance].selectedPlace.devices allObjects] mutableCopy];
    
    //排序
    if (_devices != nil && _devices.count != 0) {
        NSSortDescriptor *sort = [NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES];
        [_devices sortUsingDescriptors:@[sort]];
    }
    
    [self.lightsTableView reloadData];
    
    //当前设备为0时
    if (_hasNotDeviceCallback) {
        _hasNotDeviceCallback(_devices.count);
    }
    
}

//开启设备状态查询定时器
- (void)openCheckDeviceStateTimer {
    
    if (!_checkDeviceStateTimer) {
        _checkDeviceStateTimer = [NSTimer scheduledTimerWithTimeInterval:_checkTimeInterval target:self selector:@selector(checkDeviceStateLoop) userInfo:nil repeats:YES];
    }
}

//结束计时器
- (void)stopCheckTimer {
    if (_checkDeviceStateTimer) {
        [_checkDeviceStateTimer invalidate];
        _checkDeviceStateTimer = nil;
    }
}
//查询设备循环
- (void)checkDeviceStateLoop {
    
    //牛逼哄哄的线程锁
    @synchronized (self) {
        //先看距离上一次发送指令的时间和当前时间是否超过1s，小于的话就这次的发送就放弃了，防止命令满天飞导致其他问题
        NSDate *lastDate = [CommandManager shareInstance].lastSendOfDate;
        NSDate *currentDate = [NSDate date];
        if ([currentDate timeIntervalSince1970] - [lastDate timeIntervalSince1970] < 1) {
            NSLog(@"刚刚发送完数据，取消这一次的查询指令");
            return;
        }
        
        //将当前屏幕显示到的设备扔进查询管理器
        NSArray *visibleCells = _lightsTableView.visibleCells;
        NSMutableArray *deviceIds = @[].mutableCopy;
        for (CELightsTableViewCell *cell in visibleCells) {
            if (cell.selectDevice.deviceId) {
                [deviceIds addObject:cell.selectDevice.deviceId];
            }
        }
        
        [[DeviceStateManager shareInstance] checkDeviceStateWith:deviceIds block:^(NSNumber *devicId) {
            
            dispatch_async(dispatch_get_main_queue(), ^{
                
                NSDate *lastDate = [CommandManager shareInstance].lastSendOfDate;
                NSDate *currentDate = [NSDate date];
                if ([currentDate timeIntervalSince1970] - [lastDate timeIntervalSince1970] < 1) {
                    NSLog(@"刚刚发送完数据，取消这一次的接收指令");
                    return;
                }
                
                NSArray *currentVisibleCells = _lightsTableView.visibleCells;
                for (CELightsTableViewCell *cell in currentVisibleCells) {
                    if ([cell.selectDevice.deviceId isEqualToNumber:devicId]) {
                        [cell updateUI];
                        break;
                    }
                }
            });
            
        }];
    }
    
}

//判断是否第一次安装（现改为不点击不再提示的话每次都会弹出）
- (void)checkFirstInstall {
    if (_showMasked) {
        return;
    }
    _showMasked = YES;
    
    NSString *firstInstall = [[NSUserDefaults standardUserDefaults] valueForKey:UD_FirstInstall];
    if (firstInstall == nil) {
        
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil
                                                                                 message:@"Please reset all your lights manually (switch on and off 5 circles, 3 seconds interval)due to user experience improvement"
                                                                          preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *action1 = [UIAlertAction actionWithTitle:@"OK"
                                                          style:UIAlertActionStyleDefault
                                                        handler:^(UIAlertAction * _Nonnull action) {
                                                            [self checkAreaPassword];
                                                        }];
        
        UIAlertAction *action2 = [UIAlertAction actionWithTitle:@"Don't show again"
                                                          style:UIAlertActionStyleDefault
                                                        handler:^(UIAlertAction * _Nonnull action) {
                                                            [[NSUserDefaults standardUserDefaults] setValue:@"installed" forKey:UD_FirstInstall];
                                                            [[NSUserDefaults standardUserDefaults] synchronize];
                                                            
                                                            [self checkAreaPassword];
                                                        }];
        
        [action1 setValue:[UIColor lightGrayColor] forKey:@"titleTextColor"];
        [action2 setValue:[UIColor lightGrayColor] forKey:@"titleTextColor"];
        
        [alertController addAction:action1];
        [alertController addAction:action2];
        
        UIWindow *keyWindow = [UIApplication sharedApplication].keyWindow;
        _maskView = [[UIView alloc] initWithFrame:keyWindow.bounds];
        [keyWindow addSubview:_maskView];
        [self presentViewController:alertController animated:YES completion:nil];
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [_maskView removeFromSuperview];
        });
        
        _alertAction1 = action1;
        _alertAction2 = action2;
        if (!_maskTimer) {
            _maskTimer = [NSTimer scheduledTimerWithTimeInterval:1.0f target:self selector:@selector(firstInstallAlertEvent) userInfo:nil repeats:YES];
        }
    }
}


- (void)firstInstallAlertEvent {
    
    static int alertTime = 5;
    NSString *title1 = [NSString stringWithFormat:@"OK(%ds)",alertTime];
    [_alertAction1 setValue:title1 forKey:@"title"];
    
    if (alertTime <= 0) {
        [_alertAction1 setValue:@"OK" forKey:@"title"];
        
        UIColor *originColor = COLOR(21, 126, 251, 1.0f);;
        [_alertAction1 setValue:originColor forKey:@"titleTextColor"];
        [_alertAction2 setValue:originColor forKey:@"titleTextColor"];
        
        _alertAction1 = nil;
        _alertAction2 = nil;
        
        [_maskView removeFromSuperview];
        [_maskTimer invalidate];
        _maskTimer = nil;
    }
    
    alertTime--;
}

- (void)checkAreaPassword {
    //没有设置过组网密码时弹出
    NSString *passcode = [[NSUserDefaults standardUserDefaults] valueForKey:UD_Passcode];
    if (!passcode) {
        CEPasscodeVC *passcodeVC = [[CEPasscodeVC alloc] init];
        UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:passcodeVC];
        [self presentViewController:nav animated:YES completion:nil];
    }
}

#pragma mark - Notifications
- (void)didAssociateDeviceNotificationInListView:(NSNotification *)sender {
    NSLog(@"关联设备后收到通知");
    [self refreshDevices];
}

- (void)didGetDeviceNotificationInListView:(NSNotification *)sender {
    NSLog(@"获取设备通知");
    [self refreshDevices];
}

//首页切换页面时通知回调
- (void)refreshDevicesForChangeHomePage:(NSNotification *)sender {
    [self refreshDevices];
    
//    dispatch_async(dispatch_get_main_queue(), ^{
//        //当前页面不是lights时停止检查设备在线状态
//        if ([sender.userInfo[@"index"] integerValue] == 0) {
//            [self openCheckDeviceStateTimer];
//        }else {
//            [self stopCheckTimer];
//        }
//    });

}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (_devices.count == 0) {
        return 0;
    }
    return _devices.count + additionalNum;  
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    CELightsTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:LightsTableViewCellIdentifier forIndexPath:indexPath];
    cell.backgroundColor = BaseBackgroundColor;
    
    if (indexPath.row == _devices.count) {  //Add new light
        cell.titleLbl.text = @"Add new light";
        cell.detailLbl.text = @"";
        cell.notFindDevice = NO;
        cell.selectDevice = nil;
        cell.switchImgView.image = [UIImage imageNamed:@"add_new_light"];
        cell.switchImgView.userInteractionEnabled = NO;
        
    }else {
                
        CSRDeviceEntity *deviceEntity = _devices[indexPath.row];
        
        if (deviceEntity.name) {
            cell.titleLbl.text = deviceEntity.name;
        }
        
        if ([deviceEntity.appearance isEqualToNumber:@(CSRApperanceNameLight)]) {
            cell.detailLbl.text = @"not in range";
        }
        
//        cell.titleLbl.text = [UDManager getDeviceUUIDString:deviceEntity.deviceId];
        
        cell.selectDevice = [[CSRDevicesManager sharedInstance] getDeviceFromDeviceId:deviceEntity.deviceId];
        BOOL online = [UDManager getDeviceOnlingState:cell.selectDevice.deviceId];
        cell.notFindDevice = !online;
                
        if (!cell.notFindDevice) {
            cell.switchImgView.image = [DeviceDataHandle getImageWithDeviceId:deviceEntity.deviceId];
            cell.switchImgView.userInteractionEnabled = YES;
        }
                
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;        
    }
    
    return cell;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.row == _devices.count) {
        return UITableViewCellEditingStyleNone;
    }
    return UITableViewCellEditingStyleDelete;
}

//删除设备
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        
        CSRDeviceEntity *deviceEntity = _devices[indexPath.row];
        
        [AlertControllerManager alertWithTitle:@"Delete"
                                       message:[NSString stringWithFormat:@"Are you sure that you want to delete this device :%@?",deviceEntity.name]
                                         style:UIAlertControllerStyleAlert
                                  actionTitles:@[@"Cancel",
                                                 @"YES"]
                                  actionStyles:@[@(UIAlertActionStyleDefault),
                                                 @(UIAlertActionStyleDefault)]
                                        target:self
                                      handlers:^(NSInteger index) {
                                          if (index == 1) {
                                              
                                              [MBProgressHUDManager showWith:self];
                                              
                                              [[DeleteDeviceManager shareInstance] deleteDevice:deviceEntity
                                                                                        success:^{
                                                                                            CCLog(@"删除设备成功");
                                                                                            [self refreshDevices];
                                                                                            
                                                                                            [MBProgressHUDManager hideWith:self];
                                                                                        } fail:^{
                                                                                            [MBProgressHUDManager hideWith:self];
                                                                                        }];
                                          }
                                      }];
        

        
    }
}

#pragma mark - UITableViewDelegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (indexPath.row == _devices.count) {  //Add new light
        CEAddNewLightVC *addNewLightVC = [[CEAddNewLightVC alloc] init];
        [self.navigationController pushViewController:addNewLightVC animated:YES];
    }else {
        
        CELightsTableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
        if (cell.notFindDevice) {
            NSLog(@"没有找到该设备~");
            return;
        }
        
        CSRDeviceEntity *deviceEntity =  [_devices objectAtIndex:indexPath.row];
        CSRmeshDevice *selectDevice = [[CSRDevicesManager sharedInstance] getDeviceFromDeviceId:deviceEntity.deviceId];
        
        [[CSRDevicesManager sharedInstance] setSelectedDevice:selectDevice];
                
        CETemperatureVC *temperatureVC = [[CETemperatureVC alloc] init];
        temperatureVC.deviceEntity = deviceEntity;
        [self.navigationController pushViewController:temperatureVC animated:YES];
    }

}

#pragma mark - APIs (private)




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
