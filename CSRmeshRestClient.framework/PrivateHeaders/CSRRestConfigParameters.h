/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Config Parameters response object
*/

@interface CSRRestConfigParameters : CSRRestBaseObject




/*!
    The transmit interval for this device. The TxInterval field is a 16-bit unsigned integer in milliseconds that determines the interval between transmitting messages.
*/
@property(nonatomic) NSNumber* txInterval;
  
/*!
    How long a single transmission should occur for. The TxDuration, or transmit duration field is a 16-bit unsigned integer in milliseconds that determines the duration of transmission for a single message.
*/
@property(nonatomic) NSNumber* txDuration;
  
/*!
    How much time this device listens for messages. The RxDutyCycle, or receiver duty cycle field is an 8-bit unsigned integer in 1/255ths of a second that determines how often the device listens for CSRmesh messages. Note: The value 0x00 implies that the device does not listen for messages. The value 0xFF implies that the device continuously listens for messages.
*/
@property(nonatomic) NSNumber* rxDutyCycle;
  
/*!
    How loud should this device transmit messages. The TxPower, or transmit power field is an 8-bit signed integer in decibels that determines the radio transmit power for a device.
*/
@property(nonatomic) NSNumber* txPower;
  
/*!
    The initial default time to live for messages. The TimeToLive field is an 8-bit unsigned integer that determines the default value for the TTL packet field in an MTL packet.
*/
@property(nonatomic) NSNumber* ttl;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestConfigParameters

  @param txInterval - (NSNumber*) The transmit interval for this device. The TxInterval field is a 16-bit unsigned integer in milliseconds that determines the interval between transmitting messages.
  @param txDuration - (NSNumber*) How long a single transmission should occur for. The TxDuration, or transmit duration field is a 16-bit unsigned integer in milliseconds that determines the duration of transmission for a single message.
  @param rxDutyCycle - (NSNumber*) How much time this device listens for messages. The RxDutyCycle, or receiver duty cycle field is an 8-bit unsigned integer in 1/255ths of a second that determines how often the device listens for CSRmesh messages. Note: The value 0x00 implies that the device does not listen for messages. The value 0xFF implies that the device continuously listens for messages.
  @param txPower - (NSNumber*) How loud should this device transmit messages. The TxPower, or transmit power field is an 8-bit signed integer in decibels that determines the radio transmit power for a device.
  @param ttl - (NSNumber*) The initial default time to live for messages. The TimeToLive field is an 8-bit unsigned integer that determines the default value for the TTL packet field in an MTL packet.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestConfigParameters
*/
- (id) initWithtxInterval: (NSNumber*) txInterval     
       txDuration: (NSNumber*) txDuration     
       rxDutyCycle: (NSNumber*) rxDutyCycle     
       txPower: (NSNumber*) txPower     
       ttl: (NSNumber*) ttl     
       deviceId: (NSNumber*) deviceId;
       

@end
