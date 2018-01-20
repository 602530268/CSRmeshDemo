/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestDataReceivedResponse.h"
#import "CSRRestDataSendRequest.h"
#import "CSRRestBaseObject.h"
#import "CSRRestResponseLink.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestDataModelApi is a part of the CSR Mesh Api and provides a set of related methods to this Model.
*/
@interface CSRRestDataModelApi: CSRRestBaseApi


/*!
  Sending Data  Upon receiving a DATA_STREAM_SEND message, the device first checks if the StreamSN field is the same as the StreamSequenceNumber model state. If these values are the same, the device passes the StreamOctets field up to the application for processing, and increments StreamSequenceNumber by the length of the StreamOctets field. It then responds with a DATA_STREAM_RECEIVED message with the current value of the StreamSequenceNumber.  Note: The DATA_STREAM_RECEIVED message is sent even if the StreamSN received is different from the StreamSequenceNumber state. This allows missing packets to be detected and retransmitted by the sending device.
 
  Sending Data  Upon receiving a DATA_STREAM_SEND message, the device first checks if the StreamSN field is the same as the StreamSequenceNumber model state. If these values are the same, the device passes the StreamOctets field up to the application for processing, and increments StreamSequenceNumber by the length of the StreamOctets field. It then responds with a DATA_STREAM_RECEIVED message with the current value of the StreamSequenceNumber.  Note: The DATA_STREAM_RECEIVED message is sent even if the StreamSN received is different from the StreamSequenceNumber state. This allows missing packets to be detected and retransmitted by the sending device.
 
  @param tenantId - (NSString*)  ID of the tenant to send the request
  @param siteId - (NSString*)  ID of the site to send the request
  @param meshId - (NSString*)  ID of the mesh to send the request
  @param deviceId - (NSString*)  ID of the device to send the request
  @param csrmeshApplicationCode - (NSString*)  Application Code of the calling Application.
  @param meshType - (NSString*) [optional] Mesh type - Either sigmesh or csrmesh are allowed.
  @param multiple - (NSNumber*) [optional] Whether the request affects multiple MCP entities.
  @param repeats - (NSNumber*) [optional] Number of times the request should be repeated on the mesh node.
  @param ack - (NSNumber*) [optional] Is response from the API call required. Defaults to true.
  @param dataSendRequest - (CSRRestDataSendRequest*)  Request Object for StreamSend API for model Data
  @param requestBlock An optional block which receives the request sent notification with an error code. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestDataReceivedResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestDataReceivedResponse and also a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) sendData :(NSString*) tenantId 
     siteId :(NSString*) siteId 
     meshId :(NSString*) meshId 
     deviceId :(NSString*) deviceId 
     csrmeshApplicationCode :(NSString*) csrmeshApplicationCode 
     meshType :(NSString*) meshType 
     multiple :(NSNumber*) multiple 
     repeats :(NSNumber*) repeats 
     ack :(NSNumber*) ack 
     dataSendRequest :(CSRRestDataSendRequest*) dataSendRequest 
     requestHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse)) requestBlock
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestDataReceivedResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end