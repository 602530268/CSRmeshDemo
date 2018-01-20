/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestTimeState.h"


/*!
    Response Object of State API for model Time
*/

@interface CSRRestTimeStateResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestTimeStateResponseStatusEnum) {
  CSRRestTimeStateResponseStatusEnumPending,
  CSRRestTimeStateResponseStatusEnumCompleted,
  CSRRestTimeStateResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestTimeStateResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Time State response object
*/
@property(nonatomic) NSArray* state;
  
/*!
  Constructs instance of CSRRestTimeStateResponse

  @param status - (CSRRestTimeStateResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param state - (NSArray*) The actual Time State response object
  
  @return instance of CSRRestTimeStateResponse
*/
- (id) initWithstatus: (CSRRestTimeStateResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       state: (NSArray*) state;
       

@end
