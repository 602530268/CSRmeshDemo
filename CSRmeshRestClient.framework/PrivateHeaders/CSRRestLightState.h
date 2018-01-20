/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Light State response object
*/

@interface CSRRestLightState : CSRRestBaseObject


/*!
    Power state
*/
 typedef NS_OPTIONS(NSInteger, CSRRestLightStatePowerEnum) {
  CSRRestLightStatePowerEnumOff,
  CSRRestLightStatePowerEnumOn,
  CSRRestLightStatePowerEnumStandby,
  CSRRestLightStatePowerEnumOnFromStandby,

};



/*!
    Power state
*/
@property(nonatomic) CSRRestLightStatePowerEnum power;

/*!
    Light level
*/
@property(nonatomic) NSNumber* level;
  
/*!
    Red light level
*/
@property(nonatomic) NSNumber* red;
  
/*!
    Green light level
*/
@property(nonatomic) NSNumber* green;
  
/*!
    Blue light level
*/
@property(nonatomic) NSNumber* blue;
  
/*!
    Colour temperature
*/
@property(nonatomic) NSNumber* colorTemperature;
  
/*!
    Bit field of supported light behaviour
*/
@property(nonatomic) NSNumber* supports;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestLightState

  @param power - (CSRRestLightStatePowerEnum) Power state
  @param level - (NSNumber*) Light level
  @param red - (NSNumber*) Red light level
  @param green - (NSNumber*) Green light level
  @param blue - (NSNumber*) Blue light level
  @param colorTemperature - (NSNumber*) Colour temperature
  @param supports - (NSNumber*) Bit field of supported light behaviour
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestLightState
*/
- (id) initWithpower: (CSRRestLightStatePowerEnum) power     
       level: (NSNumber*) level     
       red: (NSNumber*) red     
       green: (NSNumber*) green     
       blue: (NSNumber*) blue     
       colorTemperature: (NSNumber*) colorTemperature     
       supports: (NSNumber*) supports     
       deviceId: (NSNumber*) deviceId;
       

@end
