//
//  CETemperatureVC.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/24.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CETemperatureVC.h"
#import "CEColorVC.h"
#import "CESettingVC.h"

#import "TemperatureTopLightView.h"
#import "TemperatureTopAreaView.h"
#import "TemperatureMiddleView.h"
#import "TemperatureBottomView.h"

#import "DeviceStateManager.h"
#import "MingleManager.h"

static NSTimeInterval checkTimeInterval = 3.0f;

@interface CETemperatureVC ()
{
    NSTimer *_checkDeviceStateTimer;    //定时查询设备状态，时间间隔为3s，不建议低于该值
    NSTimer *_checkPowerConsumptionTimer;   //查询耗电量
    BOOL _currentPower;    //当前页面的power值
}

@property(nonatomic,assign) BOOL isAllLights;

@property(nonatomic,strong) CSRmeshDevice *selectDevice;
@property(nonatomic,strong) CSRmeshArea *selectArea;

@property(nonatomic,strong) TemperatureTopLightView *temTopLightView;
@property(nonatomic,strong) TemperatureTopAreaView *temTopAreaView;
@property(nonatomic,strong) TemperatureMiddleView *temMiddleView;
@property(nonatomic,strong) TemperatureBottomView *temBottomView;

@end

@implementation CETemperatureVC

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

    if (_belongArea == NO) {
        [self openCheckDeviceStateTimer];
        [self registerNotify];        
    }
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    
    [self stopCheckTimer];
    [self removeNotify];
}

#pragma mark - UI
- (void)createUI {
    
    self.view.backgroundColor = BaseBackgroundColor;

    [self navUI];
    [self createTemperatureView];
}

- (void)navUI {
    
    UIImageView *titleView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"CE_brand"]];
    titleView.contentMode = UIViewContentModeScaleAspectFit;
    self.navigationItem.titleView = titleView;
    
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
    
    
    WeakSelf(weakSelf)
    [self customBackBarBtnItemTo:^{
        [weakSelf.navigationController popViewControllerAnimated:YES];
    }];
}

