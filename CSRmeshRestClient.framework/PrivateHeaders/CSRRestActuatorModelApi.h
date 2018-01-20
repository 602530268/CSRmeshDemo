/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestActuatorTypesResponse.h"
#import "CSRRestActuatorGetTypesRequest.h"
#import "CSRRestActuatorGetValueAckRequest.h"
#import "CSRRestActuatorValueAckResponse.h"
#import "CSRRestActuatorSetValueRequest.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestActuatorModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestActuatorModelApi: CSRRestBaseApi


/*!
  Upon receiving an ACTUATOR_GET_TYPES message, the device responds with an ACTUATOR_TYPES message with a list of supported types greater than or equal to the FirstType field. If the device does not support any types greater than or equal to FirstType, it sends an ACTUATOR_TYPES message with a zero length Types field.
 
  Upon receiving an ACTUATOR_GET_TYPES message, the device responds with an ACTUATOR_TYPES message with a list of supported types greater than or equal to the FirstType field. If the device does not support any types greater than or equal to FirstType, it sends an ACTUATOR_TYPES message with a zero length Types field.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param actuatorGetTypesRequest - (CSRRestActuatorGetTypesRequest*)  Request Object for GetTypes API for model Actuator
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestActuatorTypesResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestActuatorTypesResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getTypes :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     actuatorGetTypesRequest :(CSRRestActuatorGetTypesRequest*) actuatorGetTypesRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestActuatorTypesResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get Current sensor state
 
  Get Current sensor state
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param actuatorGetValueAckRequest - (CSRRestActuatorGetValueAckRequest*)  Request Object for GetValueAck API for model Actuator
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestActuatorValueAckResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestActuatorValueAckResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getValueAck :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     actuatorGetValueAckRequest :(CSRRestActuatorGetValueAckRequest*) actuatorGetValueAckRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestActuatorValueAckResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get sensor state. Upon receiving an ACTUATOR_SET_VALUE_NO_ACK message, where the destination address is the device ID of this device and the Type field is a supported actuator type, the device shall immediately use the Value field for the given Type field. The meaning of this actuator value is not defined in this specification. Upon receiving an ACTUATOR_SET_VALUE_NO_ACK message, where the destination address is is the device ID of this device but the Type field is not a supported actuator type, the device shall ignore the message.
 
  Get sensor state. Upon receiving an ACTUATOR_SET_VALUE_NO_ACK message, where the destination address is the device ID of this device and the Type field is a supported actuator type, the device shall immediately use the Value field for the given Type field. The meaning of this actuator value is not defined in this specification. Upon receiving an ACTUATOR_SET_VALUE_NO_ACK message, where the destination address is is the device ID of this device but the Type field is not a supported actuator type, the device shall ignore the message.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param ack - (NSNumber*) [optional] Is response from the API call required. Defaults to true.
  @param actuatorSetValueRequest - (CSRRestActuatorSetValueRequest*)  Request Object for SetValue API for model Actuator
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestActuatorValueAckResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestActuatorValueAckResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) setValue :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     ack :(NSNumber*) ack 
     actuatorSetValueRequest :(CSRRestActuatorSetValueRequest*) actuatorSetValueRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestActuatorValueAckResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end