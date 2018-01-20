//
//  CEAreasVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/18.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEAreasVC.h"
#import "CEAreasTableViewCell.h"
#import "CETemperatureVC.h"
#import "CEAreaDetailVC.h"

#import "DeviceStateManager.h"
#import "AlertControllerManager.h"
#import "DeleteDeviceManager.h"

static NSInteger additionalNum = 2; //加上一个All Light 和 Add new Light
static NSTimeInterval _checkTimeInterval = 3.0f;

@interface CEAreasVC ()<UITableViewDataSource,UITableViewDelegate>
{
    NSMutableArray *_areas;
    NSTimer *_checkDeviceStateTimer;    //定时查询设备状态，时间间隔为3s，不建议低于该值,在这里为查看灯组状态，只需要获取设备状态即可    
}

@property(nonatomic,strong) UITableView *areasTableView;

@end

@implementation CEAreasVC

#pragma mark - View Lifecycle
- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initData];
    [self createUI];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    _areas = @[].mutableCopy;
    
    [self refreshDevices];
    [self openCheckDeviceStateTimer];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [self removeNotification];
    [self stopCheckTimer];
}

- (void)refreshDevices {
    
    [_areas removeAllObjects];
    _areas = [[[CSRAppStateManager sharedInstance].selectedPlace.areas allObjects] mutableCopy];
    
    if (_areas != nil || [_areas count] != 0) {
        NSSortDescriptor *sort = [NSSortDescriptor sortDescriptorWithKey:@"areaName" ascending:YES]; //@"name"
        [_areas sortUsingDescriptors:[NSArray arrayWithObject:sort]];
    }
    
    [self.areasTableView reloadData];
    
}

#pragma mark - UI
- (void)createUI {
    [self createAreasTableView];
}

- (void)createAreasTableView {
    _areasTableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
    _areasTableView.dataSource = self;
    _areasTableView.delegate = self;
    _areasTableView.backgroundColor = BaseBackgroundColor;
    _areasTableView.separatorColor = [UIColor clearColor];
    _areasTableView.rowHeight = 100.0f;
    _areasTableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    [self.view addSubview:_areasTableView];
    [_areasTableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.left.right.bottom.equalTo(self.view);
    }];
    
    [_areasTableView registerNib:[UINib nibWithNibName:NSStringFromClass([CEAreasTableViewCell class]) bundle:[NSBundle mainBundle]] forCellReuseIdentifier:AreasTableViewCellIdentifier];
}

#pragma mark - Data
- (void)initData {
    
    [self registerNotify];
    
    _areas = [CSRDevicesManager sharedInstance].meshAreas.mutableCopy;
    NSLog(@"_areas = %@",_areas);
}

- (void)registerNotify {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(updateAreaDevicesInfo:) name:NSManagedObjectContextObjectsDidChangeNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(updateAreaDevicesInfo:)
                                                 name:Notify_ChangeHomeSegment
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(refreshDevices)
                                                 name:Notify_UpdateOfExportFile
                                               object:nil];
}

- (void)removeNotification {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NSManagedObjectContextObjectsDidChangeNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:Notify_ChangeHomeSegment object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:Notify_UpdateOfExportFile object:nil];
}

//更新组内灯的数量
- (void)updateAreaDevicesInfo:(NSNotification *)sender {
    
    dispatch_async(dispatch_get_main_queue(), ^{
        
        if ([sender.userInfo[@"index"] integerValue] == 1 || sender.userInfo == nil) {
            CCLog(@"更新组内灯的数量");
            [self refreshDevices];
        }
    });
    
}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _areas.count + additionalNum;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    CEAreasTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:AreasTableViewCellIdentifier forIndexPath:indexPath];
    
    if (indexPath.row == 0) {
        
        cell.titleLbl.text = @"All Lights";
        cell.detailLbl.text = [NSString stringWithFormat:@"%ld Devices",[CSRAppStateManager sharedInstance].selectedPlace.devices.count];
        cell.switchImgView.userInteractionEnabled = YES;
        cell.switchImgView.image = [DeviceDataHandle getImageWithDeviceId:@(0)];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.areaEntity = nil;
        cell.selectArea = nil;

    }else if (indexPath.row == _areas.count - 1 + additionalNum) {
        
        cell.titleLbl.text = @"Add new Group";
        cell.detailLbl.text = @"";
        
        cell.switchImgView.image = [UIImage imageNamed:@"add_new_light"];
        cell.switchImgView.userInteractionEnabled = NO;
        cell.areaEntity = nil;
        cell.selectArea = nil;

    }else {
        
        CSRAreaEntity *areaEntity = [_areas objectAtIndex:indexPath.row - 1];
        
        if (areaEntity.areaName != nil){
            cell.titleLbl.text = areaEntity.areaName;
        }
        if (areaEntity.devices && [areaEntity.devices count] > 1) {
            cell.detailLbl.text = [NSString stringWithFormat:@"%lu Devices", (unsigned long)[areaEntity.devices count]];
        }
        if ([areaEntity.devices count] == 1) {
            cell.detailLbl.text = [NSString stringWithFormat:@"%lu Device", (unsigned long)[areaEntity.devices count]];
        }
        if ([areaEntity.devices count] < 1) {
            cell.detailLbl.text = @"0 Devices";
        }
        
        cell.selectArea = [[CSRDevicesManager sharedInstance] getAreaFromId:areaEntity.areaID];
        cell.areaEntity = areaEntity;
        
        cell.switchImgView.userInteractionEnabled = YES;
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.switchImgView.image = [DeviceDataHandle getImageWithDeviceId:areaEntity.areaID];
    }
    
    if ([cell.titleLbl.text isEqualToString:@"Add new Group"]) {
        cell.switchImgView.image = [UIImage imageNamed:@"add_new_light"];
    }
    
    return cell;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
    //删除组网功能
    if (indexPath.row == 0) {
        return UITableViewCellEditingStyleDelete;
    }
    return UITableViewCellEditingStyleNone;
}