- (void)createTemperatureView {
    
    UIView *topView = nil;
    
    if (_belongArea) {
        _temTopAreaView = [[[NSBundle mainBundle] loadNibNamed:NSStringFromClass([TemperatureTopAreaView class]) owner:self options:nil] objectAtIndex:0];
        [self.view addSubview:_temTopAreaView];
        [_temTopAreaView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.view).offset(StateBarAndNavBarHeight);
            make.left.right.equalTo(self.view);
            make.height.equalTo(@(ScreenViewHeight * 0.33));
        }];
        _temTopAreaView.leftArrowImgView.hidden = YES;
        _temTopAreaView.nameLbl.text = _areaEntity.areaName;
        _temTopAreaView.numbersLbl.text = [NSString stringWithFormat:@"%ld Lights",_areaEntity.devices.count];
        
        if (_isAllLights) {
            _temTopAreaView.nameLbl.text = @"All lights";
            _temTopAreaView.numbersLbl.text = [NSString stringWithFormat:@"%ld Lights",[CSRAppStateManager sharedInstance].selectedPlace.devices.count];
        }
        
        
        topView = _temTopAreaView;
    }else {
        _temTopLightView = [[[NSBundle mainBundle] loadNibNamed:NSStringFromClass([TemperatureTopLightView class]) owner:self options:nil] objectAtIndex:0];
        [self.view addSubview:_temTopLightView];
        [_temTopLightView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(self.view).offset(StateBarAndNavBarHeight);
            make.left.right.equalTo(self.view);
            make.height.equalTo(@(ScreenViewHeight * 0.33));
        }];
        _temTopLightView.leftArrowImgView.hidden = YES;
        _temTopLightView.nameLbl.text = _deviceEntity.name;        
        
        topView = _temTopLightView;
    }
    
    _temMiddleView = [[[NSBundle mainBundle] loadNibNamed:NSStringFromClass([TemperatureMiddleView class]) owner:self options:nil] objectAtIndex:0];
    [self.view addSubview:_temMiddleView];
    [_temMiddleView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(topView.mas_bottom);
        make.left.right.equalTo(self.view);
        make.height.equalTo(@(ScreenViewHeight * 0.33));
    }];
    
    _temBottomView = [[[NSBundle mainBundle] loadNibNamed:NSStringFromClass([TemperatureBottomView class]) owner:self options:nil] objectAtIndex:0];
    [self.view addSubview:_temBottomView];
    [_temBottomView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(_temMiddleView.mas_bottom);
        make.left.right.bottom.equalTo(self.view);
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
    
    NSDictionary *info = [DeviceDataHandle handlePowerConsumptionAndOtherWith:_selectDevice.deviceId data:dataInfo[@"info"] type:DeviceTypeTemperature];

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
        [_temTopLightView.wattBtn setTitle:watt forState:UIControlStateNormal];
        [_temTopLightView.voltBtn setTitle:volt forState:UIControlStateNormal];
        [_temTopLightView.milliampereBtn setTitle:ampere forState:UIControlStateNormal];
        [_temTopLightView.kilowattBtn setTitle:powerConsumption forState:UIControlStateNormal];
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
    
    weakSelf.temTopLightView.switchImgView.switchCallback = ^{
        
        BOOL power = [UDManager getPowerStateWith:weakSelf.selectDevice.deviceId];
        NSLog(@"switch: %d",!power);
        [[CommandManager shareInstance] sendPower:!power];
        [UDManager savePowerStateWith:weakSelf.selectDevice.deviceId power:!power];
        _currentPower = !power;

        weakSelf.temTopLightView.switchImgView.image = [DeviceDataHandle getImgWith:weakSelf.deviceEntity.deviceId Type:DeviceTypeTemperature];
        [weakSelf updateSubDevicesData];
    };
    
    weakSelf.temTopAreaView.switchImgView.switchCallback = ^{
        BOOL power = [UDManager getPowerStateWith:weakSelf.selectDevice.deviceId];
        NSLog(@"switch: %d",!power);
        [[CommandManager shareInstance] sendPower:!power];
        [UDManager savePowerStateWith:weakSelf.selectDevice.deviceId power:!power];
        
        _currentPower = !power;
        
        weakSelf.temTopAreaView.switchImgView.image = [DeviceDataHandle getImgWith:weakSelf.selectDevice.deviceId Type:DeviceTypeTemperature];
        [weakSelf updateSubDevicesData];
    };
    
    weakSelf.temTopLightView.rightArrowEventCallback = ^{
        NSLog(@"rightArrowEventCallback");
        
        CEColorVC *colorVC = [[CEColorVC alloc] init];
        colorVC.deviceEntity = weakSelf.deviceEntity;
        colorVC.areaEntity = weakSelf.areaEntity;
        [weakSelf.navigationController pushViewController:colorVC animated:YES];
    };
    
    weakSelf.temTopAreaView.rightArrowEventCallback = ^{
        NSLog(@"rightArrowEventCallback");
        CEColorVC *colorVC = [[CEColorVC alloc] init];
        colorVC.belongArea = weakSelf.belongArea;
        colorVC.deviceEntity = weakSelf.deviceEntity;
        colorVC.areaEntity = weakSelf.areaEntity;
        [weakSelf.navigationController pushViewController:colorVC animated:YES];
    };
    
    weakSelf.temMiddleView.brightnessSliderValueChangeCallback = ^(CGFloat value) {
        NSLog(@"brightnessSliderValueChangeCallback: %f",value);
        [[CommandManager shareInstance] sendTemperatureBrightness:value];
        _currentPower = YES;

        [weakSelf updateSwitchImgView];
    };
    
    weakSelf.temMiddleView.brightnessSliderTouchEventCallback = ^{
        NSLog(@"brightnessSliderTouchEventCallback");
        _currentPower = YES;

        [UDManager savePowerStateWith:weakSelf.selectDevice.deviceId power:YES];  //调节时会自动打开
        [UDManager saveTemperatureBrightnessWith:weakSelf.selectDevice.deviceId brightness:weakSelf.temMiddleView.brightnessSlider.value * 255];    //注意色温亮度值范围
        [UDManager saveCurrentTypeWith:weakSelf.selectDevice.deviceId type:DeviceTypeTemperature];
        [weakSelf updateSubDevicesData];
    };
    
    weakSelf.temMiddleView.temperatureIndexCallback = ^(NSInteger index, NSInteger temperature) {
        NSLog(@"temperatureIndexCallback: %ld",temperature);
        _currentPower = YES;

        [[CommandManager shareInstance] sendTemperature:temperature];
        
        [UDManager savePowerStateWith:weakSelf.selectDevice.deviceId power:YES];
        [UDManager saveTemperatureWith:weakSelf.selectDevice.deviceId temperature:temperature];
        [UDManager saveTemperatureIndexWith:weakSelf.selectDevice.deviceId index:index];
        [UDManager saveCurrentTypeWith:weakSelf.selectDevice.deviceId type:DeviceTypeTemperature];
        
        [weakSelf updateSwitchImgView];
        [weakSelf updateSubDevicesData];
    };
    
    weakSelf.temBottomView.sceneModeBtnEventCallback = ^(SceneMode sceneMode) {
        NSLog(@"sceneMode");
        _currentPower = YES;

        NSInteger temperature = 2700;
        CGFloat brightness = 1.0f;
        
        switch (sceneMode) {
            case SceneModeWake:
                temperature = 5000;
                brightness = 1.0f;
                break;
            case SceneModeSleep:
                temperature = 2700;
                brightness = 0.4f;
                break;
            case SceneModeConcentrate:
                temperature = 4000;
                brightness = 1.0f;
                break;
            case SceneModeRelax:
                temperature = 3000;
                brightness = 0.75f;
                break;
                
            default:
                break;
        }
        
        [[CommandManager shareInstance] sendTemperatureBrightness:brightness];
        [CommandManager shareInstance].canSend = YES;
        [[CommandManager shareInstance] sendTemperature:temperature];

        [UDManager savePowerStateWith:weakSelf.selectDevice.deviceId power:YES];
        [UDManager saveCurrentTypeWith:weakSelf.selectDevice.deviceId type:DeviceTypeTemperature];
        [UDManager saveTemperatureWith:weakSelf.selectDevice.deviceId temperature:temperature];
        [UDManager saveTemperatureBrightnessWith:weakSelf.selectDevice.deviceId brightness:brightness * 255];
        
        weakSelf.temMiddleView.temperature = temperature;
        [UDManager saveTemperatureIndexWith:weakSelf.selectDevice.deviceId index:[weakSelf.temMiddleView getSelectIndex]];
        
        [weakSelf updateControlsUI];
        [weakSelf updateSubDevicesData];
    };
}


