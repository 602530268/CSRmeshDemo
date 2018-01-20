/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestGroupModelGroupid.h"


/*!
    Response Object of ModelGroupid API for model Group
*/

@interface CSRRestGroupModelGroupidResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestGroupModelGroupidResponseStatusEnum) {
  CSRRestGroupModelGroupidResponseStatusEnumPending,
  CSRRestGroupModelGroupidResponseStatusEnumCompleted,
  CSRRestGroupModelGroupidResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestGroupModelGroupidResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Group ModelGroupid response object
*/
@property(nonatomic) NSArray* modelGroupid;
  
/*!
  Constructs instance of CSRRestGroupModelGroupidResponse

  @param status - (CSRRestGroupModelGroupidResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param modelGroupid - (NSArray*) The actual Group ModelGroupid response object
  
  @return instance of CSRRestGroupModelGroupidResponse
*/
- (id) initWithstatus: (CSRRestGroupModelGroupidResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       modelGroupid: (NSArray*) modelGroupid;
       

@end
