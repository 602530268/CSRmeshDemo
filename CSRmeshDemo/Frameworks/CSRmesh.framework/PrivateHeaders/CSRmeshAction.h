//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

// This file is generated and should not be modified.

@import Foundation;
#import "CSRsensorValue.h"

/**
 @enum CSRBeacon_Type - Beacon type
 */
typedef NS_ENUM (uint32_t, CSRBeacon_Type){
    /** Lumicast */
    Lumicast = 5,
    /** Eddystone URL */
    Eddystone_URL = 2,
    /** Eddystone UID */
    Eddystone_UID = 3,
    /** iBeacon */
    IBeacon = 1,
    /** CSRmesh Beacon */
    CSR = 0,
    /** LTE direct */
    LTE_Direct = 4
};

/**
 @enum CSRBoolean - Boolean values
 */
typedef NS_ENUM (uint32_t, CSRBoolean){
    /** False */
    False = 0,
    /** True */
    True = 1
};

/**
 @enum CSRBearer_Bitfield - Boolean values
 */
typedef NS_ENUM (uint32_t, CSRBearer_Bitfield){
    /** Wifi beacon */
    Wifi_Beacon_Bearer = 32,
    /** Low energy Advertising */
    Le_Advertising = 1,
    /** Low energy Gatt Server */
    Le_Gatt_Server = 2,
    /** UDP IPv6 */
    Udp_Ip_6 = 8,
    /** UDP IPv4 */
    Udp_Ip_4 = 4,
    /** TCP IP */
    Tcp_Ip = 16
};

/**
 @enum CSRDevice_Information - Device information values
 */
typedef NS_ENUM (uint32_t, CSRDevice_Information){
    /** Model high */
    Model_High = 3,
    /** Model low */
    Model_Low = 2,
    /** UUID High */
    UUID_High = 1,
    /** Appearance */
    Appearance = 5,
    /** VID PID version */
    VID_PID_Version = 4,
    /** UUID Low */
    UUID_Low = 0,
    /** Last ETag */
    LastETag = 6
};

/**
 @enum CSRSide_Effect_Bitfield - Side effect bitfield values
 */
typedef NS_ENUM (uint32_t, CSRSide_Effect_Bitfield){
    /** Movement detected */
    Movement = 4,
    /** Light detected */
    Light = 1,
    /** Audio detected */
    Audio = 2,
    /** Stationary detected */
    Stationary = 8,
    /** Human detected */
    Human = 16
};

/**
 @enum CSRPower_State - Power state values
 */
typedef NS_ENUM (uint32_t, CSRPower_State){
    /** Standby state */
    Standby = 2,
    /** Off state */
    Off = 0,
    /** On state */
    On = 1,
    /** On from Standby state */
    OnFromStandby = 3
};

@interface CSRMeshAction:NSObject

@property	NSMutableDictionary * _Nullable parameters;

/*!
* @brief initWithLargeObjectTransferAnnounce: Returns a CSRMeshAction object initialised with initWithLargeObjectTransferAnnounce and the following parameters or nil for errors. A node wanting to provide a large object to neighbouring Mesh Nodes issues an ANNOUNCE with the associated content type. This message will have TTL=0, thus will only be answered by its immediate neighbours. The ANNOUNCE has the total size of the packet to be issued. The format and encoding of the large object is subject to the provided type and is out of scope of this document. The destination ID can either be 0, a group or a specific Device ID. In case the destination ID is not zero, only members of the group (associated with the LOT model) or the device with the specified Device ID responds with the intent to download the object for their own consumption. Every other node either ignores or accepts the offer for the purpose of relaying the packet.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param companyCode: Bluetooth Company Code
* @param typeEncoding: Type description of the intended payload
* @param size: Number of bytes of the intended Large Object
* @param objectVersion: Object Version (e.g. Firmware version x.y.z). A node can use this to decide if it already has this version of the object
* @param targetDestination: Destination of the Large Object
*/
+ (id _Nullable)initWithLargeObjectTransferAnnounce:(NSNumber * _Nonnull)destinationDeviceId companyCode:(NSNumber * _Nonnull)companyCode typeEncoding:(NSNumber * _Nonnull)typeEncoding size:(NSNumber * _Nonnull)size objectVersion:(NSData * _Nonnull)objectVersion targetDestination:(NSNumber * _Nonnull)targetDestination;

/*!
* @brief initWithBeaconGetBeaconStatus: Returns a CSRMeshAction object initialised with initWithBeaconGetBeaconStatus and the following parameters or nil for errors. 
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param beaconType: Enum type = CSRBeacon_Type. 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
*/
+ (id _Nullable)initWithBeaconGetBeaconStatus:(NSNumber * _Nonnull)destinationDeviceId beaconType:(CSRBeacon_Type)beaconType;

/*!
* @brief initWithBeaconGetTypes: Returns a CSRMeshAction object initialised with initWithBeaconGetTypes and the following parameters or nil for errors. sent *to* a beacon to get the types of payload it sends, plus battery state and time since last message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithBeaconGetTypes:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithBeaconSetStatus: Returns a CSRMeshAction object initialised with initWithBeaconSetStatus and the following parameters or nil for errors. 
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param beaconType: Enum type = CSRBeacon_Type. 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
* @param beaconInterval: Time between beacon transmissions in 100ths of seconds (0..100). Setting this to 0 stops that beacon type transmitting.
* @param meshInterval: How many minutes between mesh wakeups (1..N).
* @param meshTime: How long node stays as a mesh node (10s of seconds).
* @param tXPower: -127..+127 dbM.
*/
+ (id _Nullable)initWithBeaconSetStatus:(NSNumber * _Nonnull)destinationDeviceId beaconType:(CSRBeacon_Type)beaconType beaconInterval:(NSNumber * _Nonnull)beaconInterval meshInterval:(NSNumber * _Nonnull)meshInterval meshTime:(NSNumber * _Nonnull)meshTime tXPower:(NSNumber * _Nonnull)tXPower;

/*!
* @brief initWithBeaconGetPayload: Returns a CSRMeshAction object initialised with initWithBeaconGetPayload and the following parameters or nil for errors. Sent to a beacon to retrieve the current payload. One or more 'SET_PAYLOAD' messages will be received in response.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param payloadType: Enum type = CSRBeacon_Type. 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x4=LTE direct, 0x5=Lumicast.
*/
+ (id _Nullable)initWithBeaconGetPayload:(NSNumber * _Nonnull)destinationDeviceId payloadType:(CSRBeacon_Type)payloadType;

