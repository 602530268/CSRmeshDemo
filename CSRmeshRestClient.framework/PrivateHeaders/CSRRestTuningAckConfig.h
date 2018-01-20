/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Tuning AckConfig response object
*/

@interface CSRRestTuningAckConfig : CSRRestBaseObject




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
    Default is 60. See tuning doc for explanation
*/
@property(nonatomic) NSNumber* normalGoalValue;
  
/*!
    Default is 75. See tuning doc for explanation
*/
@property(nonatomic) NSNumber* highGoalValue;
  
/*!
    Duty cycle 1..100% or 101..255 (x-100) per mille
*/
@property(nonatomic) NSNumber* currentScanDutyCycle;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestTuningAckConfig

  @param numeratorHighTrafficNeighRatio - (NSNumber*) Default is 14. See tuning doc for explanation
  @param numeratorNormalTrafficNeighRatio - (NSNumber*) Default is 12. See tuning doc for explanation
  @param denominatorTrafficNeighRatio - (NSNumber*) Default is 10. See tuning doc for explanation
  @param normalGoalValue - (NSNumber*) Default is 60. See tuning doc for explanation
  @param highGoalValue - (NSNumber*) Default is 75. See tuning doc for explanation
  @param currentScanDutyCycle - (NSNumber*) Duty cycle 1..100% or 101..255 (x-100) per mille
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestTuningAckConfig
*/
- (id) initWithnumeratorHighTrafficNeighRatio: (NSNumber*) numeratorHighTrafficNeighRatio     
       numeratorNormalTrafficNeighRatio: (NSNumber*) numeratorNormalTrafficNeighRatio     
       denominatorTrafficNeighRatio: (NSNumber*) denominatorTrafficNeighRatio     
       normalGoalValue: (NSNumber*) normalGoalValue     
       highGoalValue: (NSNumber*) highGoalValue     
       currentScanDutyCycle: (NSNumber*) currentScanDutyCycle     
       deviceId: (NSNumber*) deviceId;
       

@end
