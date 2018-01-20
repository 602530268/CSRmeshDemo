/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Tracker Found response object
*/

@interface CSRRestTrackerFound : CSRRestBaseObject




/*!
    Device ID of this asset
*/
@property(nonatomic) NSNumber* assetDeviceId;
  
/*!
    RSSI of ASSET_ANNOUNCE
*/
@property(nonatomic) NSNumber* rssi;
  
/*!
    Zone: 0=Immediate 1=Near 2=Distant
*/
@property(nonatomic) NSNumber* zone;
  
/*!
    How long since last seen
*/
@property(nonatomic) NSNumber* ageSeconds;
  
/*!
    Side effects for this asset
*/
@property(nonatomic) NSNumber* sideEffects;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestTrackerFound

  @param assetDeviceId - (NSNumber*) Device ID of this asset
  @param rssi - (NSNumber*) RSSI of ASSET_ANNOUNCE
  @param zone - (NSNumber*) Zone: 0=Immediate 1=Near 2=Distant
  @param ageSeconds - (NSNumber*) How long since last seen
  @param sideEffects - (NSNumber*) Side effects for this asset
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestTrackerFound
*/
- (id) initWithassetDeviceId: (NSNumber*) assetDeviceId     
       rssi: (NSNumber*) rssi     
       zone: (NSNumber*) zone     
       ageSeconds: (NSNumber*) ageSeconds     
       sideEffects: (NSNumber*) sideEffects     
       deviceId: (NSNumber*) deviceId;
       

@end
