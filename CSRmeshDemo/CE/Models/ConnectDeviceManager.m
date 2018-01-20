//
//  ConnectDeviceManager.m
//  CSRmeshDemo
//
//  Created by double on 2017/7/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "ConnectDeviceManager.h"

@implementation ConnectDeviceManager
{
//    CSRmeshDevice *_currentMeshDevice;  //当前正在连接的设备
    NSArray *_prepareConnectDevices;    //准备连接的设备
    NSMutableArray *_connectFinishDevices;  //连接成功或失败都算是连接完成
    NSString *_currentDeviceName;   //当前正在连接的设备名
    NSInteger _connectedDeviceCount;    //已连接设备数量
    NSString *_currentDeviceUUIDString; //当前连接设备的UUID
    NSNumber *_currentDeviceId; //当前连接设备的deviceId
    
    NSMutableArray *_orderConnectDevices;   //准备连接的设备，顺序连接
    
    NSMutableArray *_preSaveInfos;  //开始连接时将设备信息存入临时数组，连接成功后将必要信息进行保存
    
    //回调
    void (^_success)(NSString *deviceName);
    void (^_progress)(NSString *deviceName, CGFloat progress);
    void (^_fail)(NSString *deviceName);
    void (^_finish)();
    
    BOOL _connecting; //正在连接
    BOOL _orderConnectMode; //连接方式为顺序连接
}

+ (ConnectDeviceManager *)shareInstance {
    static ConnectDeviceManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[ConnectDeviceManager alloc] init];
        [manager registerNotify];
    });
    
    return manager;
}

#pragma mark - APIs (public)
- (void)connectDevices:(NSMutableArray *)devices success:(void (^)(NSString *))success progress:(void (^)(NSString *, CGFloat))progress fail:(void (^)(NSString *))fail finish:(void (^)())finish {
    
    if (_connecting) {
        return;
    }
    _connecting = YES;
    
    CCLog(@"开始连接...");
    
    _prepareConnectDevices = @[].mutableCopy;
    _connectFinishDevices = @[].mutableCopy;
    
    _success = success;
    _progress = progress;
    _fail = fail;
    _finish = finish;
    
    _prepareConnectDevices = devices;
    _connectedDeviceCount = 0;
    
    [self setupNewDeviceId];
    
    _preSaveInfos = @[].mutableCopy;
    
//    [self sameTimeConnect];
//    return;
    
//    if (devices.count <= 10) {
        _orderConnectMode = YES;
        _orderConnectDevices = _prepareConnectDevices.mutableCopy;
        [self orderConnect];
//    }else {
//        _orderConnectMode = NO;
//        [self sameTimeConnect];
//    }
    
}

//取消后续设备的连接
- (void)cancelConnect {
    _connectedDeviceCount = _prepareConnectDevices.count * 2;
}

#pragma mark - APIs  (private)
//设置deviceId
- (void)setupNewDeviceId {
    
    [CSRDevicesManager sharedInstance].isDeviceTypeGateway = NO;
    if ([CSRDevicesManager sharedInstance].isDeviceTypeGateway) {
        _currentDeviceId = [[CSRDatabaseManager sharedInstance] getNextFreeGatewayDeviceId];
    } else {
        _currentDeviceId = [[CSRDatabaseManager sharedInstance] getNextFreeIDOfType:@"CSRDeviceEntity"];
    }
}

//全部同时连接，需要手动指定deviceId
- (void)sameTimeConnect {
    //获取最新可用的deviceId
    NSNumber *deviceId = _currentDeviceId;
    
    _currentDeviceName = nil;
    _currentDeviceUUIDString = nil;
    
    for (CSRmeshDevice *device in _prepareConnectDevices) {
        
        [CSRDevicesManager sharedInstance].isDeviceTypeGateway = NO;
        if (device.appearanceShortname) {
            
            _currentDeviceUUIDString = [device.uuid UUIDString];
            CCLog(@"连接时: %@ UUID: %@, %@",_currentDeviceName,_currentDeviceUUIDString,device.uuid);
            
            _currentDeviceId = deviceId;

            [[CSRDevicesManager sharedInstance] new_associateDeviceFromCSRDeviceManager:device.deviceHash authorisationCode:nil deviceId:deviceId];
            
            NSString *shortName = [CSRUtilities stringFromData:device.appearanceShortname];
            _currentDeviceName = [DeviceDataHandle getDeviceNameWith:shortName];
            
            CCLog(@"%@ 设备为准备连接状态，现在开始连接...",_currentDeviceName);
            CCLog(@"设备ID为: %@",deviceId);
            CCLog(@"设备UUID: %@",[device.uuid UUIDString]);
            NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithCapacity:0];
            [dic setValue:deviceId forKey:@"deviceId"];
            [dic setValue:shortName forKey:@"deviceName"];
            
            if (device.uuid.UUIDString) {
                [dic setValue:device.uuid.UUIDString forKey:@"uuid"];
            }

            [_preSaveInfos addObject:dic];
            
            NSInteger number = [deviceId integerValue];
            number++;
            deviceId = @(number);
        }
    }
}

