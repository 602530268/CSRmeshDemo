//
//  CEAddNewLightVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/18.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEAddNewLightVC.h"

#import "CEBottomDetailView.h"
#import "CEAddNewLightTableViewCell.h"

#import "ConnectDeviceManager.h"
#import "CSRBluetoothLE.h"

#define UnAsscoistedHeaderText @"unsynced lights"
#define AsscoistedHeaderText @"synced lights"

@interface CEAddNewLightVC ()<UITableViewDataSource,UITableViewDelegate>
{
    NSMutableArray *_unAssociateds; //未连接设备
    NSMutableArray *_associateds;   //已连接设备
    NSMutableArray *_selectLights;  //选中设备
    
    NSTimer *_reloadTableTimer; //定时刷新计时器
    BOOL _updateRequired;
}

@property(nonatomic,strong) UIButton *scanBtn;
@property(nonatomic,strong) CEBottomDetailView *bottomDetailView;
@property(nonatomic,strong) UITableView *tableView;

@end

@implementation CEAddNewLightVC

#pragma mark - Life cycle
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initData];
    [self createUI];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

    //注册通知
    [self regisiterNotifycation];

    //开始扫描
    [self startScan];

    [self reloadTable];
}

- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];

    //删除扫描到的未连接的设备
    [[CSRDevicesManager sharedInstance] deleteDevicesInArray];

    //停止扫描
    [self stopScan];

    //移除监听
    [self removeNotifycation];
    
    //注销计时器
    [_reloadTableTimer invalidate];
    _reloadTableTimer = nil;
    
    [ConnectDeviceManager shareInstance].connecting = NO;
    [[ConnectDeviceManager shareInstance] cancelConnect];
}

#pragma mark - UI
- (void)createUI {
    
    self.view.backgroundColor = BaseBackgroundColor;
    [self navUI];
    [self createScanBtn];
    [self createBottomDetailView];
    [self createTableView];
    [self updateConnectBtnTitle];
}

- (void)navUI {
    self.title = @"Add new light";
    
    WeakSelf(weakSelf)
    [self customBackBarBtnItemTo:^{
        [weakSelf.navigationController popViewControllerAnimated:YES];
    }];
}

- (void)createScanBtn {
    _scanBtn = [[UIButton alloc] init];
    [_scanBtn setTitle:@"scan for lights" forState:UIControlStateNormal];
    [_scanBtn setTitleColor:[UIColor darkGrayColor] forState:UIControlStateNormal];
    [_scanBtn setTitleColor:[UIColor lightGrayColor] forState:UIControlStateHighlighted];
    _scanBtn.backgroundColor = [UIColor colorWithRed:229/255. green:143/255. blue:0/255. alpha:1.0];
    _scanBtn.layer.cornerRadius = 15.0f;
    _scanBtn.layer.masksToBounds = YES;
    [self.view addSubview:_scanBtn];
    [_scanBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.view);
        make.top.equalTo(self.view).offset(10 + StateBarAndNavBarHeight);
        make.width.equalTo(@160);
        make.height.equalTo(@30);
    }];
    [_scanBtn addTarget:self action:@selector(scanBtnEvent:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)createBottomDetailView {
    _bottomDetailView = [[CEBottomDetailView alloc] init];
    _bottomDetailView.backgroundColor = BaseNavColor;
    [self.view addSubview:_bottomDetailView];
    [_bottomDetailView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.left.right.equalTo(self.view);
        make.height.equalTo(self.view).multipliedBy(1.0/4.0);
    }];
    
    WeakSelf(weakSelf)
    _bottomDetailView.btnCallback = ^{
        [weakSelf stopScan];
        [weakSelf connectBtnEvent:nil];
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
        make.top.equalTo(_scanBtn.mas_bottom).offset(10);
        make.left.right.equalTo(self.view);
        make.bottom.equalTo(_bottomDetailView.mas_top);
    }];
}

