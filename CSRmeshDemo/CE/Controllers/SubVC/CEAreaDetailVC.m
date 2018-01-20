//
//  CEAreaDetailVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/23.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEAreaDetailVC.h"
#import "CEBottomDetailView.h"
#import "CEAddNewLightTableViewCell.h"
#import "ColorBottomView.h"

#import "AreaDetailManager.h"
#import "AlertControllerManager.h"

#define GroupName @"gourp"
#define UnGroupedHeaderText @"ungrouped lights"
#define GroupedHeaderText @"already grouped lights"

@interface CEAreaDetailVC ()<UITableViewDataSource,UITableViewDelegate>
{
    NSMutableArray *_defaultDevices;    //该组网默认设备
    NSMutableArray *_unGroupedDevices;   //未组网设备
    NSMutableArray *_alreadyGroupedDevices; //已组网设备
    NSMutableArray *_deleteAlreadyGroupedDevices;   //已有组网，但是需要移除出去的设备
    NSMutableArray *_editDeleteAlreadyGroupedDevices;   //同_deleteAlreadyGroupedDevices，但是当用户又取消了该设备的选取，就不需要操作这个设备
    NSMutableArray *_flashDevices;  //点击后闪烁过的设备，用于恢复原来显示状态
    
    __block NSMutableArray *_theAddArr;    //需要添加组网的设备
    __block NSMutableArray *_theDeleteArr;  //需要删除组网的设备
}

@property(nonatomic,strong) CEBottomDetailView *bottomDetailView;
@property(nonatomic,strong) UITableView *tableView;

@end

@implementation CEAreaDetailVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initData];
    [self createUI];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self checkAreaEntity];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [MBProgressHUD hideHUDForView:self.navigationController.view animated:YES];
    [self recoverChooseLights:_flashDevices];

}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
}

#pragma mark - UI
- (void)createUI {
    
    [self navUI];
    [self createBottomDetailView];
    [self createTableView];
}

- (void)navUI {
    
    if (_areaEntity) {
        self.title = @"midify group";
    }else {
        self.title = @"create new group";
    }
    
    WeakSelf(weakSelf)
    [self customBackBarBtnItemTo:^{
        [weakSelf.navigationController popViewControllerAnimated:YES];
    }];
}

- (void)createBottomDetailView {
    _bottomDetailView = [[CEBottomDetailView alloc] init];
    _bottomDetailView.backgroundColor = BaseNavColor;
    [self.view addSubview:_bottomDetailView];
    [_bottomDetailView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.left.right.equalTo(self.view);
        make.height.equalTo(self.view).multipliedBy(1.0/4.0);
    }];
    
    _bottomDetailView.tipLabel.text = @"select multiple lights to\nassign them to a group";
    _bottomDetailView.connectDetailLabel.hidden = YES;
    _bottomDetailView.progressView.hidden = YES;
    _bottomDetailView.connectBtn.hidden = YES;
    
    WeakSelf(weakSelf)
    __weak NSMutableArray *addArr = _theAddArr;
    __weak NSMutableArray *deleteArr = _theDeleteArr;
    __weak NSMutableArray *editDeleteAlreadyGroupedDevices = _editDeleteAlreadyGroupedDevices;
    _bottomDetailView.btnCallback = ^{
        
        //提示框
        dispatch_async(dispatch_get_main_queue(), ^{
            [MBProgressHUD hideHUDForView:weakSelf.navigationController.view animated:YES];
            
            MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:weakSelf.navigationController.view animated:YES];
            hud.bezelView.style = MBProgressHUDBackgroundStyleSolidColor;
            hud.bezelView.color = [[UIColor blackColor] colorWithAlphaComponent:0.8f];
            hud.activityIndicatorColor = [UIColor whiteColor];
//            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3.8f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//                [MBProgressHUD hideHUDForView:weakSelf.navigationController.view animated:YES];
//            });
        });
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.05f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            NSLog(@"addArr: %@",addArr);
            NSLog(@"deleteArr: %@",deleteArr);
            NSLog(@"editDeleteAlreadyGroupedDevices: %ld",editDeleteAlreadyGroupedDevices.count);
            NSLog(@"areaEntity: %@",weakSelf.areaEntity);
            
            weakSelf.bottomDetailView.connectBtn.enabled = NO;
            
            //先移除原有组网
            for (CSRDeviceEntity *deviceEntity in editDeleteAlreadyGroupedDevices) {
                
                CSRAreaEntity *areaEntity = deviceEntity.areas.allObjects.firstObject;
                if (areaEntity) {
                    [[AreaDetailManager shareInstance] editDeviceWith:deviceEntity
                                                           areaEntity:areaEntity
                                                               finish:nil];
                }
            }
            
            [NSThread sleepForTimeInterval:0.5f];
            
            [[AreaDetailManager shareInstance] editAreaWith:weakSelf.areaEntity
                                                theAddArray:addArr
                                             theDeleteArray:deleteArr
                                                     finish:^{
                                                         
                                                         [weakSelf.navigationController popViewControllerAnimated:YES];
                                                     }];
        });

        
    };
    
}

