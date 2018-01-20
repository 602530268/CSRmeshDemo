/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetModelGroupid API for the Group model
*/

@interface CSRRestGroupSetModelGroupidRequest : CSRRestBaseObject




/*!
    Model number
*/
@property(nonatomic) NSNumber* model;
  
/*!
    Index of the group
*/
@property(nonatomic) NSNumber* groupIndex;
  
/*!
    Instance of the group
*/
@property(nonatomic) NSNumber* instance;
  
/*!
    Group identifier
*/
@property(nonatomic) NSNumber* groupId;
  
/*!
  Constructs instance of CSRRestGroupSetModelGroupidRequest

  @param model - (NSNumber*) Model number
  @param groupIndex - (NSNumber*) Index of the group
  @param instance - (NSNumber*) Instance of the group
  @param groupId - (NSNumber*) Group identifier
  
  @return instance of CSRRestGroupSetModelGroupidRequest
*/
- (id) initWithmodel: (NSNumber*) model     
       groupIndex: (NSNumber*) groupIndex     
       instance: (NSNumber*) instance     
       groupId: (NSNumber*) groupId;
       

@end
