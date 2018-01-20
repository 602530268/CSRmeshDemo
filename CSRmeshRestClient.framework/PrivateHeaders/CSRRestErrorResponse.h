/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestErrorInfo.h"


/*!
*/

@interface CSRRestErrorResponse : CSRRestBaseObject




  /*!
    Status code for the response error.
  */
  @property(nonatomic) NSNumber* statusCode;
  
  /*!
    Array of errors that occurred on server.
  */
  @property(nonatomic) NSArray* errors;
  

/*!
  Constructs instance of CSRRestErrorResponse

  @param statusCode - (NSNumber*) Status code for the response error.
  @param errors - (NSArray*) Array of errors that occurred on server.
  
  @return instance of CSRRestErrorResponse
*/
- (id) initWithstatusCode: (NSNumber*) statusCode     
       errors: (NSArray*) errors;
       

@end
