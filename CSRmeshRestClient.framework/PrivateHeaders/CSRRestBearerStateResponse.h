/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestBearerState.h"


/*!
    Response Object of State API for model Bearer
*/

@interface CSRRestBearerStateResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBearerStateResponseStatusEnum) {
  CSRRestBearerStateResponseStatusEnumPending,
  CSRRestBearerStateResponseStatusEnumCompleted,
  CSRRestBearerStateResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestBearerStateResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Bearer State response object
*/
@property(nonatomic) NSArray* state;
  
/*!
  Constructs instance of CSRRestBearerStateResponse

  @param status - (CSRRestBearerStateResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param state - (NSArray*) The actual Bearer State response object
  
  @return instance of CSRRestBearerStateResponse
*/
- (id) initWithstatus: (CSRRestBearerStateResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       state: (NSArray*) state;
       

@end
