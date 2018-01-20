/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Delete API for the Action model
*/

@interface CSRRestActionDeleteRequest : CSRRestBaseObject




/*!
    Bit mask indicating which Action to be deleted. The bit position (for clarity 00000000 00000000 00000000 00000001 = actionID #1 only) determines the Action ID (from 1 to 31)
*/
@property(nonatomic) NSNumber* actionIDs;
  
/*!
  Constructs instance of CSRRestActionDeleteRequest

  @param actionIDs - (NSNumber*) Bit mask indicating which Action to be deleted. The bit position (for clarity 00000000 00000000 00000000 00000001 = actionID #1 only) determines the Action ID (from 1 to 31)
  
  @return instance of CSRRestActionDeleteRequest
*/
- (id) initWithactionIDs: (NSNumber*) actionIDs;
       

@end
