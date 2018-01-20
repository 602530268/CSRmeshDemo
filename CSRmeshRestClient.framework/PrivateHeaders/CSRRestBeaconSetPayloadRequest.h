/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetPayload API for the Beacon model
*/

@interface CSRRestBeaconSetPayloadRequest : CSRRestBaseObject


/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconSetPayloadRequestBeaconTypeEnum) {
  CSRRestBeaconSetPayloadRequestBeaconTypeEnumCSR,
  CSRRestBeaconSetPayloadRequestBeaconTypeEnumiBeacon,
  CSRRestBeaconSetPayloadRequestBeaconTypeEnumEddystone_URL,
  CSRRestBeaconSetPayloadRequestBeaconTypeEnumEddystone_UID,
  CSRRestBeaconSetPayloadRequestBeaconTypeEnumLTE_direct,
  CSRRestBeaconSetPayloadRequestBeaconTypeEnumLumicast,

};



/*!
    ID of this payload (so beacon can know whether it needs to update).
*/
@property(nonatomic) NSNumber* payloadId;
  
/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
@property(nonatomic) CSRRestBeaconSetPayloadRequestBeaconTypeEnum beaconType;

/*!
    Offset into Payload. If this number is 0..0xBF then it is an offset into the raw advert data. If this number is 0xC0.0xFF then it is an offset into non-advertising data (e.g. crypto information).
*/
@property(nonatomic) NSNumber* payloadOffset;
  
/*!
    Payload data - up to 4 bytes total (segmented)
*/
@property(nonatomic) NSArray* payload;
  
/*!
  Constructs instance of CSRRestBeaconSetPayloadRequest

  @param payloadId - (NSNumber*) ID of this payload (so beacon can know whether it needs to update).
  @param beaconType - (CSRRestBeaconSetPayloadRequestBeaconTypeEnum) 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
  @param payloadOffset - (NSNumber*) Offset into Payload. If this number is 0..0xBF then it is an offset into the raw advert data. If this number is 0xC0.0xFF then it is an offset into non-advertising data (e.g. crypto information).
  @param payload - (NSArray*) Payload data - up to 4 bytes total (segmented)
  
  @return instance of CSRRestBeaconSetPayloadRequest
*/
- (id) initWithpayloadId: (NSNumber*) payloadId     
       beaconType: (CSRRestBeaconSetPayloadRequestBeaconTypeEnum) beaconType     
       payloadOffset: (NSNumber*) payloadOffset     
       payload: (NSArray*) payload;
       

@end
