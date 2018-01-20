//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header GroupModelApi is a part of the CSRmesh Api and provides a set of methods related to the Group Model.
 */


@protocol GroupModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetNumModelGroupIds. Invoked by the CSRmesh library to indicate success:get Number of Model Group IDs. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param modelNo - (NSNumber *) The model number for which this calback is made.
 * @param numberOfModelGroupIds - (NSNumber *) The number of Group indexes supported by this model
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetNumModelGroupIds:(NSNumber *)deviceId
                       modelNo:(NSNumber *)modelNo
         numberOfModelGroupIds:(NSNumber *)numberOfModelGroupIds
                 meshRequestId:(NSNumber *)meshRequestId;



/*!
 * @brief didSetModelGroupId. Invoked by the CSRmesh library to indicate success:set Model Group ID
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param modelNo - (NSNumber *) The model number
 * @param groupIndex - (NSData *) The offset of the groupID in the table of Group indexes supported by the model
 * @param instance - (NSNumber *) The model instance
 * @param groupId - (NSNumber *) The group ID is an unsigned 16-bit number.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didSetModelGroupId:(NSNumber *)deviceId
                   modelNo:(NSNumber *)modelNo
                groupIndex:(NSNumber *)groupIndex
                  instance:(NSNumber *)instance
                   groupId:(NSNumber *)groupId
             meshRequestId:(NSNumber *)meshRequestId;

@end



@interface GroupModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief getNumModelGroupIds - Request the Total number of Group Ids for a Model. The callback didGetNumModelGroupIds is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param modelNo - (NSNumber *) The Model number for the Group IDs request
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetNumModelGroupIds.
 */
- (NSNumber * _Nullable)getNumModelGroupIds:(NSNumber *)deviceId
                                    modelNo:(NSNumber *)modelNo
                                    success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                                NSNumber * _Nullable modelNo,
                                                                NSNumber * _Nullable numberOfModelGroupIds))success
                                    failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief setModelGroupId - Set Group Id for a Model, group index and model instance. The callback didSetModelGroupId is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param modelNo - (NSNumber *) The Model number for the Group IDs request
 * @param groupIndex - (NSNumber *) A number of Group IDs can be stored in a model instance, this is determined by a call to
 * @param instance - (NSNumber *) The model instance for this device for which the Group ID for the given group index is set
 * @param groupId - (NSNumber *) The groupId to be set for the given Model, intance and Group index
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetNumModelGroupIds.
 */
- (NSNumber * _Nullable)setModelGroupId:(NSNumber *)deviceId
                                modelNo:(NSNumber *)modelNo
                             groupIndex:(NSNumber *)groupIndex
                               instance:(NSNumber *)instance
                                groupId:(NSNumber *)groupId
                                success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                            NSNumber * _Nullable modelNo,
                                                            NSNumber * _Nullable groupIndex,
                                                            NSNumber * _Nullable instance,
                                                            NSNumber * _Nullable groupId))success
                                failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 * @brief getModelGroupId - Get Group Id for a Model and group index. The callback didSetModelGroupId is invoked upon success. The MeshServiceApi:didTimeoutMessage is invoked on failure.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param modelNo - (NSNumber *) The Model number for the Group IDs request
 * @param groupIndex - (NSNumber *) A number of Group IDs can be stored in a model instance, this is determined by a call to
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - (NSNumber *) The id of the request. Pair up with the id returned in didGetNumModelGroupIds.
 */
- (NSNumber * _Nullable)getModelGroupId:(NSNumber *)deviceId
                                modelNo:(NSNumber *)modelNo
                             groupIndex:(NSNumber *)groupIndex
                                success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                            NSNumber * _Nullable modelNo,
                                                            NSNumber * _Nullable groupIndex,
                                                            NSNumber * _Nullable instance,
                                                            NSNumber * _Nullable groupId))success
                                failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<GroupModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<GroupModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END