/*!
* @brief initWithBeaconPayloadAck: Returns a CSRMeshAction object initialised with initWithBeaconPayloadAck and the following parameters or nil for errors. Sent by a beacon to signal successful or unsuccessful receipt of a new payload
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param payloadType: Enum type = CSRBeacon_Type. 0x00=CSR, 0x01=iBeacon, 0x02=Eddystone URL, 0x03=Eddystone UID, 0x04=LTE direct, 0x05=Lumicast.
* @param ackOrNack: 0 means success, set bits indicate missing packet numbers 1..16.
* @param payloadID: Payload ID which was received, or 0xFFFF if no final packet was received.
*/
+ (id _Nullable)initWithBeaconPayloadAck:(NSNumber * _Nonnull)destinationDeviceId payloadType:(CSRBeacon_Type)payloadType ackOrNack:(NSNumber * _Nonnull)ackOrNack payloadID:(NSNumber * _Nonnull)payloadID;

/*!
* @brief initWithBeaconProxyGetDevices: Returns a CSRMeshAction object initialised with initWithBeaconProxyGetDevices and the following parameters or nil for errors. Sent to a proxy to find the devices it is managing.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithBeaconProxyGetDevices:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithSensorSetState: Returns a CSRMeshAction object initialised with initWithSensorSetState and the following parameters or nil for errors. Setting Sensor State: Upon receiving a SENSOR_SET_STATE message, where the destination address is the device ID of this device and the Type field is a supported sensor type, the device saves the RxDutyCycle field and responds with a SENSOR_STATE message with the current state information of the sensor type. If the Type field is not a supported sensor type, the device ignores the message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param type: Sensor type.The Type field is a 16-bit unsigned integer that determines the sensor type for the associated state.
* @param repeatInterval: How often the sensor value is repeated. The RepeatInterval is an 8-bit unsigned integer representing the interval in seconds between repeated transmissions of sensor values by this device.
*/
+ (id _Nullable)initWithSensorSetState:(NSNumber * _Nonnull)destinationDeviceId type:(CSRsensorType)type repeatInterval:(NSNumber * _Nonnull)repeatInterval;

/*!
* @brief initWithSensorGetTypes: Returns a CSRMeshAction object initialised with initWithSensorGetTypes and the following parameters or nil for errors. Upon receiving a SENSOR_GET_TYPES message, the device responds with a SENSOR_TYPES message with the list of supported types greater than or equal to the FirstType field. If the device does not support any types greater than or equal to the FirstType field, then it sends a SENSOR_TYPES message with zero-length Types field.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param firstType: The FirstType field is a 16-bit unsigned integer that determines the first Type that can be returned in the corresponding SENSOR_TYPES message.
*/
+ (id _Nullable)initWithSensorGetTypes:(NSNumber * _Nonnull)destinationDeviceId firstType:(CSRsensorType)firstType;

/*!
* @brief initWithSensorWriteValue: Returns a CSRMeshAction object initialised with initWithSensorWriteValue and the following parameters or nil for errors. Writing Sensor Value: Upon receiving a SENSOR_WRITE_VALUE message, where the Type field is a supported sensor type, the device saves the value into the current value of the sensor type on this device and responds with a SENSOR_VALUE message with the current value of this sensor type.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param value: Sensor Value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type field.
* @param value1: Sensor Value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type field.
* @param acknowledge: =YES means message will be acknowledged
*/
+ (id _Nullable)initWithSensorWriteValue:(NSNumber * _Nonnull)destinationDeviceId value:(CSRsensorValue * _Nonnull)value value1:(CSRsensorValue * _Nullable)value1 acknowledge:(BOOL)acknowledge;

/*!
* @brief initWithSensorGetState: Returns a CSRMeshAction object initialised with initWithSensorGetState and the following parameters or nil for errors. Getting Sensor State: Upon receiving a SENSOR_GET_STATE message, where the destination address is the deviceID of this device and the Type field is a supported sensor type, the device shall respond with a SENSOR_STATE message with the current state information of the sensor type. Upon receiving a SENSOR_GET_STATE message, where the destination address is the device ID of this device but the Type field is not a supported sensor type, the device shall ignore the message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param type: Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor types being configured.
*/
+ (id _Nullable)initWithSensorGetState:(NSNumber * _Nonnull)destinationDeviceId type:(CSRsensorType)type;

/*!
* @brief initWithSensorReadValue: Returns a CSRMeshAction object initialised with initWithSensorReadValue and the following parameters or nil for errors. Getting Sensor Value: Upon receiving a SENSOR_READ_VALUE message, where the Type field is a supported sensor type, the device responds with a SENSOR_VALUE message with the value of the sensor type. Proxy Behaviour: Upon receiving a SENSOR_GET_STATE where the destination of the message and the sensor type correspond to a previously received SENSOR_BROADCAST_VALUE or SENSOR_BROADCAST_NEW message, the device responds with a SENSOR_VALUE message with the remembered values.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param type: Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type being read.
* @param type2: Sensor type. The Type field is a 16-bit unsigned integer that determines the second sensor type being read. This field is optional.
*/
+ (id _Nullable)initWithSensorReadValue:(NSNumber * _Nonnull)destinationDeviceId type:(CSRsensorType)type type2:(CSRsensorType)type2;

/*!
* @brief initWithActuatorGetTypes: Returns a CSRMeshAction object initialised with initWithActuatorGetTypes and the following parameters or nil for errors. Upon receiving an ACTUATOR_GET_TYPES message, the device responds with an ACTUATOR_TYPES message with a list of supported types greater than or equal to the FirstType field. If the device does not support any types greater than or equal to FirstType, it sends an ACTUATOR_TYPES message with a zero length Types field.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param firstType: First type to fetch. The FirstType field is a 16-bit unsigned integer that determines the first Type that can be returned in the corresponding ACTUATOR_TYPES message.
*/
+ (id _Nullable)initWithActuatorGetTypes:(NSNumber * _Nonnull)destinationDeviceId firstType:(CSRsensorType)firstType;

/*!
* @brief initWithActuatorGetValueAck: Returns a CSRMeshAction object initialised with initWithActuatorGetValueAck and the following parameters or nil for errors. Get Current sensor state
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param type: Actuator type. The Type field is a 16-bit value that determines the actuator type.
*/
+ (id _Nullable)initWithActuatorGetValueAck:(NSNumber * _Nonnull)destinationDeviceId type:(CSRsensorType)type;

