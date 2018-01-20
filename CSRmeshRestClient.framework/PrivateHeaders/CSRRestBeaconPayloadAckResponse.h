/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestBeaconPayloadAck.h"


/*!
    Response Object of PayloadAck API for model Beacon
*/

@interface CSRRestBeaconPayloadAckResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconPayloadAckResponseStatusEnum) {
  CSRRestBeaconPayloadAckResponseStatusEnumPending,
  CSRRestBeaconPayloadAckResponseStatusEnumCompleted,
  CSRRestBeaconPayloadAckResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestBeaconPayloadAckResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Beacon PayloadAck response object
*/
@property(nonatomic) NSArray* payloadAck;
  
/*!
  Constructs instance of CSRRestBeaconPayloadAckResponse

  @param status - (CSRRestBeaconPayloadAckResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param payloadAck - (NSArray*) The actual Beacon PayloadAck response object
  
  @return instance of CSRRestBeaconPayloadAckResponse
*/
- (id) initWithstatus: (CSRRestBeaconPayloadAckResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       payloadAck: (NSArray*) payloadAck;
       

@end
