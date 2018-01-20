/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestPingResponse.h"


/*!
    Response Object of Response API for model Ping
*/

@interface CSRRestPingResponseResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestPingResponseResponseStatusEnum) {
  CSRRestPingResponseResponseStatusEnumPending,
  CSRRestPingResponseResponseStatusEnumCompleted,
  CSRRestPingResponseResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestPingResponseResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Ping Response response object
*/
@property(nonatomic) NSArray* response;
  
/*!
  Constructs instance of CSRRestPingResponseResponse

  @param status - (CSRRestPingResponseResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param response - (NSArray*) The actual Ping Response response object
  
  @return instance of CSRRestPingResponseResponse
*/
- (id) initWithstatus: (CSRRestPingResponseResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       response: (NSArray*) response;
       

@end