/*!
* @brief initWithActuatorSetValue: Returns a CSRMeshAction object initialised with initWithActuatorSetValue and the following parameters or nil for errors. Get sensor state. Upon receiving an ACTUATOR_SET_VALUE_NO_ACK message, where the destination address is the device ID of this device and the Type field is a supported actuator type, the device shall immediately use the Value field for the given Type field. The meaning of this actuator value is not defined in this specification. Upon receiving an ACTUATOR_SET_VALUE_NO_ACK message, where the destination address is is the device ID of this device but the Type field is not a supported actuator type, the device shall ignore the message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param value: Actuator value. The Value field is the value that the actuator type.
* @param acknowledge: =YES means message will be acknowledged
*/
+ (id _Nullable)initWithActuatorSetValue:(NSNumber * _Nonnull)destinationDeviceId value:(CSRsensorValue * _Nonnull)value acknowledge:(BOOL)acknowledge;

/*!
* @brief initWithDataBlockSend: Returns a CSRMeshAction object initialised with initWithDataBlockSend and the following parameters or nil for errors. A block of data, no acknowledgement. Upon receiving a DATA_BLOCK_SEND message, the device passes the DatagramOctets field up to the application for processing.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param datagramOctets: Datagram of octets
*/
+ (id _Nullable)initWithDataBlockSend:(NSNumber * _Nonnull)destinationDeviceId datagramOctets:(NSData * _Nonnull)datagramOctets;

/*!
* @brief initWithPingRequest: Returns a CSRMeshAction object initialised with initWithPingRequest and the following parameters or nil for errors. Ping Request: Upon receiving a PING_REQUEST message, the device responds with a PING_RESPONSE message with the TTLAtRx field set to the TTL value from the PING_REQUEST message, and the RSSIAtRx field set to the RSSI value of the PING_REQUEST message. If the bearer used to receive the PING_REQUEST message does not have an RSSI value, then the value 0x00 is used.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param arbitraryData: Arbitrary data
* @param rspTTL: Response packet time to live
*/
+ (id _Nullable)initWithPingRequest:(NSNumber * _Nonnull)destinationDeviceId arbitraryData:(NSData * _Nonnull)arbitraryData rspTTL:(NSNumber * _Nonnull)rspTTL;

/*!
* @brief initWithTuningSetConfig: Returns a CSRMeshAction object initialised with initWithTuningSetConfig and the following parameters or nil for errors. Setting (or reading) tuning config: Omitted or zero fields mean do not change. This message enforces the state of the recipient. The state is  defined by two goals, normal and high traffic, and their associated number of neighbour to decide which cases to follow. Goals are expressed with unit-less values ranging from 0 to 255. These goals relate to metrics calculated on the basis of density computed at the node and across the network. The expectation is for these goals to be maintained through modification of the receive duty cycle. The average of number of neighbours for high and normal traffic is expressed as a ratio, both numbers sharing the same denominator and each representing their respective numerators. The duty cycle encoding follows the same rules as per duty cycle encoding encountered in PROBE message. This message comes in two formats. A fully truncated form containing only the OpCode (thus of length 2) is used to indicate a request for information. This message should be answered by the appropriate ACK_CONFIG. Further interpretations of this message are: 1. Missing ACK field implies that a request for ACK_CONFIG is made. Thus, this is a special case of the fully truncated mode. However, the provided fields are meant to be used in the setting of goals. 2. Individual fields with zero value are meant NOT to be changed in the received element. Same as for missing fields in truncated messages. Furthermore, in order to improve testing, a combination of values for main and high goals are conventionally expected to be used for defining two behaviours: 1. Suspended: Tuning Probe messages (TTL=0) should be sent and statistics maintained, but the duty cycle should not be changed - thus goals will never be achieved. The encoding are: Main Goal = 0x00 and High Goal = 0xFE. 2. Disable: No Tuning Probe message should be sent and statistics should not be gathered - averaged values should decay. The encoding are: Main Goal = 0x00 and High Goal = 0xFF.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param numeratorHighTrafficNeighRatio: Default is 14. See tuning doc for explanation
* @param numeratorNormalTrafficNeighRatio: Default is 12. See tuning doc for explanation
* @param denominatorTrafficNeighRatio: Default is 10. See tuning doc for explanation
* @param normalGoalValue: Default is 60. Set to 0 to disable/suspend tuning
* @param highGoalValue: Default is 75. Set to 254 to suspend, 255 to disable tuning
* @param currentScanDutyCycle: Duty cycle 1..100% or 101..255 (x-100) per mille
* @param ackRequest: Enum type = CSRBoolean. Whether ack required
*/
+ (id _Nullable)initWithTuningSetConfig:(NSNumber * _Nonnull)destinationDeviceId numeratorHighTrafficNeighRatio:(NSNumber * _Nonnull)numeratorHighTrafficNeighRatio numeratorNormalTrafficNeighRatio:(NSNumber * _Nonnull)numeratorNormalTrafficNeighRatio denominatorTrafficNeighRatio:(NSNumber * _Nonnull)denominatorTrafficNeighRatio normalGoalValue:(NSNumber * _Nonnull)normalGoalValue highGoalValue:(NSNumber * _Nonnull)highGoalValue currentScanDutyCycle:(NSNumber * _Nonnull)currentScanDutyCycle ackRequest:(CSRBoolean)ackRequest;

/*!
* @brief initWithTuningGetStats: Returns a CSRMeshAction object initialised with initWithTuningGetStats and the following parameters or nil for errors. Getting Tuning Stats: These messages are aimed at collecting statistics from specific nodes. This message allows for the request of all information or for some of its parts. Responses are multi-parts, each identified with an index (combining a continuation flag - top bit). MissingReplyParts for the required field serves at determining the specific responses one would like to collect. If instead all the information is requested, setting this field to zero will inform the destination device to send all messages. Importantly, response (STATS_RESPONSE) messages will not necessarily come back in order, or all reach the requestor. It is essential to handle these cases in the treatment of the collected responses.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param missingReplyParts: Bitset of missing reply parts (0 means send all)
*/
+ (id _Nullable)initWithTuningGetStats:(NSNumber * _Nonnull)destinationDeviceId missingReplyParts:(NSNumber * _Nonnull)missingReplyParts;

