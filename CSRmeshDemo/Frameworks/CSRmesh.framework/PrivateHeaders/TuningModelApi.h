//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header TuningModelApi is a part of the CSRmesh Api and provides a set of methods related to the Tuning Model.
 */


@protocol TuningModelApiDelegate <NSObject>
@optional

/**
 * @brief Response to the request tuningStatsRequest.
 * @param deviceId
 * @param partNumber Current part of the message set. Bit 7 is used to indicate that there are more messages to follow.
 * @param neighbourId1 Identity of the first neighbour of this message part
 * @param neighbourRate1 Average rate reported by first neighbour. 6.2 fixed format [0..63 with one decimal place in quarter]
 * @param neighbourRssi1 Average RSSI for first neighbour. Signed value.
 * @param neighbourId2 Identity of the second neighbour of this message part
 * @param neighbourRate2 Average rate reported by second neighbour. 6.2 fixed format [0..63 with one decimal place in quarter]
 * @param neighbourRssi2 Average RSSI for second neighbour. Signed value.
 * @param meshRequestId - meshRequestId
 */
- (void)didGetTuningStats:(NSNumber *)deviceId
               partNumber:(NSNumber *)partNumber
             neighbourId1:(NSNumber *)neighbourId1
           neighbourRate1:(NSNumber *)neighbourRate1
           neighbourRssi1:(NSNumber *)neighbourRssi1
             neighbourId2:(NSNumber *)neighbourId2 neighbourRate2:(NSNumber *)neighbourRate2
           neighbourRssi2:(NSNumber *)neighbourRssi2
__deprecated_msg("use success and failure blocks in the method - (NSNumber * _Nullable)tuningStatsRequest:(NSNumber *)deviceId issingReplyParts:(NSNumber *)missingReplyParts success:(void (^ _Nullable)(NSNumber * _Nullable deviceId, NSNumber * _Nullable partNumber, NSNumber * _Nullable neighbourId1, NSNumber * _Nullable neighbourRate1, NSNumber * _Nullable neighbourRssi1, NSNumber * _Nullable neighbourId2, NSNumber * _Nullable neighbourRate2, NSNumber * _Nullable neighbourRssi2))success failure:(void (^ _Nullable)(NSError * _Nullable error))failure");

/**
 * @brief response to a TUNING_SET_CONFIG.
 * @param deviceId
 * @param numeratorHighTrafficNeighRatio Numerator of High Traffic neighbour. Value is NumeratorHighTrafficNeighRatio/ (DenominatorTrafficNeighRatio*10)
 * @param numeratorNormalTrafficNeighRatio Numerator of Normal Traffic neighbour. Value is NumeratorNormalTrafficNeighRatio / (DenominatorTrafficNeighRatio*10)
 * @param denominatorTrafficNeighRatio Denominator for above ratios – in 10th units.
 * @param normalGoalValue Normal Goal Value (unit less)
 * @param highGoalValue High Goal Value (unit less)
 * @param currentScanDutyCycle Duty Cycle currently associated
 * @param ackRequest Determine the need to acknowledge (omission of this section will result in not having the above values committed).
 * @param meshRequestId - meshRequestId
 */
- (void)didGetTuningConfig:(NSNumber *)deviceId
numeratorHighTrafficNeighRatio:(NSNumber *)numeratorHighTrafficNeighRatio
numeratorNormalTrafficNeighRatio:(NSNumber *)numeratorNormalTrafficNeighRatio
denominatorTrafficNeighRatio:(NSNumber *)denominatorTrafficNeighRatio
           normalGoalValue:(NSNumber *)normalGoalValue
             highGoalValue:(NSNumber *)highGoalValue
      currentScanDutyCycle:(NSNumber *)currentScanDutyCycle
             meshRequestId:(NSNumber *)meshRequestId
