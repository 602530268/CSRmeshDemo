//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

/*!
 * @header BeaconModelApi is a part of the CSRmesh Api and provides a set of methods related to the Beacon Model.
 */

NS_ASSUME_NONNULL_BEGIN

@protocol BeaconModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetBeaconStatus. An acknowledgement to the request to set the Beacon Status. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param type - (NSNumber *) The beacon Type as an unsigned char NSNumber.
 * @param beaconInterval - (NSNumber *) The interval between beacon transmissions as an unsigned char.
 * @param meshInterval - (NSNumber *) The interval between mesh wakeups as an unsigned short.
 * @param meshTime - (NSNumber *) The time for which beacon stays as a mesh node as an unsigned char.
 * @param txPower - (NSNumber *) The TX power as an unsigned char.
 * @param batteryLevel - (NSNumber *) The battery level as an unsigned char.
 * @param payloadId - (NSNumber *) The Id of latest received payload for this beacon type an unsigned short.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetBeaconStatus:(NSNumber *)deviceId
                      type:(NSNumber *)type
            beaconInterval:(NSNumber *)beaconInterval
              meshInterval:(NSNumber *)meshInterval
                  meshTime:(NSNumber *)meshTime
                   txPower:(NSNumber *)txPower
              batteryLevel:(NSNumber *)batteryLevel
                 payloadId:(NSNumber *) payloadId
             meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didGetBeaconTypes. An acknowledgement to the request to get the Beacon types. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param beaconTypes - (NSArray *) The beacon types as a NSArray of enums wrapped up in NSNumbers.
 * @param batteryLevel - (NSNumber *) Battery level as an unsigned char wrapped up in a NSNumber
 * @param timeSinceLastMessage - (NSNumber *) Time in 10s of seconds since last message received. Unsigned short wrapped up in a NSNumber. 0 means that message was received less than 10 seconds ago, 1 means 10..19 seconds, etc. Special 0xFFFF value means that no messages have been received since proxy was last started. When message was received directly from beacon this value is always 0.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetBeaconTypes:(NSNumber *)deviceId
              beaconTypes:(NSArray *)beaconTypes
             batteryLevel:(NSNumber *)batteryLevel
     timeSinceLastMessage:(NSNumber *)timeSinceLastMessage
            meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didSetBeaconPayload. An acknowledgement to the request to setPayload. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param payloadType - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param ackNack - (NSNumber *) unsigned short wrapped in an NSNumber.
 * @param payloadId - (NSNumber *) unsigned short wrapped in an NSNumber.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didSetBeaconPayload:(NSNumber *)deviceId
                payloadType:(NSNumber *)payloadType
                    ackNack:(NSNumber *)ackNack
                  payloadId:(NSNumber *)payloadId
              meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didGetBeaconPayload. An acknowledgement to the request to setPayload. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param payloadType - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param payloadId - (NSNumber *) unsigned short wrapped in an NSNumber.
 * @param payloadOffset - (NSNumber *) unsigned char wrapped in an NSNumber.
 * @param payloadData - (NSData *) Beacon payload data.
 */
- (void)didGetBeaconPayload:(NSNumber *)deviceId
                payloadType:(NSNumber *)payloadType
                  payloadId:(NSNumber *)payloadId
              payloadOffset:(NSNumber *)payloadOffset
                payloadData:(NSData *)payloadData;

@end

/**
 @enum CSRBeaconType - Beacon types
 */
typedef NS_ENUM (NSInteger, CSRBeaconType) {
    /** CSRmesh Beacon */
    CSRBeaconType_CSR = 0,
    /** iBeacon */
    CSRBeaconType_iBeacon,
    /** Eddystone URL */
    CSRBeaconType_EddystoneURL,
    /** Eddystone URL */
    CSRBeaconType_EddystoneUID,
    /** LTEDirect */
    CSRBeaconType_LTEdirect,
    /** Lumicast */
    CSRBeaconType_Lumicast
};

@interface BeaconModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief setStatus - Set the status for the given beacon. The success code block is executed upon a successful transaction. The failure code block is executed upon an unsuccessful transaction and the callbackMeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param type - (CSRBeaconType) The beacon type.
 * @param beaconInterval - (NSNumber *) The interval between beacon transmissions as an unsigned char.
 * @param meshInterval - (NSNumber *) The interval between mesh wakeups as an unsigned short.
 * @param meshTime - (NSNumber *) The time for which beacon stays as a mesh node as an unsigned char.
 * @param txPower - (NSNumber *) The TX power as an unsigned char.
 * @param success - Upon a successful transaction, this code block is executed with the parameters (NSNumber * deviceId, NSNumber * type, NSNumber * beaconInterval, NSNumber * meshInterval, NSNumber * meshTime, NSNumber * txPower, NSNumber * batteryLevel, NSNumber * payloadId).
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetBeaconState.
 */
