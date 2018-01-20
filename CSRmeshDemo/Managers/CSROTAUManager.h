//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>
//#import <BTLibrary.h>
#import "CSROTAU.h"
#import "CSRConnectionManager.h"

#define CSROTAUError                    @"Aborting the Update"
#define CSROTAUError_1                  @"Unknown command"
#define CSROTAUError_2                  @"Bad length"
#define CSROTAUError_3                  @"Wrong variant"
#define CSROTAUError_4                  @"Wrong partition number"
#define CSROTAUError_5                  @"Partition size mismatch"
#define CSROTAUError_6                  @"Partition type not found"
#define CSROTAUError_7                  @"Partition open failed"
#define CSROTAUError_8                  @"Partition write failed"
#define CSROTAUError_9                  @"Partition close failed"
#define CSROTAUError_10                 @"SFS validation failed"
#define CSROTAUError_11                 @"OEM validation failed"
#define CSROTAUError_12                 @"Update failed"
#define CSROTAUError_13                 @"App not ready"
#define CSROTAUError_14                 @"App configuration version incompatible"
#define CSROTAUError_15                 @"Loader error"
#define CSROTAUError_16                 @"Unexpected loader error"
#define CSROTAUError_17                 @"Missing loader error"
#define CSROTAUError_18                 @"Battery low error"
#define CSROTAUError_Unknown            @"Unknown error: %ld"
#define CSROTAUError_UnknownResponse    @"Unknown response from Sync Request: %ld"

#define CSROTAUCommandError_1           @"An invalid Command ID was specified"
#define CSROTAUCommandError_2           @"The host is not authenticated to use a Command ID orcontrol a Feature Type"
#define CSROTAUCommandError_3           @"The command was valid, but the device could not successfully carry out the command"
#define CSROTAUCommandError_4           @"The device is in the process of authenticating the host"
#define CSROTAUCommandError_5           @"An invalid parameter was used in the command"
#define CSROTAUCommandError_6           @"The device is not in the correct state to process the command"
#define CSROTAUCommandError_7           @"The command is already in progress"

#define CSRStatusReconnectingString     @"Reconnecting..."
#define CSRStatusReconnectedString      @"Reconnected. Initialising..."
#define CSRStatusPairingString          @"Initialised."
#define CSRStatusFinalisingString       @"Finalising..."

/*!
 @header CSROTAUManager
 Manage long running operations
 */

@protocol CSRUpdateManagerDelegate;

/*!
 @class CSROTAUManager
 @abstract Singleton class that manages long running operations
 @discussion The connection manager implements CSROTAUDelegate and CSRConnectionManagerDelegate
 */
@interface CSROTAUManager : NSObject <CSROTAUDelegate, CSRConnectionManagerDelegate>

/// @brief True of an OTAU is in progress
@property (nonatomic) BOOL updateInProgress;

/// @brief The name of the file being used for OTAU
@property (nonatomic) NSString *updateFileName;

/// @brief A percentage complete value
@property (nonatomic) double updateProgress;

/// @brief Delegate class for callbacks.
@property (nonatomic, weak) id<CSRUpdateManagerDelegate> delegate;

/*!
 @brief The singleton instance
 @return sharedInstance - The id of the singleton object.
 */
+ (CSROTAUManager *)sharedInstance;

/*!
 @brief Start an OTAU
 @param fileName The file name to use.
 */
- (void)start:(NSString *)fileName;

/*!
 @brief Stop the current OTAU. An abort message will be sent and acknowledged.
 */
- (void)stop;

/*!
 @brief The OTAU data transfer is complete. The user can choose not to apply the new data.
 @param value True to go ahead and apply the update.
 */
- (void)commitConfirm:(BOOL)value;

/*!
 @brief The OTAU protocol can ask the user can stop and wait for the user to OK.
 OTAU will continue after calling this method.
 */
- (void)eraseSqifConfirm;

/*!
 @brief The OTAU protocol can ask the user to confirm an error.
 OTAU will continue after calling this method.
 */
- (void)confirmError;

/*!
 @brief If you want to cancel the upgrade.
 */
