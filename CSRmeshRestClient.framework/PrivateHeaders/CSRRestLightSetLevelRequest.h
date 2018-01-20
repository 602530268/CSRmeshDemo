/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetLevel API for the Light model
*/

@interface CSRRestLightSetLevelRequest : CSRRestBaseObject




/*!
    Light level
*/
@property(nonatomic) NSNumber* level;
  
/*!
  Constructs instance of CSRRestLightSetLevelRequest

  @param level - (NSNumber*) Light level
  
  @return instance of CSRRestLightSetLevelRequest
*/
- (id) initWithlevel: (NSNumber*) level;
       

@end
