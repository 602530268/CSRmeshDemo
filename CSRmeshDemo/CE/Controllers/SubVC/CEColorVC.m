//
//  CEColorVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/8/15.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CEColorVC.h"
#import "CESettingVC.h"

#import "TemperatureTopAreaView.h"
#import "TemperatureTopLightView.h"
#import "ColorMiddleView.h"
#import "ColorBottomView.h"

#import "DeviceStateManager.h"
#import "MingleManager.h"

static NSTimeInterval checkTimeInterval = 3.0f;

@interface CEColorVC ()
{
    NSTimer *_checkDeviceStateTimer;    //定时查询设备状态，时间间隔为3s，不建议低于该值
    NSTimer *_checkPowerConsumptionTimer;   //查询耗电量
    BOOL _currentPower;
}

@property(nonatomic,assign) BOOL isAllLights;

@property(nonatomic,strong) CSRmeshDevice *selectDevice;
@property(nonatomic,strong) CSRmeshArea *selectArea;

@property(nonatomic,strong) TemperatureTopLightView *colorTopLightView;
@property(nonatomic,strong) TemperatureTopAreaView *colorTopAreaView;
@property(nonatomic,strong) ColorMiddleView *colorMiddleView;
@property(nonatomic,strong) ColorBottomView *colorBottomView;

@end

@implementation CEColorVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self initData];
    [self createUI];
    [self controlsEventCallback];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    [self updateControlsUI];
    
    if (!_belongArea) {
        [self openCheckDeviceStateTimer];
        [self registerNotify];
        
        //查询一次耗电量
//        [[CommandManager shareInstance] inquirePowerRate];
    }
    
    if (_colorBottomView.rgbInfo) {
        [CommandManager shareInstance].rgbInfo = _colorBottomView.rgbInfo;
    }
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    if (!_belongArea) {
        [self stopCheckTimer];
    }
    
    [self removeNotify];
}

#pragma mark - UI
- (void)createUI {
    
    self.view.backgroundColor = BaseBackgroundColor;

    [self navUI];
    [self createColorView];
}

- (void)navUI {
    
    UIImageView *titleView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"CE_brand"]];
    titleView.contentMode = UIViewContentModeScaleAspectFit;
    self.navigationItem.titleView = titleView;
    
    WeakSelf(weakSelf)
    [self customBackBarBtnItemTo:^{
        [weakSelf.navigationController popViewControllerAnimated:YES];
    }];
    
    //all lights下不显示设置按钮
    if (_isAllLights) {
        return;
    }
    
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
    }
}

- (void)createColorView {
    
    UIView *topView = nil;
    
    //UI大致相同，就和TemperatureVC共用一个topView
    
    if (_belongArea) {
        _colorTopAreaView = [[[NSBundle mainBundle] loadNibNamed:NSStringFromClass([TemperatureTopAreaView class]) owner:self options:nil] objectAtIndex:0];
        [self.view addSubview:_colorTopAreaView];
        [_colorTopAreaView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.view).offset(StateBarAndNavBarHeight);
            make.left.right.equalTo(self.view);
            make.height.equalTo(@(ScreenViewHeight * 0.33));
        }];
        _colorTopAreaView.rightArrowImgView.hidden = YES;
        topView = _colorTopAreaView;
        
    }else {
        _colorTopLightView = [[[NSBundle mainBundle] loadNibNamed:NSStringFromClass([TemperatureTopLightView class]) owner:self options:nil] objectAtIndex:0];
        [self.view addSubview:_colorTopLightView];
        [_colorTopLightView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.view).offset(StateBarAndNavBarHeight);
            make.left.right.equalTo(self.view);
            make.height.equalTo(@(ScreenViewHeight * 0.33));
        }];
        _colorTopLightView.rightArrowImgView.hidden = YES;
        
        topView = _colorTopLightView;
    }
    
    _colorMiddleView = [[[NSBundle mainBundle] loadNibNamed:NSStringFromClass([ColorMiddleView class]) owner:self options:nil] objectAtIndex:0];
    [self.view addSubview:_colorMiddleView];
    [_colorMiddleView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(topView.mas_bottom);
        make.left.right.equalTo(self.view);
//        make.height.equalTo(@(ScreenViewHeight * 0.23));
        make.height.equalTo(@(ScreenViewHeight * 0.33));
    }];
    
    _colorBottomView = [[[NSBundle mainBundle] loadNibNamed:NSStringFromClass([ColorBottomView class]) owner:self options:nil] objectAtIndex:0];
    [self.view addSubview:_colorBottomView];
    [_colorBottomView mas_makeConstraints:^(MASConstraintMaker *make) {
//        make.top.equalTo(_colorMiddleView.mas_bottom);
        make.left.right.bottom.equalTo(self.view);
        make.height.equalTo(@(ScreenViewHeight * 0.42));
    }];
}


