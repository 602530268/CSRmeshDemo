//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

/*!
 * @header CSRMeshApi Class is the base class for the Model Api classes.
 */

#ifndef CSRMESHAPI_H
#define CSRMESHAPI_H    1

@import Foundation;
@import CoreBluetooth;
#import "CSRMeshUserManager.h"
#import "CSRRestConsts.h"

// Error Keys
#define kCSRMESH_ERROR_DOMAIN               @"com.csr.mesh"
#define kMeshRequestId                      @"MeshRequestId"
#define kFailureDeviceId                    @"FailureDeviceId"
#define kTwoOpCodes                         0x80
#define kAckToken                           0x8A08
#define ksMeshNameErrorParam                @"name"
#define ksMeshApiTimeoutError               @"The command timed out"

// Opcodes
#define kCSR_WATCHDOG_MESSAGE               0x0000
#define kCSR_WATCHDOG_SET_INTERVAL          0x0001
#define kCSR_WATCHDOG_INTERVAL              0x0002

#define kCSR_LIGHT_SET_LEVEL_NO_ACK         0x8A00
#define kCSR_LIGHT_SET_LEVEL                0x8A01
#define kCSR_LIGHT_SET_RGB_NO_ACK           0x8A02
#define kCSR_LIGHT_SET_RGB                  0x8A03
#define kCSR_LIGHT_SET_POWER_LEVEL_NO_ACK   0x8A04
#define kCSR_LIGHT_SET_POWER_LEVEL          0x8A05
#define kCSR_LIGHT_SET_COLOR_TEMP           0x8A06
#define kCSR_LIGHT_GET_STATE                0x8A07

#define kCSR_LIGHT_STATE                    0x8A08
#define kCSR_LIGHT_STATE_UNSOLICITED        0x8A09
#define kCSR_LIGHT_SET_WHITE                0x8A0A
#define kCSR_LIGHT_SET_WHITE_NO_ACK         0x8A0B
#define kCSR_LIGHT_GET_WHITE                0x8A0C
#define kCSR_LIGHT_WHITE                    0x8A0D
#define kCSR_LIGHT_WHITE_UNSOLICITED        0x8A0E

#define kCSR_CONFIG_LAST_SEQ_NUM            0x03
#define kCSR_CONFIG_RESET_DEVICE            0x04
#define kCSR_CONFIG_SET_DEVICE_IDENTIFIER   0x05
#define kCSR_CONFIG_SET_PARAMETERS          0x06
#define kCSR_CONFIG_GET_PARAMETERS          0x07
#define kCSR_CONFIG_PARAMETERS              0x08
#define kCSR_CONFIG_DISCOVER_DEVICE         0x09
#define kCSR_CONFIG_DEVICE_IDENTIFIER       0x0A
#define kCSR_CONFIG_GET_INFO                0x0B
#define kCSR_CONFIG_INFO                    0x0C
#define kCSR_CONFIG_SET_MESSAGE_PARAMETERS  0x12
#define kCSR_CONFIG_GET_MESSAGE_PARAMETERS  0x13
#define kCSR_CONFIG_MESSAGE_PARAMETERS      0x14

#define kCSR_GROUP_GET_NUM_GROUP_IDS        0x0D
#define kCSR_GROUP_NUM_GROUPS               0x0E
#define kCSR_GROUP_SET_GROUPID              0x0F
#define kCSR_GROUP_GET_GROUPID              0x10
#define kCSR_GROUP_GROUPID                  0x11

#define kCSR_SENSOR_GET_TYPES               0x20
#define kCSR_SENSOR_TYPES                   0x21
#define kCSR_SENSOR_SET_STATE               0x22
#define kCSR_SENSOR_GET_STATE               0x23
#define kCSR_SENSOR_STATE                   0x24
#define kCSR_SENSOR_WRITE_VALUE             0x25
#define kCSR_SENSOR_WRITE_VALUE_NO_ACK      0x26
#define kCSR_SENSOR_READ_VALUE              0x27
#define kCSR_SENSOR_VALUE                   0x28
#define kCSR_SENSOR_MISSING                 0x29

#define kCSR_ACTUATOR_GET_TYPES             0x30
#define kCSR_ACTUATOR_TYPES                 0x31
#define kCSR_ACTUATOR_SET_VALUE_NO_ACK      0x32
#define kCSR_ACTUATOR_SET_VALUE             0x33
#define kCSR_ACTUATOR_GET_VALUE_ACK         0x34
#define kCSR_ACTUATOR_VALUE_ACK             0x35

