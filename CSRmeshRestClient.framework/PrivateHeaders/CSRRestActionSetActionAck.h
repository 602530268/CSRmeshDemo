/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Set Action Ack response object
*/

@interface CSRRestActionSetActionAck : CSRRestBaseObject




/*!
    Unique Id for each action
*/
@property(nonatomic) NSNumber* actionId;
  
/*!
  Constructs instance of CSRRestActionSetActionAck

  @param actionId - (NSNumber*) Unique Id for each action
  
  @return instance of CSRRestActionSetActionAck
*/
- (id) initWithactionId: (NSNumber*) actionId;
       

@end
