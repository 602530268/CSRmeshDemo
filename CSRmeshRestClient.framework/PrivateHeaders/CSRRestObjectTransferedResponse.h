/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestObjectTransfer.h"


/*!
    Response Object for Object Transfer transaction api
*/

@interface CSRRestObjectTransferedResponse : CSRRestBaseObject


/*!
    Status of the request - Pending or Completed
*/
 typedef NS_OPTIONS(NSInteger, CSRRestObjectTransferedResponseStatusEnum) {
  CSRRestObjectTransferedResponseStatusEnumPending,
  CSRRestObjectTransferedResponseStatusEnumCompleted,
  CSRRestObjectTransferedResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending or Completed
*/
@property(nonatomic) CSRRestObjectTransferedResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Object Transfer response object
*/
@property(nonatomic) NSArray* transfer;
  
/*!
  Constructs instance of CSRRestObjectTransferedResponse

  @param status - (CSRRestObjectTransferedResponseStatusEnum) Status of the request - Pending or Completed
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param transfer - (NSArray*) The actual Object Transfer response object
  
  @return instance of CSRRestObjectTransferedResponse
*/
- (id) initWithstatus: (CSRRestObjectTransferedResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       transfer: (NSArray*) transfer;
       

@end
