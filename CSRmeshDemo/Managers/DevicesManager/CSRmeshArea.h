//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>

@interface CSRmeshArea : NSObject

@property (strong, atomic) NSNumber *areaNumber;
@property (strong, atomic) NSString *areaName;

@property (strong, atomic) id areaDevice;


//---------- Temperature Control -----------------
// will be set by UI
@property (strong, nonatomic)   NSNumber *desiredTemperatureSetByUser;
@property (strong, nonatomic)   NSNumber *desiredTemperatureAcknowledged;

@property (strong, nonatomic)   NSNumber *currentTemperature;

@property (strong, nonatomic)   NSTimer *setTemperatureDelay;


// Sensor request management
// Array of Dictionaries
@property (strong, nonatomic)   NSMutableDictionary *meshRequests;
// Keys for above dictionary
#define AREA_MESH_REQUEST   @"GROUP_MESH_REQUEST"
#define AREA_SENSOR_TYPE    @"GROUP_SENSOR_TYPE"
#define AREA_SENSOR_VALUE   @"GROUP_SENSOR_VALUE"
#define AREA_SENSOR_CONVERTED_VALUE  @"GROUP_SENSOR_CONVERTED_VALUE"


- (id) initWithNumber :(NSNumber *) areaNumber andName:(NSString*) areaName;

@end
