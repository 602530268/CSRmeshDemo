/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object of Message API for model Watchdog
*/

@interface CSRRestActionSetActionRequest : CSRRestBaseObject


/*!
    0=ABSOLUTE_NO_REPEAT, 1=ABSOLUTE_REPEAT, 2=RELATIVE_NO_REPEAT, 3=RELATIVE_REPEAT
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActionSetActionRequestTimeTypeEnum) {
  CSRRestActionSetActionRequestTimeTypeEnumABSOLUTE_NO_REPEAT,
  CSRRestActionSetActionRequestTimeTypeEnumABSOLUTE_REPEAT,
  CSRRestActionSetActionRequestTimeTypeEnumRELATIVE_NO_REPEAT,
  CSRRestActionSetActionRequestTimeTypeEnumRELATIVE_REPEAT,

};



/*!
    Device Id for which the action needs to be set .
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
    Unique Id for each action .
*/
@property(nonatomic) NSNumber* actionId;
  
/*!
    The actual Action Object
*/
@property(nonatomic) CSRRestBaseObject* action;
  
/*!
    Time for which Action is scheduled .
*/
@property(nonatomic) NSNumber* startTime;
  
/*!
    Repeat Interval For the Action .
*/
@property(nonatomic) NSNumber* repeatInterval;
  
/*!
    Number of times Action Needs to be repeated .
*/
@property(nonatomic) NSNumber* numRepeats;
  
/*!
    0=ABSOLUTE_NO_REPEAT, 1=ABSOLUTE_REPEAT, 2=RELATIVE_NO_REPEAT, 3=RELATIVE_REPEAT
*/
@property(nonatomic) CSRRestActionSetActionRequestTimeTypeEnum timeType;

/*!
  Constructs instance of CSRRestActionSetActionRequest

  @param deviceId - (NSNumber*) Device Id for which the action needs to be set .
  @param actionId - (NSNumber*) Unique Id for each action .
  @param action - (CSRRestBaseObject*) The actual Action Object
  @param startTime - (NSNumber*) Time for which Action is scheduled .
  @param repeatInterval - (NSNumber*) Repeat Interval For the Action .
  @param numRepeats - (NSNumber*) Number of times Action Needs to be repeated .
  @param timeType - (CSRRestActionSetActionRequestTimeTypeEnum) 0=ABSOLUTE_NO_REPEAT, 1=ABSOLUTE_REPEAT, 2=RELATIVE_NO_REPEAT, 3=RELATIVE_REPEAT
  
  @return instance of CSRRestActionSetActionRequest
*/
- (id) initWithdeviceId: (NSNumber*) deviceId     
       actionId: (NSNumber*) actionId     
       action: (CSRRestBaseObject*) action     
       startTime: (NSNumber*) startTime     
       repeatInterval: (NSNumber*) repeatInterval     
       numRepeats: (NSNumber*) numRepeats     
       timeType: (CSRRestActionSetActionRequestTimeTypeEnum) timeType;
       

@end
