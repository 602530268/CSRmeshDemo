/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestActionActionStatus.h"


/*!
    Response Object of ActionStatus API for model Action
*/

@interface CSRRestActionActionStatusResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActionActionStatusResponseStatusEnum) {
  CSRRestActionActionStatusResponseStatusEnumPending,
  CSRRestActionActionStatusResponseStatusEnumCompleted,
  CSRRestActionActionStatusResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestActionActionStatusResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Action ActionStatus response object
*/
@property(nonatomic) NSArray* actionStatus;
  
/*!
  Constructs instance of CSRRestActionActionStatusResponse

  @param status - (CSRRestActionActionStatusResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param actionStatus - (NSArray*) The actual Action ActionStatus response object
  
  @return instance of CSRRestActionActionStatusResponse
*/
- (id) initWithstatus: (CSRRestActionActionStatusResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       actionStatus: (NSArray*) actionStatus;
       

@end
