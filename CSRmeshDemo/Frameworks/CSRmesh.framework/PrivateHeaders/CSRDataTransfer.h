//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;

@interface CSRDataTransfer : NSObject

@property (nonatomic) NSNumber *_Nonnull currentSequenceNumber;

/// @brief The device id
@property (nonatomic) NSNumber * _Nonnull deviceId;

/// @brief Data to be sent
@property (nonatomic) NSData * _Nullable data;

/// @brief Set externally once the transfer is complete, i.e. has sent the final flush
@property (nonatomic) BOOL complete;

/// @brief The complete set of packets for the tranfer, including start flush and end flush.
@property (nonatomic) NSMutableDictionary * _Nullable blocks;

/// @brief The id for this request
@property (nonatomic) NSNumber * _Nonnull meshRequestId;



/*!
 * @brief initWithData create a new request and fill calculate the data packets to send.
 * @param data The data to send
 * @param deviceId The device number
 * @param meshRequestId The mesh request id
 */
- (id _Nonnull)initWithData:(NSData * _Nonnull)data deviceId:(NSNumber * _Nonnull)device meshRequestId:(NSNumber * _Nonnull)number;

/*!
 * @brief nextData Return the data to complete the next send
 * @param sequenceNumber The packet to send
 * @return NSData
*/
- (NSData * _Nonnull)nextData:(NSNumber * _Nonnull)sequenceNumber;

/*!
 * @brief acknowledge Returns true if this is the final packet (Flush)
 * @param sequenceNumber The packet to check
 * @return BOOL
 */
- (BOOL)acknowledge:(NSNumber * _Nonnull)sequenceNumber;

@end
