//
//  CESettingVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/23.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CESettingVC.h"
#import "CEAreaDetailVC.h"

#import "CEChangeNameView.h"

#import "AlertControllerManager.h"
#import "AreaDetailManager.h"
#import "DeleteDeviceManager.h"
#import "DeviceVersionHandle.h"

#define SettingTableViewCellIdentifier @"SettingTableViewCellIdentifier"

@interface CESettingVC ()<UITableViewDataSource,UITableViewDelegate>

@property(nonatomic,strong) UITableView *tableView;

@end

@implementation CESettingVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.

    [self initData];
    [self createUI];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [MBProgressHUD hideHUDForView:self.view animated:YES];
}

#pragma mark - UI
- (void)createUI {
    [self navUI];
    [self createTableView];
}

- (void)navUI {
    
    if (_belongArea) {
        self.title = @"Group Settings";
    }else {
        self.title = @"Light Settings";
    }
    
    WeakSelf(weakSelf)
    [self customBackBarBtnItemTo:^{
        [weakSelf.navigationController popViewControllerAnimated:YES];
    }];
}

- (void)createTableView {
    
    _tableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStyleGrouped];
    _tableView.dataSource = self;
    _tableView.delegate = self;
    [_tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:SettingTableViewCellIdentifier];
    [self.view addSubview:_tableView];
    [_tableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.view);
        make.size.equalTo(self.view);
    }];
}

#pragma mark - Data
- (void)initData {
    
}

#pragma mark - Interaction Event

#pragma mark - Trigger Event
//删除组网
- (void)deleteArea {
    
    if (!_belongArea) {
        return;
    }
    
    NSLog(@"删除组网");
    
    //提示框
    dispatch_async(dispatch_get_main_queue(), ^{
        [MBProgressHUD hideHUDForView:self.view animated:YES];
        
        MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        hud.bezelView.style = MBProgressHUDBackgroundStyleSolidColor;
        hud.bezelView.color = [[UIColor blackColor] colorWithAlphaComponent:0.8f];
        hud.activityIndicatorColor = [UIColor whiteColor];
    });
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.05 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [[AreaDetailManager shareInstance] deleteAreaWith:_areaEntity finish:^{
            [MBProgressHUD hideHUDForView:self.view animated:YES];
            [self.navigationController popToRootViewControllerAnimated:YES];
        }];
    });

    
}

//method to getIndexByValue
- (NSNumber *) getValueByIndex:(CSRDeviceEntity*)deviceEntity
{
    
    uint16_t *dataToModify = (uint16_t*)deviceEntity.groups.bytes;
    
    for (int count=0; count < deviceEntity.groups.length/2; count++, dataToModify++) {
        if (*dataToModify == [_areaEntity.areaID unsignedShortValue]) {
            return @(count);
            
        } else if (*dataToModify == 0){
            return @(count);
        }
    }
    
    return @(-1);
}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == 0) {
        return 2;
    }else if (section == 1) {
        return 1;
    }
    return 0;
}

/*
 Light setting和Group setting共用一套页面
 */
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:(UITableViewCellStyle)UITableViewCellStyleValue1 reuseIdentifier:SettingTableViewCellIdentifier];
    
    if (indexPath.section == 0) {
        
        if (_belongArea) {
            switch (indexPath.row) {
                case 0:
                    cell.textLabel.text = @"Group Name";
                    cell.detailTextLabel.text = _areaEntity.areaName;
                    break;
                case 1:
                    cell.textLabel.text = @"Grouped Lights";
                    cell.detailTextLabel.text = @"";
                    break;
                default:
                    break;
            }
            cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        }else {

            if (indexPath.row == 0) {
                
                cell.textLabel.text = @"Light Name";
                cell.detailTextLabel.text = _deviceEntity.name;
                cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
            }else if (indexPath.row == 1) {
                
                cell.textLabel.text = @"Version Info";
                cell.accessoryType = UITableViewCellAccessoryNone;
                
                [DeviceVersionHandle getDeviceVersionWith:_deviceEntity.deviceId
                                                   finish:^(NSString *version) {
                                                       cell.detailTextLabel.text = version;
                                                   }];
            }
        }

        
    }else if (indexPath.section == 1) {
        
        cell.textLabel.text = @"";
        cell.detailTextLabel.text = @"";
        cell.accessoryType = UITableViewCellAccessoryNone;
        
        //自定义label
        NSString *title = nil;
        if (_belongArea) {
            title = @"Delete Group";
        }else {
            title = @"Delete Light";
        }
        
        for (UIView *subView in cell.subviews) {
            if ([subView isKindOfClass:[UILabel class]]) {
                UILabel *label = (UILabel *)subView;
                if ([label.text isEqualToString:title]) {
                    return cell;
                }
            }
        }
        
        UILabel *label = [[UILabel alloc] init];
        label.text = title;
        label.textAlignment = NSTextAlignmentCenter;
        label.textColor = [UIColor redColor];
        [cell addSubview:label];
        [label mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.right.equalTo(cell);
            make.center.equalTo(cell);
        }];
    }
    
    return cell;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 2;
}

