//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

#ifndef  SENSORMODELAPI_H
#define SENSORMODELAPI_H    1

@import Foundation;
#import "CSRmeshApi.h"
#import "CSRsensorValue.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header SensorModelApi is a part of the CSRmesh Api and provides a set of methods related to the Sensor Model.
 */


@protocol SensorModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetSensorMissing. Unsolicited message to inform the library that a device has missing sensor types
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param sensorTypesArray - (NSArray *) Array of NSNumber objects of CSRsensorType.
 */
- (void)didGetSensorMissing:(NSNumber *)deviceId
           sensorTypesArray:(NSArray *)sensorTypesArray;

/*!
 * @brief didGetSensorTypes. An acknowledgement to the request to get the Sensor Types. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param sensorTypesArray - (NSArray *) Array of NSNumber objects of CSRsensorType.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetSensorTypes:(NSNumber *)deviceId
         sensorTypesArray:(NSArray *)sensorTypesArray
            meshRequestId:(NSNumber *)meshRequestId;


/*!
 * @brief didSetSensorState. An acknowledgement to the request to set the Sensor State. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param sensorType - (CSRsensorType) The sensor Type.
 * @param repeatInterval - (NSNumber *) The repeat Interval as an unsigned char.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetSensorState:(NSNumber *)deviceId
               sensorType:(CSRsensorType)sensorType
           repeatInterval:(NSNumber *)repeatInterval
            meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didGetSensorValue. An acknowledgement to the request to set the Sensor State. Provides the value for up to 2 sensor types. The value is of variable length from 0 to 4 octets. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param sensors - (NSArray) - Array of CSRsensorValue objects, maximum of two.
 * Temperature value will be of type float in units of kelvin and in steps of 1/32 or 0.03125
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetSensorValue:(NSNumber *)deviceId
                  sensors:(NSArray *)sensors
            meshRequestId:(NSNumber *)meshRequestId;

@end


@interface SensorModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief getTypes - request the Sensor Types that follow from the given sensor. Upon a successful transaction the success code block is executed with the parameters (NSNumber *deviceId, NSArray *sensorTypes) and the callback didGetSensorTypes is invoked. Upon a failed transaction the failure code block is executed and the callback MeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param firstType - (CSRsensorType) The first sensor type.
 * @param success - Block called upon successful execution. (NSNumber *deviceId, NSArray *sensorTypes) where NSArray contains NSNumber objects of CSRsensorType
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)getTypes:(NSNumber *)deviceId
                       firstType:(CSRsensorType) firstType
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSArray * _Nullable sensorTypes))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief setState - Set the given sensor to the given state. Upon a successful transaction the success code block is executes with the parameters (NSNumber *deviceId, NSNumber *sensorType, NSNumber *repeatInterval) and the callback didGetSensorState is invoked. Upon a failed transaction the failure code block is executed and the callback MeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param sensorType - (CSRsensorType) The sensor type.
 * @param repeatInterval - (NSNumber *) The sensor repeat interval state as an unsigned char.
 * @param success - Block called upon successful execution. (NSNumber *deviceId, CSRsensorType sensorType, NSNumber *repeatInterval)
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)setState:(NSNumber *)deviceId
                      sensorType:(CSRsensorType)sensorType
                  repeatInterval:(NSNumber *)repeatInterval
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     CSRsensorType sensorType,
                                                     NSNumber * _Nullable repeatInterval))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 * @brief getState - Get the state for the given sensor. The success code block is executed upon a successful transaction and the the callback didSetSensorState is invoked. The failure code block is executed upon an unsuccessful transaction and the callbackMeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param sensorType - (CSRsensorType) The sensor type as an unsigned short wrapped up in an NSNumber.
 * @param success - Upon a successful transaction, this code block is executed with the parameters (NSNumber *deviceId, CSRsensorType sensorType, NSNumber *repeatInterval)
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)getState:(NSNumber *)deviceId
                      withSensorType:(CSRsensorType)sensorType
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     CSRsensorType sensorType,
                                                     NSNumber * _Nullable repeatInterval)) success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

- (NSNumber *) getState:(NSNumber *)deviceId
            sensorType:(NSNumber *)sensorType
               success:(void (^)(NSNumber *deviceId,
                                 NSNumber *sensorType,
                                 NSNumber *repeatInterval)) success
               failure:(void (^)(NSError *error))failure
__deprecated_msg("use - (NSNumber * _Nullable)getState:(NSNumber *)deviceId sensorType:(CSRsensorType)sensorType success:(void (^ _Nullable)(NSNumber * _Nullable deviceId, CSRsensorType sensorType, NSNumber * _Nullable repeatInterval)) success failure:(void (^ _Nullable)(NSError * _Nullable error))failure");

/*!
 * @brief setValue - Write the given value to the given sensor. Up to two sensors can be written in one command. If success is not nil then the meshRequestId will be returned, otherwise nil will be returned. If success code block is not nil then it will be executed upon a successful transaction and the callback didGetSensorValue will be invoked. If the transaction fails then the failure code block is executed. If the success parameter is nil then CSRmesh acknowledgement will be supressed.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param sensors - (NSDictionary) - The key is the NSNumber of the sensor Type as an unsigned short and the Value is the NSNumber of the sensor value of size one to four octets.
 * Temperature value should be in Kelvin and of type float wrapped in an NSNumber.
 * @param success - Code block executed upon a successful transaction. The success code block parameters are (NSNumber *deviceId, NSArray *sensors), where the sensors NSArray is made up of CSRsensorValue objects
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)setValue:(NSNumber *)deviceId
                         sensor1:(CSRsensorValue *) sensor1
                         sensor2:(CSRsensorValue *) sensor2
                     acknowledge:(NSNumber *)ack
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSArray * _Nullable sensors))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

-(NSNumber *) setValue:(NSNumber *)deviceId
               sensors:(NSDictionary *)sensors
           acknowledge:(NSNumber *)ack
               success:(void (^)(NSNumber *deviceId, NSDictionary *sensors)) success
               failure:(void (^)(NSError *error))failure
__deprecated_msg("use - (NSNumber * _Nullable)setValue:(NSNumber *)deviceId sensor1:(CSRsensorValue *) sensor1 sensor2:(CSRsensorValue *) sensor2 acknowledge:(NSNumber *)ack success:(void (^ _Nullable)(NSNumber * _Nullable deviceId, NSArray * _Nullable sensors))success failure:(void (^ _Nullable)(NSError * _Nullable error))failure");

/*!
 * @brief getValue - Read the value for the given sensor(s). A read request for up to two sensors can be made in one command. Upon a successful transaction the success code block will be executed and the callback didGetSensorValue will be invoked. If the transaction is unsuccessful the failure code block will be executed and the callback MeshServiceApi:didTimeoutMessage will be invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param sensorType1 - (CSRsensorType) The first sensor type.
 * @param sensorType2 - (CSRsensorType) The second sensor type. select CSRsensorType_Unknown is not used.
 * @param success - Code block executed upon a successful transaction. The success code block parameters are (NSNumber *deviceId, NSArray *sensors), where the sensors NSArray is made up of CSRsensorValue objects
 * @param failure - Code block executed upon an unsuccessful transaction.
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState.
 */
- (NSNumber * _Nullable)getValue:(NSNumber *)deviceId
                     withSensorType1:(CSRsensorType)sensorType1
                     withSensorType2:(CSRsensorType)sensorType2
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSArray * _Nullable sensors))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

-(NSNumber *) getValue:(NSNumber *)deviceId
           sensorType1:(NSNumber *)sensorType1
           sensorType2:(NSNumber *)sensorType2
               success:(void (^)(NSNumber *deviceId,
                                 NSDictionary *sensors)) success
               failure:(void (^)(NSError *error))failure
__deprecated_msg("use - (NSNumber * _Nullable)getValue:(NSNumber *)deviceId sensorType1:(CSRsensorType)sensorType1 sensorType2:(CSRsensorType)sensorType2 success:(void (^ _Nullable)(NSNumber * _Nullable deviceId, NSDictionary * _Nullable sensors))success failure:(void (^ _Nullable)(NSError * _Nullable error))failure");

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<SensorModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<SensorModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END

#endif


