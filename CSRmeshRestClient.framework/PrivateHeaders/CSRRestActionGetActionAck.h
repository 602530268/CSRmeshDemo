/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Get Action Ack response object
*/

@interface CSRRestActionGetActionAck : CSRRestBaseObject


/*!
    Actuator type. The Type field is the actuator type value being set.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActionGetActionAckTimeTypeEnum) {
  CSRRestActionGetActionAckTimeTypeEnumABSOLUTE_NO_REPEAT,
  CSRRestActionGetActionAckTimeTypeEnumABSOLUTE_REPEAT,
  CSRRestActionGetActionAckTimeTypeEnumRELATIVE_NO_REPEAT,
  CSRRestActionGetActionAckTimeTypeEnumRELATIVE_REPEAT,

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
    Actuator type. The Type field is the actuator type value being set.
*/
@property(nonatomic) CSRRestActionGetActionAckTimeTypeEnum timeType;

/*!
  Constructs instance of CSRRestActionGetActionAck

  @param deviceId - (NSNumber*) Device Id for which the action needs to be set .
  @param actionId - (NSNumber*) Unique Id for each action .
  @param action - (CSRRestBaseObject*) The actual Action Object
  @param startTime - (NSNumber*) Time for which Action is scheduled .
  @param repeatInterval - (NSNumber*) Repeat Interval For the Action .
  @param numRepeats - (NSNumber*) Number of times Action Needs to be repeated .
  @param timeType - (CSRRestActionGetActionAckTimeTypeEnum) Actuator type. The Type field is the actuator type value being set.
  
  @return instance of CSRRestActionGetActionAck
*/
- (id) initWithdeviceId: (NSNumber*) deviceId     
       actionId: (NSNumber*) actionId     
       action: (CSRRestBaseObject*) action     
       startTime: (NSNumber*) startTime     
       repeatInterval: (NSNumber*) repeatInterval     
       numRepeats: (NSNumber*) numRepeats     
       timeType: (CSRRestActionGetActionAckTimeTypeEnum) timeType;
       

@end
