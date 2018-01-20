/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetMessageParams API for the Config model
*/

@interface CSRRestConfigSetMessageParamsRequest : CSRRestBaseObject




/*!
    Max number of messages in transmit queue.
*/
@property(nonatomic) NSNumber* txQueueSize;
  
/*!
    Number of times to transmit a relayed message.
*/
@property(nonatomic) NSNumber* relayRepeatCount;
  
/*!
    Number of times to transmit a message from this device.
*/
@property(nonatomic) NSNumber* deviceRepeatCount;
  
/*!
  Constructs instance of CSRRestConfigSetMessageParamsRequest

  @param txQueueSize - (NSNumber*) Max number of messages in transmit queue.
  @param relayRepeatCount - (NSNumber*) Number of times to transmit a relayed message.
  @param deviceRepeatCount - (NSNumber*) Number of times to transmit a message from this device.
  
  @return instance of CSRRestConfigSetMessageParamsRequest
*/
- (id) initWithtxQueueSize: (NSNumber*) txQueueSize     
       relayRepeatCount: (NSNumber*) relayRepeatCount     
       deviceRepeatCount: (NSNumber*) deviceRepeatCount;
       

@end
