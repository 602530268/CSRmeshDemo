/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestAttentionState.h"


/*!
    Response Object of State API for model Attention
*/

@interface CSRRestAttentionStateResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestAttentionStateResponseStatusEnum) {
  CSRRestAttentionStateResponseStatusEnumPending,
  CSRRestAttentionStateResponseStatusEnumCompleted,
  CSRRestAttentionStateResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestAttentionStateResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Attention State response object
*/
@property(nonatomic) NSArray* state;
  
/*!
  Constructs instance of CSRRestAttentionStateResponse

  @param status - (CSRRestAttentionStateResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param state - (NSArray*) The actual Attention State response object
  
  @return instance of CSRRestAttentionStateResponse
*/
- (id) initWithstatus: (CSRRestAttentionStateResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       state: (NSArray*) state;
       

@end
