/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestBeaconProxyCommandStatusDevices.h"


/*!
    Response Object of CommandStatusDevices API for model Beacon_proxy
*/

@interface CSRRestBeaconProxyCommandStatusDevicesResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconProxyCommandStatusDevicesResponseStatusEnum) {
  CSRRestBeaconProxyCommandStatusDevicesResponseStatusEnumPending,
  CSRRestBeaconProxyCommandStatusDevicesResponseStatusEnumCompleted,
  CSRRestBeaconProxyCommandStatusDevicesResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestBeaconProxyCommandStatusDevicesResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Beacon_proxy CommandStatusDevices response object
*/
@property(nonatomic) NSArray* commandStatusDevices;
  
/*!
  Constructs instance of CSRRestBeaconProxyCommandStatusDevicesResponse

  @param status - (CSRRestBeaconProxyCommandStatusDevicesResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param commandStatusDevices - (NSArray*) The actual Beacon_proxy CommandStatusDevices response object
  
  @return instance of CSRRestBeaconProxyCommandStatusDevicesResponse
*/
- (id) initWithstatus: (CSRRestBeaconProxyCommandStatusDevicesResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       commandStatusDevices: (NSArray*) commandStatusDevices;
       

@end