/*!
* @brief initWithTuningProbe: Returns a CSRMeshAction object initialised with initWithTuningProbe and the following parameters or nil for errors. Tuning Probe: The Tuning Probe message is sent to discover neighbours. This messages is issued by devices wanting to determine their density metrics.<br> The message is sent in two forms. A short form omitting both ScanDutyCycle and BatteryState with a TTL=0. This allows immediate neighbours to perform various calculations and in turn provide their own PROBE messages. The long version is only provided with TTL>0. This cannot be used for immediate neighbour density determination, but can be used to determine the overall network density. The ability to identify if a node is a potential pinch-point in the Mesh network can be achieved through the comparison of immediate and average number of neighbours within the network. The usage of the PROBE message with TTL=0 or TTL>0 is a way to perform these computations.  It is worth noting that the periodicity of these two types of messages are different; messages with TTL>0 is much more infrequent than messages with TTL=0. Furthermore, it is wise not to use messages for TTL>0 and embedded values in the determination of the average values. The AverageNumNeighbour field is fixed point 6.2 format encoded. The ScanDutyCycle is expressing percentage for numbers from 1 to 100 and (x-100)/10 percentage for numbers from 101 to 255.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param transmissionRateAndTxPower: Transmission rate (seconds, low 10 bits), Tx power, dbM (high 6 bits)
* @param numAudibleNeighbours: Number of audible neighbours
* @param averageNumNeighbours: Average number of neighbours seen, 6.2 fixed point format
* @param scanDutyCycle: Duty cycle 1..100% or 101..255 (x-100) per mille
* @param batteryState: Battery state 0..100%
*/
+ (id _Nullable)initWithTuningProbe:(NSNumber * _Nonnull)destinationDeviceId transmissionRateAndTxPower:(NSNumber * _Nonnull)transmissionRateAndTxPower numAudibleNeighbours:(NSNumber * _Nonnull)numAudibleNeighbours averageNumNeighbours:(NSNumber * _Nonnull)averageNumNeighbours scanDutyCycle:(NSNumber * _Nonnull)scanDutyCycle batteryState:(NSNumber * _Nonnull)batteryState;

/*!
* @brief initWithExtensionRequest: Returns a CSRMeshAction object initialised with initWithExtensionRequest and the following parameters or nil for errors. Request for Extension OpCode to be approved by the whole Mesh. A device wanting to use an OpCode, makes a request to the entire Mesh Network. This message is issued to target identity 0. The device waits some time, proportional to the size of the Mesh network and only after this period, messages using these proposed OpCode are used. Device receiving this message and wanting to oppose the usage of such code will respond to the source node with a CONFLICT. In case no conflict is known and the OpCode is for a message the node is interested in implementing (through comparison with hash value), a record of the OpCode and its mapping is kept.  Request messages are relayed in cases of absence of conflict. The hash function is SHA-256, padded as per SHA-256 specifications2, for which the least significant 6 bytes will be used in the message. The range parameter indicates the maximum number of OpCode reserved from the based provided in the Proposed OpCode field. The last OpCode reserved is determined through the sum of the Proposed OpCode with the range value. This range parameter varies from 0 to 127, leaving the top bit free.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param extensionHash: 48bits Hash (SHA-256) of Text supplied by OEM for characterisation of intended usage
* @param proposedOpCode: Proposed OpCode - start of range requested
* @param range: Number of OpCode to be allocated, starting from ProposedOpCode
*/
+ (id _Nullable)initWithExtensionRequest:(NSNumber * _Nonnull)destinationDeviceId extensionHash:(NSData * _Nonnull)extensionHash proposedOpCode:(NSNumber * _Nonnull)proposedOpCode range:(NSNumber * _Nonnull)range;

/*!
* @brief initWithTimeSetState: Returns a CSRMeshAction object initialised with initWithTimeSetState and the following parameters or nil for errors. Setting Time Broadcast Interval: Upon receiving a TIME_SET_STATE message, the device saves the TimeInterval field into the appropriate state value. It then responds with a TIME_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param interval: Interval between time broadcasts
*/
+ (id _Nullable)initWithTimeSetState:(NSNumber * _Nonnull)destinationDeviceId interval:(NSNumber * _Nonnull)interval;

/*!
* @brief initWithTimeGetState: Returns a CSRMeshAction object initialised with initWithTimeGetState and the following parameters or nil for errors. Getting Time Broadcast Interval: Upon receiving a TIME_GET_STATE message, the device responds with a TIME_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithTimeGetState:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithAttentionSetState: Returns a CSRMeshAction object initialised with initWithAttentionSetState and the following parameters or nil for errors. Setting Flashing State: Upon receiving an ATTENTION_SET_STATE message, the device saves the AttractAttention and AttentionDuration fields into the appropriate state value. It then responds with an ATTENTION_STATE message with the current state information. If the AttractAttention field is set to 0x01 and the AttentionDuration is not 0xFFFF, then any existing attention timer is cancelled and a new attention timer is started that will expire after AttentionDuration milliseconds. If the AttractAttention field is set to 0x01 and the AttentionDuration field is 0xFFFF, then the attention timer is ignored. If the AttractAttention field is set to 0x00, then the attention timer is cancelled if it is already running.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param attractAttention: Enum type = CSRBoolean. Attract attention
* @param duration: Duration for attracting attention
*/
+ (id _Nullable)initWithAttentionSetState:(NSNumber * _Nonnull)destinationDeviceId attractAttention:(CSRBoolean)attractAttention duration:(NSNumber * _Nonnull)duration;

/*!
* @brief initWithBearerSetState: Returns a CSRMeshAction object initialised with initWithBearerSetState and the following parameters or nil for errors. Setting Bearer State: Upon receiving a BEARER_SET_STATE message, where the destination address is the device ID of this device, the device saves the BearerRelayActive, BearerEnabled, and BearerPromiscuous fields into the appropriate state value. Then the device responds with a BEARER_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param bearerRelayActive: Enum type = CSRBearer_Bitfield. Multiple values can be set using OR | . Bit field of active relay bearers that are used to relay messages to.
* @param bearerEnabled: Enum type = CSRBearer_Bitfield. Multiple values can be set using OR | . Bit field of enabled bearers.
* @param bearerPromiscuous: Enum type = CSRBearer_Bitfield. Multiple values can be set using OR | . Relay all messages, regardless of MAC
*/
+ (id _Nullable)initWithBearerSetState:(NSNumber * _Nonnull)destinationDeviceId bearerRelayActive:(CSRBearer_Bitfield)bearerRelayActive bearerEnabled:(CSRBearer_Bitfield)bearerEnabled bearerPromiscuous:(CSRBearer_Bitfield)bearerPromiscuous;

