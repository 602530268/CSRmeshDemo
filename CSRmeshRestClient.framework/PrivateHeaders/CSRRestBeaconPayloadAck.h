/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Beacon PayloadAck response object
*/

@interface CSRRestBeaconPayloadAck : CSRRestBaseObject


/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconPayloadAckPayloadTypeEnum) {
  CSRRestBeaconPayloadAckPayloadTypeEnumCSR,
  CSRRestBeaconPayloadAckPayloadTypeEnumiBeacon,
  CSRRestBeaconPayloadAckPayloadTypeEnumEddystone_URL,
  CSRRestBeaconPayloadAckPayloadTypeEnumEddystone_UID,
  CSRRestBeaconPayloadAckPayloadTypeEnumLTE_direct,
  CSRRestBeaconPayloadAckPayloadTypeEnumLumicast,

};



/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
@property(nonatomic) CSRRestBeaconPayloadAckPayloadTypeEnum payloadType;

/*!
    0 means success, set bits indicate missing packet numbers 1..16.
*/
@property(nonatomic) NSNumber* ackOrNack;
  
/*!
    Payload ID which was received, or 0xFFFF if no final packet was received.
*/
@property(nonatomic) NSNumber* payloadId;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestBeaconPayloadAck

  @param payloadType - (CSRRestBeaconPayloadAckPayloadTypeEnum) 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
  @param ackOrNack - (NSNumber*) 0 means success, set bits indicate missing packet numbers 1..16.
  @param payloadId - (NSNumber*) Payload ID which was received, or 0xFFFF if no final packet was received.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestBeaconPayloadAck
*/
- (id) initWithpayloadType: (CSRRestBeaconPayloadAckPayloadTypeEnum) payloadType     
       ackOrNack: (NSNumber*) ackOrNack     
       payloadId: (NSNumber*) payloadId     
       deviceId: (NSNumber*) deviceId;
       

@end
