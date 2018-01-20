/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 
 REVISION:      $Revision: #14 $
 */

#import <Foundation/Foundation.h>
#import "CSRRestApiStatusCode.h"


/*! Category on NSError class, for providing status code returned by Model Api. */
@interface NSError (StatusCode)

/*!
 Extract CSRRestApiStatusCode from NSError object
 
 @return status code from CSRRestApiStatusCode enum.
 */
- (CSRRestApiStatusCode) statusCode;

@end
