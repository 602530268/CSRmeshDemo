/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Bearer State response object
*/

@interface CSRRestBearerState : CSRRestBaseObject




/*!
    Bitfield of active relay bearers
*/
@property(nonatomic) NSNumber* bearerRelayActive;
  
/*!
    Bitfield of enabled bearers
*/
@property(nonatomic) NSNumber* bearerEnabled;
  
/*!
    Relay all messages, regardless of MAC
*/
@property(nonatomic) NSNumber* bearerPromiscuous;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestBearerState

  @param bearerRelayActive - (NSNumber*) Bitfield of active relay bearers
  @param bearerEnabled - (NSNumber*) Bitfield of enabled bearers
  @param bearerPromiscuous - (NSNumber*) Relay all messages, regardless of MAC
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestBearerState
*/
- (id) initWithbearerRelayActive: (NSNumber*) bearerRelayActive     
       bearerEnabled: (NSNumber*) bearerEnabled     
       bearerPromiscuous: (NSNumber*) bearerPromiscuous     
       deviceId: (NSNumber*) deviceId;
       

@end
