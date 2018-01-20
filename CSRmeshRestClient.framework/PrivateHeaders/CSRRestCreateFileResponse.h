/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Response Object for file created
*/

@interface CSRRestCreateFileResponse : CSRRestBaseObject




/*!
    Number of bytes written
*/
@property(nonatomic) NSNumber* size;
  
/*!
    Revision of the file created or uploaded
*/
@property(nonatomic) NSNumber* revision;
  
/*!
    Mime-type of the file, as supplied in ContentType header
*/
@property(nonatomic) NSString* mimeType;
  
/*!
    delete policy of the file
*/
@property(nonatomic) NSString* deletePolicy;
  
/*!
  Constructs instance of CSRRestCreateFileResponse

  @param size - (NSNumber*) Number of bytes written
  @param revision - (NSNumber*) Revision of the file created or uploaded
  @param mimeType - (NSString*) Mime-type of the file, as supplied in ContentType header
  @param deletePolicy - (NSString*) delete policy of the file
  
  @return instance of CSRRestCreateFileResponse
*/
- (id) initWithsize: (NSNumber*) size     
       revision: (NSNumber*) revision     
       mimeType: (NSString*) mimeType     
       deletePolicy: (NSString*) deletePolicy;
       

@end
