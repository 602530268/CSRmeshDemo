/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for LastSequenceNumber API for the Config model
*/

@interface CSRRestConfigLastSequenceNumberRequest : CSRRestBaseObject




/*!
    The last sequence number seen by the source device from the destination device.
*/
@property(nonatomic) NSNumber* lastSequenceNumber;
  
/*!
  Constructs instance of CSRRestConfigLastSequenceNumberRequest

  @param lastSequenceNumber - (NSNumber*) The last sequence number seen by the source device from the destination device.
  
  @return instance of CSRRestConfigLastSequenceNumberRequest
*/
- (id) initWithlastSequenceNumber: (NSNumber*) lastSequenceNumber;
       

@end
