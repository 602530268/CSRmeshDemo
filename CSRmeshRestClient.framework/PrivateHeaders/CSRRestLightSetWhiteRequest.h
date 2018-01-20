/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetWhite API for the Light model
*/

@interface CSRRestLightSetWhiteRequest : CSRRestBaseObject




/*!
    White level
*/
@property(nonatomic) NSNumber* level;
  
/*!
    Time before light reaches desired level
*/
@property(nonatomic) NSNumber* duration;
  
/*!
  Constructs instance of CSRRestLightSetWhiteRequest

  @param level - (NSNumber*) White level
  @param duration - (NSNumber*) Time before light reaches desired level
  
  @return instance of CSRRestLightSetWhiteRequest
*/
- (id) initWithlevel: (NSNumber*) level     
       duration: (NSNumber*) duration;
       

@end
