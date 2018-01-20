/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetColorTemp API for the Light model
*/

@interface CSRRestLightSetColorTempRequest : CSRRestBaseObject




/*!
    Colour temperature
*/
@property(nonatomic) NSNumber* colorTemperature;
  
/*!
    Time over which colour temperature will change
*/
@property(nonatomic) NSNumber* tempDuration;
  
/*!
  Constructs instance of CSRRestLightSetColorTempRequest

  @param colorTemperature - (NSNumber*) Colour temperature
  @param tempDuration - (NSNumber*) Time over which colour temperature will change
  
  @return instance of CSRRestLightSetColorTempRequest
*/
- (id) initWithcolorTemperature: (NSNumber*) colorTemperature     
       tempDuration: (NSNumber*) tempDuration;
       

@end
