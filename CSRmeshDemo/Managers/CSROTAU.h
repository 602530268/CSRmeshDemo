//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>
#import "CSROTAUGattCommand.h"
#import <CoreBluetooth/CoreBluetooth.h>
#import "CSRPeripheral.h"
#import "CSRConnectionManager.h"

#define CSROTAUErrorDomain          @"com.csr.OTAU"
#define CSROTAUErrorParam           @"name"
#define CSR_OTAU_VENDOR_ID          0x000A
#define CSR_OTAU_UPDATE_ID          0x12345678

#define UUID_OTAU_SERVICE           @"00001100-d102-11e1-9b23-00025b00a5a5"
#define UUID_OTAU_COMMAND_ENDPOINT  @"00001101-d102-11e1-9b23-00025b00a5a5"
#define UUID_OTAU_RESPONSE_ENDPOINT @"00001102-d102-11e1-9b23-00025b00a5a5"
#define UUID_OTAU_DATA_ENDPOINT     @"00001103-d102-11e1-9b23-00025b00a5a5"

/*!
 @header CSROTAU
 The OTAU object manages sending and recieving commands.
 */

@protocol CSROTAUDelegate;

@interface CSROTAU : NSObject

/// @brief The delegate for callbacks
@property (nonatomic, weak) id<CSROTAUDelegate> delegate;

/// @brief The OTAU service
@property (nonatomic) CBService *service;

/// @brief The OTAU command characteristic. Write only.
@property (nonatomic) CBCharacteristic *commandCharacteristic;

/// @brief The OTAU response characteristic. Read only.
/// A listener is normally attached so that the delegate is called back with responses.
@property (nonatomic) CBCharacteristic *responseCharacteristic;

/// @brief The OTAU data characteristic. Can be used for slightly enhanced data rates.
@property (nonatomic) CBCharacteristic *dataCharacteristic;

/// @brief An MD5 hash of the current OTAU file.
@property (nonatomic) NSData *fileMD5;

/*!
 @brief The singleton instance
 @return id - The id of the singleton object.
 */
+ (CSROTAU *)sharedInstance;

/*!
 @brief Connect to the OTAU service. Set up the characteristics ready for executing commands.
 @param peripheral The peripheral to connect to.
 */
- (void)connectPeripheral:(CSRPeripheral *)peripheral;

/*!
 @brief Disconnect from the OTAU service. Removes the listener on the response characteristic.
 */
- (void)disconnectPeripheral;

/// @brief Execute a no operation command
- (void)noOperation;

/// @brief Get the on chip application version
- (void)getApiVersion;

/// @brief Get the current LED state
- (void)getLEDState;

/// @brief Get the current battery level
- (void)getBattery;

/// @brief Get the current audio source
- (void)getAudioSource;

/*!
 @brief Requests the device send a "Find Me" request to the HID remote connected to it.
 @param value 0 - None, 1 - Mid alert, 2 - High alert
 */
- (void)findMe:(NSUInteger)value;

/*!
 @brief Control the device LED
 @param enabled On or off value
 */
- (void)setLED:(BOOL)enabled;

/*!
 @brief Control the device volume
 @param value Volume valid values are 0 to 10
 */
- (void)setVolume:(NSInteger)value;

/*!
 @brief Set the TWS trim volume for a device
 @param device Master is 0 and slave is 1.
 @param value Volume valid values are 0 to 10
 */
- (void)trimTWSVolume:(NSInteger)device volume:(NSInteger)value;

/*!
 @brief Get the device volume
 @param device Master is 0 and slave is 1.
 */
- (void)getTWSVolume:(NSInteger)device;

/*!
 @brief Set the device volume
 @param device Master is 0 and slave is 1.
 @param value Volume valid values are 0 to 10
 */
- (void)setTWSVolume:(NSInteger)device volume:(NSInteger)value;

/*!
 @brief Get the device routing.
 0 - Routing both stereo channels
 1 - Routing left channel
 2 - Routing right channel
 3 - Mixing left and right channels to mono
 @param device Master is 0 and slave is 1.
 */
- (void)getTWSRouting:(NSInteger)device;

/*!
 @brief Get the device routing
 @param device Master is 0 and slave is 1.
 @param value 0 - Routing both stereo channels
 1 - Routing left channel
 2 - Routing right channel
 3 - Mixing left and right channels to mono
 */
- (void)setTWSRouting:(NSInteger)device routing:(NSInteger)value;

/*!
 @brief Get the bass boost
 0 - Bass boost is disabled
 1 - Bass boost is enabled
 */
- (void)getBassBoost;

/*!
 @brief Get the bass boost
 @param value 0 - Bass boost is disabled
 1 - Bass boost is enabled
 */
