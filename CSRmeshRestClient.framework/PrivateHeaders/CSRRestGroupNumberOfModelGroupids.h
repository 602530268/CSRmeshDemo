/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Group NumberOfModelGroupids response object
*/

@interface CSRRestGroupNumberOfModelGroupids : CSRRestBaseObject




/*!
    Model number
*/
@property(nonatomic) NSNumber* model;
  
/*!
    Number of model groups
*/
@property(nonatomic) NSNumber* numGroups;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestGroupNumberOfModelGroupids

  @param model - (NSNumber*) Model number
  @param numGroups - (NSNumber*) Number of model groups
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestGroupNumberOfModelGroupids
*/
- (id) initWithmodel: (NSNumber*) model     
       numGroups: (NSNumber*) numGroups     
       deviceId: (NSNumber*) deviceId;
       

@end
