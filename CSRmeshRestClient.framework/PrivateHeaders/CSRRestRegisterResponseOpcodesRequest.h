/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Requesting Response for Opcodes .
*/

@interface CSRRestRegisterResponseOpcodesRequest : CSRRestBaseObject





@property(nonatomic) NSNumber* proposedOpCode;
  

@property(nonatomic) NSNumber* range;
  
/*!
  Constructs instance of CSRRestRegisterResponseOpcodesRequest

  @param proposedOpCode - (NSNumber*)
  @param range - (NSNumber*)
  
  @return instance of CSRRestRegisterResponseOpcodesRequest
*/
- (id) initWithproposedOpCode: (NSNumber*) proposedOpCode     
       range: (NSNumber*) range;
       

@end
