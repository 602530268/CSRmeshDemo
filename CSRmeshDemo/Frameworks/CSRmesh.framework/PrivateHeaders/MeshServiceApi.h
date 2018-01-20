//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//


/*!
 * @header MeshServiceApi Class is a part of the CSRmesh Api and provides a set of Api methods to Initialise the CSRmesh library, Discover and Associate Mesh Devices, Control a mesh Device. The Api also provides support for REST calls and therefore the frameowrk CSRmeshRestClient.framework should be included in the project.
 */

@import Foundation;
@import CoreBluetooth;
#import "CSRmeshApi.h"
#import "CSRMeshRestClient/CSRRestAuthenticationApi.h"
#import "CSRmeshRestClient/CSRRestMeshConfigModelApi.h"

NS_ASSUME_NONNULL_BEGIN

#define CSR_NotifiedValueForCharacteristic  @"CSR_NotifiedValueForCharacteristic"
#define CSR_didUpdateValueForCharacteristic @"CSR_didUpdateValueForCharacteristic"
#define CSR_PERIPHERAL                      @"CSR_PERIPHERAL"

@protocol MeshServiceApiDelegate <NSObject>
@optional
/*!
 * @brief didAssociate delegate. invoked by the CSRmesh library upon successful Association of a device.
 * @param deviceId - The CSRMesh Network ID of this device as an unsigned short
 * @param deviceHash - The hash of the UUID of the device.
 * @param dhmKey - The DHM of the device.
 * @param meshRequestId - The ID returned of the original associateDevice Api call.
 */
- (void)didAssociateDevice:(NSNumber *)deviceId
                deviceHash:(NSData *)deviceHash
                    dhmKey:(NSData *)dhmKey
             meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief isAssociatingDevice delegate. Invoked by the CSRmesh library. Provides an indication of progress.
 * @param deviceHash - The device under Association
 * @param stepsCompleted - The number of steps completed
 * @param totalSteps - The total number of steps
 * @param meshRequestId - The ID returned from the associateDevice Api call.
 * @warning If the stepsCompleted > totalSteps this indicates failed to Associate
 */
- (void)isAssociatingDevice:(NSData *)deviceHash
             stepsCompleted:(NSNumber *)stepsCompleted
                 totalSteps:(NSNumber *)totalSteps
              meshRequestId:(NSNumber *)meshRequestId;

/*!
 * @brief didDiscoverDevice delegate. Invoked by the CSRmesh library.
 * @param uuid - The CBUUID of the Un-Associated Mesh Device
 * @param rssi - The signal strength at the receiver.
 */
- (void)didDiscoverDevice:(CBUUID *)uuid
                     rssi:(NSNumber *)rssi;

/*!
 * @brief setScannerEnabled delegate. Invoked by the CSRmesh library.
 * @param enabled - NSNumber boolValue of the request from the Library to change the state of the Scanner. If this delegate is not implemented then the CSRmesh Library will control the scanner directly. This is conditional on the Application having first made a call to setCentralManager to pass the CBCentralManager handle to the Library.
 */
- (void)setScannerEnabled:(NSNumber *)enabled;

/*!
 * @brief didUpdateAppearance delegate. Invoked by the CSRmesh library.
 * @param deviceHash - NSData. This is the lowest 31-bits of the SHA-256 of the DeviceUUID of New Device.
 * @param appearanceValue - NSNumber. The Appearance field is a 24-bit value that is composed of an “organization” and an “organization appearance”. The following organizations are defined:
 * 0x00 = Bluetooth SIG
 * For the Bluetooth SIG organization, the organization appearance is from the assigned numbers for the Appearance Characteristic Value.
 * @param shortName - NSData. The ShortName field is the first 9-octets of the name of this device. This is set by the manufacturer of the device.
 */
-(void) didUpdateAppearance:(NSData *)deviceHash
            appearanceValue:(NSNumber *)appearanceValue
                  shortName:(NSData *)shortName;

/*!
 * @brief didTimeoutMessage delegate. Invoked by the CSRmesh library to indicate loss of acknowledgement. Each of the acknowledged Api methods when called returns a meshRequestId. The same meshRequestId is used in this callback to indicate a loss of acknowledgement for the given messageId within the given timeout. The timeout can be computed as the (number_of_retries x retry_interval)
 * @param meshRequestId - NSNumber. This is an int32 and is the ID of method call made into the library.
 * @deprecated Replaced with failure code block.
 */
