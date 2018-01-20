//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

#ifndef  POWERMODELAPI_H
#define POWERMODELAPI_H    1


@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/**
 @enum CSRPowerState - Power state values
 */
typedef NS_ENUM (NSInteger, CSRPowerState) {
    /** Off state */
    CSRPOwerState_Off = 0,
    /** On state */
    CSRPOwerState_On,
    /** Standby state */
    CSRPOwerState_Standby,
    /** On from Standby state */
    CSRPOwerState_OnFromStandby
};

@protocol PowerModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetPowerState. An acknowledgement to the request to getState, setPowerState. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param state - (NSNumber *) The current power state (0=Off, 1=On, 2=Standby, 3=On from Standby)
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetPowerState:(NSNumber *)deviceId
                   state:(NSNumber *)state
           meshRequestId:(NSNumber *)meshRequestId;

@end


@interface PowerModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief getState - Request the power state. The callback didGetPowerState is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The ID of this device. Refer to the delegate MeshServiceApi.didAssociateDevice
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)getState:(NSNumber *)deviceId
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSNumber * _Nullable state))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief setPowerState - Set the power state. The callback didGetPowerState is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param state - (NSNumber *) The desired power state (0=Off, 1=On, 2=Standby, 3=On from Standby)
 * @param success - Block called upon successful execution, set to nil to inhibit acknowledgement.
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)setPowerState:(NSNumber *)deviceId
                                state:(NSNumber *)state
                              success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                          NSNumber * _Nullable state)) success
                              failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief togglePowerState - If the current PowerState is 0x00, Off, then the PowerState shall be set to 0x01, On.
 If the current PowerState is 0x01, On, then the PowerState shall be set to 0x00, Off.
 If the current PowerState is 0x02, Standby, then the PowerState shall be set to 0x03, OnFromStandby. If the current PowerState is 0x03, OnFromStandby, then the PowerState shall be set to 0x02, Standby.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Block called upon successful execution, set to nil to inhibit acknowledgement.
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)togglePowerState:(NSNumber *)deviceId
                                 success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                             NSNumber * _Nullable state))success
                                 failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<PowerModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<PowerModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END

#endif
