/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestSensorGetStateRequest.h"
#import "CSRRestSensorStateResponse.h"
#import "CSRRestSensorGetTypesRequest.h"
#import "CSRRestSensorTypesResponse.h"
#import "CSRRestSensorValueResponse.h"
#import "CSRRestSensorReadValueRequest.h"
#import "CSRRestSensorSetStateRequest.h"
#import "CSRRestSensorWriteValueRequest.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestSensorModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestSensorModelApi: CSRRestBaseApi


/*!
  Getting Sensor State: Upon receiving a SENSOR_GET_STATE message, where the destination address is the deviceID of this device and the Type field is a supported sensor type, the device shall respond with a SENSOR_STATE message with the current state information of the sensor type. Upon receiving a SENSOR_GET_STATE message, where the destination address is the device ID of this device but the Type field is not a supported sensor type, the device shall ignore the message.
 
  Getting Sensor State: Upon receiving a SENSOR_GET_STATE message, where the destination address is the deviceID of this device and the Type field is a supported sensor type, the device shall respond with a SENSOR_STATE message with the current state information of the sensor type. Upon receiving a SENSOR_GET_STATE message, where the destination address is the device ID of this device but the Type field is not a supported sensor type, the device shall ignore the message.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param sensorGetStateRequest - (CSRRestSensorGetStateRequest*)  Request Object for GetState API for model Sensor
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestSensorStateResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestSensorStateResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

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
     sensorGetStateRequest :(CSRRestSensorGetStateRequest*) sensorGetStateRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestSensorStateResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Upon receiving a SENSOR_GET_TYPES message, the device responds with a SENSOR_TYPES message with the list of supported types greater than or equal to the FirstType field. If the device does not support any types greater than or equal to the FirstType field, then it sends a SENSOR_TYPES message with zero-length Types field.
 
  Upon receiving a SENSOR_GET_TYPES message, the device responds with a SENSOR_TYPES message with the list of supported types greater than or equal to the FirstType field. If the device does not support any types greater than or equal to the FirstType field, then it sends a SENSOR_TYPES message with zero-length Types field.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param sensorGetTypesRequest - (CSRRestSensorGetTypesRequest*)  Request Object for GetTypes API for model Sensor
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestSensorTypesResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestSensorTypesResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

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
     sensorGetTypesRequest :(CSRRestSensorGetTypesRequest*) sensorGetTypesRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestSensorTypesResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Getting Sensor Value: Upon receiving a SENSOR_READ_VALUE message, where the Type field is a supported sensor type, the device responds with a SENSOR_VALUE message with the value of the sensor type. Proxy Behaviour: Upon receiving a SENSOR_GET_STATE where the destination of the message and the sensor type correspond to a previously received SENSOR_BROADCAST_VALUE or SENSOR_BROADCAST_NEW message, the device responds with a SENSOR_VALUE message with the remembered values.
 
  Getting Sensor Value: Upon receiving a SENSOR_READ_VALUE message, where the Type field is a supported sensor type, the device responds with a SENSOR_VALUE message with the value of the sensor type. Proxy Behaviour: Upon receiving a SENSOR_GET_STATE where the destination of the message and the sensor type correspond to a previously received SENSOR_BROADCAST_VALUE or SENSOR_BROADCAST_NEW message, the device responds with a SENSOR_VALUE message with the remembered values.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param sensorReadValueRequest - (CSRRestSensorReadValueRequest*)  Request Object for ReadValue API for model Sensor
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestSensorValueResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestSensorValueResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) readValue :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     sensorReadValueRequest :(CSRRestSensorReadValueRequest*) sensorReadValueRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestSensorValueResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Setting Sensor State: Upon receiving a SENSOR_SET_STATE message, where the destination address is the device ID of this device and the Type field is a supported sensor type, the device saves the RxDutyCycle field and responds with a SENSOR_STATE message with the current state information of the sensor type. If the Type field is not a supported sensor type, the device ignores the message.
 
  Setting Sensor State: Upon receiving a SENSOR_SET_STATE message, where the destination address is the device ID of this device and the Type field is a supported sensor type, the device saves the RxDutyCycle field and responds with a SENSOR_STATE message with the current state information of the sensor type. If the Type field is not a supported sensor type, the device ignores the message.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param sensorSetStateRequest - (CSRRestSensorSetStateRequest*)  Request Object for SetState API for model Sensor
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestSensorStateResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestSensorStateResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

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
     sensorSetStateRequest :(CSRRestSensorSetStateRequest*) sensorSetStateRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestSensorStateResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Writing Sensor Value: Upon receiving a SENSOR_WRITE_VALUE message, where the Type field is a supported sensor type, the device saves the value into the current value of the sensor type on this device and responds with a SENSOR_VALUE message with the current value of this sensor type.
 
  Writing Sensor Value: Upon receiving a SENSOR_WRITE_VALUE message, where the Type field is a supported sensor type, the device saves the value into the current value of the sensor type on this device and responds with a SENSOR_VALUE message with the current value of this sensor type.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param ack - (NSNumber*) [optional] Is response from the API call required. Defaults to true.
  @param sensorWriteValueRequest - (CSRRestSensorWriteValueRequest*)  Request Object for WriteValue API for model Sensor
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestSensorValueResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestSensorValueResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) writeValue :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     ack :(NSNumber*) ack 
     sensorWriteValueRequest :(CSRRestSensorWriteValueRequest*) sensorWriteValueRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestSensorValueResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end