/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Find API for the Tracker model
*/

@interface CSRRestTrackerFindRequest : CSRRestBaseObject




/*!
    Device ID for this asset
*/
@property(nonatomic) NSNumber* assetDeviceId;
  
/*!
  Constructs instance of CSRRestTrackerFindRequest

  @param assetDeviceId - (NSNumber*) Device ID for this asset
  
  @return instance of CSRRestTrackerFindRequest
*/
- (id) initWithassetDeviceId: (NSNumber*) assetDeviceId;
       

@end
