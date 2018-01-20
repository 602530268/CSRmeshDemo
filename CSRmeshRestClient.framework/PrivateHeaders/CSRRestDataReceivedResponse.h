/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Response Object for Data send transaction api
*/

@interface CSRRestDataReceivedResponse : CSRRestBaseObject


/*!
    Status of the request - Pending or Completed
*/
 typedef NS_OPTIONS(NSInteger, CSRRestDataReceivedResponseStatusEnum) {
  CSRRestDataReceivedResponseStatusEnumPending,
  CSRRestDataReceivedResponseStatusEnumCompleted,

};



/*!
    Status of the request - Pending or Completed
*/
@property(nonatomic) CSRRestDataReceivedResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
  Constructs instance of CSRRestDataReceivedResponse

  @param status - (CSRRestDataReceivedResponseStatusEnum) Status of the request - Pending or Completed
  @param statusUrl - (NSString*) Status check URL for pending responses.
  
  @return instance of CSRRestDataReceivedResponse
*/
- (id) initWithstatus: (CSRRestDataReceivedResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl;
       

@end
