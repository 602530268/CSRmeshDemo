/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Uploading a file.
*/

@interface CSRRestCreateFileRequest : CSRRestBaseObject




/*!
    Content of a file
*/
@property(nonatomic) NSData* content;
  
/*!
  Constructs instance of CSRRestCreateFileRequest

  @param content - (NSData*) Content of a file
  
  @return instance of CSRRestCreateFileRequest
*/
- (id) initWithcontent: (NSData*) content;
       

@end
