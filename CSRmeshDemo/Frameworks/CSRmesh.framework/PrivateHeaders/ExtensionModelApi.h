//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header The Extension Model allows dynamic allocation of OpCode within a Mesh Network. This, permits extension of existing models without the risk of encoding clashes as per Data Model usage. A node wanting to introduce a new Model/Message or a new Message to an existing model, has to select an OpCode unique for that purpose. Given that there is no overall authority able to allocate a unique OpCode, this model proposes a collaborative method, within the existing Mesh Network, to obtain this unique information. Two messages are proposed, one performing a request, another informing of a conflict.<br><br> As per the nature of Mesh Network, there is never an absolute guarantee of a solution, it is therefore necessary for the request to be repeated periodically. If anything, the periodic issue of this message will allow for new nodes to have the ability to collect the information. The request message has two purposes, indication of the intended OpCode and the mapping of this OpCode with the extension it is aimed at supplying. Identification of the function cover by the OpCode is done through an identity supplied by the manufacturer.<br><br> In order to avoid the obvious denial of service through blocking of requests from specific manufacturers, the unique identity is calculated from the hashing of a sentence provided by the manufacturer. The one-way nature of the Hash makes it hard to reverse.<br><br> For nodes intending to support these new messages, matching of the identity with the request, allows them to determine the OpCode to be used. Requests are relayed from node to node. Only when a node determine that the proposed Opcodes are conflicting with some internally used ones, the message will not be relayed, instead a conflict will be issued. Upon reception of a request, a node required to implement this function, takes note of the OpCode and starts processing messages with such OpCodes. <br><br> Conflict messages carry the conflicting OpCodes and the reason for issuing of the conflict. Conflict messages are processed by all, thus allowing non-conflicting nodes to make of note of the fact that the OpCode is invalid and thus prevent their processing. Each node is expected to keep track of all the OpCodes it is currently using. These are either static or dynamic. A node wishing to introduce a new (model, message) pair can do so through a proposal to the Mesh Networks it belongs to, of the new range of Opcodes it intends to use.
 */

@protocol ExtensionModelApiDelegate <NSObject>
@optional

/**
 * @brief Response to the request tuningStatsRequest.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param providerCode - Text supplied by OEM for characterisation of intended usage
 * @param proposedOpCode - Proposed OpCode - start of range requested
 * @param reason Code describing reason for rejection
 */
- (void)didGetExtensionConflict:(NSNumber *)deviceId
                   providerCode:(NSString * _Nullable)providerCode
                 proposedOpCode:(NSNumber * _Nullable)proposedOpCode
                         reason:(NSNumber * _Nullable)reason;


/**
 * @brief didGetExtensionRequest - A proposed opcode with range was revceived and no conflict was found with CSRmesh reserved opcodes. The App should check whether there is a conflict and if necessary call the message extensionConflict
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param providerCode - Text supplied by OEM for characterisation of intended usage
 * @param proposedOpCodes - An array of opcodes to be checked by the App.
 */
- (void)didGetExtensionRequest:(NSNumber *)deviceId
                  providerCode:(NSString *)providerCode
               proposedOpCodes:(NSArray *)proposedOpCodes;

/**
 * @brief didGetMessageCustomResponse: A message was received with an opcode that appears in the observed list of opcodes.
 * @param deviceId
 * @param opcode - The opcode on the observation list.
 * @param messageBody - The body part of the message.
 */
- (void)didGetMessageCustomResponse:(NSNumber *)deviceId
                             opcode:(NSNumber * _Nullable)opcode
                        messageBody:(NSData * _Nullable)messageBody;

@end

@interface ExtensionModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet *delegates;

/**
 * @brief extensionRequestWithproviderCode - Make a request into the CSRMesh network to use the given opcode
 * @param providerCode - Text supplied by OEM for characterisation of intended usage
 * @param proposedOpCode - Proposed OpCode in the range 0x00-0x7f and 0x8000-0xffff
 * @param range - range of OpCodes to be allocated from 0 to 0x7f
 * @param failure - NSError object returned upon encountering an error, refer to userinfo dictionary for description of failure
 */
- (void)extensionRequestWithproviderCode:(NSString *)providerCode
                          proposedOpCode:(NSNumber *)proposedOpCode
                                   range:(NSNumber *)range
                                 failure:(void (^)(NSError *error))failure;


/**
 * @brief extensionConflict - Response message to indicate an opcode conflict for an inbound request
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param providerCode - Text supplied by OEM for characterisation of intended usage
 * @param proposedOpCode - Proposed OpCode in the range 0x00-0x7f and 0x8000-0xffff
 * @param reason - Reason for conflict. If bit 7 = 0, bits 0..6 indicate reason, 1 means Conflict. If bit 7 = 1, Bits 0..6 indicate range of alternative opcodes
 * @param failure - NSError object returned upon encountering an error, refer to userinfo dictionary for description of failure
 */
- (void)extensionConflict:(NSNumber *)deviceId
             providerCode:(NSString *)providerCode
           proposedOpCode:(NSNumber *)proposedOpCode
                   reason:(NSNumber *)reason
                  failure:(void (^)(NSError *error))failure;


/**
 * @brief extensionSendMessage: Send an extension message to the given Device/Group with the given opcode and message. The total length of the opcode+message cannot exceed 11 octets. The opcode size is 1 if its value is <= 0x7f or 2 if it is >= 0x8000
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param opcode - Use this opcode for the give message
 * @param message - The message to be sent.
 * @param failure - NSError object returned upon encountering an error, refer to userinfo dictionary for description of failure
 */
- (void)extensionSendMessage:(NSNumber *)deviceId
                      opcode:(NSNumber *)opcode
                     message:(NSData *)message
                     failure:(void (^)(NSError * _Nullable error))failure;

/**
 * @brief registerForResponseOpcode: Register a custom opcode so that packets with that opcode will be passed back to the application.
 * @param reponseOpcode - Over BLE the opode is added to the list of opcodes to be observed. Over REST to receive the packet with the specified opcode a call must be made to opcodeMessage.
 * @param range - range of OpCodes to be allocated from 0 to 0x7f
 * @param failure - NSError object returned upon encountering an error, refer to userinfo dictionary for description of failure
 */
- (void)registerForResponseOpcode:(NSNumber *)reponseOpcode
                            range:(NSNumber *)range
                          failure:(void (^)(NSError *error))failure;


/**
 * @brief opcodeMessage: Retrieve any messages received by the CLOUD bearer that were registered with registerForResponseOpcode. This message is not supported over BLE. If a packet with this opcode is received, the response will be returned as didGetMessageCustomResponse
 * @param reponseOpcode - The opcode to retrieve receive the packet with the specified opcode a call must be made to opcodeMessage.
 * @param replyAfter - Return all responses received after this time. Should be a unix time stamp, seconds since 1 Jan 1970 00:00 (UTC)
 * @param failure - NSError object returned upon encountering an error, refer to userinfo dictionary for description of failure
 */
- (void)opcodeMessage:(NSNumber *)reponseOpcode
           replyAfter:(NSNumber *)replyAfter
              failure:(void (^)(NSError *error))failure;



/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<ExtensionModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<ExtensionModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
