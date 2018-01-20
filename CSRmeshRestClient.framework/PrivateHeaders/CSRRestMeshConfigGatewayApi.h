/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestAssociationStatusLink.h"
#import "CSRRestNewDeviceBroadCastStatusResponse.h"
#import "CSRRestGetGatewayProfileResponse.h"
#import "CSRRestBaseObject.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestMeshConfigGatewayApi is a part of the CSR Mesh Api and provides a set of related methods.
*/
@interface CSRRestMeshConfigGatewayApi: CSRRestBaseApi


/*!
  Trigger new device transmit flow for MASP.
 
  This API applies only to the gateway. It requests gateway to trigger new device transmit flow for MASP.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling application.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestAssociationStatusLink is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestAssociationStatusLink and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) newDeviceBroadcast : (NSString*) csrmeshApplicationCode 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestAssociationStatusLink* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get current status of MASP new device association flow.
 
  This API will get current status of MASP new device association flow, for the gateway behaving as non-configuring device.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling application.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestNewDeviceBroadCastStatusResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestNewDeviceBroadCastStatusResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) statusNewDeviceBroadcast : (NSString*) csrmeshApplicationCode 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestNewDeviceBroadCastStatusResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get profile of gateway.
 
  This API will return the profile of the gateway that the API is addressing.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling application.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestGetGatewayProfileResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestGetGatewayProfileResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) gatewayProfile : (NSString*) csrmeshApplicationCode 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestGetGatewayProfileResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Delete a mesh network on a gateway.
 
  A gateway supports more than one mesh network. This API is used to remove a single network on the gateway. This API will remove corresponding network keys from the CSRmesh stack on the gateway.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling application.
  @param meshId - (NSString*)   Mesh ID of the mesh network that is to be removed from the gateway.
  @param responseBlock An optional block which receives the results of the resource load.
          If success, error object will be nil. If failure a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) removeNetwork : (NSString*) csrmeshApplicationCode 
     meshId : (NSString*) meshId 
     responseHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end
