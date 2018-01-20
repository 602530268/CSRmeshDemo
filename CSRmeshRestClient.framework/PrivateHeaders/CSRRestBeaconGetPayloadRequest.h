/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for GetPayload API for the Beacon model
*/

@interface CSRRestBeaconGetPayloadRequest : CSRRestBaseObject


/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x4=LTE direct, 0x5=Lumicast.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconGetPayloadRequestPayloadTypeEnum) {
  CSRRestBeaconGetPayloadRequestPayloadTypeEnumCSR,
  CSRRestBeaconGetPayloadRequestPayloadTypeEnumiBeacon,
  CSRRestBeaconGetPayloadRequestPayloadTypeEnumEddystone_URL,
  CSRRestBeaconGetPayloadRequestPayloadTypeEnumEddystone_UID,
  CSRRestBeaconGetPayloadRequestPayloadTypeEnumLTE_direct,
  CSRRestBeaconGetPayloadRequestPayloadTypeEnumLumicast,

};



/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x4=LTE direct, 0x5=Lumicast.
*/
@property(nonatomic) CSRRestBeaconGetPayloadRequestPayloadTypeEnum payloadType;

/*!
  Constructs instance of CSRRestBeaconGetPayloadRequest

  @param payloadType - (CSRRestBeaconGetPayloadRequestPayloadTypeEnum) 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x4=LTE direct, 0x5=Lumicast.
  
  @return instance of CSRRestBeaconGetPayloadRequest
*/
- (id) initWithpayloadType: (CSRRestBeaconGetPayloadRequestPayloadTypeEnum) payloadType;
       

@end
