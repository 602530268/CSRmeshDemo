/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetRgb API for the Light model
*/

@interface CSRRestLightSetRgbRequest : CSRRestBaseObject




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
    Time over which the colour will change
*/
@property(nonatomic) NSNumber* colorDuration;
  
/*!
  Constructs instance of CSRRestLightSetRgbRequest

  @param level - (NSNumber*) Light level
  @param red - (NSNumber*) Red light level
  @param green - (NSNumber*) Green light level
  @param blue - (NSNumber*) Blue light level
  @param colorDuration - (NSNumber*) Time over which the colour will change
  
  @return instance of CSRRestLightSetRgbRequest
*/
- (id) initWithlevel: (NSNumber*) level     
       red: (NSNumber*) red     
       green: (NSNumber*) green     
       blue: (NSNumber*) blue     
       colorDuration: (NSNumber*) colorDuration;
       

@end
