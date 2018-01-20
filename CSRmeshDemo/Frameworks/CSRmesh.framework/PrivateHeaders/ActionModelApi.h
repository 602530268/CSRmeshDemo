//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

@import Foundation;
@import UIKit;
#import "CSRmeshApi.h"
#import "CSRmeshAction.h"

NS_ASSUME_NONNULL_BEGIN

@protocol ActionModelApiDelegate <NSObject>
@optional

/*!
 * @brief didsetAction. An acknowledgement to the request to get the Action Types. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actionId - (NSNumber *) The ID of this action (8-bit value in the range 0..31)
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */

- (void)didSetAction:(NSNumber *)deviceId
            actionId:(NSNumber *)actionId
       meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didGetAction. An acknowledgement to the request to get the Action Types. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actionId - (NSNumber *) The ID of this action (8-bit value in the range 0..31)
 * @param meshAction (CSRMeshAction *) MeshAction
 * @param timeType - (NSNumber *) timeType as follows
 0x02 - Absolute time in seconds from 1st January 2015 – not recurring
 0x03 - Absolute time in seconds from 1st January 2015 – recurring. The relative time (3 bytes) has to be provided – this will be used to express the number of second to wait after each triggering
 0x04 - Relative time in seconds from the point of reception - first field (4 bytes) will be used to express time. Not recurring.
 0x05 - Relative time in seconds from the point of reception - first field (4 bytes) will be used to express time. recurring. The relative time (3 bytes) has to be provided – this will be used to express the number of second to wait after each triggering
 * @param triggerTime (NSNumber *) Trigger Action after this many seconds have elapsed.
 * @param recurringTime (NSNumber *) Number of seconds to wait after each triggering. 0 if not recurring.
 * @param recurrences (NSNumber *) Number of times to recur, must be >0 if recurringSeconds>0
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */

- (void)didGetAction:(NSNumber *)deviceId
            actionId:(NSNumber *)actionId
          meshAction:(CSRMeshAction *)meshAction
            timeType:(NSNumber *)timeType
         triggerTime:(NSNumber *)triggerTime
       recurringTime:(NSNumber *)recurringTime
         recurrences:(NSNumber *)recurrences
       meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didDeleteAction. An acknowledgement to the request to get the Action Types. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actionIdsDeleted - (NSNumber *) The ID of this action (8-bit value in the range 0..31)
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */

- (void)didDeleteAction:(NSNumber *)deviceId
       actionIdsDeleted:(NSNumber *)actionIdsDeleted
          meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didGetStatus. An acknowledgement to the request to get the Action Types. This callback will be replaced with success and failure code blocks in the next version therefore please discontinue its use.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actionId - (NSNumber *) The ID of this action (8-bit value in the range 0..31)
 * @param maxActions - (NSNumber *) max number of actions
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */

- (void)didGetStatus:(NSNumber *)deviceId
            actionId:(NSNumber *)actionId
          maxActions:(NSNumber *)maxActions
       meshRequestId:(NSNumber *)meshRequestId;


@end


@interface ActionModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/**
 * @brief setAction. Define the action that needs to be taken.
 *
 *
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actionId (NSNumber *) The ID of this action (8-bit value in the range 0..31)
 * @param meshAction (CSRMeshAction *) MeshAction
 * @param absoluteTriggerTime (NSDate *) Absolute time that the action will be triggered.
 * @param recurringSeconds (NSNumber *) Number of seconds to wait after each triggering. 0 if not recurring.
 * @param recurrences (NSNumber *) Number of times to recur, must be >0 if recurringSeconds>0
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable)setAction:(NSNumber *)deviceId
                         actionId:(NSNumber *)actionId
                       meshAction:(CSRMeshAction *)meshAction
              absoluteTriggerTime:(NSDate *)absoluteTriggerTime
                 recurringSeconds:(NSNumber *)recurringSeconds
                      recurrences:(NSNumber *)recurrences
                          success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                      NSNumber * _Nullable actionId))success
                          failure:(void (^ _Nullable)(NSError * _Nullable error))failure;



/**
 * @brief setAction. Define the action that needs to be taken.
 *
 *
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actionId (NSNumber *) The ID of this action (8-bit value in the range 0..31)
 * @param meshAction (CSRMeshAction *) MeshAction
 * @param relativeTime (NSNumber *) Trigger Action after this many seconds have elapsed.
 * @param recurringSeconds (NSNumber *) Number of seconds to wait after each triggering. 0 if not recurring.
 * @param recurrences (NSNumber *) Number of times to recur, must be >0 if recurringSeconds>0
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable)setAction:(NSNumber *)deviceId
                         actionId:(NSNumber *)actionId
                       meshAction:(CSRMeshAction *)meshAction
              relativeTriggerTime:(NSNumber *)relativeTriggerTime
                 recurringSeconds:(NSNumber *)recurringSeconds
                      recurrences:(NSNumber *)recurrences
                          success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                      NSNumber * _Nullable actionId))success
                          failure:(void (^ _Nullable)(NSError * _Nullable error))failure;



/**
 * @brief getStatus. Gets a list of Used and unused actions
 *
 *
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param success - Block called upon successful execution. The actionsIds is a 32-bit number where the bit position denotes an Action Id and a value of 1 indicates a used Action. For example a value of 0x80000003 means that ActionId 1, 2 & 32 are used, all other ActionIds are unused.
 * @param failure - Block called upon error
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable)getStatus:(NSNumber *)deviceId
                          success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                      NSNumber *_Nullable actionIds,
                                                      NSNumber *_Nullable maxActions))success
                          failure:(void (^ _Nullable)(NSError *_Nullable error))failure;


/**
 * @brief deleteAction. Delete the given set of Actions
 *
 *
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actionId (NSArray *) An array of Action IDs. Each action ID is an NSNumber containing an integer value in the range 1 to 32
 * @param success - Block called upon successful execution. The actionIdsDeleted is a 32-bit number where a bit position denotes an ActionId and a value of 1 indicates a deleted Action. For example a value of 0x80000003 means that ActionId 1, 2 & 32 were deleted, all other ActionIds remain in their used or unused state.
 * @param failure - Block called upon error
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable) deleteAction:(NSNumber *)deviceId
                            actionIds:(NSArray *)actionIds
                              success:(void (^_Nullable)(NSNumber *_Nullable deviceId,
                                                         NSNumber *_Nullable actionIdsDeleted))success
                              failure:(void (^_Nullable)(NSError *_Nullable error))failure;

/**
 * @brief getAction. get Action
 *
 *
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param actionId (NSNumber *) The ID of this action (8-bit value in the range 0..31)
 * @param success - Block called upon successful execution.
 * @param failure - Block called upon error
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable)getAction:(NSNumber *)deviceId
                         actionId:(NSNumber *)actionId
                          success:(void (^_Nullable)(NSNumber *_Nullable deviceId,
                                                     NSNumber *_Nullable actionId,
                                                     CSRMeshAction *_Nullable meshAction,
                                                     NSNumber *_Nullable timeType,
                                                     NSNumber *_Nullable time,
                                                     NSNumber *_Nullable recurringSeconds,
                                                     NSNumber * _Nullable recurrences))success
                          failure:(void (^_Nullable)(NSError *_Nullable error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<ActionModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<ActionModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
