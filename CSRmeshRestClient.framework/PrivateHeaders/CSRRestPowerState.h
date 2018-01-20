/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Power State response object
*/

@interface CSRRestPowerState : CSRRestBaseObject


/*!
    Power state
*/
 typedef NS_OPTIONS(NSInteger, CSRRestPowerStateStateEnum) {
  CSRRestPowerStateStateEnumOff,
  CSRRestPowerStateStateEnumOn,
  CSRRestPowerStateStateEnumStandby,
  CSRRestPowerStateStateEnumOnFromStandby,

};



/*!
    Power state
*/
@property(nonatomic) CSRRestPowerStateStateEnum state;

/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestPowerState

  @param state - (CSRRestPowerStateStateEnum) Power state
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestPowerState
*/
- (id) initWithstate: (CSRRestPowerStateStateEnum) state     
       deviceId: (NSNumber*) deviceId;
       

@end
