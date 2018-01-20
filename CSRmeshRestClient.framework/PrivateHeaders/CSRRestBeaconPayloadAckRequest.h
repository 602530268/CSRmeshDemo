/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for PayloadAck API for the Beacon model
*/

@interface CSRRestBeaconPayloadAckRequest : CSRRestBaseObject


/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconPayloadAckRequestPayloadTypeEnum) {
  CSRRestBeaconPayloadAckRequestPayloadTypeEnumCSR,
  CSRRestBeaconPayloadAckRequestPayloadTypeEnumiBeacon,
  CSRRestBeaconPayloadAckRequestPayloadTypeEnumEddystone_URL,
  CSRRestBeaconPayloadAckRequestPayloadTypeEnumEddystone_UID,
  CSRRestBeaconPayloadAckRequestPayloadTypeEnumLTE_direct,
  CSRRestBeaconPayloadAckRequestPayloadTypeEnumLumicast,

};



/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
@property(nonatomic) CSRRestBeaconPayloadAckRequestPayloadTypeEnum payloadType;

/*!
    0 means success, set bits indicate missing packet numbers 1..16.
*/
@property(nonatomic) NSNumber* ackOrNack;
  
/*!
    Payload ID which was received, or 0xFFFF if no final packet was received.
*/
@property(nonatomic) NSNumber* payloadId;
  
/*!
  Constructs instance of CSRRestBeaconPayloadAckRequest

  @param payloadType - (CSRRestBeaconPayloadAckRequestPayloadTypeEnum) 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
  @param ackOrNack - (NSNumber*) 0 means success, set bits indicate missing packet numbers 1..16.
  @param payloadId - (NSNumber*) Payload ID which was received, or 0xFFFF if no final packet was received.
  
  @return instance of CSRRestBeaconPayloadAckRequest
*/
- (id) initWithpayloadType: (CSRRestBeaconPayloadAckRequestPayloadTypeEnum) payloadType     
       ackOrNack: (NSNumber*) ackOrNack     
       payloadId: (NSNumber*) payloadId;
       

@end
