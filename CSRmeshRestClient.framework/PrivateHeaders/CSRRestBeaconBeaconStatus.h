/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Beacon BeaconStatus response object
*/

@interface CSRRestBeaconBeaconStatus : CSRRestBaseObject


/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconBeaconStatusBeaconTypeEnum) {
  CSRRestBeaconBeaconStatusBeaconTypeEnumCSR,
  CSRRestBeaconBeaconStatusBeaconTypeEnumiBeacon,
  CSRRestBeaconBeaconStatusBeaconTypeEnumEddystone_URL,
  CSRRestBeaconBeaconStatusBeaconTypeEnumEddystone_UID,
  CSRRestBeaconBeaconStatusBeaconTypeEnumLTE_direct,
  CSRRestBeaconBeaconStatusBeaconTypeEnumLumicast,

};



/*!
    0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
@property(nonatomic) CSRRestBeaconBeaconStatusBeaconTypeEnum beaconType;

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
    0..100 (percent).
*/
@property(nonatomic) NSNumber* batteryLevel;
  
/*!
    ID of latest received payload for this beacon type, as returned by beacon payload ack.
*/
@property(nonatomic) NSNumber* payloadId;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestBeaconBeaconStatus

  @param beaconType - (CSRRestBeaconBeaconStatusBeaconTypeEnum) 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
  @param beaconInterval - (NSNumber*) Time between beacon transmissions in 100ths of seconds (0..100). Setting this to 0 stops that beacon type transmitting.
  @param meshInterval - (NSNumber*) How many minutes between mesh wakeups (1..N).
  @param meshTime - (NSNumber*) How long node stays as a mesh node (10s of seconds).
  @param tXPower - (NSNumber*) -127..+127 dbM.
  @param batteryLevel - (NSNumber*) 0..100 (percent).
  @param payloadId - (NSNumber*) ID of latest received payload for this beacon type, as returned by beacon payload ack.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestBeaconBeaconStatus
*/
- (id) initWithbeaconType: (CSRRestBeaconBeaconStatusBeaconTypeEnum) beaconType     
       beaconInterval: (NSNumber*) beaconInterval     
       meshInterval: (NSNumber*) meshInterval     
       meshTime: (NSNumber*) meshTime     
       tXPower: (NSNumber*) tXPower     
       batteryLevel: (NSNumber*) batteryLevel     
       payloadId: (NSNumber*) payloadId     
       deviceId: (NSNumber*) deviceId;
       

@end
