//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "CBPeripheral+Info.h"



@interface CSRBridgeRoaming : NSObject

@property (atomic) NSUInteger numberOfConnectedBridges;

+ (id)sharedInstance;
- (NSDictionary *)didDiscoverBridgeDevice:(CBCentralManager *)central peripheral:(CBPeripheral *)peripheral advertisment:(NSDictionary *)advertisment RSSI:(NSNumber *)RSSI;
- (void)disconnectedPeripheral:(CBPeripheral *)peripheral;
- (void)connectedPeripheral:(CBPeripheral *)peripheral;

//double add
//处理桥连接，当桥连接数量大于1时，保留一个桥，断开其他桥
- (void)handleBridgeCount;

@end
