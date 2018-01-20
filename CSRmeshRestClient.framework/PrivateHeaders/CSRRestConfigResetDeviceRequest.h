/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for ResetDevice API for the Config model
*/

@interface CSRRestConfigResetDeviceRequest : CSRRestBaseObject




/*!
    8 lowest bytes of HMAC(DHM_KEY,DeviceHash).
*/
@property(nonatomic) NSArray* signature;
  
/*!
  Constructs instance of CSRRestConfigResetDeviceRequest

  @param signature - (NSArray*) 8 lowest bytes of HMAC(DHM_KEY,DeviceHash).
  
  @return instance of CSRRestConfigResetDeviceRequest
*/
- (id) initWithsignature: (NSArray*) signature;
       

@end
