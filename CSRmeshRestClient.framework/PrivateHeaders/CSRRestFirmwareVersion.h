/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Firmware Version response object
*/

@interface CSRRestFirmwareVersion : CSRRestBaseObject




/*!
    Firmware Major Version
*/
@property(nonatomic) NSNumber* majorVersion;
  
/*!
    Firmware Minor Version
*/
@property(nonatomic) NSNumber* minorVersion;
  
/*!
    Not used
*/
@property(nonatomic) NSArray* reserved;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestFirmwareVersion

  @param majorVersion - (NSNumber*) Firmware Major Version
  @param minorVersion - (NSNumber*) Firmware Minor Version
  @param reserved - (NSArray*) Not used
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestFirmwareVersion
*/
- (id) initWithmajorVersion: (NSNumber*) majorVersion     
       minorVersion: (NSNumber*) minorVersion     
       reserved: (NSArray*) reserved     
       deviceId: (NSNumber*) deviceId;
       

@end
