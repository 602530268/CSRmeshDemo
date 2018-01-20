/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestExtensionConflictResponse.h"
#import "CSRRestExtensionRequestRequest.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestExtensionModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestExtensionModelApi: CSRRestBaseApi


/*!
  Request for Extension OpCode to be approved by the whole Mesh. A device wanting to use an OpCode, makes a request to the entire Mesh Network. This message is issued to target identity 0. The device waits some time, proportional to the size of the Mesh network and only after this period, messages using these proposed OpCode are used. Device receiving this message and wanting to oppose the usage of such code will respond to the source node with a CONFLICT. In case no conflict is known and the OpCode is for a message the node is interested in implementing (through comparison with hash value), a record of the OpCode and its mapping is kept.  Request messages are relayed in cases of absence of conflict. The hash function is SHA-256, padded as per SHA-256 specifications2, for which the least significant 6 bytes will be used in the message. The range parameter indicates the maximum number of OpCode reserved from the based provided in the Proposed OpCode field. The last OpCode reserved is determined through the sum of the Proposed OpCode with the range value. This range parameter varies from 0 to 127, leaving the top bit free.
 
  Request for Extension OpCode to be approved by the whole Mesh. A device wanting to use an OpCode, makes a request to the entire Mesh Network. This message is issued to target identity 0. The device waits some time, proportional to the size of the Mesh network and only after this period, messages using these proposed OpCode are used. Device receiving this message and wanting to oppose the usage of such code will respond to the source node with a CONFLICT. In case no conflict is known and the OpCode is for a message the node is interested in implementing (through comparison with hash value), a record of the OpCode and its mapping is kept.  Request messages are relayed in cases of absence of conflict. The hash function is SHA-256, padded as per SHA-256 specifications2, for which the least significant 6 bytes will be used in the message. The range parameter indicates the maximum number of OpCode reserved from the based provided in the Proposed OpCode field. The last OpCode reserved is determined through the sum of the Proposed OpCode with the range value. This range parameter varies from 0 to 127, leaving the top bit free.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param extensionRequestRequest - (CSRRestExtensionRequestRequest*)  Request Object for Request API for model Extension
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestExtensionConflictResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestExtensionConflictResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) request :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     extensionRequestRequest :(CSRRestExtensionRequestRequest*) extensionRequestRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestExtensionConflictResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end