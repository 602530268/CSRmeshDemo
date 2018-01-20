//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header BearerModelApi is a part of the CSRmesh Api and provides a set of methods related to the Bearer Model.
 */


@protocol BearerModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetBearerState delegate. Invoked by the CSRmesh library upon receiving a State message fron the device
 * @param deviceId - The ID assigned by the library to this device
 * @param bearerRelayActive -  Unsigned Short Integer of the Bitfield of active relay bearers with bits mapped as follows
 *  Bit 0 = le_advertising
 *  Bit 1 = le_gatt_server
 *  Bit 2 = udp_ip_4
 *  Bit 3 = udp_ip_6
 *  Bit 4 = tcp_ip
 *  Bit 5 = wifi_beacon_bearer
 * @param bearerEnabled -  Unsigned Short Integer of the Bitfield of enabled bearers with bits mapps as follows
 *  Bit 0 = le_advertising
 *  Bit 1 = le_gatt_server
 *  Bit 2 = udp_ip_4
 *  Bit 3 = udp_ip_6
 *  Bit 4 = tcp_ip
 *  Bit 5 = wifi_beacon_bearer
 * @param promiscuous -  (NSNumber *) Unsigned Short Integer of the bitfield where each bit determines if the given bearer promiscuity is enabled. Enabled in this context means that the bearer can relay all traffic it receives even if it does not match any known NetworkKeys
 * Bit 0 = le_advertising
 * Bit 1 = le_gatt_server
 */
- (void)didGetBearerState:(NSNumber *)deviceId bearerRelayActive:(NSNumber *)bearerRelayActive bearerEnabled:(NSNumber *)bearerEnabled promiscuous:(NSNumber *)promiscuous meshRequestId:(NSNumber *)meshRequestId;

@end

@interface BearerModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

// Bearer Api Methods
/*!
 * @brief getState - Request the state from the given device. As this is an asynchronous process, the request will be returned via the didGetBearerState delegate call.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - The id of the message.
 */
- (NSNumber * _Nullable)getState:(NSNumber *)deviceId
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSNumber * _Nullable bearerRelayActive,
                                                     NSNumber * _Nullable bearerEnabled,
                                                     NSNumber * _Nullable promiscuous))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief setState - Set the device Bearer and Relay state to the values given. The delegate didGetBearerState will be invoked upon successful completion of this request.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param bearerRelayActive -  (NSNumber *)  Unsigned Short Integer of the Bitfield of active relay bearers with bits mapped as follows
 * Bit 0 = le_advertising
 * Bit 1 = le_gatt_server
 * Bit 2 = udp_ip_4
 * Bit 3 = udp_ip_6
 * Bit 4 = tcp_ip
 * Bit 5 = wifi_beacon_bearer
 * @param bearerEnabled - (NSNumber *) Unsigned Short Integer of the Bitfield of enabled bearers with bits mapps as follows
 * Bit 0 = le_advertising
 * Bit 1 = le_gatt_server
 * Bit 2 = udp_ip_4
 * Bit 3 = udp_ip_6
 * Bit 4 = tcp_ip
 * Bit 5 = wifi_beacon_bearer
 * @param promiscuous -  (NSNumber *) Unsigned Short Integer of the bitfield where each bit determines if the given bearer promiscuity is enabled. Enabled in this context means that the bearer can relay all traffic it receives even if it does not match any known NetworkKeys
 * Bit 0 = le_advertising
 * Bit 1 = le_gatt_server
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - The id of the message.
 */
- (NSNumber * _Nullable)setState:(NSNumber *)deviceId
               bearerRelayActive:(NSNumber *)bearerRelayActive
                   bearerEnabled:(NSNumber *)bearerEnabled
                     promiscuous:(NSNumber *)promiscuous
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSNumber * _Nullable bearerRelayActive,
                                                     NSNumber * _Nullable bearerEnabled,
                                                     NSNumber * _Nullable promiscuous))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<BearerModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<BearerModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