#pragma mark - Data
- (void)initData {
    
    _isAllLights = NO;
    
    _selectDevice = [CSRDevicesManager sharedInstance].selectedDevice;
    _selectArea = [CSRDevicesManager sharedInstance].selectedArea;
    
    if (!_selectArea && !_selectDevice) {
        NSLog(@"belong All Lights");
        _isAllLights = YES;
    }
}

- (void)registerNotify {
    
    //接收到耗电量数据
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receivePowerConsumptionData:) name:Notify_ReceivePowerConsumptionData object:nil];
}

- (void)removeNotify {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

# pragma mark - Notify
- (void)receivePowerConsumptionData:(NSNotification *)sender {
    
    NSDictionary *dataInfo = sender.userInfo;
    
    NSDictionary *info = [DeviceDataHandle handlePowerConsumptionAndOtherWith:_selectDevice.deviceId data:dataInfo[@"info"] type:DeviceTypeRGB];
    
    if (![info.allKeys containsObject:@"watt"] ||
        ![info.allKeys containsObject:@"volt"] ||
        ![info.allKeys containsObject:@"ampere"] ||
        ![info.allKeys containsObject:@"powerConsumption"]) {
        NSLog(@"不正确的耗电量回调数据.");
        return;
    }
    
    NSString *watt = info[@"watt"];
    NSString *volt = info[@"volt"];
    NSString *ampere = info[@"ampere"];
    NSString *powerConsumption = info[@"powerConsumption"];
    
    if (_belongArea == NO) {
        [_colorTopLightView.wattBtn setTitle:watt forState:UIControlStateNormal];
        [_colorTopLightView.voltBtn setTitle:volt forState:UIControlStateNormal];
        [_colorTopLightView.milliampereBtn setTitle:ampere forState:UIControlStateNormal];
        [_colorTopLightView.kilowattBtn setTitle:powerConsumption forState:UIControlStateNormal];
    }
}

#pragma mark - Interaction Event
//导航栏设置按钮
- (void)settingBarBtnItemEvent {
    NSLog(@"setting");
    
    CESettingVC *settingVC = [[CESettingVC alloc] init];
    settingVC.belongArea = _belongArea;
    settingVC.deviceEntity = _deviceEntity;
    settingVC.areaEntity = _areaEntity;

    [self.navigationController pushViewController:settingVC animated:YES];
}

//控件block回调，统一管理
- (void)controlsEventCallback {
    WeakSelf(weakSelf)
    
    weakSelf.colorTopLightView.switchImgView.switchCallback = ^{
        BOOL power = [UDManager getPowerStateWith:weakSelf.selectDevice.deviceId];
        NSLog(@"switch: %d",!power);
        [[CommandManager shareInstance] sendPower:!power];
        _currentPower = !power;

        [weakSelf updateSwitchImgView];
        [weakSelf updateSubDevicesData];
    };
    
    weakSelf.colorTopAreaView.switchImgView.switchCallback = ^{
        BOOL power = [UDManager getPowerStateWith:weakSelf.selectDevice.deviceId];
        NSLog(@"switch: %d",!power);
        [[CommandManager shareInstance] sendPower:!power];
        _currentPower = !power;
        [weakSelf updateSwitchImgView];
        [weakSelf updateSubDevicesData];
    };
    
    weakSelf.colorTopLightView.leftArrowEventCallback = ^{
        NSLog(@"leftArrowEventCallback");
        
        [weakSelf.navigationController popViewControllerAnimated:YES];
    };
    
    weakSelf.colorTopAreaView.leftArrowEventCallback = ^{
        NSLog(@"leftArrowEventCallback");
        
        [weakSelf.navigationController popViewControllerAnimated:YES];
    };
    
    weakSelf.colorMiddleView.brightnessSliderValueChangeCallback = ^(CGFloat value) {
        NSLog(@"brightnessSliderValueChangeCallback, value: %f",value);
        
        [[CommandManager shareInstance] sendRGBBirghtness:value rgbInfo:_colorBottomView.rgbInfo];
        [weakSelf updateSwitchImgView];
        [weakSelf updateSubDevicesData];
    };
    
    weakSelf.colorMiddleView.brightnessSliderTouchEventCallback = ^{
        NSLog(@"brightnessSliderTouchEventCallback");
        
        _currentPower = YES;

        [UDManager savePowerStateWith:weakSelf.selectDevice.deviceId power:YES];  //调节时会自动打开
        [UDManager saveRGBBrigrtnessWith:weakSelf.selectDevice.deviceId brightness:weakSelf.colorMiddleView.brightnessSlider.value];
        [UDManager saveCurrentTypeWith:weakSelf.selectDevice.deviceId type:DeviceTypeRGB];
        [weakSelf updateSubDevicesData];
    };
    
    weakSelf.colorBottomView.rgbInfoCallback = ^(NSInteger index, NSDictionary *rgbInfo) {
        NSLog(@"rgbInfoCallback");
        
        if (rgbInfo == nil) {
            return;
        }
        
        _currentPower = YES;

        NSDictionary *newRgbInfo = rgbInfo;
                
        [[CommandManager shareInstance] sendRGBCommandWithRGBInfo:newRgbInfo];
        
        [UDManager savePowerStateWith:weakSelf.selectDevice.deviceId power:YES];
        [UDManager saveRGBWith:weakSelf.selectDevice.deviceId index:index];
        [UDManager saveCurrentTypeWith:weakSelf.selectDevice.deviceId type:DeviceTypeRGB];
        [weakSelf updateSwitchImgView];
        [weakSelf updateSubDevicesData];
    };
}

#pragma mark - Trigger Event
//更新页面UI
- (void)updateControlsUI {
    
    if (_belongArea) {
        _colorTopAreaView.rightArrowImgView.hidden = YES;
        _colorTopAreaView.nameLbl.text = _areaEntity.areaName;
        _colorTopAreaView.numbersLbl.text = [NSString stringWithFormat:@"%ld Light%@",_areaEntity.devices.allObjects.count,_areaEntity.devices.count > 1 ? @"s":@""];

        _colorTopAreaView.switchImgView.image = [DeviceDataHandle getImgWith:_selectDevice.deviceId Type:DeviceTypeRGB];
        
        if (_isAllLights) {
            _colorTopAreaView.nameLbl.text = @"All Lights";
            _colorTopAreaView.numbersLbl.text = [NSString stringWithFormat:@"%ld Lights",[CSRAppStateManager sharedInstance].selectedPlace.devices.allObjects.count];
            _colorTopAreaView.switchImgView.image = [DeviceDataHandle getImgWith:@(0) Type:DeviceTypeRGB];
        }
    }else {
        _colorTopLightView.rightArrowImgView.hidden = YES;
        _colorTopLightView.nameLbl.text = _deviceEntity.name;
        
        BOOL online = [UDManager getDeviceOnlingState:_deviceEntity.deviceId];
        _colorTopLightView.connectStateLbl.text = online == YES ? @"connected" : @"unConnect";
        
        NSSet *areasSet = _deviceEntity.areas ;
        NSMutableArray *areasArray = @[].mutableCopy;
        for (CSRAreaEntity *area in areasSet) {
            [areasArray addObject:area];
        }
        CSRAreaEntity *area = areasArray.firstObject;
        if (area) {
            _colorTopLightView.belongAreasLbl.text = [area.areaName stringByAppendingString:@"     "];    //拼接空格显示好看些 *_*
        }else {
            _colorTopLightView.belongAreasLbl.text = @"Ungrouped     ";
        }
        
        _colorTopLightView.switchImgView.image = [DeviceDataHandle getImgWith:_selectDevice.deviceId Type:DeviceTypeRGB];
        
        CGFloat powerConsumption = [UDManager getPowerConsumption:_deviceEntity.deviceId];
        if (powerConsumption > 0) {
            [_colorTopLightView.kilowattBtn setTitle:[NSString stringWithFormat:@"%0.3fkwh",powerConsumption] forState:UIControlStateNormal];
        }
    }
    
    CGFloat rgbBightness = [UDManager getRGBBrightnessWith:_selectDevice.deviceId];
    _colorMiddleView.brightnessSlider.value = rgbBightness;

    NSInteger colorIndex = [UDManager getRGBIndexWith:_selectDevice.deviceId];
    _colorBottomView.selectIndex = colorIndex;
    
    [CommandManager shareInstance].rgbInfo = _colorBottomView.rgbInfo;
}

//更新开关
- (void)updateSwitchImgView {
    WeakSelf(weakSelf)
    
    weakSelf.colorTopAreaView.switchImgView.image = [DeviceDataHandle getImgWith:weakSelf.selectDevice.deviceId Type:DeviceTypeRGB];
    weakSelf.colorTopLightView.switchImgView.image = [DeviceDataHandle getImgWith:weakSelf.selectDevice.deviceId Type:DeviceTypeRGB];
}

//控制组网时，同时更新子设备的UD数据
- (void)updateSubDevicesData {
    
    WeakSelf(weakSelf)
    if (weakSelf.belongArea) {
        //异步去执行存储操作
        dispatch_queue_t serialQueue = dispatch_queue_create("serial", DISPATCH_QUEUE_SERIAL);
        dispatch_async(serialQueue, ^{
            @autoreleasepool {
                @synchronized(self) {
                    [DeviceDataHandle updateSubDevicesData:weakSelf.selectDevice.deviceId];
                }
            }
        });
    }
}

//开启设备状态查询定时器
- (void)openCheckDeviceStateTimer {
    if (!_checkDeviceStateTimer) {
        _checkDeviceStateTimer = [NSTimer scheduledTimerWithTimeInterval:checkTimeInterval target:self selector:@selector(checkDeviceStateLoop) userInfo:nil repeats:YES];
    }
    
    if ([MingleManager isRGBLight:_selectDevice.deviceId] ||
        [MingleManager isOldLights:_selectDevice.deviceId]) {
        if (!_checkPowerConsumptionTimer && _belongArea == NO) {
            _checkPowerConsumptionTimer = [NSTimer scheduledTimerWithTimeInterval:1.5f target:self selector:@selector(checkPowerConsumptionLoop) userInfo:nil repeats:YES];
        }
    }
}

//结束计时器
- (void)stopCheckTimer {
    if (_checkDeviceStateTimer) {
        [_checkDeviceStateTimer invalidate];
        _checkDeviceStateTimer = nil;
    }
    
    if (_checkPowerConsumptionTimer) {
        [_checkPowerConsumptionTimer invalidate];
        _checkPowerConsumptionTimer = nil;
    }
}
//查询设备循环
- (void)checkDeviceStateLoop {
    
    //牛逼哄哄的线程锁
    @synchronized (self) {
        //先看距离上一次发送指令的时间和当前时间是否超过1s，小于的话就这次的发送就放弃了，防止命令满天飞导致其他问题
        NSDate *lastDate = [CommandManager shareInstance].lastSendOfDate;
        NSDate *currentDate = [NSDate date];
        if ([currentDate timeIntervalSince1970] - [lastDate timeIntervalSince1970] < 1.0f) {
            NSLog(@"刚刚发送完数据，取消这一次的查询指令");
            return;
        }
        if (!self.selectDevice.deviceId) {
            return;
        }
        
        NSMutableArray *mArr = [NSMutableArray arrayWithObject:self.selectDevice.deviceId];
        [[DeviceStateManager shareInstance] checkDeviceStateWith:mArr block:^(NSNumber *devicId) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self updateControlsUI];
            });
        }];
    }
    
}

- (void)checkPowerConsumptionLoop {
    
//    查询耗电量
    [[CommandManager shareInstance] inquirePowerRate];
    
    return;
    
    NSDictionary *info = [DeviceDataHandle fakeDataForPowerConsumptionWith:_selectDevice.deviceId type:DeviceTypeRGB size:14];
    
    NSString *watt = info[@"watt"];
    NSString *volt = info[@"volt"];
    NSString *ampere = info[@"ampere"];
    NSString *powerConsumption = info[@"powerConsumption"];
    
    if (_belongArea == NO) {
        [_colorTopLightView.wattBtn setTitle:watt forState:UIControlStateNormal];
        [_colorTopLightView.voltBtn setTitle:volt forState:UIControlStateNormal];
        [_colorTopLightView.milliampereBtn setTitle:ampere forState:UIControlStateNormal];
        
        if (powerConsumption) {
            [_colorTopLightView.kilowattBtn setTitle:powerConsumption forState:UIControlStateNormal];
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
