//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

@import Foundation;

NS_ASSUME_NONNULL_BEGIN

@interface CSRBeaconPayload : NSObject

/// @brief Number of total packets for BeaconModelApi setPayload method
@property (nonatomic) NSNumber * totalNumberOfPackets;

/// @brief The id for this request
@property (nonatomic) NSNumber * meshRequestId;

/// @brief The device id
@property (nonatomic) NSNumber * deviceId;

/// @brief The payload id
@property (nonatomic) NSNumber * payloadId;

/// @brief The payload id
@property (nonatomic) NSNumber * payloadType;

/// @brief Data to be sent
@property (nonatomic) NSData * _Nullable data;

/// @brief The complete set of packets for the tranfer.
@property (nonatomic) NSMutableArray * _Nullable packets;

/// @brief The complete set of packets for the tranfer.
@property (nonatomic) NSMutableDictionary * _Nullable receivedPackets;

/*!
 * @brief initWithData create a new request and fill calculate the data packets to send.
 * @param data The data to send
 * @param deviceId The device number
 * @param meshRequestId The mesh request id
 */
- (id)initWithData:(NSData *)data
                   deviceId:(NSNumber *)deviceId
              meshRequestId:(NSNumber *)number;

/*!
 * @brief initWithPayload create a new container for specific payloadId and deviceId ready to be filled with data packets.
 * @param payloadId The payloadId of the data
 * @param deviceId The device number
 * @param meshRequestId The mesh request id
 */
- (id)initWithPayloadId:(NSNumber *)payloadId
            payloadType:(NSNumber *)payloadType
               deviceId:(NSNumber *)deviceId
          meshRequestId:(NSNumber *)number;

/*!
 * @brief initWithDeviceId create a new container for specific payloadId and deviceId ready to be filled with data packets received from Proxy
 * @param deviceId The device number
 * @param meshRequestId The mesh request id
 */
- (id)initWithDeviceId:(NSNumber *)deviceId
         meshRequestId:(NSNumber *)number;

NS_ASSUME_NONNULL_END



@end
