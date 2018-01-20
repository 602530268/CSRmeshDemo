/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetState API for the Bearer model
*/

@interface CSRRestBearerSetStateRequest : CSRRestBaseObject




/*!
    Bit field of active relay bearers that are used to relay messages to.
*/
@property(nonatomic) NSNumber* bearerRelayActive;
  
/*!
    Bit field of enabled bearers.
*/
@property(nonatomic) NSNumber* bearerEnabled;
  
/*!
    Relay all messages, regardless of MAC
*/
@property(nonatomic) NSNumber* bearerPromiscuous;
  
/*!
  Constructs instance of CSRRestBearerSetStateRequest

  @param bearerRelayActive - (NSNumber*) Bit field of active relay bearers that are used to relay messages to.
  @param bearerEnabled - (NSNumber*) Bit field of enabled bearers.
  @param bearerPromiscuous - (NSNumber*) Relay all messages, regardless of MAC
  
  @return instance of CSRRestBearerSetStateRequest
*/
- (id) initWithbearerRelayActive: (NSNumber*) bearerRelayActive     
       bearerEnabled: (NSNumber*) bearerEnabled     
       bearerPromiscuous: (NSNumber*) bearerPromiscuous;
       

@end
