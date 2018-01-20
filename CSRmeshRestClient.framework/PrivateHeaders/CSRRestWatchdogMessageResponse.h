/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestWatchdogMessage.h"


/*!
    Response Object of Message API for model Watchdog
*/

@interface CSRRestWatchdogMessageResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestWatchdogMessageResponseStatusEnum) {
  CSRRestWatchdogMessageResponseStatusEnumPending,
  CSRRestWatchdogMessageResponseStatusEnumCompleted,
  CSRRestWatchdogMessageResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestWatchdogMessageResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Watchdog Message response object
*/
@property(nonatomic) NSArray* message;
  
/*!
  Constructs instance of CSRRestWatchdogMessageResponse

  @param status - (CSRRestWatchdogMessageResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param message - (NSArray*) The actual Watchdog Message response object
  
  @return instance of CSRRestWatchdogMessageResponse
*/
- (id) initWithstatus: (CSRRestWatchdogMessageResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       message: (NSArray*) message;
       

@end
