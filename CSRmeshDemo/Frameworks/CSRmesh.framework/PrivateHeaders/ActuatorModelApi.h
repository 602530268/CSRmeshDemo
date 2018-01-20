//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

#ifndef  ACTUATORMODELAPI_H
#define ACTUATORMODELAPI_H    1

@import Foundation;
#import "CSRmeshApi.h"
#import "CSRsensorValue.h"

NS_ASSUME_NONNULL_BEGIN

@protocol ActuatorModelApiDelegate <NSObject>
@optional


/*!
 * @brief didGetActuatorTypes. An acknowledgement to the request to get the Actuator Types. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actuatorTypesArray - (NSArray *) Array of unsigned short NSNumber values that represent the Actuator types.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetActuatorTypes:(NSNumber *)deviceId
         actuatorTypesArray:(NSArray *)actuatorTypesArray
              meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didGetActuatorValue. An acknowledgement to the request to set the Actuator State. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actuatorValue - (CSRSensorValue *) The encoded actuator Type and value. Use the method getValue to obtain the converted value.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetActuatorValueAck:(NSNumber *)deviceId
                 actuatorValue:(CSRsensorValue *)actuatorValue
                 meshRequestId:(NSNumber *)meshRequestId;


@end


@interface ActuatorModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet *delegates;


/*!
 * @brief getTypes - request the Actuator Types that follow from the given given Actuator. If success is not nil then upon a successful transaction the success code block is executed and the callback didGetActuatorTypes shall be invoked. If the transaction fails then the failure code block shall be executed and the callback MeshServiceApi:didTimeoutMessage shall be invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param firstType - (CSRsensorType) The first actuator type as an unsigned short.
 * @param success - Code block executed upon a successful transaction. The success code block parameters are (NSNumber *deviceId, NSArray *actuatorTypes) where NSArray is NSNumber objects of CSRsensorType
 * @param failure - Code block executed upon a failed transaction.
 * @return meshRequestId - (NSNumber *) The id of the request. If success is nil then it is assumed an acknowledge is not required and therefore nil shall be returned.
 */
- (NSNumber * _Nullable)getTypes:(NSNumber *)deviceId
                       withFirstType:(CSRsensorType)firstType
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSArray * _Nullable actuatorTypes))success
                         failure:(CSRErrorCompletion _Nullable)failure;

- (NSNumber *)getTypes:(NSNumber *)deviceId
             firstType:(NSNumber *)firstType
               success:(void (^)(NSNumber *deviceId, NSArray *actuatorTypes)) success
               failure:(void (^)(NSError *error))failure
__deprecated_msg("use - (NSNumber * _Nullable)getTypes:(NSNumber *)deviceId firstType:(CSRsensorType)firstType success:(void (^ _Nullable)(NSNumber * _Nullable deviceId, NSArray * _Nullable actuatorTypes))success failure:(CSRErrorCompletion _Nullable)failure");

/*!
 * @brief setValue - Write the given value to the given actuator. If success is not nil then upon a successful transaction the success code block is executed and the callback didGetActuatorValue shall be invoked. If the transaction fails then the failure code block shall be executed and the callback MeshServiceApi:didTimeoutMessage shall be invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actuatorValue - (CSRSensorValue *) The encoded actuator Type and value. Use the method getValue to obtain the converted value.
 * @param success - Code block executed upon a successful transaction. The success code block parameters are (NSNumber *deviceId, CSRsensorValue *actuatorValue)
 * @param failure - Code block executed upon a failed transaction.
 * @return meshRequestId - (NSNumber *) The id of the request. If success is nil then it is assumed an acknowledge is not required and therefore nil shall be returned.
 */
- (NSNumber * _Nullable)setValue:(NSNumber *)deviceId
                   actuatorValue:(CSRsensorValue *) actuatorValue
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     CSRsensorValue * _Nullable actuatorValue))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

-(NSNumber *) setValue:(NSNumber *)deviceId
          actuatorType:(NSNumber *)actuatorType
         actuatorValue:(NSNumber *)actuatorValue
               success:(void (^)(NSNumber *deviceId, NSNumber *actuatorType, NSNumber *actuatorValue)) success
               failure:(void (^)(NSError *error))failure
__deprecated_msg("use - (NSNumber * _Nullable)setValue:(NSNumber *)deviceId actuatorValue:(CSRsensorValue *) actuatorValue success:(void (^ _Nullable)(NSNumber * _Nullable deviceId, CSRsensorValue * _Nullable actuatorValue))success failure:(void (^ _Nullable)(NSError * _Nullable error))failure");

/*!
 * @brief getValue - Request the value for the given actuator. Upon a successful transaction the success code block is executed and the callback didGetActuatorValue shall be invoked. If the transaction fails then the failure code block shall be executed and the callback MeshServiceApi:didTimeoutMessage shall be invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param sensorValue - (NSCSRsensorValue *) The encoded Type and Value
 * @param success - Code block executed upon a successful transaction. The success code block parameters are (NSNumber *deviceId, CSRsensorType actuatorType)
 * @param failure - Code block executed upon a failed transaction.
 * @return meshRequestId - (NSNumber *) The id of the request. If success is nil then it is assumed an acknowledge is not required and therefore nil shall be returned.
 */
- (NSNumber * _Nullable)getValue:(NSNumber *)deviceId
                    withActuatorType:(CSRsensorType)actuatorType
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     CSRsensorValue *_Nullable value))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

- (NSNumber *)getValue:(NSNumber *)deviceId
          actuatorType:(NSNumber *)actuatorType
               success:(void (^)(NSNumber *deviceId, NSNumber *actuatorType, NSNumber *actuatorValue)) success
               failure:(void (^)(NSError *error))failure
__deprecated_msg("use - (NSNumber * _Nullable)getValue:(NSNumber *)deviceId actuatorType:(CSRsensorType)actuatorType success:(void (^ _Nullable)(NSNumber * _Nullable deviceId, CSRsensorValue *_Nullable value))success failure:(void (^ _Nullable)(NSError * _Nullable error))failure");

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<ActuatorModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<ActuatorModelApiDelegate>)delegate;


@end

NS_ASSUME_NONNULL_END

#endif