__deprecated_msg("use success and failure blocks in the method - (NSNumber * _Nullable) tuningSetConfig:(NSNumber *)deviceId numeratorHighTrafficNeighRatio:(NSNumber *)numeratorHighTrafficNeighRatio numeratorNormalTrafficNeighRatio:(NSNumber *)numeratorNormalTrafficNeighRatio denominatorTrafficNeighRatio:(NSNumber *)denominatorTrafficNeighRatio normalGoalValue:(NSNumber *)normalGoalValue highGoalValue:(NSNumber *)highGoalValue currentScanDutyCycle:(NSNumber *)currentScanDutyCycle ackRequest:(NSNumber *)ackRequest success:(void (^ _Nullable)(NSNumber * _Nullable deviceId, NSNumber * _Nullable numeratorHighTrafficNeighRatio, NSNumber * _Nullable numeratorNormalTrafficNeighRatio, NSNumber * _Nullable denominatorTrafficNeighRatio, NSNumber * _Nullable normalGoalValue, NSNumber * _Nullable highGoalValue, NSNumber * _Nullable currentScanDutyCycle))success failure:(void (^ _Nullable)(NSError * _Nullable error))failure");


@end

@interface TuningModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/**
 * @brief Collecting statistics from specific nodes.
 * @param deviceId
 * @param missingReplyParts determining the specific responses one would like to collect
 * @param success - Block called upon successful execution, set nil to inhibit acknowledgement
 * @param failure - Block called upon error
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable)tuningStatsRequest:(NSNumber *)deviceId
                         missingReplyParts:(NSData *)missingReplyParts
                                   success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                               NSNumber * _Nullable partNumber,
                                                               NSNumber * _Nullable neighbourId1,
                                                               NSNumber * _Nullable neighbourRate1,
                                                               NSNumber * _Nullable neighbourRssi1,
                                                               NSNumber * _Nullable neighbourId2,
                                                               NSNumber * _Nullable neighbourRate2,
                                                               NSNumber * _Nullable neighbourRssi2))success
                                   failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/**
 * @brief enforce the state of the recipient.
 * @param deviceId
 * @param numeratorHighTrafficNeighRatio Numerator of High Traffic neighbour. Value is NumeratorHighTrafficNeighRatio/ (DenominatorTrafficNeighRatio*10)
 * @param numeratorNormalTrafficNeighRatio Numerator of Normal Traffic neighbour. Value is NumeratorNormalTrafficNeighRatio / (DenominatorTrafficNeighRatio*10)
 * @param denominatorTrafficNeighRatio Denominator for above ratios – in 10th units.
 * @param normalGoalValue Normal Goal Value (unit less)
 * @param highGoalValue High Goal Value (unit less)
 * @param currentScanDutyCycle Duty Cycle currently associated
 * @param ackRequest Determine the need to acknowledge (omission of this section will result in not having the above values committed).
 * @param success - Block called upon successful execution, set nil to inhibit acknowledgement
 * @param failure - Block called upon error
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable)tuningSetConfig:(NSNumber *)deviceId
         numeratorHighTrafficNeighRatio:(NSNumber *)numeratorHighTrafficNeighRatio
       numeratorNormalTrafficNeighRatio:(NSNumber *)numeratorNormalTrafficNeighRatio
           denominatorTrafficNeighRatio:(NSNumber *)denominatorTrafficNeighRatio
                        normalGoalValue:(NSNumber *)normalGoalValue
                          highGoalValue:(NSNumber *)highGoalValue
                   currentScanDutyCycle:(NSNumber *)currentScanDutyCycle
                             ackRequest:(NSNumber *)ackRequest
                                success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                            NSNumber * _Nullable numeratorHighTrafficNeighRatio,
                                                            NSNumber * _Nullable numeratorNormalTrafficNeighRatio,
                                                            NSNumber * _Nullable denominatorTrafficNeighRatio,
                                                            NSNumber * _Nullable normalGoalValue,
                                                            NSNumber * _Nullable highGoalValue,
                                                            NSNumber * _Nullable currentScanDutyCycle))success
                                failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<TuningModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<TuningModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
