/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetStatus API for the Beacon model
*/

@interface CSRRestBeaconSetStatusRequest : CSRRestBaseObject


/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconSetStatusRequestBeaconTypeEnum) {
  CSRRestBeaconSetStatusRequestBeaconTypeEnumCSR,
  CSRRestBeaconSetStatusRequestBeaconTypeEnumiBeacon,
  CSRRestBeaconSetStatusRequestBeaconTypeEnumEddystone_URL,
  CSRRestBeaconSetStatusRequestBeaconTypeEnumEddystone_UID,
  CSRRestBeaconSetStatusRequestBeaconTypeEnumLTE_direct,
  CSRRestBeaconSetStatusRequestBeaconTypeEnumLumicast,

};



/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
@property(nonatomic) CSRRestBeaconSetStatusRequestBeaconTypeEnum beaconType;

/*!
    Time between beacon transmissions in 100ths of seconds (0..100). Setting this to 0 stops that beacon type transmitting.
*/
@property(nonatomic) NSNumber* beaconInterval;
  
/*!
    How many minutes between mesh wakeups (1..N).
*/
@property(nonatomic) NSNumber* meshInterval;
  
/*!
    How long node stays as a mesh node (10s of seconds).
*/
@property(nonatomic) NSNumber* meshTime;
  
/*!
    -127..+127 dbM.
*/
@property(nonatomic) NSNumber* tXPower;
  
/*!
  Constructs instance of CSRRestBeaconSetStatusRequest

  @param beaconType - (CSRRestBeaconSetStatusRequestBeaconTypeEnum) 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
  @param beaconInterval - (NSNumber*) Time between beacon transmissions in 100ths of seconds (0..100). Setting this to 0 stops that beacon type transmitting.
  @param meshInterval - (NSNumber*) How many minutes between mesh wakeups (1..N).
  @param meshTime - (NSNumber*) How long node stays as a mesh node (10s of seconds).
  @param tXPower - (NSNumber*) -127..+127 dbM.
  
  @return instance of CSRRestBeaconSetStatusRequest
*/
- (id) initWithbeaconType: (CSRRestBeaconSetStatusRequestBeaconTypeEnum) beaconType     
       beaconInterval: (NSNumber*) beaconInterval     
       meshInterval: (NSNumber*) meshInterval     
       meshTime: (NSNumber*) meshTime     
       tXPower: (NSNumber*) tXPower;
       

@end
