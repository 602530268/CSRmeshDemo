/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Remove API for the Beacon_proxy model
*/

@interface CSRRestBeaconProxyRemoveRequest : CSRRestBaseObject




/*!
    Bits 0..2 How many device are in this message. Queued messages for these devices will be cleared.
*/
@property(nonatomic) NSNumber* numDevices;
  
/*!
    Device addresses to remove. These can be group addresses. Also, the special address '0' can be used to cease making this a proxy for all devices.
*/
@property(nonatomic) NSArray* deviceAddresses;
  
/*!
  Constructs instance of CSRRestBeaconProxyRemoveRequest

  @param numDevices - (NSNumber*) Bits 0..2 How many device are in this message. Queued messages for these devices will be cleared.
  @param deviceAddresses - (NSArray*) Device addresses to remove. These can be group addresses. Also, the special address '0' can be used to cease making this a proxy for all devices.
  
  @return instance of CSRRestBeaconProxyRemoveRequest
*/
- (id) initWithnumDevices: (NSNumber*) numDevices     
       deviceAddresses: (NSArray*) deviceAddresses;
       

@end
