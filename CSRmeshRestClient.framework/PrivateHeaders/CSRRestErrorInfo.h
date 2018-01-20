/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
*/

@interface CSRRestErrorInfo : CSRRestBaseObject




/*!
    Specific error code.
*/
@property(nonatomic) NSString* errorCode;
  
/*!
    Detailed description of the error code.
*/
@property(nonatomic) NSString* message;
  
/*!
  Constructs instance of CSRRestErrorInfo

  @param errorCode - (NSString*) Specific error code.
  @param message - (NSString*) Detailed description of the error code.
  
  @return instance of CSRRestErrorInfo
*/
- (id) initWitherrorCode: (NSString*) errorCode     
       message: (NSString*) message;
       

@end
