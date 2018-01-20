/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetProximityConfig API for the Tracker model
*/

@interface CSRRestTrackerSetProximityConfigRequest : CSRRestBaseObject




/*!
    Threshold in dBm for Zone 0  (signed). Default -60
*/
@property(nonatomic) NSNumber* zone0RssiThreshold;
  
/*!
    Threshold in dBm for Zone 1 (signed). Default -83
*/
@property(nonatomic) NSNumber* zone1RssiThreshold;
  
/*!
    Threshold in dBm for Zone 2 (signed). Default -100
*/
@property(nonatomic) NSNumber* zone2RssiThreshold;
  
/*!
    How long until cached entry is deleted (seconds). Default 600
*/
@property(nonatomic) NSNumber* cacheDeleteInterval;
  
/*!
    Offset value for RSSI to delay computation. Default 60
*/
@property(nonatomic) NSNumber* delayOffset;
  
/*!
    Factor for RSSI to delay computation. Default 30
*/
@property(nonatomic) NSNumber* delayFactor;
  
/*!
    Destination ID to which asset reports will be sent. Default 0 
*/
@property(nonatomic) NSNumber* reportDest;
  
/*!
  Constructs instance of CSRRestTrackerSetProximityConfigRequest

  @param zone0RssiThreshold - (NSNumber*) Threshold in dBm for Zone 0  (signed). Default -60
  @param zone1RssiThreshold - (NSNumber*) Threshold in dBm for Zone 1 (signed). Default -83
  @param zone2RssiThreshold - (NSNumber*) Threshold in dBm for Zone 2 (signed). Default -100
  @param cacheDeleteInterval - (NSNumber*) How long until cached entry is deleted (seconds). Default 600
  @param delayOffset - (NSNumber*) Offset value for RSSI to delay computation. Default 60
  @param delayFactor - (NSNumber*) Factor for RSSI to delay computation. Default 30
  @param reportDest - (NSNumber*) Destination ID to which asset reports will be sent. Default 0 
  
  @return instance of CSRRestTrackerSetProximityConfigRequest
*/
- (id) initWithzone0RssiThreshold: (NSNumber*) zone0RssiThreshold     
       zone1RssiThreshold: (NSNumber*) zone1RssiThreshold     
       zone2RssiThreshold: (NSNumber*) zone2RssiThreshold     
       cacheDeleteInterval: (NSNumber*) cacheDeleteInterval     
       delayOffset: (NSNumber*) delayOffset     
       delayFactor: (NSNumber*) delayFactor     
       reportDest: (NSNumber*) reportDest;
       

@end
