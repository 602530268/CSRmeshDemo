//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <CoreBluetooth/CoreBluetooth.h>

@interface CBPeripheral (Info)

typedef NS_ENUM (NSInteger,CSRBridgeDiscoveryState) {
    DiscoveringServices = 0,
    DiscoveringCharacteristics,
    DiscoveredCharacteristics,
    IsBridge,
    IsNotBridge
};

@property   (strong, nonatomic) NSString *localName;
@property   (strong, nonatomic) NSNumber *rssi;
@property   (strong, nonatomic) NSDate   *startOfDiscovery;
@property   CSRBridgeDiscoveryState   *discoveryState;
@property   (strong, nonatomic) NSNumber *isBridgeService;

@end

