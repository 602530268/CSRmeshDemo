/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestBatteryState.h"


/*!
    Response Object of State API for model Battery
*/

@interface CSRRestBatteryStateResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBatteryStateResponseStatusEnum) {
  CSRRestBatteryStateResponseStatusEnumPending,
  CSRRestBatteryStateResponseStatusEnumCompleted,
  CSRRestBatteryStateResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestBatteryStateResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Battery State response object
*/
@property(nonatomic) NSArray* state;
  
/*!
  Constructs instance of CSRRestBatteryStateResponse

  @param status - (CSRRestBatteryStateResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param state - (NSArray*) The actual Battery State response object
  
  @return instance of CSRRestBatteryStateResponse
*/
- (id) initWithstatus: (CSRRestBatteryStateResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       state: (NSArray*) state;
       

@end
