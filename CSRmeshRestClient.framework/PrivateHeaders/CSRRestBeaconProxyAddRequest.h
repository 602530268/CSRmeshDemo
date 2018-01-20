/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Add API for the Beacon_proxy model
*/

@interface CSRRestBeaconProxyAddRequest : CSRRestBaseObject




/*!
    Bits 0..2 How many device are in this message.If bit 6 is set, the first device address is a GROUP address, to which the other device will be assigned. If bit 7 is set, queued messages for these devices will be cleared.
*/
@property(nonatomic) NSNumber* numDevices;
  
/*!
    Device addresses to add. The first can be a group address.
*/
@property(nonatomic) NSArray* deviceAddresses;
  
/*!
  Constructs instance of CSRRestBeaconProxyAddRequest

  @param numDevices - (NSNumber*) Bits 0..2 How many device are in this message.If bit 6 is set, the first device address is a GROUP address, to which the other device will be assigned. If bit 7 is set, queued messages for these devices will be cleared.
  @param deviceAddresses - (NSArray*) Device addresses to add. The first can be a group address.
  
  @return instance of CSRRestBeaconProxyAddRequest
*/
- (id) initWithnumDevices: (NSNumber*) numDevices     
       deviceAddresses: (NSArray*) deviceAddresses;
       

@end