#pragma mark - UITableViewDelegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    if (indexPath.section == 0) {   //第一分区
        
        if (indexPath.row == 0) {   //第一行，修改名字
            
            //修改名字弹窗
            CEChangeNameView *changeNameView = [[CEChangeNameView alloc] initWithFrame:CGRectZero superView:self.view];
            [self.view addSubview:changeNameView];
            if (_belongArea) {
                changeNameView.textField.text = _areaEntity.areaName;
            }else {
                changeNameView.textField.text = _deviceEntity.name;
            }
            
            WeakSelf(weakSelf)
            changeNameView.newNameCallback = ^(NSString *name) {
                NSLog(@"new name: %@",name);
                
                if (_belongArea) {
                    weakSelf.areaEntity.areaName = name;
                }else {
                    weakSelf.deviceEntity.name = name;
                    CSRmeshDevice *device = [[CSRDevicesManager sharedInstance] getDeviceFromDeviceId:weakSelf.deviceEntity.deviceId];
                    device = [[CSRDevicesManager sharedInstance] getDeviceFromDeviceId:_deviceEntity.deviceId];
                    device.name = name;
                }
                
                [[CSRDatabaseManager sharedInstance] saveContext];
                [weakSelf.tableView reloadData];
            };
            
        }else if (indexPath.row == 1) {
            
            if (_belongArea) {  //第二行，组网设置
                CEAreaDetailVC *areaDetailVC = [[CEAreaDetailVC alloc] init];
                areaDetailVC.areaEntity = _areaEntity;
                [self.navigationController pushViewController:areaDetailVC animated:YES];
            }else {
                //硬件版本
            }

        }
        
    }else if (indexPath.section == 1) { //第二分区,移除设备/组网
        
        if (_belongArea) {
            [AlertControllerManager alertWithTitle:@"Warning"
                                           message:@"Remove Group:Are you sure?"
                                             style:UIAlertControllerStyleAlert
                                      actionTitles:@[@"YES",
                                                     @"NO"]
                                      actionStyles:@[@(UIAlertActionStyleDefault),
                                                     @(UIAlertActionStyleDefault)]
                                            target:self
                                          handlers:^(NSInteger index) {
                                              if (index == 0) {
                                                  [self deleteArea];
                                              }else if (index == 1) {
                                                  
                                              }
                                          }];
        }else {
            [AlertControllerManager alertWithTitle:@"Delete Device"
                                           message:[NSString stringWithFormat:@"Are you sure that you want to delete this device :%@?",_deviceEntity.name]
                                             style:UIAlertControllerStyleAlert
                                      actionTitles:@[@"Cancel",
                                                     @"YES"]
                                      actionStyles:@[@(UIAlertActionStyleDefault),
                                                     @(UIAlertActionStyleDefault)]
                                            target:self
                                          handlers:^(NSInteger index) {
                                              if (index == 1) {
                                                  
                                                  [MBProgressHUDManager showWith:self];
                                                  
                                                  [[DeleteDeviceManager shareInstance] deleteDevice:_deviceEntity
                                                                                            success:^{
                                                                                                NSLog(@"删除设备成功");
                                                                                                [MBProgressHUDManager hideWith:self];

                                                                                                [self.navigationController popToRootViewControllerAnimated:YES];

                                                                                            } fail:^{
                                                                                                [MBProgressHUDManager hideWith:self];
                                                                                            }];
                                              }
                                          }];
        }

    }
    
 
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
