/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestActionDeleteRequest.h"
#import "CSRRestActionDeleteAckResponse.h"
#import "CSRRestActionGetActionAckResponse.h"
#import "CSRRestActionGetRequest.h"
#import "CSRRestActionActionStatusResponse.h"
#import "CSRRestActionSetActionRequest.h"
#import "CSRRestActionSetActionAckResponse.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestActionModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestActionModelApi: CSRRestBaseApi


/*!
  This message allows a set of actions to be removed. Actions are identified through a bitmask reflecting the ActionID one wishes to delete. This message will be acknowledged through ACTION_DELETE_ACK.
 
  This message allows a set of actions to be removed. Actions are identified through a bitmask reflecting the ActionID one wishes to delete. This message will be acknowledged through ACTION_DELETE_ACK.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param actionDeleteRequest - (CSRRestActionDeleteRequest*)  Request Object for Delete API for model Action
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestActionDeleteAckResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestActionDeleteAckResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) delete :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     actionDeleteRequest :(CSRRestActionDeleteRequest*) actionDeleteRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestActionDeleteAckResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Recover action specified through the specify action ID.
 
  Recover action specified through the specify action ID.
 
  @param tenantId - (NSString*)  Tenant ID
  @param siteId - (NSString*)  Site ID
  @param meshId - (NSString*)  Mesh ID
  @param deviceId - (NSString*)  Device ID
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param actionGetRequest - (CSRRestActionGetRequest*)  Request Object of Get API for model Action
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestActionGetActionAckResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestActionGetActionAckResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) get :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     meshType :(NSString*) meshType 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     actionGetRequest :(CSRRestActionGetRequest*) actionGetRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestActionGetActionAckResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Request towards a node about the various Actions currently handled. This will be answered through an ACTION_STATUS. A Transaction ID is provided to ensure identification of response with request.
 
  Request towards a node about the various Actions currently handled. This will be answered through an ACTION_STATUS. A Transaction ID is provided to ensure identification of response with request.
 
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
         If success, a valid object of CSRRestActionActionStatusResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestActionActionStatusResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getActionStatus :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestActionActionStatusResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Set Action.
 
  Set Action .
 
  @param tenantId - (NSString*)  Tenant ID
  @param siteId - (NSString*)  Site ID
  @param meshId - (NSString*)  Mesh ID
  @param deviceId - (NSString*)  Device ID
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param actionSetActionRequest - (CSRRestActionSetActionRequest*)  Request Object of Message API for model action
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestActionSetActionAckResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestActionSetActionAckResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) setAction :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     actionSetActionRequest :(CSRRestActionSetActionRequest*) actionSetActionRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestActionSetActionAckResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end