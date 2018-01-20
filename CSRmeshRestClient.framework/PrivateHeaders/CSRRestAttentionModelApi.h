/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestAttentionSetStateRequest.h"
#import "CSRRestAttentionStateResponse.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestAttentionModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestAttentionModelApi: CSRRestBaseApi


/*!
  Setting Flashing State: Upon receiving an ATTENTION_SET_STATE message, the device saves the AttractAttention and AttentionDuration fields into the appropriate state value. It then responds with an ATTENTION_STATE message with the current state information. If the AttractAttention field is set to 0x01 and the AttentionDuration is not 0xFFFF, then any existing attention timer is cancelled and a new attention timer is started that will expire after AttentionDuration milliseconds. If the AttractAttention field is set to 0x01 and the AttentionDuration field is 0xFFFF, then the attention timer is ignored. If the AttractAttention field is set to 0x00, then the attention timer is cancelled if it is already running.
 
  Setting Flashing State: Upon receiving an ATTENTION_SET_STATE message, the device saves the AttractAttention and AttentionDuration fields into the appropriate state value. It then responds with an ATTENTION_STATE message with the current state information. If the AttractAttention field is set to 0x01 and the AttentionDuration is not 0xFFFF, then any existing attention timer is cancelled and a new attention timer is started that will expire after AttentionDuration milliseconds. If the AttractAttention field is set to 0x01 and the AttentionDuration field is 0xFFFF, then the attention timer is ignored. If the AttractAttention field is set to 0x00, then the attention timer is cancelled if it is already running.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param attentionSetStateRequest - (CSRRestAttentionSetStateRequest*)  Request Object for SetState API for model Attention
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestAttentionStateResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestAttentionStateResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

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
     attentionSetStateRequest :(CSRRestAttentionSetStateRequest*) attentionSetStateRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestAttentionStateResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end