/*!
* @brief initWithBearerGetState: Returns a CSRMeshAction object initialised with initWithBearerGetState and the following parameters or nil for errors. Getting Bearer State: Upon receiving a BEARER_GET_STATE message, where the destination address is the device ID of this device, the device responds with a BEARER_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithBearerGetState:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithGroupGetNumberOfModelGroupids: Returns a CSRMeshAction object initialised with initWithGroupGetNumberOfModelGroupids and the following parameters or nil for errors. Getting Number of Group IDs: Upon receiving a GROUP_GET_NUMBER_OF_MODEL_GROUPS message, where the destination address is the DeviceID of this device, the device responds with a GROUP_NUMBER_OF_MODEL_GROUPS message with the number of Group IDs that the given model supports on this device.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param model: Model number
*/
+ (id _Nullable)initWithGroupGetNumberOfModelGroupids:(NSNumber * _Nonnull)destinationDeviceId model:(NSNumber * _Nonnull)model;

/*!
* @brief initWithGroupSetModelGroupid: Returns a CSRMeshAction object initialised with initWithGroupSetModelGroupid and the following parameters or nil for errors. Setting Model Group ID: Upon receiving a GROUP_SET_MODEL_GROUPID message, where the destination address is the DeviceID of this device, the device saves the Instance and GroupID fields into the appropriate state value determined by the Model and GroupIndex fields. It then responds with a GROUP_MODEL_GROUPID message with the current state information held for the given model and the GroupIndex values.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param model: Model number
* @param groupIndex: Index of the group
* @param instance: Instance of the group
* @param groupID: Group identifier
*/
+ (id _Nullable)initWithGroupSetModelGroupid:(NSNumber * _Nonnull)destinationDeviceId model:(NSNumber * _Nonnull)model groupIndex:(NSNumber * _Nonnull)groupIndex instance:(NSNumber * _Nonnull)instance groupID:(NSNumber * _Nonnull)groupID;

/*!
* @brief initWithGroupGetModelGroupid: Returns a CSRMeshAction object initialised with initWithGroupGetModelGroupid and the following parameters or nil for errors. Getting Model Group ID: Upon receiving a GROUP_GET_MODEL_GROUPID message, where the destination address is the DeviceID of this device, the device responds with a GROUP_MODEL_GROUPID message with the current state information held for the given Model and GroupIndex values.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param model: Model number
* @param groupIndex: Index of the group
*/
+ (id _Nullable)initWithGroupGetModelGroupid:(NSNumber * _Nonnull)destinationDeviceId model:(NSNumber * _Nonnull)model groupIndex:(NSNumber * _Nonnull)groupIndex;

/*!
* @brief initWithBatteryGetState: Returns a CSRMeshAction object initialised with initWithBatteryGetState and the following parameters or nil for errors. Getting Battery State: Upon receiving a BATTERY_GET_STATE message, the device responds with a BATTERY_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithBatteryGetState:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithWatchdogMessage: Returns a CSRMeshAction object initialised with initWithWatchdogMessage and the following parameters or nil for errors. Upon receiving a WATCHDOG_MESSAGE message, if the RspSize field is set to a non-zero value, then the device shall respond with a WATCHDOG_MESSAGE with the RspSize field set to zero, and RspSize -1 octets of additional RandomData.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param rspSize: Size of any expected response
* @param randomData: Random data from a device: Because the RandomData field is encrypted, a passive eavesdropper will not be able to determine the contents of this message, compared with any other message. However, it is still good practice to use random contents in this field. Note: All messages are encrypted and the sequence number is unique even if the RandomData field is a constant value, so the transmitted data are different in each message. However, knowledge of this constant value will enable a possible known plain text attack, so the use of a constant value for the RandomData field is not recommended.
*/
+ (id _Nullable)initWithWatchdogMessage:(NSNumber * _Nonnull)destinationDeviceId rspSize:(NSNumber * _Nonnull)rspSize randomData:(NSData * _Nonnull)randomData;

/*!
* @brief initWithWatchdogSetInterval: Returns a CSRMeshAction object initialised with initWithWatchdogSetInterval and the following parameters or nil for errors. Upon receiving a WATCHDOG_SET_INTERVAL message, the device shall save the Interval and ActiveAfterTime fields into the Interval and ActiveAfterTime variables and respond with a WATCHDOG_INTERVAL message with the current variable values.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param interval: The watchdog Interval being set in seconds and indicates the maximum interval that watchdog messages should be sent.
* @param activeAfterTime: The watchdog ActiveAfterTime being set in seconds that indicates the period of time that a device will listen for responses after sending a watchdog message.
*/
+ (id _Nullable)initWithWatchdogSetInterval:(NSNumber * _Nonnull)destinationDeviceId interval:(NSNumber * _Nonnull)interval activeAfterTime:(NSNumber * _Nonnull)activeAfterTime;

/*!
* @brief initWithConfigGetMessageParams: Returns a CSRMeshAction object initialised with initWithConfigGetMessageParams and the following parameters or nil for errors. 
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithConfigGetMessageParams:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithConfigSetDeviceIdentifier: Returns a CSRMeshAction object initialised with initWithConfigSetDeviceIdentifier and the following parameters or nil for errors. When the device with a DeviceID of 0x0000 receives a CONFIG_SET_DEVICE_IDENTIFIER message and the DeviceHash of the message matches the DeviceHash of this device, the DeviceID of this device is set to the DeviceID field of this message. Then the device responds with the DEVICE_CONFIG_IDENTIFIER message using the new DeviceID as the source address. Note: This function is not necessary in normal operation of a CSRmesh network as DeviceID is distributed as part of the MASP protocol in the MASP_ID_DISTRIBUTION message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param deviceHash: The DeviceHash for the device that will have a new DeviceID.
* @param deviceID: The new DeviceID for the device identified by DeviceHash.
*/
+ (id _Nullable)initWithConfigSetDeviceIdentifier:(NSNumber * _Nonnull)destinationDeviceId deviceHash:(NSData * _Nonnull)deviceHash deviceID:(NSNumber * _Nonnull)deviceID;

