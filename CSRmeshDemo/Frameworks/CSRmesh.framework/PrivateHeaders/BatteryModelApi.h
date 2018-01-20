//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header BatteryModelApi is a part of the CSRmesh Api and provides a set of methods related to the Battery Model.
 */

@protocol BatteryModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetBatteryState. An acknowledgement to the request to get the Battery State. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param batteryLevel - (NSNumber *) one octet - values from 0x00 to 0x64 that represent a linear scaling from empty to full capacity.
 * @param batteryState - (NSNumber *) one octet - Each bit is a Boolean value that determines if a given state is true or false. The value of zero is false, the value of one is true. Battery is powering device 0 ,Battery is charging 1 , Device is externally powered 2 , Service is required for battery 3 , Battery needs replacement 4.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetBatteryState:(NSNumber *)deviceId
              batteryLevel:(NSNumber *)batteryLevel
              batteryState:(NSNumber *)batteryState
             meshRequestId:(NSNumber *)meshRequestId;

@end

@interface BatteryModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief getState - request the Battery info from the CSRmesh device. The callback didGetBatteryState is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Block called upon successful execution. batteryLevel - (NSNumber *) one octet - values from 0x00 to 0x64 that represent a linear scaling from empty to full capacity.
 *batteryState - (NSNumber *) one octet - Each bit is a Boolean value that determines if a given state is true or false. The value of zero is false, the value of one is true. Battery is powering device 0 ,Battery is charging 1 , Device is externally powered 2 , Service is required for battery 3 , Battery needs replacement 4.
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)getState:(NSNumber *)deviceId
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSNumber * _Nullable batteryLevel,
                                                     NSNumber * _Nullable batteryState))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<BatteryModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<BatteryModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
