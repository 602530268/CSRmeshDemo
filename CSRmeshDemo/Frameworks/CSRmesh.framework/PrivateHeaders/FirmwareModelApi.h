//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header FirmwareModelApi is a part of the CSRmesh Api and provides a set of methods related to the Firmware Model.
 */

@protocol FirmwareModelApiDelegate <NSObject>
@optional

/*!
 * @brief didSetUpdateRequired. Invoked by the CSRmesh library to indicate success:set Device to Firmware update mode. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didSetUpdateRequired:(NSNumber *)deviceId
               meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didSetUpdateRequired. Invoked by the CSRmesh library to indicate success:set Device to Firmware update mode. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param versionMajor - (NSNumber *) unsigned Short of the major portion of the version number
 * @param versionMinor - (NSNumber *) unsigned Short of the minor portion of the version number
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetVersionInfo:(NSNumber *)deviceId
             versionMajor:(NSNumber *)versionMajor
             versionMinor:(NSNumber *)versionMinor
            meshRequestId:(NSNumber *)meshRequestId;
@end


@interface FirmwareModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief setUpdateRequired - Request the device to enter Firmware Update Mode. The callback didSetUpdateRequired is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didSetUpdateRequired.
 */
- (NSNumber * _Nullable)setUpdateRequired:(NSNumber *)deviceId
                                  success:(void (^ _Nullable)(NSNumber * _Nullable deviceId))success
                                  failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 * @brief getVersionInfo - Request the device software version. The callback didGetVersionInfo is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetVersionInfo.
 */
- (NSNumber * _Nullable)getVersionInfo:(NSNumber *)deviceId
                               success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                           NSNumber * _Nullable versionMajor,
                                                           NSNumber * _Nullable versionMinor))success
                               failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<FirmwareModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<FirmwareModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