/*!
* @brief initWithConfigDiscoverDevice: Returns a CSRMeshAction object initialised with initWithConfigDiscoverDevice and the following parameters or nil for errors. Upon receiving a CONFIG_DISCOVER_DEVICE message directed at the 0x0000 group identifier or to DeviceID of this device, the device responds with a CONFIG_DEVICE_IDENTIFIER message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithConfigDiscoverDevice:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithConfigSetParameters: Returns a CSRMeshAction object initialised with initWithConfigSetParameters and the following parameters or nil for errors. Upon receiving a CONFIG_SET_PARAMETERS message, where the destination address is the DeviceID of this device, the device saves the TxInterval, TxDuration, RxDutyCycle, TxPower and TTL fields into the TransmitInterval, TransmitDuration, ReceiverDutyCycle, TransmitPower and DefaultTimeToLive state respectively. Then the device responds with a CONFIG_PARAMETERS message with the current configuration model state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param txInterval: The transmit interval for this device. The TxInterval field is a 16-bit unsigned integer in milliseconds that determines the interval between transmitting messages.
* @param txDuration: How long a single transmission should occur for. The TxDuration, or transmit duration field is a 16-bit unsigned integer in milliseconds that determines the duration of transmission for a single message.
* @param rxDutyCycle: How much time this device listens for messages. The RxDutyCycle, or receiver duty cycle field is an 8-bit unsigned integer in 1/255ths of a second that determines how often the device listens for CSRmesh messages. Note: The value 0x00 implies that the device does not listen for messages. The value 0xFF implies that the device continuously listens for messages.
* @param txPower: How loud the device transmits messages. The TxPower, or transmit power field is an 8-bit signed integer in decibels that determines the radio transmit power for a device.
* @param timeToLive: The initial default time to live for messages. The TimeToLive field is an 8-bit unsigned integer that determines the default value for the TTL packet field in an MTL packet.
*/
+ (id _Nullable)initWithConfigSetParameters:(NSNumber * _Nonnull)destinationDeviceId txInterval:(NSNumber * _Nonnull)txInterval txDuration:(NSNumber * _Nonnull)txDuration rxDutyCycle:(NSNumber * _Nonnull)rxDutyCycle txPower:(NSNumber * _Nonnull)txPower timeToLive:(NSNumber * _Nonnull)timeToLive;

/*!
* @brief initWithConfigLastSequenceNumber: Returns a CSRMeshAction object initialised with initWithConfigLastSequenceNumber and the following parameters or nil for errors. Upon receiving a CONFIG_LAST_SEQUENCE_NUMBER message from a trusted device, the local device updates the SequenceNumber to at least one higher than the LastSequenceNumber in the message. Note: A trusted device means a device that is not only on the same CSRmesh network, having the same network key, but also interacted with in the past. This message is most useful to check if a device has been reset, for example when the batteries of the device are changed, but it does not remember its last sequence number in non-volatile memory.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param lastSequenceNumber: The last sequence number seen by the source device from the destination device.
*/
+ (id _Nullable)initWithConfigLastSequenceNumber:(NSNumber * _Nonnull)destinationDeviceId lastSequenceNumber:(NSData * _Nonnull)lastSequenceNumber;

/*!
* @brief initWithConfigGetInfo: Returns a CSRMeshAction object initialised with initWithConfigGetInfo and the following parameters or nil for errors. Upon receiving a CONFIG_GET_INFO message, directed at the DeviceID of this device, the device responds with a CONFIG_INFO message. The Info field of the CONFIG_GET_INFO message determines the information to be included in the CONFIG_INFO message. The following information values are defined: DeviceUUIDLow (0x00) contains the least significant eight octets of the DeviceUUID state value. DeviceUUIDHigh (0x01) contains the most significant eight octets of the DeviceUUID state value. ModelsLow (0x02) contains the least significant eight octets of the ModelsSupported state value. ModelsHigh (0x03) contains the most significant eight octets of the ModelsSupported state value.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param info: Enum type = CSRDevice_Information. The type of information being requested. The Info field is an 8-bit unsigned integer that enumerates the information being requested. The following values are defined: 0x00 = UUID Low, 0x01 UUID High, 0x02 = Model Low, 0x03 = Model High, 0x04 = VID_PID_Version, 0x05 = Appearance, 0x06 = LastETag, 0x07 = Conformance, 0x08 = Stack Version.
*/
+ (id _Nullable)initWithConfigGetInfo:(NSNumber * _Nonnull)destinationDeviceId info:(CSRDevice_Information)info;

/*!
* @brief initWithConfigSetMessageParams: Returns a CSRMeshAction object initialised with initWithConfigSetMessageParams and the following parameters or nil for errors. 
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param txQueueSize: Max number of messages in transmit queue.
* @param relayRepeatCount: Number of times to transmit a relayed message.
* @param deviceRepeatCount: Number of times to transmit a message from this device.
*/
+ (id _Nullable)initWithConfigSetMessageParams:(NSNumber * _Nonnull)destinationDeviceId txQueueSize:(NSNumber * _Nonnull)txQueueSize relayRepeatCount:(NSNumber * _Nonnull)relayRepeatCount deviceRepeatCount:(NSNumber * _Nonnull)deviceRepeatCount;

/*!
* @brief initWithConfigResetDevice: Returns a CSRMeshAction object initialised with initWithConfigResetDevice and the following parameters or nil for errors. Upon receiving a CONFIG_RESET_DEVICE message from a trusted device directed at only this device, the local device sets the DeviceID to zero, and forgets all network keys, associated NetworkIVs and other configuration information. The device may act as if it is not associated and use MASP to re-associate with a network. Note: If the CONFIG_RESET_DEVICE message is received on any other destination address than the DeviceID of the local device, it is ignored. This is typically used when selling a device, to remove the device from the network of the seller so that the purchaser can associate the device with their network.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param signature: 8 lowest bytes of HMAC(DHM_KEY,DeviceHash).
*/
+ (id _Nullable)initWithConfigResetDevice:(NSNumber * _Nonnull)destinationDeviceId signature:(NSData * _Nonnull)signature;

/*!
* @brief initWithConfigGetParameters: Returns a CSRMeshAction object initialised with initWithConfigGetParameters and the following parameters or nil for errors. Upon receiving a CONFIG_GET_PARAMETERS message, where the destination address is the DeviceID of this device, the device will respond with a CONFIG_PARAMETERS message with the current config model state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithConfigGetParameters:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithAssetSetState: Returns a CSRMeshAction object initialised with initWithAssetSetState and the following parameters or nil for errors. Setting Asset State: Upon receiving an ASSET_SET_STATE message, the device saves the Interval, SideEffects, ToDestination, TxPower, Number of Announcements and AnnounceInterval  fields into the appropriate state values. It then responds with an ASSET_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param interval: Interval between asset broadcasts
* @param sideEffects: Enum type = CSRSide_Effect_Bitfield. Multiple values can be set using OR | . Side effects for this asset
* @param toDestinationID: Asset announce destination
* @param txPower: Asset TxPower
* @param numAnnounces: Number of times to send announce
* @param announceInterval: Time between announce repeats
*/
+ (id _Nullable)initWithAssetSetState:(NSNumber * _Nonnull)destinationDeviceId interval:(NSNumber * _Nonnull)interval sideEffects:(CSRSide_Effect_Bitfield)sideEffects toDestinationID:(NSNumber * _Nonnull)toDestinationID txPower:(NSNumber * _Nonnull)txPower numAnnounces:(NSNumber * _Nonnull)numAnnounces announceInterval:(NSNumber * _Nonnull)announceInterval;

