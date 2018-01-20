/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetConfig API for the Tuning model
*/

@interface CSRRestTuningSetConfigRequest : CSRRestBaseObject


/*!
    Whether ack required
*/
 typedef NS_OPTIONS(NSInteger, CSRRestTuningSetConfigRequestAckRequestEnum) {
  CSRRestTuningSetConfigRequestAckRequestEnumFalse,
  CSRRestTuningSetConfigRequestAckRequestEnumTrue,

};



/*!
    Default is 14. See tuning doc for explanation
*/
@property(nonatomic) NSNumber* numeratorHighTrafficNeighRatio;
  
/*!
    Default is 12. See tuning doc for explanation
*/
@property(nonatomic) NSNumber* numeratorNormalTrafficNeighRatio;
  
/*!
    Default is 10. See tuning doc for explanation
*/
@property(nonatomic) NSNumber* denominatorTrafficNeighRatio;
  
/*!
    Default is 60. Set to 0 to disable/suspend tuning
*/
@property(nonatomic) NSNumber* normalGoalValue;
  
/*!
    Default is 75. Set to 254 to suspend, 255 to disable tuning
*/
@property(nonatomic) NSNumber* highGoalValue;
  
/*!
    Duty cycle 1..100% or 101..255 (x-100) per mille
*/
@property(nonatomic) NSNumber* currentScanDutyCycle;
  
/*!
    Whether ack required
*/
@property(nonatomic) CSRRestTuningSetConfigRequestAckRequestEnum ackRequest;

/*!
  Constructs instance of CSRRestTuningSetConfigRequest

  @param numeratorHighTrafficNeighRatio - (NSNumber*) Default is 14. See tuning doc for explanation
  @param numeratorNormalTrafficNeighRatio - (NSNumber*) Default is 12. See tuning doc for explanation
  @param denominatorTrafficNeighRatio - (NSNumber*) Default is 10. See tuning doc for explanation
  @param normalGoalValue - (NSNumber*) Default is 60. Set to 0 to disable/suspend tuning
  @param highGoalValue - (NSNumber*) Default is 75. Set to 254 to suspend, 255 to disable tuning
  @param currentScanDutyCycle - (NSNumber*) Duty cycle 1..100% or 101..255 (x-100) per mille
  @param ackRequest - (CSRRestTuningSetConfigRequestAckRequestEnum) Whether ack required
  
  @return instance of CSRRestTuningSetConfigRequest
*/
- (id) initWithnumeratorHighTrafficNeighRatio: (NSNumber*) numeratorHighTrafficNeighRatio     
       numeratorNormalTrafficNeighRatio: (NSNumber*) numeratorNormalTrafficNeighRatio     
       denominatorTrafficNeighRatio: (NSNumber*) denominatorTrafficNeighRatio     
       normalGoalValue: (NSNumber*) normalGoalValue     
       highGoalValue: (NSNumber*) highGoalValue     
       currentScanDutyCycle: (NSNumber*) currentScanDutyCycle     
       ackRequest: (CSRRestTuningSetConfigRequestAckRequestEnum) ackRequest;
       

@end
