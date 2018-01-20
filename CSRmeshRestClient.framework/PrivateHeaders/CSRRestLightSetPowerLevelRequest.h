/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetPowerLevel API for the Light model
*/

@interface CSRRestLightSetPowerLevelRequest : CSRRestBaseObject


/*!
    Power state
*/
 typedef NS_OPTIONS(NSInteger, CSRRestLightSetPowerLevelRequestPowerEnum) {
  CSRRestLightSetPowerLevelRequestPowerEnumOff,
  CSRRestLightSetPowerLevelRequestPowerEnumOn,
  CSRRestLightSetPowerLevelRequestPowerEnumStandby,
  CSRRestLightSetPowerLevelRequestPowerEnumOnFromStandby,

};



/*!
    Power state
*/
@property(nonatomic) CSRRestLightSetPowerLevelRequestPowerEnum power;

/*!
    Light level
*/
@property(nonatomic) NSNumber* level;
  
/*!
    Time before light reaches desired level
*/
@property(nonatomic) NSNumber* levelDuration;
  
/*!
    Time that light will stay at desired level
*/
@property(nonatomic) NSNumber* sustain;
  
/*!
    Time over which light will decay to zero light level
*/
@property(nonatomic) NSNumber* decay;
  
/*!
  Constructs instance of CSRRestLightSetPowerLevelRequest

  @param power - (CSRRestLightSetPowerLevelRequestPowerEnum) Power state
  @param level - (NSNumber*) Light level
  @param levelDuration - (NSNumber*) Time before light reaches desired level
  @param sustain - (NSNumber*) Time that light will stay at desired level
  @param decay - (NSNumber*) Time over which light will decay to zero light level
  
  @return instance of CSRRestLightSetPowerLevelRequest
*/
- (id) initWithpower: (CSRRestLightSetPowerLevelRequestPowerEnum) power     
       level: (NSNumber*) level     
       levelDuration: (NSNumber*) levelDuration     
       sustain: (NSNumber*) sustain     
       decay: (NSNumber*) decay;
       

@end
