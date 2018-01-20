/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual OpcodeMessage response object
*/

@interface CSRRestOpcodeMessage : CSRRestBaseObject




/*!
    Id of the device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
    List of Base 64 encoded Payload for Opcode
*/
@property(nonatomic) NSString* payload;
  
/*!
  Constructs instance of CSRRestOpcodeMessage

  @param deviceId - (NSNumber*) Id of the device
  @param payload - (NSString*) List of Base 64 encoded Payload for Opcode
  
  @return instance of CSRRestOpcodeMessage
*/
- (id) initWithdeviceId: (NSNumber*) deviceId     
       payload: (NSString*) payload;
       

@end
