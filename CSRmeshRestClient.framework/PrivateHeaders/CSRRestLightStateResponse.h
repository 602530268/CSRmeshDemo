/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestLightState.h"


/*!
    Response Object of State API for model Light
*/

@interface CSRRestLightStateResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestLightStateResponseStatusEnum) {
  CSRRestLightStateResponseStatusEnumPending,
  CSRRestLightStateResponseStatusEnumCompleted,
  CSRRestLightStateResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestLightStateResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Light State response object
*/
@property(nonatomic) NSArray* state;
  
/*!
  Constructs instance of CSRRestLightStateResponse

  @param status - (CSRRestLightStateResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param state - (NSArray*) The actual Light State response object
  
  @return instance of CSRRestLightStateResponse
*/
- (id) initWithstatus: (CSRRestLightStateResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       state: (NSArray*) state;
       

@end