- (void)createTableView {
    _tableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
    _tableView.dataSource = self;
    _tableView.delegate = self;
    _tableView.rowHeight = 60.0f;
    _tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    _tableView.backgroundColor = [UIColor clearColor];
    _tableView.separatorColor = [UIColor clearColor];
    [self.view addSubview:_tableView];
    [_tableView registerNib:[UINib nibWithNibName:NSStringFromClass([CEAddNewLightTableViewCell class]) bundle:[NSBundle mainBundle]] forCellReuseIdentifier:CEAddNewLightTableViewCellIdentifier];
    [_tableView mas_makeConstraints:^(MASConstraintMaker *make) {
        
        make.top.equalTo(self.view).offset(StateBarAndNavBarHeight);
        make.left.right.equalTo(self.view);
        make.bottom.equalTo(_bottomDetailView.mas_top);
    }];
    
}


#pragma mark - Data
- (void)initData {
    
    _defaultDevices = @[].mutableCopy;
    _unGroupedDevices = @[].mutableCopy;
    _alreadyGroupedDevices = @[].mutableCopy;
    _deleteAlreadyGroupedDevices = @[].mutableCopy;
    _editDeleteAlreadyGroupedDevices = @[].mutableCopy;
    _flashDevices = @[].mutableCopy;
    
    _theAddArr = @[].mutableCopy;
    _theDeleteArr = @[].mutableCopy;
    
    //默认设备
    NSSet *alreadyPresentDevicesSet = _areaEntity.devices;
    for (CSRDeviceEntity *deviceObj in alreadyPresentDevicesSet) {
        [_defaultDevices addObject:deviceObj];
    }
    
    NSMutableArray *allDevices = [[CSRAppStateManager sharedInstance].selectedPlace.devices allObjects].mutableCopy;
    for (CSRDeviceEntity *deviceEntity in allDevices) {
        
        if (deviceEntity.areas.count) {
            NSLog(@"该设备已被添加进组");
            [_alreadyGroupedDevices addObject:deviceEntity];
        }else {
            NSLog(@"该设备尚未被组网");
            [_unGroupedDevices addObject:deviceEntity];
        }
    }
    
    //分配到当前组的灯不会显示在已分配栏里
    for (CSRDeviceEntity *deviceEntity in _defaultDevices) {
        if ([_alreadyGroupedDevices containsObject:deviceEntity]) {
            [_alreadyGroupedDevices removeObject:deviceEntity];
        }
    }
    
    [_tableView reloadData];
}

//查看改组网是否存在
- (void)checkAreaEntity {

    if (!_areaEntity) {
        
        //获取最新的组名
        NSNumber *areaIdNumber = [[CSRDatabaseManager sharedInstance] getNextFreeIDOfType:@"CSRAreaEntity"];
        NSString *areaName = [NSString stringWithFormat:@"Group %d", [areaIdNumber intValue]];

        _areaEntity = [[CSRDevicesManager sharedInstance] addMeshArea:areaName];
        [[CSRAppStateManager sharedInstance].selectedPlace addAreasObject:_areaEntity];
    }
}

#pragma mark - Interaction Event

#pragma mark - Trigger Event
- (void)updateBottomView {
    
    if (_theAddArr.count || _theDeleteArr.count) {
        _bottomDetailView.tipLabel.text = @"selected lights\nshoule be blinking";
        _bottomDetailView.connectBtn.hidden = NO;
    }else {
        _bottomDetailView.tipLabel.text = @"select multiple lights to\nassign them to a group";
        _bottomDetailView.connectBtn.hidden = YES;
    }
    
    NSString *plural = (_theAddArr.count + _theDeleteArr.count) > 1 ? @"s" : @"";
    NSString *title = [NSString stringWithFormat:@"group %ld light%@",_theAddArr.count + _theDeleteArr.count,plural];
    [_bottomDetailView.connectBtn setTitle:title forState:UIControlStateNormal];
}

