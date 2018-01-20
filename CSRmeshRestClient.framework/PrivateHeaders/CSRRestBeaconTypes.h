/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Beacon Types response object
*/

@interface CSRRestBeaconTypes : CSRRestBaseObject




/*!
    0x01=CSR, 0x02=iBeacon, 0x04=Eddystone URL, 0x08=Eddystone UID, 0x10=LTE direct, 0x20=Lumicast.
*/
@property(nonatomic) NSNumber* beaconType;
  
/*!
    0..100 (percent)
*/
@property(nonatomic) NSNumber* batteryLevel;
  
/*!
    Time in 10s of seconds since last message received. 0 means message received less than 10 seconds ago, 1 means 10..19 seconds and so on. The special value 0xFFFF means no messages have been received from this beacon since the proxy was last started. If this message is received direct from a beacon rather than from a proxy, this field will always be 0.
*/
@property(nonatomic) NSNumber* timeSinceLastMessage;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestBeaconTypes

  @param beaconType - (NSNumber*) 0x01=CSR, 0x02=iBeacon, 0x04=Eddystone URL, 0x08=Eddystone UID, 0x10=LTE direct, 0x20=Lumicast.
  @param batteryLevel - (NSNumber*) 0..100 (percent)
  @param timeSinceLastMessage - (NSNumber*) Time in 10s of seconds since last message received. 0 means message received less than 10 seconds ago, 1 means 10..19 seconds and so on. The special value 0xFFFF means no messages have been received from this beacon since the proxy was last started. If this message is received direct from a beacon rather than from a proxy, this field will always be 0.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestBeaconTypes
*/
- (id) initWithbeaconType: (NSNumber*) beaconType     
       batteryLevel: (NSNumber*) batteryLevel     
       timeSinceLastMessage: (NSNumber*) timeSinceLastMessage     
       deviceId: (NSNumber*) deviceId;
       

@end
