//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header PingModelApi is a part of the CSRmesh Api and provides a set of methods related to the Ping Model. 
 */


@protocol PingModelApiDelegate <NSObject>
@optional


/*!
 * @brief didPing. An acknowledgement to the request to ping. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param arbitaryData - (NSData *) data received, 4 octets.
 * @param TTLAtRx - (NSNumber *) Time to Live, TTL, value at device, 1 octet
 * @param RSSIAtRx - (NSNumber *) RSSI of received signal at device, 1 octet
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didPing:(NSNumber *)deviceId
   arbitaryData:(NSData *)arbitaryData
        TTLAtRx:(NSNumber *)TTLAtRx
       RSSIAtRx:(NSNumber *)RSSIAtRx
  meshRequestId:(NSNumber *)meshRequestId;


@end

@interface PingModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief ping - ping the device with some data. The callback didPing is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param data - (NSData *) Data, up to 250 octets.
 * @param rspTTL - (NSNumber *) 1 octet wrapped in NSNumber.
 * @param success - Block called upon successful execution.
 * arbitaryData - (NSData *) data received, 4 octets.
 * TTLAtRx - (NSNumber *) Time to Live, TTL, value at device, 1 octet
 * RSSIAtRx - (NSNumber *) RSSI of received signal at device, 1 octet
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)ping:(NSNumber *)deviceId
              data:(NSData *)data
            rspTTL:(NSNumber *)rspTTL
           success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                       NSData * _Nullable arbitaryData,
                                       NSNumber * _Nullable TTLAtRx,
                                       NSNumber * _Nullable RSSIAtRx))success
           failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<PingModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<PingModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
