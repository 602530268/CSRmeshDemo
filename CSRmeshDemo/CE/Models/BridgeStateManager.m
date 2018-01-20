//
//  BridgeStateManager.m
//  CSRmeshDemo
//
//  Created by double on 2017/11/9.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "BridgeStateManager.h"
#import "CSRBluetoothLE.h"
#import "CSRAppStateManager.h"
#import "CSRBridgeRoaming.h"

@implementation BridgeStateManager
{
    NSTimer *_timer;
}

+ (BridgeStateManager *)shareInstance {
    static BridgeStateManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[BridgeStateManager alloc] init];
    });
    return manager;
}

//搜索周围桥并连接
- (void)scanBridgeAndConnect {

    if (_timer) {
        [_timer invalidate];
        _timer = nil;
    }
    
    _timer = [NSTimer scheduledTimerWithTimeInterval:3.0f target:self selector:@selector(timeLoop) userInfo:nil repeats:YES];
}

//当没有连接桥的时候开启扫描连接
- (void)timeLoop {
    
    @synchronized (self) {
        if ([CSRAppStateManager sharedInstance].bearerType == CSRSelectedBearerType_Bluetooth)
        {
            if ([[CSRBridgeRoaming sharedInstance] numberOfConnectedBridges] == 0) {
                [[CSRBluetoothLE sharedInstance] setScanner:YES source:self];
                [[CSRBluetoothLE sharedInstance] startScan];
                
                _bridgeConnnected = NO;
                CCLog(@"无桥连接，开始扫描...");
            }else {
                
                //当连接的桥大于1时，只保留第一个桥，其他的都断开连接
                NSInteger count = [[CSRBridgeRoaming sharedInstance] numberOfConnectedBridges];
                if (count > 1) {
                    [[CSRBridgeRoaming sharedInstance] handleBridgeCount];
                    _bridgeConnnected = NO;
                }else {
                    _bridgeConnnected = YES;
                }
                CCLog(@"已连接桥 %ld",(long)[[CSRBridgeRoaming sharedInstance] numberOfConnectedBridges]);
            }
        }
    }

}

@end