- (void)didTimeoutMessage:(NSNumber *)meshRequestId
__deprecated_msg("use failure block to receive an NSError failure:(void (^)(NSError * _Nullable error))failure");

/*!
 * @brief didNotifyAuthenticationState delegate. Invoked by the CSRmesh library to indicate Gateway authentication state change.
 * @param The status of the authentication request is given by the property csrRestAuthenticationState. The possible values are CSRRestAuthenticationState(CSRRestNotAuthenticated, CSRRestAuthenticated, CSRRestAuthenticationInProgress, CSRRestAuthenticationExpired)
 */
- (void)didNotifyAuthenticationState:(CSRRestAuthenticationState)status;

/*!
 * @brief didRequestKeyIvStatus delegate. Invoked by the CSRmesh library to indicate a device has made a request to check its copy of the Network Key and Metwork IV. The App should either ingnore the request or call the method respondKeyIvStatus.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param signature - (NSData *) signature provided by sender
 */
- (void)didRequestKeyIvStatus:(NSNumber *)deviceId
                    signature:(NSData *)signature;

///*!
// * @brief didRequestNetworkKeyIV delegate. Invoked by the CSRmesh library to indicate a device has made a request to provide  copy of the Network Key and Metwork IV. The App should either ingnore the request or call the method respondKeyIvStatus.
// * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
// * @param signature - (NSData *) signature provided by sender
// * @param keyIV - (NSData *) request description provided by sender
// */
//- (void)didRequestNetworkKeyIV:(NSNumber *)deviceId
//                     signature:(NSData *)signature
//                         keyIV:(NSData *)requestDescription;



/*!
 * @brief didReceiveNetworkSecurityUpdateStatus delegate. Invoked by the CSRmesh library to indicate status of the network security update.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param updateStatus - (CSRNetworkSecurityUpdateStatus) update status after the operation finishes
 * @param meshRequestId - The ID returned of the original updateNetworkSecurity Api call.
 */
- (void)didReceiveNetworkSecurityUpdateStatus:(NSNumber *)deviceId
                                 updateStatus:(CSRNetworkSecurityUpdateStatus)updateStatus
                                meshRequestId:(NSNumber *)meshRequestId;


/*!
 * @brief didGetPublicNetworkkey delegate. The given Public network key was received
 * @param networkKey - The received public networkKey
 */
- (void)didGetPublicNetworkkey:(NSData *)networkKey;


@end


enum {
    NOT_MESH = 0,
    IS_BRIDGE,
    DID_ABSORB_MESSAGE,
    IS_BRIDGE_DISCOVERED_SERVICE
};

/**
 @enum CSRBleListenMode - Bluetooth Low Energy listen modes
 */
typedef NS_ENUM(NSUInteger, CSRBleListenMode) {
    /** Scan & listen */
    CSRBleListenMode_ScanListen = 0,
    /** Scan & notification & listen */
    CSRBleListenMode_ScanNotificationListen,
    /** Notification & listen */
    CSRBleListenMode_NotificationListen
};

@interface MeshServiceApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/// @brief status of REST authentication
@property  CSRRestAuthenticationState csrRestAuthenticationState;

    // Mesh Service Api Method

/*!
 * @brief getDeviceHashFromUuid. Convert the given CBUUID to a deviceHash.
 * @param uuid - The CBUUID of the device
 * @return NSData * - The deviceHash in little endian format.
 * @warning - The uuid is converted to little Endian Format, the device hash is computed and this is also converted to little endian format before it is returned.
 */
- (NSData *)getDeviceHashFromUuid:(CBUUID *)uuid;

/*!
 * @brief getDeviceHash64FromUuid. Convert the given CBUUID to a deviceHash.
 * @param uuid - The CBUUID of the device
 * @return NSData * - The 64-bits of deviceHash in little endian format.
 * @warning - The uuid is converted to little Endian Format, the device hash is computed and this is also converted to little endian format before it is returned.
 */
-(NSData *) getDeviceHash64FromUuid:(CBUUID *)uuid;

