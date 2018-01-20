/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestActuatorValueAck.h"


/*!
    Response Object of ValueAck API for model Actuator
*/

@interface CSRRestActuatorValueAckResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActuatorValueAckResponseStatusEnum) {
  CSRRestActuatorValueAckResponseStatusEnumPending,
  CSRRestActuatorValueAckResponseStatusEnumCompleted,
  CSRRestActuatorValueAckResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestActuatorValueAckResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Actuator ValueAck response object
*/
@property(nonatomic) NSArray* valueAck;
  
/*!
  Constructs instance of CSRRestActuatorValueAckResponse

  @param status - (CSRRestActuatorValueAckResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param valueAck - (NSArray*) The actual Actuator ValueAck response object
  
  @return instance of CSRRestActuatorValueAckResponse
*/
- (id) initWithstatus: (CSRRestActuatorValueAckResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       valueAck: (NSArray*) valueAck;
       

@end
