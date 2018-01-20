/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestOpcodeMessage.h"


/*!
    Response Object for Opcode Message transaction api
*/

@interface CSRRestOpcodeMessageResponse : CSRRestBaseObject




/*!
    Time stamp of the responses.
*/
@property(nonatomic) NSNumber* timeStamp;
  
/*!
    The actual OpcodeMessage Message response object
*/
@property(nonatomic) NSArray* message;
  
/*!
  Constructs instance of CSRRestOpcodeMessageResponse

  @param timeStamp - (NSNumber*) Time stamp of the responses.
  @param message - (NSArray*) The actual OpcodeMessage Message response object
  
  @return instance of CSRRestOpcodeMessageResponse
*/
- (id) initWithtimeStamp: (NSNumber*) timeStamp     
       message: (NSArray*) message;
       

@end
