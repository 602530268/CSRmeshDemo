/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Config DeviceIdentifier response object
*/

@interface CSRRestConfigDeviceIdentifier : CSRRestBaseObject




/*!
    Hash of the DeviceUUID. The DeviceHash field is a 64-bit hash of the DeviceUUID that is used to identify this device.
*/
@property(nonatomic) NSArray* deviceHash;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestConfigDeviceIdentifier

  @param deviceHash - (NSArray*) Hash of the DeviceUUID. The DeviceHash field is a 64-bit hash of the DeviceUUID that is used to identify this device.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestConfigDeviceIdentifier
*/
- (id) initWithdeviceHash: (NSArray*) deviceHash     
       deviceId: (NSNumber*) deviceId;
       

@end