- (NSNumber * _Nullable)setStatus:(NSNumber *)deviceId
                       beaconType:(CSRBeaconType)type
                   beaconInterval:(NSNumber *)beaconInterval
                     meshInterval:(NSNumber *)meshInterval
                         meshTime:(NSNumber *)meshTime
                          txPower:(NSNumber *)txPower
                          success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                      NSNumber * _Nullable type,
                                                      NSNumber * _Nullable beaconInterval,
                                                      NSNumber * _Nullable meshInterval,
                                                      NSNumber * _Nullable meshTime,
                                                      NSNumber * _Nullable txPower,
                                                      NSNumber * _Nullable batteryLevel,
                                                      NSNumber * _Nullable lastPayloadId))success
                          failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 * @brief getStatus - Get the status for the given beacon. The success code block is executed upon a successful transaction. The failure code block is executed upon an unsuccessful transaction and the callbackMeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param type - (CSRBeaconType) The beacon type.
 * @param success - Upon a successful transaction, this code block is executed with the parameters (NSNumber * deviceId, NSNumber * type, NSNumber * beaconInterval, NSNumber * meshInterval, NSNumber * meshTime, NSNumber * txPower, NSNumber * batteryLevel, NSNumber * payloadId).
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetBeaconState.
 */
- (NSNumber * _Nullable)getStatus:(NSNumber *)deviceId
                       beaconType:(CSRBeaconType)type
                          success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                      NSNumber * _Nullable type,
                                                      NSNumber * _Nullable beaconInterval,
                                                      NSNumber * _Nullable meshInterval,
                                                      NSNumber * _Nullable meshTime,
                                                      NSNumber * _Nullable txPower,
                                                      NSNumber * _Nullable batteryLevel,
                                                      NSNumber * _Nullable payloadId))success
                          failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief getBeaconTypes - Get the types for the given beacon. The success code block is executed upon a successful transaction. The failure code block is executed upon an unsuccessful transaction and the callbackMeshServiceApi:didTimeoutMessage is invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Upon a successful transaction, this code block is executed with the parameters (NSNumber * deviceId, NSNumber * type, NSNumber * beaconInterval, NSNumber * meshInterval, NSNumber * meshTime, NSNumber * txPower, NSNumber * batteryLevel, NSNumber * payloadId).
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetBeaconState.
 */
- (NSNumber * _Nullable)getBeaconTypes:(NSNumber *)deviceId
                               success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                           NSArray * _Nullable beaconTypes,
                                                           NSNumber * _Nullable batteryLevel,
                                                           NSNumber * _Nullable timeSinceLastMessage))success
                               failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief setPayload - Set Beacon Payload for given beacon device id. If success is not nil then upon a successful transaction the success code block is executed and the callback didSetBeaconPayload shall be invoked. If the transaction fails then the failure code block shall be executed and the callback MeshServiceApi:didTimeoutMessage shall be invoked.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param payloadId - (NSNumber *) The ID of the payload as an unsigned short wrapped up in a NSNumber.
 * @param payloadOffset - (NSNumber *) The offset of the payload as an unsigned char wrapped up in a NSNumber.
 * @param beaconType - (NSNumber *) The beacon type.
 * @param payload - (NSData *) The payload data for a beacon, up to 120 octets.
 * @param success - Code block executed upon a successful transaction. The success code block parameters are (NSNumber * deviceId, NSNumber * payloadType, NSNumber * ackNack, NSNumber * payloadId)
 * @param failure - Code block executed upon a failed transaction.
 * @return meshRequestId - (NSNumber *) The id of the request. If success is nil then it is assumed an acknowledge is not required and therefore nil shall be returned.
 */
- (NSNumber * _Nullable)setPayload:(NSNumber *)deviceId
                         payloadId:(NSNumber *)payloadId
                     payloadOffset:(NSNumber *)payloadOffset
                        beaconType:(CSRBeaconType)type
                           payload:(NSData *)data
                           success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                       NSNumber * _Nullable payloadType,
                                                       NSNumber * _Nullable ackNack,
                                                       NSNumber * _Nullable payloadId))success
                           failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief getPayload - Get Beacon Payload for given beacon device id. If success is not nil then upon a successful transaction the success code block is executed and the callback didGetBeaconPayload shall be invoked. If the transaction fails then the failure code block shall be executed and the callback MeshServiceApi:didTimeoutMessage shall be invoked.
 Due to the fact that incoming payload parts can be sent asynchronously, ideally subscribe to the delegate method - (void)didGetBeaconPayload:(NSNumber *)deviceId payloadId:(NSNumber *)payloadId payloadType:(NSNumber *)payloadType payloadData:(NSData *)payloadData. This method will return be executed once the whole payload has been received.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param payloadType - (NSNumber *) The beacon type.
 * @param success - Code block executed upon a successful transaction. The success code block parameters are (NSNumber * deviceId,  NSNumber * payloadType, NSData * payloadData). One or more messages will be received in response (use delegate).
 * @param failure - Code block executed upon a failed transaction.
 * @return meshRequestId - (NSNumber *) The id of the request. If success is nil then it is assumed an acknowledge is not required and therefore nil shall be returned.
 */
- (NSNumber * _Nullable)getPayload:(NSNumber *)deviceId
                       payloadType:(CSRBeaconType)payloadType
                           success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                       NSNumber * _Nullable payloadType,
                                                       NSNumber * _Nullable payloadId,
                                                       NSNumber * _Nullable payloadOffset,
                                                       NSData * _Nullable payloadData))success
                           failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<BeaconModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<BeaconModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
