//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CSRPeripheral.h"

@implementation CSRPeripheral

@synthesize advertisementData;
@synthesize signalStrength;

- (id)initWithCBPeripheral:(CBPeripheral *)cbPeripheral
         advertisementData:(NSDictionary *)dict
                      rssi:(NSNumber *)rssi {
    if (self = [super init]) {
        self.peripheral = cbPeripheral;
        self.advertisementData = dict;
        self.signalStrength = rssi;
    }
    
    return self;
}

- (BOOL)isConnected {
    if (self.peripheral) {
        return (self.peripheral.state == CBPeripheralStateConnected);
    }
    
    return NO;
}

@end
