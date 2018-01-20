/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Time State response object
*/

@interface CSRRestTimeState : CSRRestBaseObject




/*!
    Interval between time broadcasts
*/
@property(nonatomic) NSNumber* interval;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestTimeState

  @param interval - (NSNumber*) Interval between time broadcasts
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestTimeState
*/
- (id) initWithinterval: (NSNumber*) interval     
       deviceId: (NSNumber*) deviceId;
       

@end