/*!
 * @brief getAuthorizationCode. Extract and return the Authorisation code from the given Short Code.
 * @param shortCode - NSString object of the shortcode.
 * @return NSData * - The authorisationCode or nil if the short code was invalid.
 */
- (NSData *)getAuthorizationCode:(NSString *)shortCode;


/*!
 * @brief getDeviceHashFromShortCode. Extract and return the device hash from the given Short Code.
 * @param shortCode - NSString object of the shortcode.
 * @return NSData * - The deviceHash or nil if the short code was invalid.
 */
- (NSData *)getDeviceHashFromShortCode:(NSString *)shortCode;


/*!
 * @brief associateDevice. En-queues the given mesh device for Association. The requets is queued because only one device at a time is allowed to be in the association state. As this is an asynchronous process, the two delegates, isAssociatingDevice and didAssociateDevice are provided for feedback on the Associaiton progress.
 * @param deviceHash - NSData object of the deviceHash.
 * @param authorisationCode - NSData object of the Authorisation code. Note this is optional and must be set to nil if authorisation code is not provided.
 * @param deviceId - The deviceId to be assigned to the Associated device
 * @param success - Block called upon successful execution
 * @param progress - Block called for each step of association that is successfuly completed
 * @param failure - Block called upon error
 * @return meshRequestId - The id of the message.
 */
- (NSNumber *)associateDevice:(NSData *)deviceHash
            authorisationCode:(NSData *)authorisationCode
                     deviceId:(NSNumber *) deviceId
                      success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                  NSData * _Nullable deviceHash,
                                                  NSData * _Nonnull dhmKey,
                                                  NSNumber * _Nullable meshRequestId))success
                     progress:(void (^ _Nullable)(NSData * _Nullable deviceHash,
                                                  NSNumber * _Nullable stepsCompleted,
                                                  NSNumber * _Nullable totalSteps,
                                                  NSNumber * _Nullable meshRequestId))progress
                      failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 * @brief advertiseForAssociation. Allow self to be associated to a configuration device, for example another phone.
 * @param uuid - CBUUID of the phone. set to nil to stop an association that is in progress.
 * @param authorisationCode - NSData object of the Authorisation code. Note this is optional and must be set to nil if authorisation code is not to be used.
 * @param appearance - NSNumber - a 3 byte integer.
 * @param shortName - NSString - an up to 9 character string that will be advertised together with appearance
 * @param success - Block called upon successful execution with parameters, deviceId, deviceHash, networkKey, dhmkey and meshRequestId.
 * @param progress - Block called for each step of association that is successfuly completed with parameters deviceHash, stepsCompleted, totalSteps, meshRequestId.
 * @param failure - Block called upon error with parameter NSError object.
 * @return meshRequestId - The id of the message.
 */
- (NSNumber *)advertiseForAssociation:(CBUUID *)uuid
                    authorisationCode:(NSData *)authorisationCode
                           appearance:(NSNumber *)appearance
                            shortName:(NSString *)shortname
                              success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                          NSData * _Nullable deviceHash,
                                                          NSData * _Nullable networkKey,
                                                          NSData * _Nullable dhmKey,
                                                          NSNumber *_Nullable meshRequestId))success
                             progress:(void (^ _Nullable)(NSData * _Nullable deviceHash,
                                                          NSNumber *_Nullable stepsCompleted,
                                                          NSNumber *_Nullable totalSteps,
                                                          NSNumber *_Nullable meshRequestId))progress
                              failure:(void (^ _Nullable)(NSError *_Nullable error))failure;


/*!
 * @brief stopAdvertisingForAssociation. Stop UUID and Appearance advertisements. Please note, this will automatically occur upon commencing association of the Phone.
 */
-(void) stopAdvertisingForAssociation;



/*!
 * @brief processMeshAdvert. The given CSRmesh advertisment is decrypted and a value is returned that indicates how the CSRmesh Library processed the advert.
 * @param advertisment - (NSDictionary *) object of the advertisment scanned by the CBCentralManager.
 * @param RSSI - (NSNumber *) object of the signal strength.
 * @return (NSNumber *) - A value that can be interpreted as follows :-
 *  0 - Advertisment not related to CSRmesh
 *  1 - This is an advertisment from a Bridge Device
 *  2 - A valid CSRmesh advertisment from a CSRmesh device that was consumed by the CSRmesh Library
 */
