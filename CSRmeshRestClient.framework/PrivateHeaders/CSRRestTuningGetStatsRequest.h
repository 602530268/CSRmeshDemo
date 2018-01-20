/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for GetStats API for the Tuning model
*/

@interface CSRRestTuningGetStatsRequest : CSRRestBaseObject




/*!
    Bitset of missing reply parts (0 means send all)
*/
@property(nonatomic) NSArray* missingReplyParts;
  
/*!
  Constructs instance of CSRRestTuningGetStatsRequest

  @param missingReplyParts - (NSArray*) Bitset of missing reply parts (0 means send all)
  
  @return instance of CSRRestTuningGetStatsRequest
*/
- (id) initWithmissingReplyParts: (NSArray*) missingReplyParts;
       

@end
