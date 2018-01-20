/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 
 REVISION:      $Revision: #1 $
 */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"



/*!
 Response Object for secret exchange.
 */

@interface CSRRestExchangeSecretResponse : CSRRestBaseObject

/*!
 Base64 encoded hash, provided by CE.
 */
@property(nonatomic) NSString* ceIdHash;

/*!
 Diversifier of gateway
 */
@property(nonatomic) NSString* diversifier;

/*!
 Base64 encoded 80 bit IV of gateway.
 */
@property(nonatomic) NSString* authMaskSeed;

/*!
 Base64 encoded Message signature, signed by source/configuring entity.
 */
@property(nonatomic) NSString* signature;


-(id)initWithCeIdHash: (NSString*) ceIdHash
          diversifier: (NSString*) diversifier
         authMaskSeed: (NSString*) authMaskSeed
            signature: (NSString*) signature;

@end
