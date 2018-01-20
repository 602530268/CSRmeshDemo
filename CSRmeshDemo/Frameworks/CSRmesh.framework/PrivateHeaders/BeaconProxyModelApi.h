//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

/*!
 * @header BeaconProxyModelApi is a part of the CSRmesh Api and provides a set of methods related to the Beacon Proxy Model.
 */

NS_ASSUME_NONNULL_BEGIN

@protocol BeaconProxyModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetBeaconProxyStatus. An acknowledgement to the request to getStatus. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param numberOfManagedNodes - (NSNumber *) The number of nodes proxy currenlt manages as an unsigned short wrapped up in an NSNumber.
 * @param numberOfQueuedTxMessages - (NSNumber *) The number of currently queued messages for transmission to beacons as an unsigned integer wrapped up in an NSNumber.
 * @param numberOfQueuedRxMessages - (NSNumber *) The number of currently queued messages for transmission by beacons as an unsigned integer wrapped up in an NSNumber.
 * @param maxQueueSize - (NSNumber *) The queue size in units of 256 messages (1=256, 2=512 etc.) as an unsigned short wrapped up in an NSNumber.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetBeaconProxyStatus:(NSNumber *)deviceId
           numberOfManagedNodes:(NSNumber *)numberOfManagedNodes
          numberOfManagedGroups:(NSNumber *)numberOfManagedGroups
       numberOfQueuedTxMessages:(NSNumber *)numberOfQueuedTxMessages
       numberOfQueuedRxMessages:(NSNumber *)numberOfQueuedRxMessages
                   maxQueueSize:(NSNumber *)maxQueueSize;
/*!
 * @brief didGetBeaconProxyDevices. An acknowledgement to the request to getDevices.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param numberOfManagedGroups - (NSNumber *) The number of managed groups, which is unsigned char wrapped up in an NSNumber.
 * @param numberOfManagedDevices - (NSNumber *) The number of managed devices, which is unsigned short wrapped up in an NSNumber.
 * @param managedGroups - (NSArray *) The array of group IDs, each of which is unsigned short wrapped up in an NSNumber.
 * @param managedDevices - (NSArray *) The array of device IDs, each of which is unsigned short wrapped up in an NSNumber.
 */
- (void)didGetBeaconProxyDevices:(NSNumber *)deviceId
           numberOfManagedGroups:(NSNumber *)numberOfManagedGroups
           numberOfManagedDevices:(NSNumber *)numberOfManagedDevices
                   managedGroups:(NSArray *)managedGroups
                  managedDevices:(NSArray *)managedDevices;

@end

