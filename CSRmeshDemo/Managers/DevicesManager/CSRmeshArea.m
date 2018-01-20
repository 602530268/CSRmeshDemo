//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import "CSRmeshArea.h"
#import "CSRmeshDevice.h"

@implementation CSRmeshArea

- (id) initWithNumber :(NSNumber *) areaNumber andName:(NSString *)areaName
{
    
    _areaNumber = areaNumber;
    _areaName = areaName;
    _areaDevice = [[CSRmeshDevice alloc] initForArea:_areaNumber];
    [_areaDevice setName:areaName];
    
    self.desiredTemperatureSetByUser = @20.0;
    self.desiredTemperatureAcknowledged = @20.0;
    self.currentTemperature = @20.0;
    
    _meshRequests = [NSMutableDictionary dictionary];


    return self;
}


@end
