/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Beacon_proxy ProxyStatus response object
*/

@interface CSRRestBeaconProxyProxyStatus : CSRRestBaseObject




/*!
    How many nodes this proxy is currently being a proxy for. If the proxy has been told to be a proxy for device address 0, this will be 0xFFFF
*/
@property(nonatomic) NSNumber* numManagedNodes;
  
/*!
    How many groups this proxy is managing
*/
@property(nonatomic) NSNumber* numManagedGroups;
  
/*!
    How many messages are currently queued at this proxy for transmission to beacons
*/
@property(nonatomic) NSNumber* numQueuedTxMsgs;
  
/*!
    How many messages have been received from beacons at this proxy since its status was last queried
*/
@property(nonatomic) NSNumber* numQueuedRxMsgs;
  
/*!
    Current maximum queue size
*/
@property(nonatomic) NSNumber* maxQueueSize;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestBeaconProxyProxyStatus

  @param numManagedNodes - (NSNumber*) How many nodes this proxy is currently being a proxy for. If the proxy has been told to be a proxy for device address 0, this will be 0xFFFF
  @param numManagedGroups - (NSNumber*) How many groups this proxy is managing
  @param numQueuedTxMsgs - (NSNumber*) How many messages are currently queued at this proxy for transmission to beacons
  @param numQueuedRxMsgs - (NSNumber*) How many messages have been received from beacons at this proxy since its status was last queried
  @param maxQueueSize - (NSNumber*) Current maximum queue size
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestBeaconProxyProxyStatus
*/
- (id) initWithnumManagedNodes: (NSNumber*) numManagedNodes     
       numManagedGroups: (NSNumber*) numManagedGroups     
       numQueuedTxMsgs: (NSNumber*) numQueuedTxMsgs     
       numQueuedRxMsgs: (NSNumber*) numQueuedRxMsgs     
       maxQueueSize: (NSNumber*) maxQueueSize     
       deviceId: (NSNumber*) deviceId;
       

@end
