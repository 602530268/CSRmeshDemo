/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Issuing Extended Opcode API 
*/

@interface CSRRestIssueExtendedOpcodeMessageRequest : CSRRestBaseObject




/*!
    Base 64 encoded Payload for Opcode .
*/
@property(nonatomic) NSString* payload;
  
/*!
    Opcode
*/
@property(nonatomic) NSNumber* opcode;
  
/*!
  Constructs instance of CSRRestIssueExtendedOpcodeMessageRequest

  @param payload - (NSString*) Base 64 encoded Payload for Opcode .
  @param opcode - (NSNumber*) Opcode
  
  @return instance of CSRRestIssueExtendedOpcodeMessageRequest
*/
- (id) initWithpayload: (NSString*) payload     
       opcode: (NSNumber*) opcode;
       

@end
