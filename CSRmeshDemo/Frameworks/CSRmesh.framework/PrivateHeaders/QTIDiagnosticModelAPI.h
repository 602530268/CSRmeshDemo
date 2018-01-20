@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

@protocol QTIDiagnosticModelAPIDelegate;

@interface QTIDiagnosticModelAPI : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * @brief getStats - Upon reception of this message, the server will issue one or more DIAGNOSTIC_STATS responses
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param flag - (uint16_t)
    1 MCP statistics
    2 MASP statistics
    3 Neighbouring devices
    4 RSSI Bin data
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable)getStats:(NSNumber *)deviceId
                            flag:(uint16_t)flag
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     uint8_t type,
                                                     NSData * _Nullable data))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/*!
 * @brief setState - When received this message is interpreted as to reconfigure the set of information collected
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param flag - (uint16_t)
 0  Enable/Disable Stats
 1  Enable/Disable RSSI binning
 2  Mask/Unmask Advertisement Channel 1
 3  Mask/Unmask Advertisement Channel 2
 4  Mask/Unmask Advertisement Channel 3
 15 Reset Stats (mode = 0x02 only)
 * @param flag - (uint8_t)
 0x00 = info
 0x01 = read
 0x02 = set
 * @param rSSI - Threshold
 * @param rSSIBIN - Size of the RSSI Bin in dB – will decompose the range -100dBm to 40dBm
 */
- (void)setState:(NSNumber * _Nonnull)deviceId
                            flag:(uint16_t)flag
                            mode:(uint8_t)mode
                            rSSI:(uint8_t)rSSI
                         rSSIBIN:(uint8_t)rSSIBIN;



/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<QTIDiagnosticModelAPIDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<QTIDiagnosticModelAPIDelegate>)delegate;

@end

@protocol QTIDiagnosticModelAPIDelegate <NSObject>

@optional


/*!
 * @brief didGetStats
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param flag - (uint8_t)
 * @param flag - Encoded data as per following table
    0x01                   0x02                        0x04                        0x04                  0x08                        0x08
 1 MCP received         MASP received                 Total                       Total               Total Bins                  Total Bins
 2 MCP received          MASP received             Index (even)                Index (odd)             0                           Index
 
 3 MCP repeated         MASP repeated               Device ID Average RSSI B0 Offset RSSI Bi
 4 Device ID RSSI B0 RSSI Bi+1
 
 5 MCP Unknown Channels (bitmask) Average RSSI RSSI B1 RSSI Bi+2
 6 Device ID Average RSSI RSSI B2 RSSI Bi+3
 
 7 Channels (bitmask) 0x00 0x00 RSSI B3 RSSI Bi+4
 */


- (void)didGetStats:(NSNumber *)deviceId
                               type:(uint8_t)type
                               data:(nullable NSData *)data
                      meshRequestId:(nullable NSNumber *)meshRequestId;

@end

NS_ASSUME_NONNULL_END

