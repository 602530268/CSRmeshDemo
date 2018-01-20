//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CBPeripheral+Info.h"
#import <objc/runtime.h>

NSString const *localNamePropertyKey = @"localNamePropertyKey";
NSString const *rssiPropertyKey = @"rssiPropertyKey";
NSString const *startOfDiscoveryPropertyKey = @"startOfDiscovery";
NSString const *isBridgeServicePropertyKey = @"isBridgeService";


@implementation CBPeripheral (Info)

@dynamic localName, rssi, startOfDiscovery, discoveryState, isBridgeService;

    //=========================================================================
    // Getter and Setter for localName
-(NSString *) localName {
    return objc_getAssociatedObject(self, &localNamePropertyKey);
}

-(void) setLocalName:(NSString *)localName {
    objc_setAssociatedObject(self, &localNamePropertyKey, localName, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

    //=========================================================================
    // Getter and Setter for RSSI
-(NSNumber *) rssi {
    return objc_getAssociatedObject(self, &rssiPropertyKey);
}

-(void) setRssi:(NSNumber *)rssi {
    
    objc_setAssociatedObject(self, &rssiPropertyKey, rssi, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

    //=========================================================================
    // Getter and Setter for start of discovery
-(NSDate *) startOfDiscovery {
    return objc_getAssociatedObject(self, &startOfDiscoveryPropertyKey);
}

-(void) setStartOfDiscovery:(NSDate *)startOfDiscovery {
    objc_setAssociatedObject(self, &startOfDiscoveryPropertyKey, startOfDiscovery, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}


    //=========================================================================
    // Getter and Setter for start of discovery
-(NSNumber *) isBridgeService {
    return objc_getAssociatedObject(self, &isBridgeServicePropertyKey);
}

-(void) setIsBridgeService:(NSNumber *) isBridgeService {
    objc_setAssociatedObject(self, &isBridgeServicePropertyKey, isBridgeService, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}






@end
