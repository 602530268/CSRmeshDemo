/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBlacklistDeviceStateResponse.h"
#import "CSRRestObjectTransferedResponse.h"
#import "CSRRestObjectTransferRequest.h"
#import "CSRRestRegisterResponseOpcodesRequest.h"
#import "CSRRestRegisterRespOpcodesResponse.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestMeshConfigModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestMeshConfigModelApi: CSRRestBaseApi


/*!
  Request for Blacklisted Status of a Device
 
  This API is used to request for the state of device which was requested to be blacklisted.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param siteId - (NSString*)  Site ID.
  @param meshId - (NSString*)  Mesh ID.
  @param deviceId - (NSString*)  Device ID whose Blacklist status need to be retrieved.
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestBlacklistDeviceStateResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestBlacklistDeviceStateResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) blacklistDeviceStateRequest :(NSString*) csrmeshApplicationCode 
     tenantId :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestBlacklistDeviceStateResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Upgrade Firmware of Device(s)
 
  This API is used to update firmware of devices in mesh network. This is used in conjunction with generic file upload API. Firmware file is first uploaded using generic file upload, file_name is then supplied in this API to start firmware update on specified devices.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param siteId - (NSString*)  Site ID.
  @param meshId - (NSString*)  Mesh ID.
  @param objectTransferRequest - (CSRRestObjectTransferRequest*)  Request Object for updating firmware of devices in mesh network.
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestObjectTransferedResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestObjectTransferedResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) objectTransfer :(NSString*) csrmeshApplicationCode 
     tenantId :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     objectTransferRequest :(CSRRestObjectTransferRequest*) objectTransferRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestObjectTransferedResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Response OpCode Registeration
 
  This API enables the applications to get the response back from the mesh for specified opcodes.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param siteId - (NSString*)  Site ID.
  @param meshId - (NSString*)  Mesh ID.
  @param registerResponseOpcodesRequest - (CSRRestRegisterResponseOpcodesRequest*)  Request Object for registering of response opcodes in mesh network.
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestRegisterRespOpcodesResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestRegisterRespOpcodesResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) registerForReponseOpcode :(NSString*) csrmeshApplicationCode 
     tenantId :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     registerResponseOpcodesRequest :(CSRRestRegisterResponseOpcodesRequest*) registerResponseOpcodesRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestRegisterRespOpcodesResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end