- (NSNumber *)processMeshAdvert:(NSDictionary *)advertisment RSSI:(NSNumber * _Nullable)RSSI;


/*!
 * @brief connectBridge. After a connection is made to a Bridge Device, this method should be called so that the CSRmesh Library can use the Bridge to send data over the Mesh network.
 * @param bridge - (CBPeripheral *) The conected peripheral
 * @param bridgeNotification - (NSNumber *) BleListenMode enum (CSR_SCAN_LISTEN_MODE, CSR_SCAN_NOTIFICATION_LISTEN_MODE, CSR_NOTIFICATION_LISTEN_MODE
 */
- (void)connectBridge:(CBPeripheral *)bridge enableBridgeNotification:(NSNumber *)bridgeNotification;

/*!
 * @brief disconnectBridge. Inform the CSRmesh Library that the given bridge was disconnected.
 * @param bridge - (CBPeripheral *) The conected peripheral
 */
 -(void) disconnectBridge:(CBPeripheral *)bridge;


/*!
 * @brief setDeviceDiscoveryFilterEnabled. Commands the CSRmesh Library to inhibit or allow the discovery of new CSRmesh un-associated devices. If allowed, the delegate didDiscoverDevice shall be invoked for each device advertisment received from an unassociated device.
 * @param enabled - (BOOL)
 *  YES = Allow
 *  NO = Inhibit
 * @param uuid - The block to execute when a CSRMeshDevice uuid is received
 * @param appearance - The block to execute when a CSRMeshDevice appearance is received
 */
- (void)setDeviceDiscoveryFilterEnabled:(BOOL)enabled
                                   uuid:(void (^ _Nullable)(CBUUID * _Nullable uuid,
                                                            NSNumber * _Nullable rssi))uuid
                             appearance:(void (^ _Nullable)(NSData * _Nullable deviceHash,
                                                            NSNumber * _Nullable appearanceValue,
                                                            NSData * _Nullable shortName))appearance;


/*!
 * @brief setNetworkPassPhrase. Set the Network key, from the passPhrase, for secure communication with Mesh Devices. The same will be used when associating new mesh devices. The network key for Devices already associated will not be changed.
 * @param passPhrase - (NSString *) The pass phrase that will be used to generate a network key.
 */
- (void)setNetworkPassPhrase:(NSString *)passPhrase;

/*!
 * @brief setNetworkKey. Set the Network key for secure communication with Mesh Devices. The same will be used when associating new mesh devices. The network key for Devices already associated will not be changed.
 * @param networkKey - (NSData *) The network key is the Hash of the passcode
 */
-(void) setNetworkKey:(NSData *)networkKey;

/*!
 * @brief broadcastPublicNetworkKey. Device that is a part of the public network can publish its network ket such that any other device could participate in that network. This message includes the 128-bit NetworkKey used to identify the public network.
 * @param networkKey - (NSData *) The network key is a 16-octet array of bytes.
 */
- (void)broadcastPublicNetworkKey:(NSData *)networkKey;


/*!
 * @brief getMeshId. Returns the MeshId for the PassPhrase most recently set by setNetworkPassPhrase. The MeshID is the HashMac of a secret Key and the PassPhrase
 */
- (NSString *)getMeshId;




/*!
 * @brief setNextDeviceId. Set the deviceId that will be assigned to the next associated device. 
 * @param deviceId - (NSNumber *) Unsigned short value
 * @warning - care should be taken to avoid using the same deviceId for more than one device as this may corrupted messages received from the devices that share the same deviceId
 */
- (void)setNextDeviceId:(NSNumber *)deviceId
__deprecated_msg("setNextDeviceId is deprecated because associateDevice now takes the deviceId as a parameter");


/*!
 * @brief setControllerAddress. Assign the given ID to the host.
 * @param hostId - (NSNumber *) Unsigned short value (0000 - FFFF)
 * @warning - care should be taken to avoid using the same hostId as the DeviceIds or GroupIds.
 */
- (void)setControllerAddress:(NSNumber *)hostId;


