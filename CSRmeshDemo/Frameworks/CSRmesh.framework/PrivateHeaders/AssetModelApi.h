//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header The Asset Model announces the presence of an asset within a mesh network.<h4>Asset State</h4>The Asset model has the following states:<ul style='list-style:square;list-style-position: inside;'><li style='list-style-type:square;'>Interval</li> <li style='list-style-type:square;'>SideEffects</li> <li style='list-style-type:square;'>ToDestinationID</li></ul><h5>Interval Variable</h5>The Interval variable is an unsigned 16-bit integer in seconds representing times from 1 second to 65535 seconds. The value 0x0000 means that the asset will never transmit an asset broadcast message. Some devices will not be able to support every possible Interval value and therefore their Interval value will be rounded to the nearest supported Interval. The rounding of Interval is implementation specific and not specified further. <h5>SideEffects</h5>The SideEffects variable is a 16-bit bit field that represents one or more possible side-effects that this asset would like to be observed. The following side effect bits are defined:<ul style='list-style:square;list-style-position: inside;'><li style='list-style-type:square;'>Light=0</li> <li style='list-style-type:square;'> Audio=1</li> <li style='list-style-type:square;'>Movement=2</li> <li style='list-style-type:square;'>Stationary=3</li> <li style='list-style-type:square;'>Human=4 </li></ul> <h5>ToDestionation</h5>ToDestionation state is a GroupID that all asset broadcast messages are sent to. <H4>Asset Background Behaviour</h4>If the Interval state has a non-zero value then the device sends an ASSET_ANNOUNCE message once every Interval to the ToDestinationID with the SideEffects value. This message is sent with TTL 0, repeated â€˜numberOfAnnouncesâ€™ times with a gap of â€˜announceIntervalâ€™ between each repeat.
 */

@protocol AssetModelApiDelegate <NSObject>
@optional

/**
 * @brief Current asset state
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param interval - Interval between asset broadcasts
 * @param sideEffects - Side effects for this asset
 * @param toDestinationId - Asset announce destination
 * @param txPower - Asset TxPower
 * @param numAnnounces - Number of times to send announce
 * @param announceInterval - Time between announce repeats
 */
- (void)didGetAssetState:(NSNumber *)deviceId
                interval:(NSNumber *)interval
             sideEffects:(NSNumber *)sideEffects
         toDestinationId:(NSNumber *)toDestinationId
                 txPower:(NSNumber *)txPower
            numAnnounces:(NSNumber *)numAnnounces
        announceInterval:(NSNumber *)announceInterval;

/**
 * @brief Asset announcement
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param txPower - Asset TxPower
 * @param frequency - Interval between asset broadcasts
 * @param sideEffects - Side effects for this asset
 */
- (void)didGetAssetAnnounce:(NSNumber *)deviceId
                    txPower:(NSNumber *)txPower
                  frequency:(NSNumber *)frequency
                sideEffects:(NSNumber *)sideEffects;

@end

@interface AssetModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/**
 * @brief Setting Asset State: Upon receiving an ASSET_SET_STATE message, the device saves the Interval, SideEffects, ToDestination, TxPower, Number of Announcements and AnnounceInterval  fields into the appropriate state values. It then responds with an ASSET_STATE message with the current state information.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param interval - Interval between asset broadcasts
 * @param sideEffects - Side effects for this asset
 * @param toDestinationId - Asset announce destination
 * @param txPower - Asset TxPower
 * @param numAnnounces - Number of times to send announce
 * @param announceInterval - Time between announce repeats
 */
- (void)setStateRequest:(NSNumber *)deviceId
               interval:(NSNumber *)interval
            sideEffects:(NSNumber *)sideEffects
        toDestinationId:(NSNumber *)toDestinationId
                txPower:(NSNumber *)txPower
           numAnnounces:(NSNumber *)numAnnounces
       announceInterval:(NSNumber *)announceInterval
                success:(void (^)(NSNumber *deviceId,
                                  NSNumber *interval,
                                  NSNumber *sideEffects,
                                  NSNumber *toDestinationId,
                                  NSNumber *txPower,
                                  NSNumber *numAnnounces,
                                  NSNumber *announceInterval)) success
                failure:(void (^)(NSError *error))failure;

/** 
 * @brief Getting Asset State: Upon receiving an ASSET_GET_STATE message, the device responds with an ASSET_STATE message with the current state information.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 */
- (void)getStateRequest:(NSNumber *)deviceId
                success:(void (^)(NSNumber *deviceId,
                                  NSNumber *interval,
                                  NSNumber *sideEffects,
                                  NSNumber *toDestinationId,
                                  NSNumber *txPower,
                                  NSNumber *numAnnounces,
                                  NSNumber *announceInterval)) success
                failure:(void (^)(NSError *error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<AssetModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<AssetModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
