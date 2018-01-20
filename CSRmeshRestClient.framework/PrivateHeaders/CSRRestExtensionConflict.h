/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Extension Conflict response object
*/

@interface CSRRestExtensionConflict : CSRRestBaseObject




/*!
    48bits Hash (SHA-256) of Text supplied by OEM for characterisation of intended usage
*/
@property(nonatomic) NSArray* extensionHash;
  
/*!
    Proposed OpCode - start of range requested
*/
@property(nonatomic) NSNumber* proposedOpCode;
  
/*!
    Code describing reason for rejection
*/
@property(nonatomic) NSNumber* reason;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestExtensionConflict

  @param extensionHash - (NSArray*) 48bits Hash (SHA-256) of Text supplied by OEM for characterisation of intended usage
  @param proposedOpCode - (NSNumber*) Proposed OpCode - start of range requested
  @param reason - (NSNumber*) Code describing reason for rejection
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestExtensionConflict
*/
- (id) initWithextensionHash: (NSArray*) extensionHash     
       proposedOpCode: (NSNumber*) proposedOpCode     
       reason: (NSNumber*) reason     
       deviceId: (NSNumber*) deviceId;
       

@end
