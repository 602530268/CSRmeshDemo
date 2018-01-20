/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Asset State response object
*/

@interface CSRRestAssetState : CSRRestBaseObject




/*!
    Interval between asset broadcasts
*/
@property(nonatomic) NSNumber* interval;
  
/*!
    Side effects for this asset
*/
@property(nonatomic) NSNumber* sideEffects;
  
/*!
    Asset announce destination
*/
@property(nonatomic) NSNumber* toDestinationId;
  
/*!
    Asset TxPower
*/
@property(nonatomic) NSNumber* txPower;
  
/*!
    Number of times to send announce
*/
@property(nonatomic) NSNumber* numAnnounces;
  
/*!
    Time between announce repeats
*/
@property(nonatomic) NSNumber* announceInterval;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestAssetState

  @param interval - (NSNumber*) Interval between asset broadcasts
  @param sideEffects - (NSNumber*) Side effects for this asset
  @param toDestinationId - (NSNumber*) Asset announce destination
  @param txPower - (NSNumber*) Asset TxPower
  @param numAnnounces - (NSNumber*) Number of times to send announce
  @param announceInterval - (NSNumber*) Time between announce repeats
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestAssetState
*/
- (id) initWithinterval: (NSNumber*) interval     
       sideEffects: (NSNumber*) sideEffects     
       toDestinationId: (NSNumber*) toDestinationId     
       txPower: (NSNumber*) txPower     
       numAnnounces: (NSNumber*) numAnnounces     
       announceInterval: (NSNumber*) announceInterval     
       deviceId: (NSNumber*) deviceId;
       

@end
