/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestSensorValue.h"


/*!
    Response Object of Value API for model Sensor
*/

@interface CSRRestSensorValueResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorValueResponseStatusEnum) {
  CSRRestSensorValueResponseStatusEnumPending,
  CSRRestSensorValueResponseStatusEnumCompleted,
  CSRRestSensorValueResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestSensorValueResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Sensor Value response object
*/
@property(nonatomic) NSArray* value;
  
/*!
  Constructs instance of CSRRestSensorValueResponse

  @param status - (CSRRestSensorValueResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param value - (NSArray*) The actual Sensor Value response object
  
  @return instance of CSRRestSensorValueResponse
*/
- (id) initWithstatus: (CSRRestSensorValueResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       value: (NSArray*) value;
       

@end
