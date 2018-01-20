/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestConfigDeviceIdentifierResponse.h"
#import "CSRRestConfigGetInfoRequest.h"
#import "CSRRestConfigInfoResponse.h"
#import "CSRRestConfigMessageParamsResponse.h"
#import "CSRRestConfigParametersResponse.h"
#import "CSRRestConfigLastSequenceNumberRequest.h"
#import "CSRRestConfigResetDeviceRequest.h"
#import "CSRRestConfigSetDeviceIdentifierRequest.h"
#import "CSRRestConfigSetMessageParamsRequest.h"
#import "CSRRestConfigSetParametersRequest.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestConfigModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestConfigModelApi: CSRRestBaseApi


/*!
  Upon receiving a CONFIG_DISCOVER_DEVICE message directed at the 0x0000 group identifier or to DeviceID of this device, the device responds with a CONFIG_DEVICE_IDENTIFIER message.
 
  Upon receiving a CONFIG_DISCOVER_DEVICE message directed at the 0x0000 group identifier or to DeviceID of this device, the device responds with a CONFIG_DEVICE_IDENTIFIER message.
 
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
         If success, a valid object of CSRRestConfigDeviceIdentifierResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestConfigDeviceIdentifierResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) discoverDevice :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestConfigDeviceIdentifierResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Upon receiving a CONFIG_GET_INFO message, directed at the DeviceID of this device, the device responds with a CONFIG_INFO message. The Info field of the CONFIG_GET_INFO message determines the information to be included in the CONFIG_INFO message. The following information values are defined: DeviceUUIDLow (0x00) contains the least significant eight octets of the DeviceUUID state value. DeviceUUIDHigh (0x01) contains the most significant eight octets of the DeviceUUID state value. ModelsLow (0x02) contains the least significant eight octets of the ModelsSupported state value. ModelsHigh (0x03) contains the most significant eight octets of the ModelsSupported state value.
 
  Upon receiving a CONFIG_GET_INFO message, directed at the DeviceID of this device, the device responds with a CONFIG_INFO message. The Info field of the CONFIG_GET_INFO message determines the information to be included in the CONFIG_INFO message. The following information values are defined: DeviceUUIDLow (0x00) contains the least significant eight octets of the DeviceUUID state value. DeviceUUIDHigh (0x01) contains the most significant eight octets of the DeviceUUID state value. ModelsLow (0x02) contains the least significant eight octets of the ModelsSupported state value. ModelsHigh (0x03) contains the most significant eight octets of the ModelsSupported state value.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param configGetInfoRequest - (CSRRestConfigGetInfoRequest*)  Request Object for GetInfo API for model Config
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestConfigInfoResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestConfigInfoResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getInfo :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     configGetInfoRequest :(CSRRestConfigGetInfoRequest*) configGetInfoRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestConfigInfoResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  
 
  
 
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
         If success, a valid object of CSRRestConfigMessageParamsResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestConfigMessageParamsResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getMessageParams :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestConfigMessageParamsResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Upon receiving a CONFIG_GET_PARAMETERS message, where the destination address is the DeviceID of this device, the device will respond with a CONFIG_PARAMETERS message with the current config model state information.
 
  Upon receiving a CONFIG_GET_PARAMETERS message, where the destination address is the DeviceID of this device, the device will respond with a CONFIG_PARAMETERS message with the current config model state information.
 
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
         If success, a valid object of CSRRestConfigParametersResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestConfigParametersResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getParameters :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestConfigParametersResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Upon receiving a CONFIG_LAST_SEQUENCE_NUMBER message from a trusted device, the local device updates the SequenceNumber to at least one higher than the LastSequenceNumber in the message. Note: A trusted device means a device that is not only on the same CSRmesh network, having the same network key, but also interacted with in the past. This message is most useful to check if a device has been reset, for example when the batteries of the device are changed, but it does not remember its last sequence number in non-volatile memory.
 
  Upon receiving a CONFIG_LAST_SEQUENCE_NUMBER message from a trusted device, the local device updates the SequenceNumber to at least one higher than the LastSequenceNumber in the message. Note: A trusted device means a device that is not only on the same CSRmesh network, having the same network key, but also interacted with in the past. This message is most useful to check if a device has been reset, for example when the batteries of the device are changed, but it does not remember its last sequence number in non-volatile memory.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param configLastSequenceNumberRequest - (CSRRestConfigLastSequenceNumberRequest*)  Request Object for LastSequenceNumber API for model Config
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  
         If success, error object will be nil. If failure a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) lastSequenceNumber :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     repeats :(NSNumber*) repeats 
     configLastSequenceNumberRequest :(CSRRestConfigLastSequenceNumberRequest*) configLastSequenceNumberRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock;



/*!
  Upon receiving a CONFIG_RESET_DEVICE message from a trusted device directed at only this device, the local device sets the DeviceID to zero, and forgets all network keys, associated NetworkIVs and other configuration information. The device may act as if it is not associated and use MASP to re-associate with a network. Note: If the CONFIG_RESET_DEVICE message is received on any other destination address than the DeviceID of the local device, it is ignored. This is typically used when selling a device, to remove the device from the network of the seller so that the purchaser can associate the device with their network.
 
  Upon receiving a CONFIG_RESET_DEVICE message from a trusted device directed at only this device, the local device sets the DeviceID to zero, and forgets all network keys, associated NetworkIVs and other configuration information. The device may act as if it is not associated and use MASP to re-associate with a network. Note: If the CONFIG_RESET_DEVICE message is received on any other destination address than the DeviceID of the local device, it is ignored. This is typically used when selling a device, to remove the device from the network of the seller so that the purchaser can associate the device with their network.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param configResetDeviceRequest - (CSRRestConfigResetDeviceRequest*) [optional] Request Object for ResetDevice API for model Config
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  
         If success, error object will be nil. If failure a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) resetDevice :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     repeats :(NSNumber*) repeats 
     configResetDeviceRequest :(CSRRestConfigResetDeviceRequest*) configResetDeviceRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock;



/*!
  When the device with a DeviceID of 0x0000 receives a CONFIG_SET_DEVICE_IDENTIFIER message and the DeviceHash of the message matches the DeviceHash of this device, the DeviceID of this device is set to the DeviceID field of this message. Then the device responds with the DEVICE_CONFIG_IDENTIFIER message using the new DeviceID as the source address. Note: This function is not necessary in normal operation of a CSRmesh network as DeviceID is distributed as part of the MASP protocol in the MASP_ID_DISTRIBUTION message.
 
  When the device with a DeviceID of 0x0000 receives a CONFIG_SET_DEVICE_IDENTIFIER message and the DeviceHash of the message matches the DeviceHash of this device, the DeviceID of this device is set to the DeviceID field of this message. Then the device responds with the DEVICE_CONFIG_IDENTIFIER message using the new DeviceID as the source address. Note: This function is not necessary in normal operation of a CSRmesh network as DeviceID is distributed as part of the MASP protocol in the MASP_ID_DISTRIBUTION message.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param configSetDeviceIdentifierRequest - (CSRRestConfigSetDeviceIdentifierRequest*)  Request Object for SetDeviceIdentifier API for model Config
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestConfigDeviceIdentifierResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestConfigDeviceIdentifierResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) setDeviceIdentifier :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     configSetDeviceIdentifierRequest :(CSRRestConfigSetDeviceIdentifierRequest*) configSetDeviceIdentifierRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestConfigDeviceIdentifierResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  
 
  
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param configSetMessageParamsRequest - (CSRRestConfigSetMessageParamsRequest*)  Request Object for SetMessageParams API for model Config
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestConfigMessageParamsResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestConfigMessageParamsResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) setMessageParams :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     configSetMessageParamsRequest :(CSRRestConfigSetMessageParamsRequest*) configSetMessageParamsRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestConfigMessageParamsResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Upon receiving a CONFIG_SET_PARAMETERS message, where the destination address is the DeviceID of this device, the device saves the TxInterval, TxDuration, RxDutyCycle, TxPower and TTL fields into the TransmitInterval, TransmitDuration, ReceiverDutyCycle, TransmitPower and DefaultTimeToLive state respectively. Then the device responds with a CONFIG_PARAMETERS message with the current configuration model state information.
 
  Upon receiving a CONFIG_SET_PARAMETERS message, where the destination address is the DeviceID of this device, the device saves the TxInterval, TxDuration, RxDutyCycle, TxPower and TTL fields into the TransmitInterval, TransmitDuration, ReceiverDutyCycle, TransmitPower and DefaultTimeToLive state respectively. Then the device responds with a CONFIG_PARAMETERS message with the current configuration model state information.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param configSetParametersRequest - (CSRRestConfigSetParametersRequest*)  Request Object for SetParameters API for model Config
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestConfigParametersResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestConfigParametersResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) setParameters :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     configSetParametersRequest :(CSRRestConfigSetParametersRequest*) configSetParametersRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestConfigParametersResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end