//顺序连接，即一盏接一盏的连接，较慢，但是稳定
- (void)orderConnect {
    //获取最新可用的deviceId
    NSNumber *deviceId = _currentDeviceId;
    
    _currentDeviceName = nil;
    _currentDeviceUUIDString = nil;
    
    CSRmeshDevice *device = _orderConnectDevices.firstObject;
    
    if (device == nil) {
        _connectedDeviceCount++;
        [self checkNeedConnect];
        return;
    }
    
    [_orderConnectDevices removeObjectAtIndex:0];   //删除一个设备
    
    //保证线程同步
    @synchronized(self) {
        [CSRDevicesManager sharedInstance].isDeviceTypeGateway = NO;
        if (device.appearanceShortname) {
            
            _currentDeviceUUIDString = [device.uuid UUIDString];
            _currentDeviceId = deviceId;
            
            [[CSRDevicesManager sharedInstance] new_associateDeviceFromCSRDeviceManager:device.deviceHash authorisationCode:nil deviceId:deviceId];
            
            _currentDeviceName = [[NSString alloc] initWithData:device.appearanceShortname encoding:NSUTF8StringEncoding];
            
            NSString *shortName = [CSRUtilities stringFromData:device.appearanceShortname];
            _currentDeviceName = [DeviceDataHandle getDeviceNameWith:shortName];
            
            CCLog(@"%@ 设备为准备连接状态，现在开始连接...",_currentDeviceName);
            CCLog(@"设备ID为: %@",deviceId);
            CCLog(@"设备UUID: %@",[device.uuid UUIDString]);
            
            NSInteger number = [deviceId integerValue];
            number++;
            _currentDeviceId = @(number);
            
            //开始连接时，回调0的进度
            if (_progress) {
                _progress(_currentDeviceName,0);
            }
        }
    }

}

//判断是否有设备需要连接
- (BOOL)checkNeedConnect {
    
    BOOL needConnect = NO;
    
    if (_connectedDeviceCount < _prepareConnectDevices.count) {
        needConnect = YES;
    }
    
    if (needConnect == NO) {
        CCLog(@"没有需要连接的设备了");

        if (_finish) {
            CCLog(@"所有设备连接完成");

            _prepareConnectDevices = @[].mutableCopy;
            _connectFinishDevices = @[].mutableCopy;
            
            _preSaveInfos = @[].mutableCopy;
            _currentDeviceName = nil;
            _currentDeviceId = nil;
            _currentDeviceUUIDString = nil;
    
            _connecting = NO;
            _finish();
        }
    }else {
        CCLog(@"还有需要连接的设备，继续连接...");
        
        if (_orderConnectMode == YES) {
            [self orderConnect];
        }
    }

    return needConnect;
}

//注册通知
- (void)registerNotify {
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(deviceAssociationSuccess:)
                                                 name:kCSRmeshManagerDeviceAssociationSuccessNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(deviceAssociationFailed:)
                                                 name:kCSRmeshManagerDeviceAssociationFailedNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(displayAssociationProgress:)
                                                 name:kCSRmeshManagerDeviceAssociationProgressNotification
                                               object:nil];
    
}

#pragma mark - Notifications
//连接成功  (改为手动调用，因为连接成功时设备信息还未存储到本地，导致设备ID错乱)
- (void)deviceAssociationSuccess:(NSNotification *)sender {
    
    CCLog(@"连接成功");
    
//    if (_currentDeviceId && _currentDeviceUUIDString) {
//        [UDManager saveDeviceUUIDStringWith:_currentDeviceId uuid:_currentDeviceUUIDString];
//    }
    
    NSNumber *deviceId = sender.userInfo[@"deviceId"];
    for (NSDictionary *dic in _preSaveInfos) {
        
        NSString *originName = dic[@"deviceName"];
        NSString *uuid = dic[@"uuid"];
        if ([dic.allKeys containsObject:@"deviceId"] && [dic[@"deviceId"] isEqualToNumber:deviceId]) {
            [UDManager saveDeviceOriginNameWith:deviceId originName:originName];
            [UDManager saveDeviceUUIDStringWith:deviceId uuid:uuid];
            break;
        }
    }
    
    _connectedDeviceCount++;
    
    //检查是否还有设备需要连接，没有说明所有设备连接成功/完成
    if (_success) {
        _success(_currentDeviceName);
    }
    
    //回调完成的进度
    if (_progress) {
        _progress(_currentDeviceName,1.0f);
    }
    [self checkNeedConnect];
}

//连接失败，如还有设备未进行连接会继续进行
- (void)deviceAssociationFailed:(NSNotification *)sender {
    
    CCLog(@"连接失败");
    _connectedDeviceCount++;
    
    if (_fail) {
        _fail(_currentDeviceName);
    }
    [self checkNeedConnect];
}

//连接进度
- (void)displayAssociationProgress:(NSNotification *)sender {
    
    if (_progress) {
        NSNumber *completedSteps = sender.userInfo[@"stepsCompleted"];
        NSNumber *totalSteps = sender.userInfo[@"totalSteps"];
        
        if ([completedSteps floatValue] <= [totalSteps floatValue] && [completedSteps floatValue] > 0) {
            _progress(_currentDeviceName,([completedSteps floatValue] / [totalSteps floatValue]));
        } else {
            CCLog(@"ERROR: 设备连接出现问题");
        }
        
    }
}

@end
