//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header AttentionModelApi is a part of the CSRmesh Api and provides a set of methods related to the Attention Model.
 *
 */

@protocol AttentionModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetState delegate. Invoked by the CSRmesh library upon receiving a state message fron the device
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param state The attract attention state of the device.
 *  YES = attracting attention
 *  NO = not attracting attention
 * @param meshRequestId The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetState:(NSNumber *)deviceId
              state:(BOOL)state
           duration:(NSNumber *)duration
      meshRequestId:(NSNumber *)meshRequestId;
@end


@interface AttentionModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

// Attention Api Method
// Flash the Light in Red at 50% duty cycle
// duration is in milliseconds
/*!
 * @brief setState - If attractAttention is set to YES then the LED will flash at duty cycle of 50% and at a rate set by duration.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param attractAttention - Enable or Disable attract attention
 * @param duration - (NSNumber *) Unsigned Short Value of the duration in milliseconds
 * @param success - Block called upon successful execution
 * @param failure - Block called upon error
 * @return meshRequestId - The id of the message.
 */
- (NSNumber * _Nullable)setState:(NSNumber *)deviceId
                attractAttention:(BOOL)attractAttention
                        duration:(NSNumber *)duration
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSNumber * _Nullable state,
                                                     NSNumber * _Nullable duration))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<AttentionModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<AttentionModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END