/*!
 * @brief getControllerAddress. Retrieves the ID of the host.
 * @return NSNumber of the Host ID
 */
- (NSNumber *)getControllerAddress;


/*!
 * @brief setResendInterval. Set the mesh packet resend interval
 * @param timeInterval - (NSNumber *) int milliseconds (maximum=60000)
 * @warning - The new resend interval will always be set for the next command to be sent. Also as there is no persistence in the CSRmesh library, please set this value on App start up.
 */
- (void)setResendInterval:(NSNumber *)timeInterval;


/*!
 * @brief setRetryCount. mesh packet retry count.
 * @param retryCount - (NSNumber *) int retryCount
 * @warning - The new Retry count will always be set for the Next Command to be sent. Also as there is no persistence in the CSRmesh library, please set this value on App start up.
 */
- (void)setRetryCount:(NSNumber *)retryCount;


/*!
 * @brief setAttentionPreAssociation. Attract attention on/off
 * @param deviceHash - NSData. This is the lowest 31-bits of the SHA-256 of the DeviceUUID of New Device.
 * @param attentionState - NSNumber. This is an NSNumber containing the BOOL value of the desired state. YES=attract Attention
 * @param duration - NSNumber. This is an NSNumber containing the 16-bit duration in milliseconds
 */
- (void)setAttentionPreAssociation:(NSData *)deviceHash
                    attentionState:(NSNumber *)attentionState
                      withDuration:(NSNumber *) duration;


/*!
 * @brief cancelTransaction. Abort an acknowledged mesh request.
 * @param meshRequestId - NSNumber meshReqeustId
 */
- (BOOL)cancelTransaction:(NSNumber * )meshRequestId;


/*!
 * @brief setTTL. The timeto live is set to 255 by default. Use this method to set to another value
 * @param ttl - unsigned char as an NSNumber of the new Time-To-Live vaue
 
 */
- (void)setTTL:(NSNumber *)ttl;

/*!
 * @brief getTTL. returns the timeto live value
 */
- (NSNumber *)getTTL;

/*!
 * @brief setRestBearerEnabled. Set bearer to REST/Cloud. Disables Bluetooth bearer.
 */
- (void)setRestBearerEnabled;

/*!
 * @brief setBluetoothBearerEnabled. Set bearer to Bluetooth. Disables REST/Cloud bearer.
 */
- (void)setBluetoothBearerEnabled;

/*!
 * @brief getActiveBearer. Get the active bearer
 */
- (CSRBearerType)getActiveBearer;

/*!
 * @brief getApplicationCode. Get the application code
 */
- (NSString *)getApplicationCode;


/*!
 * @brief resetDevice. Resets device to un-associated device. If the feature is enabled, then the device will start emitting its UUID and appearance over the CSRmesh network.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param dhmKey - NSData. The lower 6 bytes of the shared secret returned from the device during association.
 * @return NO if unable to contruct payload.
 */
- (BOOL)resetDevice:(NSNumber *)deviceId dhmKey:(NSData *)dhmKey;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<MeshServiceApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<MeshServiceApiDelegate>)delegate;

/*!
*@brief Commence authentication of Gateway. The status of the authentication request is given by the property csrRestAuthenticationState. The possible values are CSRRestAuthenticationState(CSRRestNotAuthenticated, CSRRestAuthenticated, CSRRestAuthenticationInProgress, CSRRestAuthenticationExpired)
*@param uuid The NSString of the device uuid
*@param dhmKey : NSData of the shared secret
 */
-(void)authenticateRest:(NSString *)uuid dhmkey:(NSData *)dhmkey;


/*!
 *@brief set Network IV to the given value.
 *@param iv : NSdata of length 8 bytes
 */
-(void)setNetworkIv:(NSData *)iv;


/*!
 *@brief get Network IV. This is useful as the initial & default value of the NetworkIV is not known to the App
 *@return networkIV : NSdata of length 8 bytes
 */
- (NSData *) getNetworkIv;


/*!
 *@brief Update network security for the given Device.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param dhmKey - (NSData *) The lower 6 bytes of the shared secret returned from the device during association.
 * @param networkPassPhrase - (NSString *) The network pass phrase string that will be used to generate a networkKey.
 * @param networkIv - (NSString *)  NSData of length 8 bytes
// * @param success - Block called upon successful execution.
// * @param failure - Block called upon error
 */
