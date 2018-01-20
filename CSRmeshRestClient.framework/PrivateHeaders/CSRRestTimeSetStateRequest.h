/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetState API for the Time model
*/

@interface CSRRestTimeSetStateRequest : CSRRestBaseObject




/*!
    Interval between time broadcasts
*/
@property(nonatomic) NSNumber* interval;
  
/*!
  Constructs instance of CSRRestTimeSetStateRequest

  @param interval - (NSNumber*) Interval between time broadcasts
  
  @return instance of CSRRestTimeSetStateRequest
*/
- (id) initWithinterval: (NSNumber*) interval;
       

@end
