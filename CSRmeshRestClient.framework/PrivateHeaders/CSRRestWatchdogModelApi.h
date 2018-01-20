/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestWatchdogMessageRequest.h"
#import "CSRRestWatchdogMessageResponse.h"
#import "CSRRestWatchdogSetIntervalRequest.h"
#import "CSRRestWatchdogIntervalResponse.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestWatchdogModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestWatchdogModelApi: CSRRestBaseApi


/*!
  Upon receiving a WATCHDOG_MESSAGE message, if the RspSize field is set to a non-zero value, then the device shall respond with a WATCHDOG_MESSAGE with the RspSize field set to zero, and RspSize -1 octets of additional RandomData.
 
  Upon receiving a WATCHDOG_MESSAGE message, if the RspSize field is set to a non-zero value, then the device shall respond with a WATCHDOG_MESSAGE with the RspSize field set to zero, and RspSize -1 octets of additional RandomData.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param watchdogMessageRequest - (CSRRestWatchdogMessageRequest*)  Request Object for Message API for model Watchdog
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestWatchdogMessageResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestWatchdogMessageResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) message :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     watchdogMessageRequest :(CSRRestWatchdogMessageRequest*) watchdogMessageRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestWatchdogMessageResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Upon receiving a WATCHDOG_SET_INTERVAL message, the device shall save the Interval and ActiveAfterTime fields into the Interval and ActiveAfterTime variables and respond with a WATCHDOG_INTERVAL message with the current variable values.
 
  Upon receiving a WATCHDOG_SET_INTERVAL message, the device shall save the Interval and ActiveAfterTime fields into the Interval and ActiveAfterTime variables and respond with a WATCHDOG_INTERVAL message with the current variable values.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param watchdogSetIntervalRequest - (CSRRestWatchdogSetIntervalRequest*)  Request Object for SetInterval API for model Watchdog
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestWatchdogIntervalResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestWatchdogIntervalResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) setInterval :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     watchdogSetIntervalRequest :(CSRRestWatchdogSetIntervalRequest*) watchdogSetIntervalRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestWatchdogIntervalResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end