-(NSNumber * _Nonnull)updateNetworkSecurity:(NSNumber *)deviceId
                                     dhmKey:(NSData *)dhmKey
                          networkPassPhrase:(NSString *)networkPassPhrase
                                  networkIv:(NSData *)networkIv
                                    success:(void (^ _Nullable)(NSNumber * deviceId,
                                                                CSRNetworkSecurityUpdateStatus updateStatus,
                                                                NSNumber * meshRequestId))success
                                    failure:(void (^ _Nullable)(NSError * _Nullable error,
                                                                NSNumber * _Nullable meshRequestId))failure;



/*!
 *@brief respondKeyIvStatus - Respond to a device which has requested a check of its Network Key and Network Iv by way of the callback didRequestKeyIvStatus
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param dhmKey - NSData. The lower 6 bytes of the shared secret returned from the device during association.
 * @param signature - (NSData *) signature provided by sender
 */
-(void)respondKeyIvStatus:(NSNumber *)deviceId
                   dhmkey:(NSData *)dhmkey
                signature:(NSData *)signature;



/*!
 *@brief addDeviceToBlacklist - Add the given device to the list of black listed devices. A blacklist device shall be reset when it comes online in the CSRmesh network.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param deviceHash - The 64-bit hash of the UUID of the device.
 * @param dhmkey - NSData. The 24 bytes of the shared secret returned from the device during association.
 * @param validity - NSNumber of the seconds to wait for response from Device, default should be 10
 * @param failure - Block called upon error
 */
-(void)addDeviceToBlacklist:(NSNumber *)deviceId
             withDeviceHash:(NSData * _Nonnull)deviceHash
                  dhmkey:(NSData * _Nullable)dhmkey
                   validity:(NSNumber *)validity
                    failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 *@brief removeDeviceFromBlacklist - Remove the given device to the list of black listed devices. A blacklist device shall be reset when it comes online in the CSRmesh network.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param deviceHash - The 64-bit hash of the UUID of the device.
 * @param dhmkey - NSData. The 24 bytes of the shared secret returned from the device during association.
 * @param validity - NSNumber of the seconds to wait for response from Device, default should be 10
 * @param failure - Block called upon error
 */
-(void)removeDeviceFromBlacklist:(NSNumber * _Nonnull)deviceId
             withDeviceHash:(NSData * _Nonnull)deviceHash
                     dhmkey:(NSData * _Nonnull)dhmkey
                      validity:(NSNumber * _Nonnull)validity
                    failure:(void (^ _Nullable)(NSError * _Nullable error))failure;



/*!
 *@brief blacklistDeviceStateRequest - Request for Blacklisted Status of a Device which was requested to be blacklisted.
 *@param deviceId - (NSNumber *) The CSRMesh Network ID of the device hose Blacklist status need to be retrieved, as an unsigned short.
 * @param success - Block called upon successful response from device
 * @param failure - Block called upon error
 */
-(void)blacklistDeviceStateRequest:(NSNumber * _Nonnull)deviceId
                           success:(void (^ _Nonnull)(CSRRestBlacklistDeviceStateResponseStateEnum status))success
                           failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 *@brief getSequenceNumber - Returns the last sequence number + 1
 * @return uint32_t of the 24-bit sequence number
 */
-(uint32_t) getSequenceNumber;


/*!
 *@brief getSequenceNumber - Returns the last sequence number + 1
 * @param sequenceNumber - The seed for the 24-bit sequence number.
 * @param failure - Block called upon error
 */
-(void) setSequenceNumber:(uint32_t)sequenceNumber
                  failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 * @property centralManager - The id of the CBCentralManager object. This makes it possible for the library to control the state of the Scanner.
 */
@property (nonatomic, strong) CBCentralManager * centralManager;


/*!
 * @property meshID - The HashMac of the PassPhrase. The initial value is @" ". The meshId is re-computed after a call to setNetworkPassPhrase. If a new PassPhrase is set then also send the meshId to the Gateway.
 */
@property (nonatomic, strong) NSString * meshId;

@end

NS_ASSUME_NONNULL_END