- (void)setBassBoost:(BOOL)value;

/*!
 @brief Get the 3D enhancement
 0 - 3D enhancement is disabled
 1 - 3D enhancement is enabled
 */
- (void)get3DEnhancement;

/*!
 @brief Get the 3D enhancement
 @param value 0 - 3D enhancement is disabled
 1 - 3D enhancement is enabled
 */
- (void)set3DEnhancement:(BOOL)value;

/*!
 @brief Set the audio source for the device
 @param value Audio source required.
 */
- (void)setAudioSource:(OTAUAudioSource)value;

- (void)getGroupEQParam:(NSData *)data;
- (void)setGroupEQParam:(NSData *)data;
- (void)getUserEQ;
- (void)setUserEQ:(BOOL)value;
- (void)setFilterType:(NSInteger)bank band:(NSInteger)band value:(NSInteger)value;
- (void)setFilterFrequency:(NSInteger)bank band:(NSInteger)band value:(double)value;
- (void)setFilterGain:(NSInteger)bank band:(NSInteger)band value:(double)value;
- (void)setFilterQ:(NSInteger)bank band:(NSInteger)band value:(double)value;
- (void)setFilterPreGain:(NSInteger)bank band:(NSInteger)band value:(double)value;
- (void)getEQControl;
- (void)setEQControl:(NSInteger)value;

/*!
 @brief Get power status for the device
 0 - The device is off
 1 - The device is on
 */
- (void)getPower;

/*!
 @brief Get power status for the device
 @param value 0 - The device is off
 1 - The device is on
 */
- (void)setPowerOn:(BOOL)value;

/*!
 @brief Execute AV commands on the device
 @param operation Operation to perform. @see //apple_ref/doc/OTAUAVControlOperation
 */
- (void)avControl:(OTAUAVControlOperation)operation;

/*!
 @brief Register for notifications.
 @param eventType The type of notifications to register for. @see //apple_ref/doc/OTAUEvent
 */
- (void)registerNotifications:(OTAUEvent)eventType;

/*!
 @brief Stop recieving notifications for the given event type.
 @param eventType The type of notifications to unregister for. @see //apple_ref/doc/OTAUEvent
 */
- (void)cancelNotifications:(OTAUEvent)eventType;

/*!
 @brief Abort the current upgrade.
 */
- (void)abort;

/*!
 @brief Connect to the VM Upgrade
 */
- (void)vmUpgradeConnect;

/*!
 @brief Disconnect from the VM Upgrade
 */
- (void)vmUpgradeDisconnect;

/*!
 @brief Send a control command to the VM Upgrade
 @param command A OTAU command. @see //apple_ref/doc/OTAUCommandUpdate
 */
- (void)vmUpgradeControl:(OTAUCommandUpdate)command;

/*!
 @brief Send a control command with no data to the VM Upgrade
 @param command The OTAU command. @see //apple_ref/doc/OTAUCommandUpdate
 */
- (void)vmUpgradeControlNoData:(OTAUCommandUpdate)command;

/*!
 @brief Send a control command with data to the VM Upgrade
 @param command The OTAU command. @see //apple_ref/doc/OTAUCommandUpdate
 @param length The length of the data passed to the command
 @param data The data for the command
 */
- (void)vmUpgradeControl:(OTAUCommandUpdate)command
                  length:(NSInteger)length
                    data:(NSData *)data;

/*!
 @brief Send a control command with data to the VM Upgrade
 @param command The OTAU command. @see //apple_ref/doc/OTAUCommandUpdate
 @param length The length of the data passed to the command
 @param data The data for the command
 @return data The complete packet of data for the command
 */
- (NSData *)vmUpgradeControlData:(OTAUCommandUpdate)command
                          length:(NSInteger)length
                            data:(NSData *)data;

/*!
 @brief Externally prompt the library to decode data.
 @param characteristic The characteristic to read data from
 */
- (void)handleResponse:(CBCharacteristic *)characteristic;

/*!
 @brief Send a raw data packet.
 @param data The raw data to send
 */
- (void)sendData:(NSData *)data;

@end

/*!
 @protocol CSROTAUDelegate
 @discussion Callbacks from changes to state
 */
@protocol CSROTAUDelegate <NSObject>

@optional

/*!
 @brief The object has connected to the peripheral and the characteristics are ready to accept commands.
 */
- (void)connectedAndInitialised;

/*!
 @brief The object has recieved a response to a command
 @param command the command recieved. See //apple_ref/doc/CSROTAUGattCommand
 */
- (void)didReceiveResponse:(CSROTAUGattCommand *)command;

@end
