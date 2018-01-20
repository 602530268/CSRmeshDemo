/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for GetModelGroupid API for the Group model
*/

@interface CSRRestGroupGetModelGroupidRequest : CSRRestBaseObject




/*!
    Model number
*/
@property(nonatomic) NSNumber* model;
  
/*!
    Index of the group
*/
@property(nonatomic) NSNumber* groupIndex;
  
/*!
  Constructs instance of CSRRestGroupGetModelGroupidRequest

  @param model - (NSNumber*) Model number
  @param groupIndex - (NSNumber*) Index of the group
  
  @return instance of CSRRestGroupGetModelGroupidRequest
*/
- (id) initWithmodel: (NSNumber*) model     
       groupIndex: (NSNumber*) groupIndex;
       

@end
