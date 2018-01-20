/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestTimeStateResponse.h"
#import "CSRRestTimeSetStateRequest.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestTimeModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestTimeModelApi: CSRRestBaseApi


/*!
  Getting Time Broadcast Interval: Upon receiving a TIME_GET_STATE message, the device responds with a TIME_STATE message with the current state information.
 
  Getting Time Broadcast Interval: Upon receiving a TIME_GET_STATE message, the device responds with a TIME_STATE message with the current state information.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestTimeStateResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestTimeStateResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getState :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestTimeStateResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Setting Time Broadcast Interval: Upon receiving a TIME_SET_STATE message, the device saves the TimeInterval field into the appropriate state value. It then responds with a TIME_STATE message with the current state information.
 
  Setting Time Broadcast Interval: Upon receiving a TIME_SET_STATE message, the device saves the TimeInterval field into the appropriate state value. It then responds with a TIME_STATE message with the current state information.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param timeSetStateRequest - (CSRRestTimeSetStateRequest*)  Request Object for SetState API for model Time
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestTimeStateResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestTimeStateResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) setState :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     timeSetStateRequest :(CSRRestTimeSetStateRequest*) timeSetStateRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestTimeStateResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end