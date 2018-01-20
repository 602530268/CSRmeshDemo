/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for GetBeaconStatus API for the Beacon model
*/

@interface CSRRestBeaconGetBeaconStatusRequest : CSRRestBaseObject


/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnum) {
  CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnumCSR,
  CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnumiBeacon,
  CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnumEddystone_URL,
  CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnumEddystone_UID,
  CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnumLTE_direct,
  CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnumLumicast,

};



/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
@property(nonatomic) CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnum beaconType;

/*!
  Constructs instance of CSRRestBeaconGetBeaconStatusRequest

  @param beaconType - (CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnum) 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
  
  @return instance of CSRRestBeaconGetBeaconStatusRequest
*/
- (id) initWithbeaconType: (CSRRestBeaconGetBeaconStatusRequestBeaconTypeEnum) beaconType;
       

@end
