/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Watchdog Interval response object
*/

@interface CSRRestWatchdogInterval : CSRRestBaseObject




/*!
    The current watchdog Interval in seconds that contains the maximum interval that watchdog messages should be sent.
*/
@property(nonatomic) NSNumber* interval;
  
/*!
    The current watchdog ActiveAfterTime that contains the period of time that a device will listen for responses after sending a watchdog message.
*/
@property(nonatomic) NSNumber* activeAfterTime;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestWatchdogInterval

  @param interval - (NSNumber*) The current watchdog Interval in seconds that contains the maximum interval that watchdog messages should be sent.
  @param activeAfterTime - (NSNumber*) The current watchdog ActiveAfterTime that contains the period of time that a device will listen for responses after sending a watchdog message.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestWatchdogInterval
*/
- (id) initWithinterval: (NSNumber*) interval     
       activeAfterTime: (NSNumber*) activeAfterTime     
       deviceId: (NSNumber*) deviceId;
       

@end
