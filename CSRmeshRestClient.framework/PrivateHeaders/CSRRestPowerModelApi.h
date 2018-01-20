/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestPowerStateResponse.h"
#import "CSRRestPowerSetStateRequest.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestPowerModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestPowerModelApi: CSRRestBaseApi


/*!
  Getting Power State: Upon receiving a POWER_GET_STATE message, the device responds with a POWER_STATE message with the current state information.
 
  Getting Power State: Upon receiving a POWER_GET_STATE message, the device responds with a POWER_STATE message with the current state information.
 
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
         If success, a valid object of CSRRestPowerStateResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestPowerStateResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

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
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestPowerStateResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Setting Power State: Upon receiving a POWER_SET_STATE_NO_ACK message, the device sets the PowerState state value to the PowerState field. It then responds with a POWER_STATE message with the current state information.
 
  Setting Power State: Upon receiving a POWER_SET_STATE_NO_ACK message, the device sets the PowerState state value to the PowerState field. It then responds with a POWER_STATE message with the current state information.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param ack - (NSNumber*) [optional] Is response from the API call required. Defaults to true.
  @param powerSetStateRequest - (CSRRestPowerSetStateRequest*)  Request Object for SetState API for model Power
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestPowerStateResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestPowerStateResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

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
     ack :(NSNumber*) ack 
     powerSetStateRequest :(CSRRestPowerSetStateRequest*) powerSetStateRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestPowerStateResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Toggling Power State: Upon receiving a POWER_Toggle_STATE_NO_ACK message, the device sets the PowerState state value as defined: 1.If the current PowerState is 0x00, Off, then PowerState should be set to 0x01, On. 2.If the current PowerState is 0x01, On, then PowerState should be set to 0x00, Off. 3.If the current PowerState is 0x02, Standby, then PowerState should be set to 0x03, OnFromStandby. 4.If the current PowerState is 0x03, OnFromStandby, then PowerState should be set to 0x02, Standby. Then the device responds with a POWER_STATE message with the current state information.
 
  Toggling Power State: Upon receiving a POWER_Toggle_STATE_NO_ACK message, the device sets the PowerState state value as defined: 1.If the current PowerState is 0x00, Off, then PowerState should be set to 0x01, On. 2.If the current PowerState is 0x01, On, then PowerState should be set to 0x00, Off. 3.If the current PowerState is 0x02, Standby, then PowerState should be set to 0x03, OnFromStandby. 4.If the current PowerState is 0x03, OnFromStandby, then PowerState should be set to 0x02, Standby. Then the device responds with a POWER_STATE message with the current state information.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param ack - (NSNumber*) [optional] Is response from the API call required. Defaults to true.
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestPowerStateResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestPowerStateResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) toggleState :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     ack :(NSNumber*) ack 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestPowerStateResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end