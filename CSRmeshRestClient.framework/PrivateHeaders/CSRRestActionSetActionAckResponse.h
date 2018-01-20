/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestActionSetActionAck.h"


/*!
    Response Object for Action Set Action Ack transaction api
*/

@interface CSRRestActionSetActionAckResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActionSetActionAckResponseStatusEnum) {
  CSRRestActionSetActionAckResponseStatusEnumPending,
  CSRRestActionSetActionAckResponseStatusEnumCompleted,
  CSRRestActionSetActionAckResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestActionSetActionAckResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    Array of the actual Action Set Action Ack response object
*/
@property(nonatomic) NSArray* setActionAck;
  
/*!
  Constructs instance of CSRRestActionSetActionAckResponse

  @param status - (CSRRestActionSetActionAckResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param setActionAck - (NSArray*) Array of the actual Action Set Action Ack response object
  
  @return instance of CSRRestActionSetActionAckResponse
*/
- (id) initWithstatus: (CSRRestActionSetActionAckResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       setActionAck: (NSArray*) setActionAck;
       

@end
