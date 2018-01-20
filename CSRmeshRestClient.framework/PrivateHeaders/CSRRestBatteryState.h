/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Battery State response object
*/

@interface CSRRestBatteryState : CSRRestBaseObject




/*!
    Battery level
*/
@property(nonatomic) NSNumber* batteryLevel;
  
/*!
    State of the battery
*/
@property(nonatomic) NSNumber* batteryState;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestBatteryState

  @param batteryLevel - (NSNumber*) Battery level
  @param batteryState - (NSNumber*) State of the battery
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestBatteryState
*/
- (id) initWithbatteryLevel: (NSNumber*) batteryLevel     
       batteryState: (NSNumber*) batteryState     
       deviceId: (NSNumber*) deviceId;
       

@end