/*!
* @brief initWithAssetGetState: Returns a CSRMeshAction object initialised with initWithAssetGetState and the following parameters or nil for errors. Getting Asset State: Upon receiving an ASSET_GET_STATE message, the device responds with an ASSET_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithAssetGetState:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithPowerToggleState: Returns a CSRMeshAction object initialised with initWithPowerToggleState and the following parameters or nil for errors. Toggling Power State: Upon receiving a POWER_Toggle_STATE_NO_ACK message, the device sets the PowerState state value as defined: 1.If the current PowerState is 0x00, Off, then PowerState should be set to 0x01, On. 2.If the current PowerState is 0x01, On, then PowerState should be set to 0x00, Off. 3.If the current PowerState is 0x02, Standby, then PowerState should be set to 0x03, OnFromStandby. 4.If the current PowerState is 0x03, OnFromStandby, then PowerState should be set to 0x02, Standby. Then the device responds with a POWER_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param acknowledge: =YES means message will be acknowledged
*/
+ (id _Nullable)initWithPowerToggleState:(NSNumber * _Nonnull)destinationDeviceId acknowledge:(BOOL)acknowledge;

/*!
* @brief initWithPowerSetState: Returns a CSRMeshAction object initialised with initWithPowerSetState and the following parameters or nil for errors. Setting Power State: Upon receiving a POWER_SET_STATE_NO_ACK message, the device sets the PowerState state value to the PowerState field. It then responds with a POWER_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param state: Enum type = CSRPower_State. State to set
* @param acknowledge: =YES means message will be acknowledged
*/
+ (id _Nullable)initWithPowerSetState:(NSNumber * _Nonnull)destinationDeviceId state:(CSRPower_State)state acknowledge:(BOOL)acknowledge;

/*!
* @brief initWithPowerGetState: Returns a CSRMeshAction object initialised with initWithPowerGetState and the following parameters or nil for errors. Getting Power State: Upon receiving a POWER_GET_STATE message, the device responds with a POWER_STATE message with the current state information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithPowerGetState:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithFirmwareGetVersion: Returns a CSRMeshAction object initialised with initWithFirmwareGetVersion and the following parameters or nil for errors. Get firmwre verison: Upon receiving a FIRMWARE_GET_VERSION the device reponds with a FIRMWARE_VERSION message containing the current firmware version
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithFirmwareGetVersion:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithFirmwareUpdateRequired: Returns a CSRMeshAction object initialised with initWithFirmwareUpdateRequired and the following parameters or nil for errors. Requesting a firmware update. Upon receiving this message, the device moves to a state where it is ready for receiving a firmware update
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithFirmwareUpdateRequired:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithTrackerFind: Returns a CSRMeshAction object initialised with initWithTrackerFind and the following parameters or nil for errors. Finding an Asset:  Upon receiving a TRACKER_FIND message, the server checks its tracker cache to see if it has received an ASSET_ANNOUNCE message recently that has the same DeviceID. If it finds one, it will send a TRACKER_FOUND message with the cached information.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param deviceID: Device ID for this asset
*/
+ (id _Nullable)initWithTrackerFind:(NSNumber * _Nonnull)destinationDeviceId deviceID:(NSNumber * _Nonnull)deviceID;

/*!
* @brief initWithTrackerSetProximityConfig: Returns a CSRMeshAction object initialised with initWithTrackerSetProximityConfig and the following parameters or nil for errors. Set tracker proximity config
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param zone0RssiThreshold: Threshold in dBm for Zone 0  (signed). Default -60
* @param zone1RssiThreshold: Threshold in dBm for Zone 1 (signed). Default -83
* @param zone2RssiThreshold: Threshold in dBm for Zone 2 (signed). Default -100
* @param cacheDeleteInterval: How long until cached entry is deleted (seconds). Default 600
* @param delayOffset: Offset value for RSSI to delay computation. Default 60
* @param delayFactor: Factor for RSSI to delay computation. Default 30
* @param reportDest: Destination ID to which asset reports will be sent. Default 0 
*/
+ (id _Nullable)initWithTrackerSetProximityConfig:(NSNumber * _Nonnull)destinationDeviceId zone0RssiThreshold:(NSNumber * _Nonnull)zone0RssiThreshold zone1RssiThreshold:(NSNumber * _Nonnull)zone1RssiThreshold zone2RssiThreshold:(NSNumber * _Nonnull)zone2RssiThreshold cacheDeleteInterval:(NSNumber * _Nonnull)cacheDeleteInterval delayOffset:(NSNumber * _Nonnull)delayOffset delayFactor:(NSNumber * _Nonnull)delayFactor reportDest:(NSNumber * _Nonnull)reportDest;

/*!
* @brief initWithDiagnosticState: Returns a CSRMeshAction object initialised with initWithDiagnosticState and the following parameters or nil for errors. When received this message is interpreted as to reconfigure the set of information collected. Statistics gathering can be turned on/off ? in the off mode no measurement of messages count and RSSI measurements will be made. RSSI binning can be stored, such that collection ALL messages? RSSI (MASP/MCP, irrespective of encoding) are split between a given number of bin, each of equal dimensions. Masking of individual broadcast channel can be specified, resulting in the collection of information specifically on the selected channels. A REST bit is also available. When present all the accumulated data will be cleared and all counters restarted. Note that it is possible to change various configurations without the RESET flag, this will result in the continuation of accumulation and therefore incoherent statistics.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param flag: 
* @param mode: 
* @param rSSI: 
* @param rSSIBIN: 
*/
+ (id _Nullable)initWithDiagnosticState:(NSNumber * _Nonnull)destinationDeviceId flag:(NSNumber * _Nonnull)flag mode:(NSNumber * _Nonnull)mode rSSI:(NSNumber * _Nonnull)rSSI rSSIBIN:(NSNumber * _Nonnull)rSSIBIN;

/*!
* @brief initWithDiagnosticGetStats: Returns a CSRMeshAction object initialised with initWithDiagnosticGetStats and the following parameters or nil for errors. 
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param flag: 
*/
+ (id _Nullable)initWithDiagnosticGetStats:(NSNumber * _Nonnull)destinationDeviceId flag:(NSNumber * _Nonnull)flag;