@interface BeaconProxyModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief addDevices - Add devices to the Beacon proxy list of managed devices. The success code block is executed upon a successful transaction. The failure code block is executed upon an unsuccessful transaction and the callbackMeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param firstDeviceIsGroup - (BOOL) YES, means the the first Device in deviceAddresses is a Group
 * @param deviceAddresses - (NSArray *) The device addresses to add. The first device will be assumed to be a group if firstDeviceIsGroup is YES. Each memeber of the array is an unsigned short (16-bit) wrapped in an NSNumber. A maximum of 4 addresses are allowed, additional addresses will be discarded.
 * @param success - Upon a successful transaction, this code block is executed with the parameters ((NSNumber * _Nullable deviceId).
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. nil will be returned if the deviceAddresses contains no objects.
 */
- (NSNumber * _Nullable)addDevices:(NSNumber *)deviceId
                firstDeviceIsGroup:(BOOL)firstDeviceIsGroup
                   deviceAddresses:(NSArray *)deviceAddresses
                           success:(void (^ _Nullable)(NSNumber * _Nullable deviceId))success
                           failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief removeDevices - Remove devices to the Beacon proxy list of managed devices. The success code block is executed upon a successful transaction. The failure code block is executed upon an unsuccessful transaction and the callbackMeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param firstDeviceIsGroup - (BOOL) YES, means the the first Device in deviceAddresses is a Group
 * @param deviceAddresses - (NSArray *) The device addresses to remove (first address can be a group address) as an array of unsigned short values wrapped up in an NSNumber (total of 4 addresses maximum - unsigned long long).
 * @param success - Upon a successful transaction, this code block is executed with the parameters ((NSNumber * _Nullable deviceId).
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request.
 */
- (NSNumber * _Nullable)removeDevices:(NSNumber *)deviceId
                   firstDeviceIsGroup:(BOOL)firstDeviceIsGroup
                      deviceAddresses:(NSArray *)deviceAddresses
                              success:(void (^ _Nullable)(NSNumber * _Nullable deviceId))success
                              failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief clearQueue - Clear messages queue for devices managed by Beacon proxy. The success code block is executed upon a successful transaction. The failure code block is executed upon an unsuccessful transaction and the callbackMeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param firstDeviceIsGroup - (BOOL) YES, means the the first Device in deviceAddresses is a Group
 * @param deviceAddresses - (NSArray *) The device addresses to add. The first device will be assumed to be a group if firstDeviceIsGroup is YES. Each memeber of the array is an unsigned short (16-bit) wrapped in an NSNumber. A maximum of 4 addresses are allowed, additional addresses will be discarded.
 * @param success - Upon a successful transaction, this code block is executed with the parameters ((NSNumber * _Nullable deviceId).
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. nil will be returned if the deviceAddresses contains no objects.
 */
- (NSNumber * _Nullable)clearQueue:(NSNumber *)deviceId
                firstDeviceIsGroup:(BOOL)firstDeviceIsGroup
                   deviceAddresses:(NSArray *)deviceAddresses
                           success:(void (^ _Nullable)(NSNumber * _Nullable deviceId))success
                           failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief removeDevices - Stop Beacon proxy to be proxy for everyone. The success code block is executed upon a successful transaction. The failure code block is executed upon an unsuccessful transaction and the callbackMeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Upon a successful transaction, this code block is executed with the parameters ((NSNumber * _Nullable deviceId).
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request.
 */
- (NSNumber * _Nullable)stopProxy:(NSNumber *)deviceId
                          success:(void (^ _Nullable)(NSNumber * _Nullable deviceId))success
                          failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief stopProxy - Get current status of Beacon proxy. This is delegate driven method hence assigment to delegate is required. Delegate callback will arrive to - (void)didGetBeaconProxyStatus:(NSNumber *)deviceId numberOfManagedNodes:(NSNumber *)numberOfManagedNodes numberOfManagedGroups:(NSNumber *)numberOfManagedGroups numberOfQueuedTxMessages:(NSNumber *)numberOfQueuedTxMessages numberOfQueuedRxMessages:(NSNumber *)numberOfQueuedRxMessages maxQueueSize:(NSNumber *)maxQueueSize
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 */
- (NSNumber * _Nullable)getStatus:(NSNumber *)deviceId;

/*!
 * @brief getDevices - Get number of groups and devices currently managed by Beacon proxy. The success code block is executed upon a successful transaction. The failure code block is executed upon an unsuccessful transaction and the callbackMeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Upon a successful transaction, this code block is executed with the parameters (NSNumber * _Nullable deviceId, NSNumber * _Nullable numberOfManagedGroups, NSNumber * _Nullable numberOfManagedDevices, NSArray * _Nullable managedGroups, NSArray * _Nullable managedDevices).
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetBeaconProxyDevices.
 */
- (NSNumber * _Nullable)getDevices:(NSNumber *)deviceId
                           success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                       NSNumber * _Nullable numberOfManagedGroups,
                                                       NSNumber * _Nullable numberOfManagedDevices,
                                                       NSArray * _Nullable managedGroups,
                                                       NSArray * _Nullable managedDevices))success
                           failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<BeaconProxyModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<BeaconProxyModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
