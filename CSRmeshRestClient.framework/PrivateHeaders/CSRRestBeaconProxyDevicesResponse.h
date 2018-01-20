/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestBeaconProxyDevices.h"


/*!
    Response Object of Devices API for model Beacon_proxy
*/

@interface CSRRestBeaconProxyDevicesResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconProxyDevicesResponseStatusEnum) {
  CSRRestBeaconProxyDevicesResponseStatusEnumPending,
  CSRRestBeaconProxyDevicesResponseStatusEnumCompleted,
  CSRRestBeaconProxyDevicesResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestBeaconProxyDevicesResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Beacon_proxy Devices response object
*/
@property(nonatomic) NSArray* devices;
  
/*!
  Constructs instance of CSRRestBeaconProxyDevicesResponse

  @param status - (CSRRestBeaconProxyDevicesResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param devices - (NSArray*) The actual Beacon_proxy Devices response object
  
  @return instance of CSRRestBeaconProxyDevicesResponse
*/
- (id) initWithstatus: (CSRRestBeaconProxyDevicesResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       devices: (NSArray*) devices;
       

@end