/*!
* @brief initWithLightSetColorTemp: Returns a CSRMeshAction object initialised with initWithLightSetColorTemp and the following parameters or nil for errors. Setting Light Colour Temperature: Upon receiving a LIGHT_SET_COLOR_TEMP message, the device saves the ColorTemperature field into the TargetColorTemperature state variable. If the TempDuration field is zero, the CurrentColorTemperature variable is set to TargetColorTemperature and DeltaColorTemperature is set to zero. If the TempDuration field is greater than zero, then the device calculates the difference between TargetColorTemperature and CurrentColorTemperature, over the TempDuration field and store this into a DeltaColorTemperature state variable, so that over TempDuration seconds, CurrentColorTemperature changes smoothly to TargetColorTemperature. The device then responds with a LIGHT_STATE message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param colorTemperature: Colour temperature
* @param tempDuration: Time over which colour temperature will change
*/
+ (id _Nullable)initWithLightSetColorTemp:(NSNumber * _Nonnull)destinationDeviceId colorTemperature:(NSNumber * _Nonnull)colorTemperature tempDuration:(NSNumber * _Nonnull)tempDuration;

/*!
* @brief initWithLightGetWhite: Returns a CSRMeshAction object initialised with initWithLightGetWhite and the following parameters or nil for errors. Setting Light White level.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithLightGetWhite:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithLightSetRgb: Returns a CSRMeshAction object initialised with initWithLightSetRgb and the following parameters or nil for errors. Setting Light Colour:  Upon receiving a LIGHT_SET_RGB_NO_ACK message, the device saves the Level, Red, Green, and Blue fields into the TargetLevel, TargetRed, TargetGreen, and TargetBlue variables respectively. LevelSDState should be set to Attacking. If the Duration field is zero, then the device saves the Level, Red, Green, and Blue fields into the CurrentLevel, CurrentRed, CurrentGreen and CurrentBlue variables, and sets the DeltaLevel, DeltaRed, DeltaGreen, and DeltaBlue variables to zero. If the Duration field is greater than zero, then the device calculates the DeltaLevel, DeltaRed, DeltaGreen, and DeltaBlue levels from the differences between the Current values and the Target values divided by the Duration field, so that over Duration seconds, the CurrentLevel, CurrentRed, CurrentGreen, and CurrentBlue variables are changed smoothly to the TargetLevel, TargetRed, TargetGreen and TargetBlue values. If ACK is requested, the device responds with a LIGHT_STATE message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param level: Light level
* @param red: Red light level
* @param green: Green light level
* @param blue: Blue light level
* @param colorDuration: Time over which the colour will change
* @param acknowledge: =YES means message will be acknowledged
*/
+ (id _Nullable)initWithLightSetRgb:(NSNumber * _Nonnull)destinationDeviceId level:(NSNumber * _Nonnull)level red:(NSNumber * _Nonnull)red green:(NSNumber * _Nonnull)green blue:(NSNumber * _Nonnull)blue colorDuration:(NSNumber * _Nonnull)colorDuration acknowledge:(BOOL)acknowledge;

/*!
* @brief initWithLightSetWhite: Returns a CSRMeshAction object initialised with initWithLightSetWhite and the following parameters or nil for errors. Setting Light White level.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param level: White level
* @param duration: Time before light reaches desired level
* @param acknowledge: =YES means message will be acknowledged
*/
+ (id _Nullable)initWithLightSetWhite:(NSNumber * _Nonnull)destinationDeviceId level:(NSNumber * _Nonnull)level duration:(NSNumber * _Nonnull)duration acknowledge:(BOOL)acknowledge;

/*!
* @brief initWithLightSetLevel: Returns a CSRMeshAction object initialised with initWithLightSetLevel and the following parameters or nil for errors. Setting Light Level: Upon receiving a LIGHT_SET_LEVEL_NO_ACK message, the device saves the Level field into the CurrentLevel model state. LevelSDState should be set to Idle. If ACK is requested, the device should respond with a LIGHT_STATE message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param level: Light level
* @param acknowledge: =YES means message will be acknowledged
*/
+ (id _Nullable)initWithLightSetLevel:(NSNumber * _Nonnull)destinationDeviceId level:(NSNumber * _Nonnull)level acknowledge:(BOOL)acknowledge;

/*!
* @brief initWithLightGetState: Returns a CSRMeshAction object initialised with initWithLightGetState and the following parameters or nil for errors. Getting Light State: Upon receiving a LIGHT_GET_STATE message, the device responds with a LIGHT_STATE message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
*/
+ (id _Nullable)initWithLightGetState:(NSNumber * _Nonnull)destinationDeviceId;

/*!
* @brief initWithLightSetPowerLevel: Returns a CSRMeshAction object initialised with initWithLightSetPowerLevel and the following parameters or nil for errors. Setting Light Power and Light Level: Upon receiving a LIGHT_SET_POWER_LEVEL_NO_ACK message, the device sets the current PowerState to the Power field, the TargetLevel variable to the Level field, the DeltaLevel to the difference between TargetLevel and CurrentLevel divided by the LevelDuration field, saves the Sustain and Decay fields into the LevelSustain and LevelDecay variables, and sets LevelSDState to the Attacking state. If ACK is requested, the device should respond with a LIGHT_STATE message.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param power: Enum type = CSRPower_State. Power state
* @param level: Light level
* @param levelDuration: Time before light reaches desired level
* @param sustain: Time that light will stay at desired level
* @param decay: Time over which light will decay to zero light level
* @param acknowledge: =YES means message will be acknowledged
*/
+ (id _Nullable)initWithLightSetPowerLevel:(NSNumber * _Nonnull)destinationDeviceId power:(CSRPower_State)power level:(NSNumber * _Nonnull)level levelDuration:(NSNumber * _Nonnull)levelDuration sustain:(NSNumber * _Nonnull)sustain decay:(NSNumber * _Nonnull)decay acknowledge:(BOOL)acknowledge;

/*!
* @brief initWithExtensionSendMessage: Returns a CSRMeshAction object initialised with initWithExtensionSendMessage and the following parameters or nil for errors.
* @param destinationDeviceId: The CSRMesh Network ID of this device as an unsigned short
* @param opcode: Custom Opcode.
* @param message: The message to be sent to the given destinationDeviceId. The total size of opcode and message, in bytes must be <12
*/
+ (id _Nullable)initWithExtensionSendMessage:(NSNumber * _Nonnull)destinationDeviceId opcode:(NSNumber * _Nonnull)opcode message:(NSData * _Nonnull)message;
@end
