/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
*/

@interface CSRRestAssociationStatusLink : CSRRestBaseObject




/*!
    Current status URL for MASP new device association flow.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
  Constructs instance of CSRRestAssociationStatusLink

  @param statusUrl - (NSString*) Current status URL for MASP new device association flow.
  
  @return instance of CSRRestAssociationStatusLink
*/
- (id) initWithstatusUrl: (NSString*) statusUrl;
       

@end