#pragma mark - Trigger Event
//更新页面UI
- (void)updateControlsUI {

    if (_belongArea) {
        _temTopAreaView.leftArrowImgView.hidden = YES;
        _temTopAreaView.nameLbl.text = _areaEntity.areaName;
        _temTopAreaView.numbersLbl.text = [NSString stringWithFormat:@"%ld Light%@",_areaEntity.devices.allObjects.count,_areaEntity.devices.count > 1 ? @"s":@""];
        _temTopAreaView.switchImgView.image = [DeviceDataHandle getImgWith:_selectDevice.deviceId Type:DeviceTypeTemperature];
        
        if (_isAllLights) {
            _temTopAreaView.nameLbl.text = @"All Lights";
            _temTopAreaView.numbersLbl.text = [NSString stringWithFormat:@"%ld Lights",[CSRAppStateManager sharedInstance].selectedPlace.devices.allObjects.count];
            _temTopAreaView.switchImgView.image = [DeviceDataHandle getImgWith:@(0) Type:DeviceTypeTemperature];
        }
        
        _temTopAreaView.rightArrowImgView.hidden = ![MingleManager containRGBLightWithArea:_areaEntity];
        
    }else {
        _temTopLightView.leftArrowImgView.hidden = YES;
        _temTopLightView.nameLbl.text = _deviceEntity.name;
        
        BOOL online = [UDManager getDeviceOnlingState:_deviceEntity.deviceId];
        _temTopLightView.connectStateLbl.text = online == YES ? @"connected" : @"unConnected";
        
        NSSet *areasSet = _deviceEntity.areas ;
        NSMutableArray *areasArray = @[].mutableCopy;
        for (CSRAreaEntity *area in areasSet) {
            [areasArray addObject:area];
        }
        CSRAreaEntity *area = areasArray.firstObject;
        if (area) {
            _temTopLightView.belongAreasLbl.text = [area.areaName stringByAppendingString:@"     "];    //拼接空格显示好看些
        }else {
            _temTopLightView.belongAreasLbl.text = @"Ungrouped     ";
        }
        
        _temTopLightView.switchImgView.image = [DeviceDataHandle getImgWith:_selectDevice.deviceId Type:DeviceTypeTemperature];
        
        _temTopLightView.rightArrowImgView.hidden = ![MingleManager isRGBLight:_deviceEntity.deviceId];
        
        CGFloat powerConsumption = [UDManager getPowerConsumption:_deviceEntity.deviceId];
        if (powerConsumption > 0) {
            [_temTopLightView.kilowattBtn setTitle:[NSString stringWithFormat:@"%0.3fkwh",powerConsumption] forState:UIControlStateNormal];
        }
    }
    
    _currentPower = [UDManager getPowerStateWith:_selectDevice.deviceId];

    CGFloat temperatureBightness = [UDManager getTemperatureBrightnessWith:_selectDevice.deviceId];
    _temMiddleView.brightnessSlider.value = temperatureBightness / 255.0f;
    
    NSInteger temperature = [UDManager getTemperatureWith:_selectDevice.deviceId];
    _temMiddleView.temperature = temperature;
    _temMiddleView.selectIndex = [_temMiddleView getSelectIndex];
        
}

