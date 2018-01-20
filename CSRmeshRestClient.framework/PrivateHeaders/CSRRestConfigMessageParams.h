/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Config MessageParams response object
*/

@interface CSRRestConfigMessageParams : CSRRestBaseObject




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
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestConfigMessageParams

  @param txQueueSize - (NSNumber*) Max number of messages in transmit queue.
  @param relayRepeatCount - (NSNumber*) Number of times to transmit a relayed message.
  @param deviceRepeatCount - (NSNumber*) Number of times to transmit a message from this device.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestConfigMessageParams
*/
- (id) initWithtxQueueSize: (NSNumber*) txQueueSize     
       relayRepeatCount: (NSNumber*) relayRepeatCount     
       deviceRepeatCount: (NSNumber*) deviceRepeatCount     
       deviceId: (NSNumber*) deviceId;
       

@end
