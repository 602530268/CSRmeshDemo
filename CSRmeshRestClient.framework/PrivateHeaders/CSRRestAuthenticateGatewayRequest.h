/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 */

#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
 Request Object for authenticate gateway.
 */
@interface CSRRestAuthenticateGatewayRequest : CSRRestBaseObject



/*!
 UUID of Device
 */
@property(nonatomic) NSString* deviceUUID;

/*!
 MeshID of network
 */
@property(nonatomic) NSString* meshID;

/*!
 AuthSeed received
 */
@property(nonatomic) NSString* authSeed;


/*!
 AuthResponseSeed received
 */
@property(nonatomic) NSString* authResponseSeed;


/*!
 AuthChallenge for gateway
 */
@property(nonatomic) NSString* authChallenge;

-(id)initWithDeviceUUID: (NSString*) deviceUUID
                 meshID: (NSString*) meshID
               authSeed: (NSString*) authSeed
       authResponseSeed: (NSString*) authResponseSeed
          authChallenge: (NSString*) authChallenge;

@end
