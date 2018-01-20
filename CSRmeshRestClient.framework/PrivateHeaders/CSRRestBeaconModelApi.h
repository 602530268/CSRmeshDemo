/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBeaconBeaconStatusResponse.h"
#import "CSRRestBeaconGetBeaconStatusRequest.h"
#import "CSRRestBeaconGetPayloadRequest.h"
#import "CSRRestBeaconSetPayloadResponse.h"
#import "CSRRestBeaconTypesResponse.h"
#import "CSRRestBeaconPayloadAckRequest.h"
#import "CSRRestBeaconPayloadAckResponse.h"
#import "CSRRestBeaconSetPayloadRequest.h"
#import "CSRRestBeaconSetStatusRequest.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestBeaconModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestBeaconModelApi: CSRRestBaseApi


/*!
  Message to be sent to a beacon in order to recover its current status. This message fetch information pertinent to a particular type. The transaction ID will help matching the pertinent BEACON_STATUS message � a different transaction ID shall be used for a different type (although the BEACON_STATUS message has the type pertinent to the status and thus could be used in conjunction to the Transaction ID for disambiguation).
 
  Message to be sent to a beacon in order to recover its current status. This message fetch information pertinent to a particular type. The transaction ID will help matching the pertinent BEACON_STATUS message � a different transaction ID shall be used for a different type (although the BEACON_STATUS message has the type pertinent to the status and thus could be used in conjunction to the Transaction ID for disambiguation).
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param beaconGetBeaconStatusRequest - (CSRRestBeaconGetBeaconStatusRequest*)  Request Object for GetBeaconStatus API for model Beacon
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestBeaconBeaconStatusResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestBeaconBeaconStatusResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getBeaconStatus :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     beaconGetBeaconStatusRequest :(CSRRestBeaconGetBeaconStatusRequest*) beaconGetBeaconStatusRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestBeaconBeaconStatusResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Message allowing a node to retrieve the current payload held on a given beacon. This message shall be answered by one or more BEACON_SET_PAYLOAD messages.
 
  Message allowing a node to retrieve the current payload held on a given beacon. This message shall be answered by one or more BEACON_SET_PAYLOAD messages.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param beaconGetPayloadRequest - (CSRRestBeaconGetPayloadRequest*)  Request Object for GetPayload API for model Beacon
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestBeaconSetPayloadResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestBeaconSetPayloadResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getPayload :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     beaconGetPayloadRequest :(CSRRestBeaconGetPayloadRequest*) beaconGetPayloadRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestBeaconSetPayloadResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Message allowing a node to fetch all supported types and associated information by a given Beacon.
 
  Message allowing a node to fetch all supported types and associated information by a given Beacon.
 
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
         If success, a valid object of CSRRestBeaconTypesResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestBeaconTypesResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

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
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestBeaconTypesResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Only one Acknowledgement message will occur for multiple BEACON_SET_PAYLOAD messages sharing the same transaction ID. Only when the last segment is received that such acknowledgement will be issued. Where missing payload messages exist, the list of their indices will be provided in the Ack field.
 
  Only one Acknowledgement message will occur for multiple BEACON_SET_PAYLOAD messages sharing the same transaction ID. Only when the last segment is received that such acknowledgement will be issued. Where missing payload messages exist, the list of their indices will be provided in the Ack field.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param beaconPayloadAckRequest - (CSRRestBeaconPayloadAckRequest*)  Request Object for PayloadAck API for model Beacon
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  
         If success, error object will be nil. If failure a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) payloadAck :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     repeats :(NSNumber*) repeats 
     beaconPayloadAckRequest :(CSRRestBeaconPayloadAckRequest*) beaconPayloadAckRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock;



/*!
  One or more of these packets may be sent to a beacon to set its payload. The content is either the raw advert data, or extra information (such as crypto cycle) which a beacon may require. The payload data is sent as a length and an offset, so the whole payload need not be sent if it has not changed. A beacon can support many beacon types - it can be sent as many different payloads as needed, one for each type. The first byte of the first payload packet contains the length and offset of the payload and the payload ID; this allows a beacon which already has the payload to send an immediate acknowledgement, saving traffic. This ID will be sent back in the 'Payload ACK' message if the beacon has received the whole payload. The payload may have to be split in several parts, in which case only the last part shall be acknowledged. Upon receiving a BEACON_SET_PAYLOAD, the beacon will update its corresponding beacon data � if data was previously available, it will be replaced by the provided payload, thus a beacon can only hold one payload per beacon type.
 
  One or more of these packets may be sent to a beacon to set its payload. The content is either the raw advert data, or extra information (such as crypto cycle) which a beacon may require. The payload data is sent as a length and an offset, so the whole payload need not be sent if it has not changed. A beacon can support many beacon types - it can be sent as many different payloads as needed, one for each type. The first byte of the first payload packet contains the length and offset of the payload and the payload ID; this allows a beacon which already has the payload to send an immediate acknowledgement, saving traffic. This ID will be sent back in the 'Payload ACK' message if the beacon has received the whole payload. The payload may have to be split in several parts, in which case only the last part shall be acknowledged. Upon receiving a BEACON_SET_PAYLOAD, the beacon will update its corresponding beacon data � if data was previously available, it will be replaced by the provided payload, thus a beacon can only hold one payload per beacon type.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param beaconSetPayloadRequest - (CSRRestBeaconSetPayloadRequest*)  Request Object for SetPayload API for model Beacon
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestBeaconPayloadAckResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestBeaconPayloadAckResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) setPayload :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     beaconSetPayloadRequest :(CSRRestBeaconSetPayloadRequest*) beaconSetPayloadRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestBeaconPayloadAckResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  May be sent to a beacon to set its status. More than one such command can be sent to set the intervals for different beacon types, which need not be the same. This message also allows for the wakeup intervals to be set if the beacon elects to only be on the mesh sporadically. The time is always with respect to the beacon�s internal clock and has no absolute meaning. This message will be answered through BEACON_STATUS.
 
  May be sent to a beacon to set its status. More than one such command can be sent to set the intervals for different beacon types, which need not be the same. This message also allows for the wakeup intervals to be set if the beacon elects to only be on the mesh sporadically. The time is always with respect to the beacon�s internal clock and has no absolute meaning. This message will be answered through BEACON_STATUS.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param beaconSetStatusRequest - (CSRRestBeaconSetStatusRequest*)  Request Object for SetStatus API for model Beacon
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestBeaconBeaconStatusResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestBeaconBeaconStatusResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) setStatus :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     beaconSetStatusRequest :(CSRRestBeaconSetStatusRequest*) beaconSetStatusRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestBeaconBeaconStatusResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end