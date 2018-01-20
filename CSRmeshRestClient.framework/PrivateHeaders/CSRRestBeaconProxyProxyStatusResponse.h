/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestBeaconProxyProxyStatus.h"


/*!
    Response Object of ProxyStatus API for model Beacon_proxy
*/

@interface CSRRestBeaconProxyProxyStatusResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconProxyProxyStatusResponseStatusEnum) {
  CSRRestBeaconProxyProxyStatusResponseStatusEnumPending,
  CSRRestBeaconProxyProxyStatusResponseStatusEnumCompleted,
  CSRRestBeaconProxyProxyStatusResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestBeaconProxyProxyStatusResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Beacon_proxy ProxyStatus response object
*/
@property(nonatomic) NSArray* proxyStatus;
  
/*!
  Constructs instance of CSRRestBeaconProxyProxyStatusResponse

  @param status - (CSRRestBeaconProxyProxyStatusResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param proxyStatus - (NSArray*) The actual Beacon_proxy ProxyStatus response object
  
  @return instance of CSRRestBeaconProxyProxyStatusResponse
*/
- (id) initWithstatus: (CSRRestBeaconProxyProxyStatusResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       proxyStatus: (NSArray*) proxyStatus;
       

@end
