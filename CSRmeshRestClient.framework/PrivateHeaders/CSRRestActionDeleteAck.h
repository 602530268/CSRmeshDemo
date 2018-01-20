/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Action DeleteAck response object
*/

@interface CSRRestActionDeleteAck : CSRRestBaseObject




/*!
    bit mask indicating which Action which have been deleted. The bit position (LSB = actionID #1) determines the Action ID (from 1 to 31).
*/
@property(nonatomic) NSNumber* actionIDs;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestActionDeleteAck

  @param actionIDs - (NSNumber*) bit mask indicating which Action which have been deleted. The bit position (LSB = actionID #1) determines the Action ID (from 1 to 31).
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestActionDeleteAck
*/
- (id) initWithactionIDs: (NSNumber*) actionIDs     
       deviceId: (NSNumber*) deviceId;
       

@end