//恢复用来组网的灯的状态
- (void)recoverChooseLights:(NSMutableArray *)lights {
    
    CSRmeshDevice *meshDevice = [CSRDevicesManager sharedInstance].selectedDevice;
    
    for (NSNumber *deviceId in lights) {
        DeviceType type = [UDManager getDeviceTypeWith:deviceId];
        CSRmeshDevice *meshDevice = [[CSRDevicesManager sharedInstance] getDeviceFromDeviceId:deviceId];
        [[CSRDevicesManager sharedInstance] setSelectedDevice:meshDevice];
        [CommandManager shareInstance].canSend = YES;
        
        if (type == DeviceTypeTemperature) {
            NSInteger temperature = [UDManager getTemperatureWith:deviceId];
            [[CommandManager shareInstance] sendTemperature:temperature];
        }else {
            NSInteger index = [UDManager getRGBIndexWith:deviceId];
            if (index != -1) {
                NSDictionary *rgbInfo = [[ColorBottomView new] getRgbInfoWith:index];
                [[CommandManager shareInstance] sendRGBCommandWithRGBInfo:rgbInfo];
            }            
        }
    }
    
    [[CSRDevicesManager sharedInstance] setSelectedDevice:meshDevice];
}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    UIView *headerView = [self tableView:tableView viewForHeaderInSection:section];
    UILabel *label = [self getFirstSubLabelWith:headerView];
    
    //根据行头文本来分类，避免错乱
    if (label && [label.text isEqualToString:_areaEntity.areaName]) {
        return _defaultDevices.count;
    }else if (label && [label.text isEqualToString:UnGroupedHeaderText]) {
        return _unGroupedDevices.count;
    }else if (label && [label.text isEqualToString:GroupedHeaderText]){
        return _alreadyGroupedDevices.count;
    }
    
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    CEAddNewLightTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CEAddNewLightTableViewCellIdentifier forIndexPath:indexPath];
    
    CSRDeviceEntity *deviceEntity = nil;
    
    if (indexPath.section == 0) {
        deviceEntity = _defaultDevices[indexPath.row];
        cell.isSelect = YES;
        cell.notChoose = NO;
        
        if ([_deleteAlreadyGroupedDevices containsObject:deviceEntity]) {   //从其他组网内的设备中取过来的
            
            if ([_theAddArr containsObject:deviceEntity.deviceId]) {
                cell.isSelect = YES;
            }else {
                cell.isSelect = NO;
            }
        }else { //默认设备
            if ([_theDeleteArr containsObject:deviceEntity.deviceId]) {
                cell.isSelect = NO;
            }else {
                cell.isSelect = YES;
            }
        }
        
    }else if (indexPath.section == 1) {
        deviceEntity = _unGroupedDevices[indexPath.row];
        cell.notChoose = NO;
        if ([_theAddArr containsObject:deviceEntity.deviceId]) {
            cell.isSelect = YES;
        }else {
            cell.isSelect = NO;
        }
    }else if (indexPath.section == 2) {
        deviceEntity = _alreadyGroupedDevices[indexPath.row];
        cell.isSelect = NO;
        cell.notChoose = YES;
    }
    
    if (deviceEntity) {
        
        if (deviceEntity.name != nil) {
            cell.titleLbl.text = deviceEntity.name;
        } else {
            cell.titleLbl.text = [NSString stringWithFormat:@"device %ld", (long)indexPath.row];
        }
        
    }
    
    return cell;
}

/*
     一分区为该组网已有设备
     二分区为未组网设备
     三分区为所有已组网设备
 */
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {    
    return 3;
}