#pragma mark - Data
- (void)initData {

    _unAssociateds = @[].mutableCopy;
    _associateds = [[[CSRAppStateManager sharedInstance].selectedPlace.devices allObjects] mutableCopy];
    _selectLights = @[].mutableCopy;
    
    _updateRequired = NO;
    
    if (!_reloadTableTimer) {
        _reloadTableTimer = [NSTimer scheduledTimerWithTimeInterval:2.0 target:self selector:@selector(reloadTableDataOnMainThread) userInfo:nil repeats:YES];
    }
}


- (void)regisiterNotifycation {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(didDiscoverDeviceNotification:)
                                                 name:kCSRmeshManagerDidDiscoverDeviceNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(didUpdateAppearanceNotification:)
                                                 name:kCSRmeshManagerDidUpdateAppearanceNotification
                                               object:nil];
}

- (void)removeNotifycation {
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kCSRmeshManagerDidDiscoverDeviceNotification
                                                  object:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kCSRmeshManagerDidUpdateAppearanceNotification
                                                  object:nil];
}

#pragma mark - Interaction Event
- (void)scanBtnEvent:(UIButton *)sender {
    [_selectLights removeAllObjects];
    [_unAssociateds removeAllObjects];
    [self updateConnectBtnTitle];
    [[CSRDevicesManager sharedInstance] deleteDevicesInArray];
    [self.tableView reloadData];
}

- (void)connectBtnEvent:(UIButton *)sender {
    
    self.bottomDetailView.connectBtn.enabled = NO;
    _scanBtn.enabled = NO;
    
    WeakSelf(weakSelf)
    [[ConnectDeviceManager shareInstance] connectDevices:_selectLights success:^(NSString *deviceName) {
//        NSLog(@"连接成功");
    } progress:^(NSString *deviceName, CGFloat progress) {
        NSString *detail = [NSString stringWithFormat:@"%@\nAssociating %.0f%%",deviceName,progress * 100];
        dispatch_async(dispatch_get_main_queue(), ^{
            weakSelf.bottomDetailView.connectDetailLabel.text = detail;
            weakSelf.bottomDetailView.progressView.progress = progress;
        });
    } fail:^(NSString *deviceName) {
        NSLog(@"连接失败");
    } finish:^{
//        NSLog(@"连接完成");
        
        //延迟1.0s等待coredata存储完成
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0f * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            NSMutableArray *copyUnassociateds = _unAssociateds.mutableCopy;
            for (CSRmeshDevice *device in copyUnassociateds) {
                if ([_selectLights containsObject:device]) {
                    [_unAssociateds removeObject:device];
                }
            }
            [_selectLights removeAllObjects];
            
            //删除扫描到的未连接的设备
            [[CSRDevicesManager sharedInstance] deleteDevicesInArray];
            
            dispatch_async(dispatch_get_main_queue(), ^{
                
                [weakSelf reloadTable];
                [weakSelf updateConnectBtnTitle];
                
                [weakSelf startScan];
                
                weakSelf.scanBtn.enabled = YES;
                weakSelf.bottomDetailView.connectBtn.enabled = YES;
            });
            
        });
    }];
}

#pragma mark - Trigger Event
- (void)startScan {
    [[CSRDevicesManager sharedInstance] setDeviceDiscoveryFilter:self mode:YES];
    [[CSRBluetoothLE sharedInstance] setScanner:YES source:self];
}

- (void)stopScan {
    [[CSRBluetoothLE sharedInstance]setScanner:NO source:self];
    [[CSRDevicesManager sharedInstance] setDeviceDiscoveryFilter:self mode:NO];
}

- (void)reloadTable {
    
    _unAssociateds = [[CSRDevicesManager sharedInstance] unassociatedMeshDevices].mutableCopy;
    _associateds = [[[CSRAppStateManager sharedInstance].selectedPlace.devices allObjects] mutableCopy];
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [_tableView reloadData];
    });
}