//更新开关
- (void)updateSwitchImgView {
    WeakSelf(weakSelf)

    weakSelf.temTopLightView.switchImgView.image = [DeviceDataHandle getImgWith:weakSelf.selectDevice.deviceId Type:DeviceTypeTemperature];
    weakSelf.temTopAreaView.switchImgView.image = [DeviceDataHandle getImgWith:weakSelf.selectDevice.deviceId Type:DeviceTypeTemperature];
    
    _currentPower = [UDManager getPowerStateWith:_selectDevice.deviceId];
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

        
        if (_belongArea) {
            
            NSMutableArray *mArr = [NSMutableArray arrayWithObject:self.areaEntity];
            [[DeviceStateManager shareInstance] checkAreaStateWith:mArr block:^(NSNumber *areaId) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    [self updateControlsUI];
                });
            }];

        }else {
            
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
    
}

- (void)checkPowerConsumptionLoop {

    //查询耗电量
    [[CommandManager shareInstance] inquirePowerRate];
    
    return;
    NSDictionary *info = [DeviceDataHandle fakeDataForPowerConsumptionWith:_selectDevice.deviceId type:DeviceTypeRGB size:14];
    
    NSString *watt = info[@"watt"];
    NSString *volt = info[@"volt"];
    NSString *ampere = info[@"ampere"];
    NSString *powerConsumption = info[@"powerConsumption"];
    
    if (_belongArea == NO) {
        [_temTopLightView.wattBtn setTitle:watt forState:UIControlStateNormal];
        [_temTopLightView.voltBtn setTitle:volt forState:UIControlStateNormal];
        [_temTopLightView.milliampereBtn setTitle:ampere forState:UIControlStateNormal];
        
        if (powerConsumption) {
            [_temTopLightView.kilowattBtn setTitle:powerConsumption forState:UIControlStateNormal];
        }
    }
}

#pragma mark - APIs(private)


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