//删除设备
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        
        NSMutableArray *lights = nil;
        CSRAreaEntity *areaEntity = nil;
        NSString *message = @"Are you sure that you want to delete all the devices?";
        
        if (indexPath.row == 0) {
            lights = [CSRAppStateManager sharedInstance].selectedPlace.devices.allObjects.mutableCopy;
        }else {
            areaEntity = [_areas objectAtIndex:indexPath.row - 1];
            lights = areaEntity.devices.allObjects.mutableCopy;
            message = @"Remove Group:Are you sure?";
        }
        
        [AlertControllerManager alertWithTitle:@"Delete"
                                       message:message
                                         style:UIAlertControllerStyleAlert
                                  actionTitles:@[@"Cancel",
                                                 @"YES"]
                                  actionStyles:@[@(UIAlertActionStyleDefault),
                                                 @(UIAlertActionStyleDefault)]
                                        target:self
                                      handlers:^(NSInteger index) {
                                          if (index == 1) {
                                              
                                              [MBProgressHUDManager showWith:self];

                                              [[DeleteDeviceManager shareInstance] deleteMoreLights:lights areaEntity:areaEntity finish:^{
                                                  [MBProgressHUDManager hideWith:self];
                                                  [self refreshDevices];
                                              }];
                                                    
                                          }
                                      }];
    }
}

#pragma mark - UITableViewDelegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    CSRAreaEntity *areaEntity = nil;
    
    if (indexPath.row == _areas.count - 1 + additionalNum) {
        NSLog(@"创建新组");
        
        CEAreaDetailVC *detailVC = [[CEAreaDetailVC alloc] init];
        [self.navigationController pushViewController:detailVC animated:YES];
    }else {

        if (indexPath.row == 0) {
            NSLog(@"All Lihgts页面");
        }else {
            areaEntity = _areas[indexPath.row - 1];
        }

        if (areaEntity.devices.count == 0 && indexPath.row != 0) {
            NSLog(@"该组设备为0");
        }

        CSRmeshArea *area = [[CSRDevicesManager sharedInstance] getAreaFromId:areaEntity.areaID];

        [[CSRDevicesManager sharedInstance] setSelectedArea:area];
        [[CSRDevicesManager sharedInstance] setSelectedDevice:area.areaDevice];

        CETemperatureVC *temperaturVC = [[CETemperatureVC alloc] init];
        temperaturVC.belongArea = YES;
        temperaturVC.areaEntity = areaEntity;
        [self.navigationController pushViewController:temperaturVC animated:YES];
    }

}

#pragma mark - Trigger Event
//method to getIndexByValue
- (NSNumber *) getValueByIndex:(CSRDeviceEntity*)deviceEntity areaEntity:(CSRAreaEntity *)areaEntity
{
    
    uint16_t *dataToModify = (uint16_t*)deviceEntity.groups.bytes;
    
    for (int count=0; count < deviceEntity.groups.length/2; count++, dataToModify++) {
        if (*dataToModify == [areaEntity.areaID unsignedShortValue]) {
            return @(count);
            
        } else if (*dataToModify == 0){
            return @(count);
        }
    }
    
    return @(-1);
}

//开启设备状态查询定时器
- (void)openCheckDeviceStateTimer {
    
    return;
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
        
        //获取当前设备组里的一个灯，将其状态赋予给灯组，会有不精确的情况，将就
        NSArray *visibleCells = _areasTableView.visibleCells;
        NSMutableArray *areas = @[].mutableCopy;
        for (CEAreasTableViewCell *cell in visibleCells) {
            if (cell.areaEntity != nil) {
                [areas addObject:cell.areaEntity];
            }
        }
        
        [[DeviceStateManager shareInstance] checkAreaStateWith:areas block:^(NSNumber *areaId) {
           
            dispatch_async(dispatch_get_main_queue(), ^{
                
                NSDate *lastDate = [CommandManager shareInstance].lastSendOfDate;
                NSDate *currentDate = [NSDate date];
                if ([currentDate timeIntervalSince1970] - [lastDate timeIntervalSince1970] < 1) {
                    NSLog(@"刚刚发送完数据，取消这一次的接收指令");
                    return;
                }
                
                NSArray *currentVisibleCells = visibleCells;
                for (CEAreasTableViewCell *cell in currentVisibleCells) {
                    if ([cell.areaEntity.areaID isEqualToNumber:areaId]) {
                        [cell updateUI];
                        break;
                    }
                }
            });
        }];
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