- (void)abort;

/*!
 @brief If there is a problem with the update the user can force the process to reset and try again.
 */
- (void)abortAndRestart;

/*!
 @brief The OTAU protocol can ask the user can stop and wait once the file transfer is complete.
 OTAU will continue after calling this method.
 */
- (void)updateTransferComplete;

/*!
 @brief The OTAU protocol can raise low battery warnings.
 OTAU will continue after calling this method.
 */
- (void)syncRequest;


/// @brief Prepare CSROTAUManager by set up delegates and listeners.
- (void)connect;

/// @brief Clear delegates and listeners.
- (void)disconnect;

/// @brief Get the current LED state
- (void)getLED;

/*!
 @brief Control the device LED
 @param value On or off value
 */
- (void)setLED:(BOOL)value;

/*!
 @brief Control the device volume
 @param value Volume valid values are 0 to 10
 */
- (void)setVolume:(NSInteger)value;

/*!
 @brief Execute AV commands on the device
 @param operation Operation to perform. @see //apple_ref/doc/OTAUAVControlOperation
 */
- (void)avControl:(OTAUAVControlOperation)operation;

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

/// @brief Get the current battery level
- (void)getBattery;

/// @brief Get the on chip application version
- (void)getApiVersion;

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

/// @brief Get the current audio source
- (void)getAudioSource;

/*!
 @brief Requests the device send a "Find Me" request to the HID remote connected to it.
 @param value 0 - None, 1 - Mid alert, 2 - High alert
 */
- (void)findMe:(NSUInteger)value;

/*!
 @brief Get the audio source
 @param value OTAUAudioSource
 */
- (void)setAudioSource:(OTAUAudioSource)value;

- (void)getEQControl;
- (void)setEQControl:(NSInteger)value;
- (void)getGroupEQParam:(NSData *)data;
- (void)setGroupEQParam:(NSData *)data;
- (void)getUserEQ;
- (void)setUserEQ:(BOOL)value;

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

- (void)setFilterType:(NSInteger)bank band:(NSInteger)band value:(NSInteger)value;
- (void)setFilterFrequency:(NSInteger)bank band:(NSInteger)band value:(double)value;
- (void)setFilterGain:(NSInteger)bank band:(NSInteger)band value:(double)value;
- (void)setFilterQ:(NSInteger)bank band:(NSInteger)band value:(double)value;
- (void)setFilterPreGain:(NSInteger)bank band:(NSInteger)band value:(double)value;

@end

/*!
 @protocol CSRUpdateManagerDelegate
 @discussion Callbacks from changes to state
 */
@protocol CSRUpdateManagerDelegate <NSObject>

/*!
 @brief The upgrade aborted.
 @param error Look at the error so see what went wrong
 */
- (void)didAbortWithError:(NSError *)error;

@optional
/// @brief The upgrade completed successfully
- (void)didCompleteUpgrade;

/// @brief The upgrade was aborted
- (void)didAbortUpgrade;

/*!
 @brief The upgrade made some progress
 @param value Percentage complete
 @param eta Estimaged time of completion
 */
- (void)didMakeProgress:(double)value eta:(NSString *)eta;

/// @brief The device rebooted after the upgrade
- (void)didWarmBoot;

/*!
 @brief State information about the device. Used when the device is in it's reboot cycle.
 @param value A string with some status information
 */
- (void)didUpdateStatus:(NSString *)value;

/*!
 @brief A response was recieved
 @param command The command response. @see //apple_ref/doc/CSROTAUGattCommand
 */
- (void)didReceiveOTAUGattResponse:(CSROTAUGattCommand *)command;

/// @brief Present the user with a yes no choice
- (void)confirmRequired;

/// @brief Present the user with an okay
- (void)okayRequired;

/// @brief Present the user with a yes no choice about forcing the upgrade
- (void)confirmForceUpgrade;

/// @brief Present the user with a yes no choice about the file transfer
- (void)confirmTransferRequired;

/// @brief Present the user with an okay about plugging their device into mains
- (void)confirmBatteryOkay;

@end
