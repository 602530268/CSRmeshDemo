//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

#ifndef LIGHTMODELAPI_H
#define LIGHTMODELAPI_H    1


@import Foundation;
@import UIKit;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header LightModelApi is a part of the CSRmesh Api and provides a set of methods related to the Light Model.
 */



@protocol LightModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetLightState. An acknowledgement to the request to getState, setColorTemperature, setRgb, setLevel. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param red - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param green - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param blue - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param level - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param powerState - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param colorTemperature - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param supports - (NSNumber *) unsigned char wrapped in an NSNumber. Support Bits
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetLightState:(NSNumber *)deviceId
                     red:(NSNumber *)red
                   green:(NSNumber *)green
                    blue:(NSNumber *)blue
                   level:(NSNumber *)level
              powerState:(NSNumber *)powerState
        colorTemperature:(NSNumber *)colorTemperature
                supports:(NSNumber *)supports
           meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didGetWhiteLevel. Unsolicited message from the light
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param level - (NSNumber *) The light power level
 */
- (void)didGetWhiteLevel:(NSNumber *)deviceId
                   level:(NSNumber *)level;

@end



@interface LightModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief getState - Request the light state. The callback didGetLightState is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetLightState.
 */
- (NSNumber * _Nullable)getState:(NSNumber *)deviceId
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     UIColor * _Nullable color,
                                                     NSNumber * _Nullable powerState,
                                                     NSNumber * _Nullable colorTemperature,
                                                     NSNumber * _Nullable supports))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;
/*!
 * @brief setColorTemperature - Set the colour temperature.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param temperature - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param duration - (NSNumber *) unsigned 16-bit wrapped in NSNumber and represents time in millieseconds over which the temperature will fade.
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetLightState.
 */
- (NSNumber * _Nullable)setColorTemperature:(NSNumber *)deviceId
                                temperature:(NSNumber *)temperature
                                   duration:(NSNumber *)duration
                                    success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                                UIColor * _Nullable color,
                                                                NSNumber * _Nullable powerState,
                                                                NSNumber * _Nullable colorTemperature,
                                                                NSNumber * _Nullable supports))success
                                    failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief setRgb - Set the colour.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param color - (UIColor *) Light color. The alpha value is level.
 * @param duration - (NSNumber *) unsigned 16-bit wrapped in NSNumber and represents time in millieseconds over which the temperature will fade.
 * @param success - Block called upon successful execution, set nil to inhibit acknowledgement
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetLightState.
 */
- (NSNumber * _Nullable)setColor:(NSNumber *)deviceId
                           color:(UIColor *)color
                        duration:(NSNumber *)duration
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     UIColor * _Nullable color,
                                                     NSNumber * _Nullable powerState,
                                                     NSNumber * _Nullable colorTemperature,
                                                     NSNumber * _Nullable supports))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 * @brief setPowerLevel - Set power state and then move the power level to the given value over the given duration
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param powesrState - (NSNumber *) unsigned char of the power state
 * @param level - (NSNumber *) unsigned char of the power level
 * @param levelDuration - (NSNumber *) unsigned short of the fade time, in mS
 * @param sustain - (NSNumber *) unsigned short of the wait before fade time, in mS
 * @param decay - (NSNumber *) unsigned short of the time for the light to decay to 0, in mS
 * @param success - Block called upon successful execution, set nil to inhibit acknowledgement
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetLightState.
 */
- (NSNumber * _Nullable)setPowerLevel:(NSNumber *)deviceId
                           powerState:(NSNumber *)powerState
                                level:(NSNumber *)level
                        levelDuration:(NSNumber *)levelDuration
                              sustain:(NSNumber *)sustain
                                decay:(NSNumber *)decay
                              success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                          UIColor * _Nullable color,
                                                          NSNumber * _Nullable powerState,
                                                          NSNumber * _Nullable colorTemperature,
                                                          NSNumber * _Nullable supports))success
                              failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 * @brief setLevel - Set the Intensity.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param level - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param success - Block called upon successful execution, set nil to inhibit acknowledgement
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetLightState.
 */
- (NSNumber * _Nullable)setLevel:(NSNumber *)deviceId
                           level:(NSNumber *)level
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     UIColor * _Nullable color,
                                                     NSNumber * _Nullable powerState,
                                                     NSNumber * _Nullable colorTemperature,
                                                     NSNumber * _Nullable supports))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief setWhite - Set the White level.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param level - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param duration - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param success - Block called upon successful execution, set nil to inhibit acknowledgement
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetLightState.
 */
- (NSNumber * _Nullable)setWhite:(NSNumber *)deviceId
                           level:(NSNumber *)level
                        duration:(NSNumber *)duration
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSNumber * _Nullable whiteLevel))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief getWhite - Set the White level.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Block called upon successful execution, set nil to inhibit acknowledgement
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetLightState.
 */
- (NSNumber * _Nullable)getWhite:(NSNumber *)deviceId
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSNumber * _Nullable whiteLevel))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<LightModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<LightModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END

#endif


