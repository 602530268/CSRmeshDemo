/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetInterval API for the Watchdog model
*/

@interface CSRRestWatchdogSetIntervalRequest : CSRRestBaseObject




/*!
    The watchdog Interval being set in seconds and indicates the maximum interval that watchdog messages should be sent.
*/
@property(nonatomic) NSNumber* interval;
  
/*!
    The watchdog ActiveAfterTime being set in seconds that indicates the period of time that a device will listen for responses after sending a watchdog message.
*/
@property(nonatomic) NSNumber* activeAfterTime;
  
/*!
  Constructs instance of CSRRestWatchdogSetIntervalRequest

  @param interval - (NSNumber*) The watchdog Interval being set in seconds and indicates the maximum interval that watchdog messages should be sent.
  @param activeAfterTime - (NSNumber*) The watchdog ActiveAfterTime being set in seconds that indicates the period of time that a device will listen for responses after sending a watchdog message.
  
  @return instance of CSRRestWatchdogSetIntervalRequest
*/
- (id) initWithinterval: (NSNumber*) interval     
       activeAfterTime: (NSNumber*) activeAfterTime;
       

@end
