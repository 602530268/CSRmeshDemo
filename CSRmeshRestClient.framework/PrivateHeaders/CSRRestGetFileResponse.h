/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Response Object for downloading a file.
*/

@interface CSRRestGetFileResponse : CSRRestBaseObject




/*!
    Content of a file
*/
@property(nonatomic) NSData* content;
  
/*!
  Constructs instance of CSRRestGetFileResponse

  @param content - (NSData*) Content of a file
  
  @return instance of CSRRestGetFileResponse
*/
- (id) initWithcontent: (NSData*) content;
       

@end
