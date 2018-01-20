/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for GetNumberOfModelGroupids API for the Group model
*/

@interface CSRRestGroupGetNumberOfModelGroupidsRequest : CSRRestBaseObject




/*!
    Model number
*/
@property(nonatomic) NSNumber* model;
  
/*!
  Constructs instance of CSRRestGroupGetNumberOfModelGroupidsRequest

  @param model - (NSNumber*) Model number
  
  @return instance of CSRRestGroupGetNumberOfModelGroupidsRequest
*/
- (id) initWithmodel: (NSNumber*) model;
       

@end
