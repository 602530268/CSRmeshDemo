/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestAssetState.h"


/*!
    Response Object of State API for model Asset
*/

@interface CSRRestAssetStateResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestAssetStateResponseStatusEnum) {
  CSRRestAssetStateResponseStatusEnumPending,
  CSRRestAssetStateResponseStatusEnumCompleted,
  CSRRestAssetStateResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestAssetStateResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Asset State response object
*/
@property(nonatomic) NSArray* state;
  
/*!
  Constructs instance of CSRRestAssetStateResponse

  @param status - (CSRRestAssetStateResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param state - (NSArray*) The actual Asset State response object
  
  @return instance of CSRRestAssetStateResponse
*/
- (id) initWithstatus: (CSRRestAssetStateResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       state: (NSArray*) state;
       

@end
