/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Beacon_proxy Devices response object
*/

@interface CSRRestBeaconProxyDevices : CSRRestBaseObject




/*!
    Packet number. Bit 7 will be set if this is the final packet. Following fields form the payload, and will be spread across multiple packets as  required.
*/
@property(nonatomic) NSNumber* packetNumber;
  
/*!
    Number of groups being managed.
*/
@property(nonatomic) NSNumber* numberOfGroups;
  
/*!
    Number of device being managed.
*/
@property(nonatomic) NSNumber* numberOfDevices;
  
/*!
    Group IDs of managed groups.
*/
@property(nonatomic) NSArray* groups;
  
/*!
    Device IDs of managed groups.
*/
@property(nonatomic) NSArray* devices;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestBeaconProxyDevices

  @param packetNumber - (NSNumber*) Packet number. Bit 7 will be set if this is the final packet. Following fields form the payload, and will be spread across multiple packets as  required.
  @param numberOfGroups - (NSNumber*) Number of groups being managed.
  @param numberOfDevices - (NSNumber*) Number of device being managed.
  @param groups - (NSArray*) Group IDs of managed groups.
  @param devices - (NSArray*) Device IDs of managed groups.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestBeaconProxyDevices
*/
- (id) initWithpacketNumber: (NSNumber*) packetNumber     
       numberOfGroups: (NSNumber*) numberOfGroups     
       numberOfDevices: (NSNumber*) numberOfDevices     
       groups: (NSArray*) groups     
       devices: (NSArray*) devices     
       deviceId: (NSNumber*) deviceId;
       

@end
