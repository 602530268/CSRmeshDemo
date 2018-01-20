/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestIssueExtendedOpcodeMessageRequest.h"
#import "CSRRestOpcodeMessageResponse.h"
#import "CSRRestBaseObject.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestOpcodeManagementApi is a part of the CSR Mesh Api and provides a set of related methods.
*/
@interface CSRRestOpcodeManagementApi: CSRRestBaseApi


/*!
  Issuing an extended OpCode message.
 
  Issuing an extended OpCode message.
 
  @param tenantId - (NSString*)  Tenant ID
  @param siteId - (NSString*)  Site ID
  @param meshId - (NSString*)  Mesh ID
  @param deviceId - (NSString*)  Device ID
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param issueExtendedOpcodeMessageRequest - (CSRRestIssueExtendedOpcodeMessageRequest*)  Request Object for Issuing Opcode Message 
  @param responseBlock An optional block which receives the results of the resource load.
          If success, error object will be nil. If failure a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) issueOpcode : (NSString*) tenantId 
     siteId : (NSString*) siteId 
     meshId : (NSString*) meshId 
     deviceId : (NSString*) deviceId 
     meshType : (NSString*) meshType 
     csrmeshApplicationCode : (NSString*) csrmeshApplicationCode 
     multiple : (NSNumber*) multiple 
     repeats : (NSNumber*) repeats 
     issueExtendedOpcodeMessageRequest : (CSRRestIssueExtendedOpcodeMessageRequest*) issueExtendedOpcodeMessageRequest 
     responseHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Upon receiving a Extended OPCODE message, response with a OPCODE_MESSAGE with the device Id and Base 64 encoded Opcode Payload will be returned.
 
  Upon receiving a Extended OPCODE message, response with a OPCODE_MESSAGE with the device Id and Base 64 encoded Opcode Payload will be returned .
 
  @param tenantId - (NSString*)  Tenant ID
  @param siteId - (NSString*)  Site ID
  @param meshId - (NSString*)  Mesh ID
  @param opcodeId - (NSString*)  Registered Opcode ID
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param replyAfter - (NSNumber*) [optional] Respond with delta after the time passed in.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestOpcodeMessageResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestOpcodeMessageResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) opcodeMessage : (NSString*) tenantId 
     siteId : (NSString*) siteId 
     meshId : (NSString*) meshId 
     opcodeId : (NSString*) opcodeId 
     csrmeshApplicationCode : (NSString*) csrmeshApplicationCode 
     replyAfter : (NSNumber*) replyAfter 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestOpcodeMessageResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end
