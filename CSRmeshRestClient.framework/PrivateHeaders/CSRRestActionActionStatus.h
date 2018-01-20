/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Action ActionStatus response object
*/

@interface CSRRestActionActionStatus : CSRRestBaseObject




/*!
    Bit mask indicating which Actions are stored. The bit position (for clarity 00000000 00000000 00000000 00000001 = actionID #1 only) determines the Action ID (from 1 to 31)
*/
@property(nonatomic) NSNumber* actionIDs;
  
/*!
    Max number of  actions supported by a Node device
*/
@property(nonatomic) NSNumber* maxActionsSupported;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestActionActionStatus

  @param actionIDs - (NSNumber*) Bit mask indicating which Actions are stored. The bit position (for clarity 00000000 00000000 00000000 00000001 = actionID #1 only) determines the Action ID (from 1 to 31)
  @param maxActionsSupported - (NSNumber*) Max number of  actions supported by a Node device
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestActionActionStatus
*/
- (id) initWithactionIDs: (NSNumber*) actionIDs     
       maxActionsSupported: (NSNumber*) maxActionsSupported     
       deviceId: (NSNumber*) deviceId;
       

@end
