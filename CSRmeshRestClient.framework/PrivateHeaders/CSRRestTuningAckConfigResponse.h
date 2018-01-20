/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestTuningAckConfig.h"


/*!
    Response Object of AckConfig API for model Tuning
*/

@interface CSRRestTuningAckConfigResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestTuningAckConfigResponseStatusEnum) {
  CSRRestTuningAckConfigResponseStatusEnumPending,
  CSRRestTuningAckConfigResponseStatusEnumCompleted,
  CSRRestTuningAckConfigResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestTuningAckConfigResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Tuning AckConfig response object
*/
@property(nonatomic) NSArray* ackConfig;
  
/*!
  Constructs instance of CSRRestTuningAckConfigResponse

  @param status - (CSRRestTuningAckConfigResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param ackConfig - (NSArray*) The actual Tuning AckConfig response object
  
  @return instance of CSRRestTuningAckConfigResponse
*/
- (id) initWithstatus: (CSRRestTuningAckConfigResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       ackConfig: (NSArray*) ackConfig;
       

@end
