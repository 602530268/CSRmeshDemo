/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Request API for the Ping model
*/

@interface CSRRestPingRequestRequest : CSRRestBaseObject




/*!
    Arbitrary data
*/
@property(nonatomic) NSArray* arbitraryData;
  
/*!
    Response packet time to live
*/
@property(nonatomic) NSNumber* rspTTl;
  
/*!
  Constructs instance of CSRRestPingRequestRequest

  @param arbitraryData - (NSArray*) Arbitrary data
  @param rspTTl - (NSNumber*) Response packet time to live
  
  @return instance of CSRRestPingRequestRequest
*/
- (id) initWitharbitraryData: (NSArray*) arbitraryData     
       rspTTl: (NSNumber*) rspTTl;
       

@end