- (void)reloadTableDataOnMainThread {
    if (_updateRequired) {
        _updateRequired = NO;
        [self reloadTable];
    }
}

- (void)updateConnectBtnTitle {
    
    if (_selectLights.count) {
        _bottomDetailView.connectBtn.hidden = NO;
        _bottomDetailView.progressView.hidden = NO;
        _bottomDetailView.connectDetailLabel.hidden = NO;
        _bottomDetailView.tipLabel.hidden = YES;
        NSString *btnTitle = [NSString stringWithFormat:@"sync %ld light%@",_selectLights.count,_selectLights.count > 1 ? @"s":@""];
        [_bottomDetailView.connectBtn setTitle:btnTitle forState:UIControlStateNormal];
    }else {
        _bottomDetailView.connectBtn.hidden = YES;
        _bottomDetailView.progressView.hidden = YES;
        _bottomDetailView.connectDetailLabel.hidden = YES;
        _bottomDetailView.tipLabel.hidden = NO;
        _bottomDetailView.connectDetailLabel.text = @"Light\nAssociating 0%";
    }
}

#pragma mark - Notifications
- (void)didDiscoverDeviceNotification:(NSNotification *)sender {
    NSLog(@"搜索到设备");
    
    if (![self alreadyDiscoveredDeviceFilteringWithDeviceUUID:(NSUUID *)sender.userInfo[kDeviceUuidString]]) {
        [[CSRDevicesManager sharedInstance] addDeviceWithUUID:sender.userInfo [kDeviceUuidString] andRSSI:sender.userInfo [kDeviceRssiString]];
        
        [self reloadTable];
        
        NSLog(@"reloadTable");
        CCLog(@"解析时: %@",(NSUUID *)sender.userInfo[kDeviceUuidString]);
    }
    
    if ([[[CSRDevicesManager sharedInstance] unassociatedMeshDevices] count] > 0) {
        NSLog(@"搜索到的未连接设备数量: %ld",(unsigned long)[[[CSRDevicesManager sharedInstance] unassociatedMeshDevices] count]);
    }
}

- (void)didUpdateAppearanceNotification:(NSNotification *)sender {
    NSLog(@"更新设备Appearance信息");
    
    NSData *updatedDeviceHash = sender.userInfo [kDeviceHashString];
    NSNumber *appearanceValue = sender.userInfo [kAppearanceValueString];
    NSData *shortName = sender.userInfo [kShortNameString];
    if (![self alreadyDiscoveredDeviceFilteringWithDeviceHash:sender.userInfo[kDeviceHashString]]) {
        [[CSRDevicesManager sharedInstance] updateAppearance:updatedDeviceHash appearanceValue:appearanceValue shortName:shortName];
        [self reloadTable];
    }
    
    _updateRequired = YES;
}

#pragma mark - Device filtering
//根据device UUID过滤重复设备
- (BOOL)alreadyDiscoveredDeviceFilteringWithDeviceUUID:(NSUUID *)uuid
{
    for (id value in [[CSRDevicesManager sharedInstance] unassociatedMeshDevices]) {
        if ([value isKindOfClass:[CSRmeshDevice class]]) {
            CSRmeshDevice *device = value;
            if ([device.uuid.UUIDString isEqualToString:uuid.UUIDString]) {
                return YES;
            }
        }
    }
    
    return NO;
}

