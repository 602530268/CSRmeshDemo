//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRWatchDevice.h"
#import "CSRConstants.h"

@implementation CSRWatchDevice

@synthesize name, deviceId, isLight, isHeater, isLock, isActivity, isDevice, isArea, desiredTemp, actualTemp;

-(id)init {
    self = [super init];
    if (self) {
        self.name=@"";
        self.deviceId=nil;
        self.isLight=NO;
        self.isHeater=NO;
        self.isLock=NO;
        self.isActivity=NO;
        self.isDevice=NO;
        self.isArea=NO;
        // temperature in degress C multiplied by 10;
        self.desiredTemp = @(kCSR_AirTemp_Default);
        self.actualTemp = @(kCSR_AirTemp_Default);
    }
    return (self);
}

-(NSArray *)getViews {
    NSMutableArray *views = [NSMutableArray array];
    if(isLight)
        [views addObject:@"CSRLightInterfaceController"];
    if(isHeater)
        [views addObject:@"CSRHeaterInterfaceController"];
    if(isLock)
        [views addObject:@"CSRLockInterfaceController"];
    return(views);
}

@end