#define kCSR_ASSET_SET_STATE                0x40
#define kCSR_ASSET_GET_STATE                0x41
#define kCSR_ASSET_STATE                    0x42
#define kCSR_ASSET_ANNOUNCE                 0x43

#define kCSR_TRACKER_FIND                   0x44
#define kCSR_TRACKER_FOUND                  0x45
#define kCSR_TRACKER_REPORT                 0x46
#define kCSR_TRACKER_CLEAR_CACHE            0x47
#define kCSR_TRACKER_SET_PROXIMITY_CONFIG   0x48

#define kCSR_DATA_STREAM_FLUSH              0x70
#define kCSR_DATA_STREAM_SEND               0x71
#define kCSR_DATA_STREAM_RECEIVED           0x72
#define kCSR_DATA_BLOCK_SEND                0x73

#define kCSR_FIRMWARE_GET_VERSION           0x78
#define kCSR_FIRMWARE_VERSION               0x79
#define kCSR_FIRMWARE_UPDATE_REQUIRED       0x7a
#define kCSR_FIRMWARE_UPDATE_ACK            0x7b

#define kCSR_BEARER_SET_STATE               0x8100
#define kCSR_BEARER_GET_STATE               0x8101
#define kCSR_BEARER_STATE                   0x8102

#define kCSR_PING_REQUEST                   0x8200
#define kCSR_PING_RESPONSE                  0x8201

#define kCSR_ATTENTION_SET_STATE            0x8400
#define kCSR_ATTENTION_STATE                0x8401

#define kCSR_POWER_SET_STATE_NO_ACK         0x8900
#define kCSR_POWER_SET_POWER_STATE          0x8901
#define kCSR_POWER_TOGGLE_STATE_NO_ACK      0x8902
#define kCSR_POWER_TOGGLE_STATE             0x8903
#define kCSR_POWER_GET_STATE                0x8904
#define kCSR_POWER_STATE                    0x8905
#define kCSR_POWER_STATE_NO_ACK             0x8906

#define kCSR_BATTERY_GET_STATE              0x8300
#define kCSR_BATTERY_STATE                  0x8301

#define kCSR_BEACON_SET_STATUS              0x60
#define kCSR_BEACON_GET_STATUS              0x62
#define kCSR_BEACON_STATUS                  0x63
#define kCSR_BEACON_GET_BEACON_TYPES        0x64
#define kCSR_BEACON_TYPES                   0x65
#define kCSR_BEACON_SET_PAYLOAD             0x66
#define kCSR_BEACON_PAYLOAD_ACK             0x67
#define kCSR_BEACON_GET_PAYLOAD             0x68

#define kCSR_BEACON_PROXY_ADD               0x69
#define kCSR_BEACON_PROXY_REMOVE            0x6A
#define kCSR_BEACON_PROXY_COMMAND_STATUS_DEVICES 0x6B
#define kCSR_BEACON_PROXY_GET_STATUS        0x6C
#define kCSR_BEACON_PROXY_STATUS            0x6D
#define kCSR_BEACON_PROXY_GET_DEVICES       0x6E
#define kCSR_BEACON_PROXY_DEVICES           0x6F

// Range values
#define kCSR_MAX_SENSOR_TYPES               64
#define kCSR_MAX_ACTUATOR_TYPES             64

#define kCSR_TIME_GET_STATE                 0x76
#define kCSR_TIME_SET_STATE                 0x75
#define kCSR_TIME_STATE                     0x77
#define kCSR_TIME_BROADCAST                 0x7F

#define kCSR_TUNING_PROBE                   0xEF01
#define kCSR_TUNING_STATS_REQUEST           0xEF02
#define kCSR_TUNING_STATS_RESPONSE          0xEF03
#define kCSR_TUNING_ACK_CONFIG              0xEF04
#define kCSR_TUNING_SET_CONFIG              0xEF05

#define kCSR_EXTENSION_REQUEST              0xEF10
#define kCSR_EXTENSION_CONFLICT             0xEF11

#define kCSR_LOT_ANNOUNCE                   0x1A
#define kCSR_LOT_INTEREST                   0xEF30

#define kCSR_DIAGNOSTIC_STATE               0xEF40
#define kCSR_DIAGNOSTIC_GET_STATS           0xEF41
#define kCSR_DIAGNOSTIC_STATS               0xEF42

#define kCSR_ACTION_SET_ACTION              0x50
#define kCSR_ACTION_SET_ACTION_ACK          0x51
#define kCSR_ACTION_GET_STATUS              0x52
#define kCSR_ACTION_STATUS                  0x53
#define kCSR_ACTION_DELETE                  0x54
#define kCSR_ACTION_DELETE_ACK              0x55
#define kCSR_ACTION_GET                     0x56