//根据device Hash值过滤重复设备
- (BOOL)alreadyDiscoveredDeviceFilteringWithDeviceHash:(NSData *)data
{
    for (id value in [[CSRDevicesManager sharedInstance] unassociatedMeshDevices]) {
        if ([value isKindOfClass:[CSRmeshDevice class]]) {
            CSRmeshDevice *device = value;
            if ([device.deviceHash isEqualToData:data]) {
                return YES;
            }
        }
    }
    
    return NO;
}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    UIView *headerView = [self tableView:tableView viewForHeaderInSection:section];
    UILabel *label = nil;
    for (UIView *subView in headerView.subviews) {
        if ([subView isKindOfClass:[UILabel class]]) {
            label = (UILabel *)subView;
            break;
        }
    }
    if (label && [label.text isEqualToString:UnAsscoistedHeaderText]) {
        return _unAssociateds.count;
    }else if (label && [label.text isEqualToString:AsscoistedHeaderText]){
        return _associateds.count;
    }
    
    return 0;
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    CEAddNewLightTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CEAddNewLightTableViewCellIdentifier forIndexPath:indexPath];
    cell.isSelect = NO;
        
    CSRmeshDevice *meshDevice = nil;
    
    if (indexPath.section == 0) {
        
        meshDevice = _unAssociateds[indexPath.row];
        CCLog(@"展示时: uuid: %@",meshDevice.uuid.UUIDString);
        
        if (meshDevice) {
            
            NSString *shortName = [CSRUtilities stringFromData:meshDevice.appearanceShortname];
            NSString *deviceName = [DeviceDataHandle getDeviceNameWith:shortName];
            
            if ([CSRUtilities isStringEmpty:deviceName]) {
                deviceName = @"have not name";
            }
            
            meshDevice.name = deviceName;
            cell.titleLbl.text = deviceName;
            
            if ([_selectLights containsObject:meshDevice]) {
                cell.isSelect = YES;
            }else {
                cell.isSelect = NO;
            }
        }
        
        cell.titleLbl.textColor = [UIColor whiteColor];
        cell.imgView.tintColor = [UIColor whiteColor];
    }else if (indexPath.section == 1) {
        meshDevice = _associateds[indexPath.row];
        cell.titleLbl.text = meshDevice.name;
        cell.isSelect = NO;
        
        cell.titleLbl.textColor = [UIColor lightGrayColor];
        cell.imgView.tintColor = [UIColor lightGrayColor];
        cell.imgView.image = [cell.imgView.image imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    }

    return cell;
}

//分区数
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {

    NSInteger numberOfSections = 0;
    if (_unAssociateds.count) {
        numberOfSections++;
    }
    if (_associateds.count) {
        numberOfSections++;
    }
    return 2;
}

#pragma mark - UITableViewDelegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    //正在连接时不允许选择
    if ([ConnectDeviceManager shareInstance].connecting) {
        return;
    }
    
    if (indexPath.section == 1) {
        return;
    }
    
    CEAddNewLightTableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    
    if (indexPath.section == 0) {
        
        CSRmeshDevice *selectDevice = _unAssociateds[indexPath.row];
        
        //添加/删除选中设备列表里的设备
        if ([_selectLights containsObject:selectDevice]) {
            [_selectLights removeObject:selectDevice];
            
            cell.isSelect = NO;
        }else {
            [_selectLights addObject:selectDevice];
            cell.isSelect = YES;
        }

        //如果是未连接设备，在点击的时候使其闪烁作为标记
        if (!selectDevice.isAssociated) {
            [[CSRDevicesManager sharedInstance] setAttentionPreAssociation:selectDevice.deviceHash attentionState:@(1) withDuration:@(3000)];
        }
    }
    
    [self updateConnectBtnTitle];
    NSLog(@"_selectLights: %@",_selectLights);
}

//行头高度
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    if (section == 0 && _unAssociateds.count > 0) {
        return 40.0f;
    }
    else if (section == 1 && _associateds.count > 0) {
        return 40.0f;
    }
    return 0.0f;
}

//行头视图
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
    
    if (section == 0 && _unAssociateds.count != 0) {
        label.text = UnAsscoistedHeaderText;
        return headerView;
    }else if (section == 0 && _unAssociateds.count == 0) {
        return nil;
    }
    
    if (section == 1 && _associateds.count != 0) {
        label.text = AsscoistedHeaderText;
        return headerView;
    }else if (section == 0 && _associateds.count == 0) {
        return nil;
    }
    
    return nil;
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
