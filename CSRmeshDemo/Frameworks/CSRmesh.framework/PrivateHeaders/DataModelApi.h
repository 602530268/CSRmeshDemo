//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header DataModelApi is a part of the CSRmesh Api and provides a set of methods related to the Data Model.
 */

@protocol DataModelApiDelegate <NSObject>
@optional

/*!
 * @brief didSendData. An acknowledgement to the request to sendData. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param data - (NSData *) The data sent.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didSendData:(NSNumber *)deviceId
               data:(NSData *)data
      meshRequestId:(NSNumber *)meshRequestId;


/*!
 * @brief didReceiveBlockData. Asynchronous callback upon receiving a block of data
 * @param destinationDeviceId - (NSNumber *) The destination DeviceId. Provided here in case it is either broadcast or group
 * @param sourceDeviceId - (NSNumber *) The sender's DeviceId.
 * @param data - (NSData *) The data sent.
 */
- (void)didReceiveBlockData:(NSNumber *)destinationDeviceId
             sourceDeviceId:(NSNumber *)sourceDeviceId
                       data:(NSData *)data ;


/*!
 * @brief didReceiveStreamData. Asynchronous callback upon receiving a packet of streamed data. More packets of data will follow until didReceiveStreamDataEnd. The receiver must assemble the parts in the correct order, as set by the stream number, to construct the whole.
 * @param deviceId - (NSNumber *) The ID of the sending device. Refer to the delegate MeshServiceApi.didAssociateDevice
 * @param streamNumber - (NSNumber *) offset in the stream for this data.
 * @param data - (NSData *) The data sent.
 */
- (void)didReceiveStreamData:(NSNumber *)deviceId
                streamNumber:(NSNumber *)streamNumber
                        data:(NSData *)data;

/*!
 * @brief didReceiveStreamDataEnd. Asynchronous callback to indicate end of stream. Terminates a stream receive.
 * @param deviceId - (NSNumber *) The ID of the sending device. Refer to the delegate MeshServiceApi.didAssociateDevice
 * @param streamNumber - (NSNumber *) total data bytes received.
 */
- (void)didReceiveStreamDataEnd:(NSNumber *)deviceId
                   streamNumber:(NSNumber *)streamNumber;

@end


@interface DataModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief sendData - Send data to device. The callback didSendData is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param data - (NSData *) Data, up to 250 octets.
 * @param success - Block called upon successful execution, if nil then data will be sent by Block Data transfer otherwise Stream data transfer
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetPowerState. For block data transfers, if the length of (NSData *)data exceeds 10 then the request will be rejected and a nil returned.
 */
- (NSNumber * _Nullable)sendData:(NSNumber *)deviceId
                            data:(NSData *)data
                         success:(void (^ _Nullable)(NSNumber * deviceId,
                                                     NSData * data))success
                         failure:(void (^ _Nullable)(NSError * error))failure;

/*!
 * @brief sendNext Try and send the next data stream item
 * @param deviceId The deviceId to try
 */
- (void)sendNext:(NSNumber *)deviceId;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<DataModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<DataModelApiDelegate>)delegate;


@end

NS_ASSUME_NONNULL_END
