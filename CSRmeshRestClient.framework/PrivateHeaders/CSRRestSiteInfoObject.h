/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Info Object of a site's meshes and gateway sent along with Create, Update and Get Site Info calls.
*/

@interface CSRRestSiteInfoObject : CSRRestBaseObject




/*!
    Mesh ID
*/
@property(nonatomic) NSString* meshId;
  
/*!
    Gateway UUID
*/
@property(nonatomic) NSArray* gatewaysUuid;
  
/*!
  Constructs instance of CSRRestSiteInfoObject

  @param meshId - (NSString*) Mesh ID
  @param gatewaysUuid - (NSArray*) Gateway UUID
  
  @return instance of CSRRestSiteInfoObject
*/
- (id) initWithmeshId: (NSString*) meshId     
       gatewaysUuid: (NSArray*) gatewaysUuid;
       

@end
