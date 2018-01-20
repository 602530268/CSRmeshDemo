/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 
 REVISION:      $Revision: #1 $
 */

#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
 Response Object for authenticate gateway.
 */
@interface CSRRestAuthenticateGatewayResponse : CSRRestBaseObject


/*!
 AuthMaskSeed received from gateway
 */
@property(nonatomic) NSString* authMaskSeed;

/*!
 Response of challange
 */
@property(nonatomic) NSString* response;


-(id)initWithAuthMaskSeed: (NSString*) authMaskSeed
                 response: (NSString*) response;

@end
