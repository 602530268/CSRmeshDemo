/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 */

#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"



/*!
 Response Object for authentication seed.
 */

@interface CSRRestAuthSeedResponse : CSRRestBaseObject



/*!
 Authentication seed string
 */
@property(nonatomic) NSString* authSeed;

/*!
 Authentication seed response which will be derived from the authSeed and filled by RESTLib it self.
 */
@property(nonatomic) NSString* authSeedResponse;

/*!
 Constructs instance of CSRRestGetFileResponse
 
 @param authSeed - (NSString*) Auth seed.
 
 @return instance of CSRRestAuthSeedResponse
 */
- (id)initWithAuthSeed: (NSString*) authSeed;

@end