#pragma mark - UITableViewDelegate
/*
 创建组网页面:
     所有未被组网的设备，可添加进该组网
 修改组网页面:
     所有未被组网的设备，可添加进该组网
     改组网内的设备，可移除出该组网
 */
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    CEAddNewLightTableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    
    UIView *headerView = [self tableView:tableView viewForHeaderInSection:indexPath.section];
    UILabel *label = [self getFirstSubLabelWith:headerView];
    
    CSRDeviceEntity *deviceEntity = nil;
    
    if (label && [label.text isEqualToString:_areaEntity.areaName]) {   //该组网内的设备，可选择移除
        deviceEntity = _defaultDevices[indexPath.row];
        
        if ([_deleteAlreadyGroupedDevices containsObject:deviceEntity]) {   //从其他组网内的设备中取过来的
            
            if ([_editDeleteAlreadyGroupedDevices containsObject:deviceEntity]) {
                [_editDeleteAlreadyGroupedDevices removeObject:deviceEntity];
                cell.isSelect = NO;

                if ([_theAddArr containsObject:deviceEntity.deviceId]) {
                    [_theAddArr removeObject:deviceEntity.deviceId];
                }
            }else {
                [_editDeleteAlreadyGroupedDevices addObject:deviceEntity];
                cell.isSelect = YES;

                if (![_theAddArr containsObject:deviceEntity.deviceId]) {
                    [_theAddArr addObject:deviceEntity.deviceId];
                }
            }
        }else { //默认设备
            if (![_theDeleteArr containsObject:deviceEntity.deviceId]) {
                [_theDeleteArr addObject:deviceEntity.deviceId];
                cell.isSelect = NO;
            }else {
                [_theDeleteArr removeObject:deviceEntity.deviceId];
                cell.isSelect = YES;
            }
        }

    }else if (label && [label.text isEqualToString:UnGroupedHeaderText]) {  //未组网设备，可选择添加
        deviceEntity = _unGroupedDevices[indexPath.row];

        if (![_theAddArr containsObject:deviceEntity.deviceId]) {
            [_theAddArr addObject:deviceEntity.deviceId];
            cell.isSelect = YES;
            
            //使该灯闪烁以标记
            [[AttentionModelApi sharedInstance] setState:deviceEntity.deviceId attractAttention:YES duration:@(3000) success:nil failure:nil];
            
            if (![_flashDevices containsObject:deviceEntity.deviceId]) {
                [_flashDevices addObject:deviceEntity.deviceId];
            }
        }else {
            [_theAddArr removeObject:deviceEntity.deviceId];
            cell.isSelect = NO;
        }
    }else if (label && [label.text isEqualToString:GroupedHeaderText]){ //已被组网的设备，可以选择移除
        deviceEntity = _alreadyGroupedDevices[indexPath.row];
        
        NSString *title = [NSString stringWithFormat:@"Selecting Light %@",deviceEntity.name];
        NSString *message = [NSString stringWithFormat:@"Adding this light to the group will\ncause it to be removed from the\nexisting group %@",_areaEntity.areaName];
        [AlertControllerManager alertWithTitle:title
                                       message:message
                                         style:UIAlertControllerStyleAlert
                                  actionTitles:@[@"Cancel",
                                                 @"Continue"]
                                  actionStyles:@[@(UIAlertActionStyleDefault),
                                                 @(UIAlertActionStyleDefault)]
                                        target:self
                                      handlers:^(NSInteger index) {
                                          if (index == 1) {
                                              
                                              //将该灯移除已连接设备，添加到当前已连接设备中
                                              if ([_alreadyGroupedDevices containsObject:deviceEntity]) {
                                                  [_alreadyGroupedDevices removeObject:deviceEntity];
                                              }
                                              
                                              [_defaultDevices addObject:deviceEntity];
                                              
                                              [_deleteAlreadyGroupedDevices addObject:deviceEntity];
                                              [_editDeleteAlreadyGroupedDevices addObject:deviceEntity];
                                              
                                              if (![_theAddArr containsObject:deviceEntity.deviceId]) {
                                                  [_theAddArr addObject:deviceEntity.deviceId];
                                              }
                                              
                                              [self.tableView reloadData];
                                              [self updateBottomView];
                                          }
                                      }];
    }
    
    [self updateBottomView];
}

//行头高度
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    
    float height = 40.0f;
    if (section == 0 && _defaultDevices.count != 0) {
        return height;
    }else if (section == 1 && _unGroupedDevices.count != 0) {
        return height;
    }else if (section == 2 && _alreadyGroupedDevices.count != 0) {
        return height;
    }
    return 0;
}

//行头视图,因为该函数执行顺序早于cellForRowAtIndexPath,所以这里做复杂判断，其他方法根据行头文本处理即可
- (nullable UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    UIView *headerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, CGRectGetWidth(tableView.frame), 40)];
    headerView.backgroundColor = [UIColor whiteColor];
    UILabel *label = [[UILabel alloc] init];
    label.textColor = [UIColor colorWithRed:72/255. green:79/255. blue:96/255. alpha:1.0];
    label.textAlignment = NSTextAlignmentCenter;
    [headerView addSubview:label];
    [label mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(headerView);
    }];
    
    if (section == 0) {
        label.text = _areaEntity.areaName;
        return headerView;
    }else if (section == 1) {
        label.text = UnGroupedHeaderText;
        return headerView;
    }else if (section == 2) {
        label.text = GroupedHeaderText;
        label.textColor = [UIColor lightGrayColor];
        return headerView;
    }
    
    return nil;
}

#pragma mark - APIs(private)
//获取第一个label子控件
- (UILabel *)getFirstSubLabelWith:(UIView *)view {
    UILabel *label = nil;
    for (UIView *subView in view.subviews) {
        if ([subView isKindOfClass:[UILabel class]]) {
            label = (UILabel *)subView;
            break;
        }
    }
    return label;
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
