/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetDeviceIdentifier API for the Config model
*/

@interface CSRRestConfigSetDeviceIdentifierRequest : CSRRestBaseObject




/*!
    The DeviceHash for the device that will have a new DeviceID.
*/
@property(nonatomic) NSArray* deviceHash;
  
/*!
    The new DeviceID for the device identified by DeviceHash.
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestConfigSetDeviceIdentifierRequest

  @param deviceHash - (NSArray*) The DeviceHash for the device that will have a new DeviceID.
  @param deviceId - (NSNumber*) The new DeviceID for the device identified by DeviceHash.
  
  @return instance of CSRRestConfigSetDeviceIdentifierRequest
*/
- (id) initWithdeviceHash: (NSArray*) deviceHash     
       deviceId: (NSNumber*) deviceId;
       

@end
