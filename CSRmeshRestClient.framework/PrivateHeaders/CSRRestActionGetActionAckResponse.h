/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestActionGetActionAck.h"


/*!
    Response Object for Action Get transaction api
*/

@interface CSRRestActionGetActionAckResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActionGetActionAckResponseStatusEnum) {
  CSRRestActionGetActionAckResponseStatusEnumPending,
  CSRRestActionGetActionAckResponseStatusEnumCompleted,
  CSRRestActionGetActionAckResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestActionGetActionAckResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Action Get response object
*/
@property(nonatomic) NSArray* setAction;
  
/*!
  Constructs instance of CSRRestActionGetActionAckResponse

  @param status - (CSRRestActionGetActionAckResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param setAction - (NSArray*) The actual Action Get response object
  
  @return instance of CSRRestActionGetActionAckResponse
*/
- (id) initWithstatus: (CSRRestActionGetActionAckResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       setAction: (NSArray*) setAction;
       

@end
