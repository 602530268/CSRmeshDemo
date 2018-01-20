/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestConfigMessageParams.h"


/*!
    Response Object of MessageParams API for model Config
*/

@interface CSRRestConfigMessageParamsResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestConfigMessageParamsResponseStatusEnum) {
  CSRRestConfigMessageParamsResponseStatusEnumPending,
  CSRRestConfigMessageParamsResponseStatusEnumCompleted,
  CSRRestConfigMessageParamsResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestConfigMessageParamsResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Config MessageParams response object
*/
@property(nonatomic) NSArray* messageParams;
  
/*!
  Constructs instance of CSRRestConfigMessageParamsResponse

  @param status - (CSRRestConfigMessageParamsResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param messageParams - (NSArray*) The actual Config MessageParams response object
  
  @return instance of CSRRestConfigMessageParamsResponse
*/
- (id) initWithstatus: (CSRRestConfigMessageParamsResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       messageParams: (NSArray*) messageParams;
       

@end
