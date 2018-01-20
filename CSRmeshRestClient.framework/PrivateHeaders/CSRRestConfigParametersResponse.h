/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestConfigParameters.h"


/*!
    Response Object of Parameters API for model Config
*/

@interface CSRRestConfigParametersResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestConfigParametersResponseStatusEnum) {
  CSRRestConfigParametersResponseStatusEnumPending,
  CSRRestConfigParametersResponseStatusEnumCompleted,
  CSRRestConfigParametersResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestConfigParametersResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Config Parameters response object
*/
@property(nonatomic) NSArray* parameters;
  
/*!
  Constructs instance of CSRRestConfigParametersResponse

  @param status - (CSRRestConfigParametersResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param parameters - (NSArray*) The actual Config Parameters response object
  
  @return instance of CSRRestConfigParametersResponse
*/
- (id) initWithstatus: (CSRRestConfigParametersResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       parameters: (NSArray*) parameters;
       

@end
