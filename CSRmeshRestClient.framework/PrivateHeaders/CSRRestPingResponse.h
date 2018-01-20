/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Ping Response response object
*/

@interface CSRRestPingResponse : CSRRestBaseObject




/*!
    Arbitrary data
*/
@property(nonatomic) NSArray* arbitraryData;
  
/*!
    Time to live when received
*/
@property(nonatomic) NSNumber* tTLAtRx;
  
/*!
    Receiver signal strength when received
*/
@property(nonatomic) NSNumber* rSSIAtRx;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestPingResponse

  @param arbitraryData - (NSArray*) Arbitrary data
  @param tTLAtRx - (NSNumber*) Time to live when received
  @param rSSIAtRx - (NSNumber*) Receiver signal strength when received
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestPingResponse
*/
- (id) initWitharbitraryData: (NSArray*) arbitraryData     
       tTLAtRx: (NSNumber*) tTLAtRx     
       rSSIAtRx: (NSNumber*) rSSIAtRx     
       deviceId: (NSNumber*) deviceId;
       

@end
