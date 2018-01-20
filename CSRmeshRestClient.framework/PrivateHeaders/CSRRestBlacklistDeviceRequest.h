/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for taking action pertaining to blacklisting of a device.
*/

@interface CSRRestBlacklistDeviceRequest : CSRRestBaseObject




/*!
    Device DHM key encrypted using Gateway's DHM key
*/
@property(nonatomic) NSArray* signature;
  
/*!
  Constructs instance of CSRRestBlacklistDeviceRequest

  @param signature - (NSArray*) Device DHM key encrypted using Gateway's DHM key
  
  @return instance of CSRRestBlacklistDeviceRequest
*/
- (id) initWithsignature: (NSArray*) signature;
       

@end
