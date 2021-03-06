/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestSensorState.h"


/*!
    Response Object of State API for model Sensor
*/

@interface CSRRestSensorStateResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorStateResponseStatusEnum) {
  CSRRestSensorStateResponseStatusEnumPending,
  CSRRestSensorStateResponseStatusEnumCompleted,
  CSRRestSensorStateResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestSensorStateResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Sensor State response object
*/
@property(nonatomic) NSArray* state;
  
/*!
  Constructs instance of CSRRestSensorStateResponse

  @param status - (CSRRestSensorStateResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param state - (NSArray*) The actual Sensor State response object
  
  @return instance of CSRRestSensorStateResponse
*/
- (id) initWithstatus: (CSRRestSensorStateResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       state: (NSArray*) state;
       

@end
