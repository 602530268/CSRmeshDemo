/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Light White response object
*/

@interface CSRRestLightWhite : CSRRestBaseObject




/*!
    White level
*/
@property(nonatomic) NSNumber* level;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestLightWhite

  @param level - (NSNumber*) White level
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestLightWhite
*/
- (id) initWithlevel: (NSNumber*) level     
       deviceId: (NSNumber*) deviceId;
       

@end
