/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestConfigInfo.h"


/*!
    Response Object of Info API for model Config
*/

@interface CSRRestConfigInfoResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestConfigInfoResponseStatusEnum) {
  CSRRestConfigInfoResponseStatusEnumPending,
  CSRRestConfigInfoResponseStatusEnumCompleted,
  CSRRestConfigInfoResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestConfigInfoResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Config Info response object
*/
@property(nonatomic) NSArray* info;
  
/*!
  Constructs instance of CSRRestConfigInfoResponse

  @param status - (CSRRestConfigInfoResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param info - (NSArray*) The actual Config Info response object
  
  @return instance of CSRRestConfigInfoResponse
*/
- (id) initWithstatus: (CSRRestConfigInfoResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       info: (NSArray*) info;
       

@end