#define kCSR_MAX_MODEL_NUMBER               34
#define kCSR_ALL_MODELS                     0xff
#define kCSR_MAX_GROUP_INDEXES              64
#define kCSR_MAX_GROUP_INSTANCE             64

// Error codes
enum {
    CSRMESH_MESSAGE_TIMED_OUT = 1000,
    CSRMESH_MESSAGE_ALREADY_IN_ASSOCIATION,
    CSRMESH_ACTION_MODEL,
    CSRMESH_CONFIG_MODEL,
    CSRMESH_BEACON_PROXY_MODEL,
    CSRMESH_BEACON_MODEL,
    CSRMESH_DATA_MODEL,
    CSRMESH_SENSOR_MODEL,
    CSRMESH_ASSET_MODEL,
    CSRMESH_EXTENSION_MODEL,
    CSRMESH_GROUP_MODEL,
    CSRMESH_ACTUATOR_MODEL,
    CSRMESH_MESHSERVICE,
    CSRMESH_LOT_MODEL
};

/**
 @enum CSRNetworkSecurityUpdateStatus - Network security update status
 */
typedef NS_ENUM(NSUInteger, CSRNetworkSecurityUpdateStatus) {
    /** Update not required */
    CSRNetworkSecurityUpdateStatus_UpdateNotRequired = 0,
    /** Updated obsolete Network Key */
    CSRNetworkSecurityUpdateStatus_UpdatedObsoleteNetworkKey,
    /** Updated obsolete Network IV */
    CSRNetworkSecurityUpdateStatus_UpdatedObsoleteNetworkIV,
    /** Updated obsolete Network Key & Network IV */
    CSRNetworkSecurityUpdateStatus_UpdatedAllParamsObsolete,
    /** Update failed */
    CSRNetworkSecurityUpdateStatus_UpdateFailed
};

@interface CSRmeshApi : NSObject

// init
/*!
 * @brief sharedInstance. Creates singleton on first use.
 * @return id - The id of the singleton object.
 */
+ (instancetype _Nonnull) sharedInstance;

/*!
 * @brief handleRespnose Decode the data returned from the response characteristic
 * Child classes must override this method to decode responses
 * @param data The content of the characteristics
 * @param deviceId The source device id
 */
- (void)handleResponse:(NSData * _Nonnull)data deviceId:(NSNumber * _Nonnull)deviceId;

/*!
 * @brief assignBlocks Create block handlers and create a mesh request id
 * @param successBlock The success block to call
 * param failureBlock The failure block to call
 * return requestId
 */
- (NSNumber * _Nonnull)assignBlocks:(id _Nullable)successBlock failure:(id _Nullable)failureBlock;

/*!
 * @brief cleanBlocks Remove handlers after method completion
 * @param meshRequestId The request to clean up
 */
- (void)cleanBlocks:(NSNumber * _Nonnull)meshRequestId;

/*!
 * @brief createPacket Convienience method for creating a CSRmesh packet.
 * @param deviceId The device id
 * @param modelCode The model the packet is from
 * @param opCode The operation being requested
 */
- (NSMutableData * _Nonnull)createPacket:(NSNumber * _Nonnull)deviceId
                         opcode:(uint16_t)opcode
                     opcodeSize:(int)opcodeSize;

@end


@interface CSRmeshApi ()

typedef  void (^CSRmeshAppearance)(NSData * _Nonnull deviceHash, NSNumber * _Nonnull appearanceValue, NSData * _Nonnull shortName);
typedef  void (^CSRmeshUUID)(CBUUID * _Nonnull uuid, NSNumber * _Nonnull rssi);

/// @typedef CSRErrorCompletion handler for returning NSError objects
typedef  void (^CSRErrorCompletion)(NSError * _Nonnull error);


// Success/Failure block dictionary
// Key is the meshRequestId
@property   (strong, nonatomic)     NSMutableDictionary * _Nullable successBlocks;
@property   (strong, nonatomic)     NSMutableDictionary * _Nullable failureBlocks;
@property   (strong, nonatomic)     NSMutableDictionary * _Nullable asynchBlocks;

@property   (strong, nonatomic)     CSRmeshAppearance  _Nullable appearanceBlock;
@property   (strong, nonatomic)     CSRmeshUUID _Nullable uuidBlock;

@property   BOOL    cloudBearer;
@property   BOOL    bluetoothBearer;

@property   (strong, nonatomic)     NSNumber * _Nonnull repeats;

@end

#endif

