/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetState API for the Power model
*/

@interface CSRRestPowerSetStateRequest : CSRRestBaseObject


/*!
    State to set
*/
 typedef NS_OPTIONS(NSInteger, CSRRestPowerSetStateRequestStateEnum) {
  CSRRestPowerSetStateRequestStateEnumOff,
  CSRRestPowerSetStateRequestStateEnumOn,
  CSRRestPowerSetStateRequestStateEnumStandby,
  CSRRestPowerSetStateRequestStateEnumOnFromStandby,

};



/*!
    State to set
*/
@property(nonatomic) CSRRestPowerSetStateRequestStateEnum state;

/*!
  Constructs instance of CSRRestPowerSetStateRequest

  @param state - (CSRRestPowerSetStateRequestStateEnum) State to set
  
  @return instance of CSRRestPowerSetStateRequest
*/
- (id) initWithstate: (CSRRestPowerSetStateRequestStateEnum) state;
       

@end
