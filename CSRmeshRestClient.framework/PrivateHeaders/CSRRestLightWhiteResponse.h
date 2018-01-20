/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestLightWhite.h"


/*!
    Response Object of White API for model Light
*/

@interface CSRRestLightWhiteResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestLightWhiteResponseStatusEnum) {
  CSRRestLightWhiteResponseStatusEnumPending,
  CSRRestLightWhiteResponseStatusEnumCompleted,
  CSRRestLightWhiteResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestLightWhiteResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Light White response object
*/
@property(nonatomic) NSArray* white;
  
/*!
  Constructs instance of CSRRestLightWhiteResponse

  @param status - (CSRRestLightWhiteResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param white - (NSArray*) The actual Light White response object
  
  @return instance of CSRRestLightWhiteResponse
*/
- (id) initWithstatus: (CSRRestLightWhiteResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       white: (NSArray*) white;
       

@end
