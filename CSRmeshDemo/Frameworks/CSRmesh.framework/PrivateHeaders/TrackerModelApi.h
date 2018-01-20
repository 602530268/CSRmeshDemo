//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header The Tracker Model finds assets within a mesh network. When a device wishes to find an asset it sends a find message into the mesh network. Any device that has recently heard from an asset that is trying to be found responds with an appropriate message indicating when and how loud it heard this message. It is possible that a device that has only heard a message with a weak signal, delays its response or does not respond at all if it subsequently hears another device saying that it had heard the device at a stronger signal level more recently. This optimises the number of messages transmitted by devices in the network when an asset has been moving around the network. <br><br> A device that is listening for and recording asset presence messages do not need to save every presence message that it receives. It could only save a subset of messages based on various heuristics such as signal strength or number of devices or frequency of message receipt.<h4>Tracker Cache</h4> The tracker model has a tracker cache, with a list of the last seen asset broadcasts with associated data. Such associated data includes the received signal strength and the time when that asset broadcast was received. It is impossible to store all possible asset broadcast messages received on a device and therefore it is assumed that devices implementing the tracker model uses a least-recently-used algorithm to remove old and/or weak data. The actual algorithm used is an implementation issue.<h4>Tracker Server Behaviour</h4>When a tracker device hears an ASSET_ANNOUNCE it first listens for other TRACKER_REPORT reports for the same asset to determine if the cached information is either louder or newer than other devices. If the server does not receive any other TRACKER_REPORT message or the RSSI and Age fields of those messages are louder or younger than the information in its tracker cache, then it does not send a TRACKER_REPORT message for the asset. The timing of sending a TRACKER_REPORT message is a function of the age and RSSI values in the tracker cache. The RSSI heard is converted to a delay in milliseconds using the formula: (DelayOffset - RSSI) * DelayFactor.<br><br> RSSI is a negative number usually between -40 and -100. DelayOffset is 60 by default and DelayFactor is 30. This gives a delay of 3 to 4.8 seconds before a REPORT is sent.
 */

@protocol TrackerModelApiDelegate <NSObject>
@optional

/**
 * @brief Current asset state
 * @param deviceId
 * @param trackerId
 * @param rssi - RSSI of ASSET_ANNOUNCE
 * @param zone - Zone: 0=Immediate 1=Near 2=Distant
 * @param ageSeconds - How long since last seen
 * @param sideEffects - Side effects for this asset
 */
- (void)didFindAsset:(NSNumber * _Nonnull)deviceId
           trackerId:(NSNumber * _Nonnull)trackerId
                rssi:(NSNumber * _Nonnull)rssi
                zone:(NSNumber * _Nonnull)zone
          ageSeconds:(NSNumber * _Nonnull)ageSeconds
         sideEffects:(NSNumber * _Nonnull)sideEffects;

/**
 * @brief Asset report
 * @param deviceId
 * @param trackerId
 * @param txPower - Asset TxPower
 * @param frequency - Interval between asset broadcasts
 * @param sideEffects - Side effects for this asset
 */
- (void)didGetAssetReport:(NSNumber * _Nonnull)deviceId
                trackerId:(NSNumber * _Nonnull)trackerId
                     rssi:(NSNumber * _Nonnull)rssi
                     zone:(NSNumber * _Nonnull)zone
               ageSeconds:(NSNumber * _Nonnull)ageSeconds
              sideEffects:(NSNumber * _Nonnull)sideEffects;

@end

@interface TrackerModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/**
 * @brief Finding an Asset:  Upon receiving a TRACKER_FIND message, the server checks its tracker cache to see if it has received an ASSET_ANNOUNCE message recently that has the same DeviceID. If it finds one, it will send a TRACKER_FOUND message with the cached information.
 * @param deviceId - The CSRMesh Network ID of this device as an unsigned short
 * @param deviceIdToFind - DeviceId of the device that we want to find.
 */
- (void)findRequest:(NSNumber * _Nonnull)deviceId
     deviceIdToFind:(NSNumber * _Nonnull)deviceIdToFind
            success:(void (^)(NSNumber *deviceId,
                              NSNumber *rssi,
                              NSNumber *zone,
                              NSNumber *ageSeconds,
                              NSNumber *sideEffects)) success
            failure:(void (^)(NSError *error))failure;

/**
 * @brief Clear tracker cache
 * @param deviceId - The CSRMesh Network ID of this device as an unsigned short
 */
- (void)clearCacheRequest:(NSNumber * _Nonnull)deviceId;

/**
 * @brief Set tracker proximity config
 * @param deviceId - The CSRMesh Network ID of this device as an unsigned short
 * @param zone0RssiThreshold - Threshold in dBm for Zone 0  (signed). Default -60
 * @param zone1RssiThreshold - Threshold in dBm for Zone 1  (signed). Default -60
 * @param zone2RssiThreshold - Threshold in dBm for Zone 2  (signed). Default -60
 * @param cacheDeleteInterval - How long until cached entry is deleted (seconds). Default 600
 * @param delayOffset - Offset value for RSSI to delay computation. Default 60
 * @param delayFactor - Factor for RSSI to delay computation. Default 30
 * @param reportDest - Destination ID to which asset reports will be sent. Default 0
 */
- (void)setProximityConfigRequest:(NSNumber * _Nonnull)deviceId
               zone0RssiThreshold:(NSNumber * _Nonnull)zone0RssiThreshold
               zone1RssiThreshold:(NSNumber * _Nonnull)zone1RssiThreshold
               zone2RssiThreshold:(NSNumber * _Nonnull)zone2RssiThreshold
              cacheDeleteInterval:(NSNumber * _Nonnull)cacheDeleteInterval
                      delayOffset:(NSNumber * _Nonnull)delayOffset
                      delayFactor:(NSNumber * _Nonnull)delayFactor
                       reportDest:(NSNumber * _Nonnull)reportDest;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<TrackerModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<TrackerModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
