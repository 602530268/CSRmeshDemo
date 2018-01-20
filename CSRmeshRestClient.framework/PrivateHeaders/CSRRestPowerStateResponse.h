/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestPowerState.h"


/*!
    Response Object of State API for model Power
*/

@interface CSRRestPowerStateResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestPowerStateResponseStatusEnum) {
  CSRRestPowerStateResponseStatusEnumPending,
  CSRRestPowerStateResponseStatusEnumCompleted,
  CSRRestPowerStateResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestPowerStateResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Power State response object
*/
@property(nonatomic) NSArray* state;
  
/*!
  Constructs instance of CSRRestPowerStateResponse

  @param status - (CSRRestPowerStateResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param state - (NSArray*) The actual Power State response object
  
  @return instance of CSRRestPowerStateResponse
*/
- (id) initWithstatus: (CSRRestPowerStateResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       state: (NSArray*) state;
       

@end
