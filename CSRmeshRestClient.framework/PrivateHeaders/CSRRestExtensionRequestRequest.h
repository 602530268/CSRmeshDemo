/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Request API for the Extension model
*/

@interface CSRRestExtensionRequestRequest : CSRRestBaseObject




/*!
    48bits Hash (SHA-256) of Text supplied by OEM for characterisation of intended usage
*/
@property(nonatomic) NSArray* extensionHash;
  
/*!
    Proposed OpCode - start of range requested
*/
@property(nonatomic) NSNumber* proposedOpCode;
  
/*!
    Number of OpCode to be allocated, starting from ProposedOpCode
*/
@property(nonatomic) NSNumber* range;
  
/*!
  Constructs instance of CSRRestExtensionRequestRequest

  @param extensionHash - (NSArray*) 48bits Hash (SHA-256) of Text supplied by OEM for characterisation of intended usage
  @param proposedOpCode - (NSNumber*) Proposed OpCode - start of range requested
  @param range - (NSNumber*) Number of OpCode to be allocated, starting from ProposedOpCode
  
  @return instance of CSRRestExtensionRequestRequest
*/
- (id) initWithextensionHash: (NSArray*) extensionHash     
       proposedOpCode: (NSNumber*) proposedOpCode     
       range: (NSNumber*) range;
       

@end
