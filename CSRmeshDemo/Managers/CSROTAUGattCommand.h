//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>

// GATT Framed command
//0 bytes  1        2        3        4          5    len+4
//+--------+--------+--------+--------+ +--------+--------+
//|    VENDOR ID    |   COMMAND ID    | | PAYLOAD   ...   |
//+--------+--------+--------+--------+ +--------+--------+

#define OTAU_GATT_HEADER_SIZE                4
#define OTAU_GATT_HEADER_OFFSET_VENDOR_ID    0
#define OTAU_GATT_HEADER_OFFSET_COMMAND_ID   2
#define OTAU_GATT_HEADER_OFFSET_PAYLOAD      4
#define OTAU_GATT_COMMAND_ACK_MASK           0x8000

/*!
 @header CSROTAUGattCommand
 This object encapsulates commands sent to OTAU.
 */

/**
 @enum OTAUCommandType - All the high level OTAU Commands
 */
typedef NS_ENUM(NSInteger, OTAUCommandType) {
    /// Retrieves the version of the configuration set
    OTAUCommand_GetConfigurationVersion         = 0x0180,
    /// Configures the LED indicators. Determines patterns to be displayed in given states and on events and configures filters to be applied as events occur.
    OTAUCommand_SetLEDConfiguration             = 0x0101,
    /// Retrieves the current LED configuration.
    OTAUCommand_GetLEDConfiguration             = 0x0181,
    /// Configures informational tones on the device.
    OTAUCommand_SetToneConfiguration            = 0x0102,
    /// Retrieves the currently configured tone configuration.
    OTAUCommand_GetToneConfiguration            = 0x0182,
    /// Sets the default volume for tones and audio.
    OTAUCommand_SetDefaultVolume                = 0x0103,
    /// Requests the default volume settings for tones and audio.
    OTAUCommand_GetDefaultVolume                = 0x0183,
    /// Resets all settings (deletes PS keys) which override factory defaults.
    OTAUCommand_FactoryDefaultReset             = 0x0104,
    /// Configures per-event vibrator patterns.
    OTAUCommand_SetVibratorConfiguration        = 0x0105,
    /// Retrieves the currently configured vibratorconfiguration.
    OTAUCommand_GetVibratorConfiguration        = 0x0185,
    /// Configures voice prompts to select a different language, voice etc.
    OTAUCommand_SetVoicePromptConfiguration     = 0x0106,
    /// Retrieves the currently configured voice prompt configuration.
    OTAUCommand_GetVoicePromptConfiguration     = 0x0186,
    /**
     Configures the various timers on the device. This command has a long form (where the payload holds the value of every timer) and a short form (where the payload holds a timer number and the value of that timer). Timer numbers, and thus the format of the long form of the command, are application-specific; for example the ADK3.5 Audio Sink app timers are
     1. AutoSwitchOffTime_s
     2. LimboTimeout_s
     3. NetworkServiceIndicatorRepeatTime_s
     4. DisablePowerOffAfterPowerOnTime_s
     5. PairModeTimeout_s
     6. MuteRemindTime_s
     7. ConnectableTimeout_
     8. PairModeTimeoutIfPDL_s
     9. ReconnectionAttempts
     10. EncryptionRefreshTimeout_m
     11. InquiryTimeout_s
     12. SecondAGConnectDelayTime_s
     13. MissedCallIndicateTime_s
     14. MissedCallIndicateAttemps
     15. A2dpLinkLossReconnectionTime_s
     16. LanguageConfirmTime_s
     17. SpeechRecRepeatTime_ms
     18. StoreCurrentSinkVolumeTimeout_s
     19. WiredAudioConnectedPowerOffTimeout_s
     20. StoreCurrentPEQSettingsTimeout_s
     21. DefragCheckTimer_s
     22. AudioAmpPowerDownTimeoutInLimbo_s     */
    OTAUCommand_SetTimerConfiguration           = 0x0109,
    /**
     Retrieves the configuration of the various timers on the device. This command has a long form (where the response holds the value of every timer) and a short form (where the command payload holds a timer number and the response holds the number and value of that timer). Timer numbers, and thus the format of the long form of the acknowledgement, are application-specific
     */
    OTAUCommand_GetTimerConfiguration           = 0x0189,
    /**
     Configures the device volume control for each of the 16 volume levels:
     1. Level to change to when Volume Up is actioned
     2. Level to change to when Volume Down is actioned
     3. Tone to play when this volume level is selected
     4. Music (A2DP) Gain at this level; must be zero since OTAU API V2.2
     5. Voice (HFP) Gain at this level
     This command has a long form (where the payload holds every one of the 16 × 5 parameters) and a short form (where the payload holds a volume profile number and the parameter values of that profile).
     */
    OTAUCommand_SetAudioGainsConfiguration      = 0x010A,
    /**
     Requests the device volume control configuration for each of the 16 volume levels:
     1. Level to change to when Volume Up is actioned
     2. Level to change to when Volume Down is actioned
     3. Tone to play when this volume level is selected
     4. Music (A2DP) Gain at this level; must be zero since OTAU API V2.2
     5. Voice (HFP) Gain at this level
     This command has a long form (where the response holds every one of the 16 × 5 parameters) and a short form (where the response holds a Volume Profile number and the values of the parameters for that profile).
     */
    OTAUCommand_GetAudioGainsConfiguration      = 0x018A,
    /// Sets the credentials to access the Wi-Fi access point.
    OTAUCommand_SetWLANCredentials              = 0x0110,
    /// Retrieves the credentials to access the Wi-Fi access point.
    OTAUCommand_GetWLANCredentials              = 0x0190,
    /// Get the mounted partitions
    OTAUCommand_GetMountedPartitions            = 0x01A0,
    /// Configures which SQIF partition is to be used for DFU operations.
    OTAUCommand_SetDFUPartition                 = 0x0121,
    /// Retrieves the index and size of the configured DFU partition.
    OTAUCommand_GetDFUPartition                 = 0x01A1,
    
    /**
     The host can raise/lower the current volume or mute/unmute audio using this command.
     The command takes a single parameter in the first byte of payload.
     */
    OTAUCommand_Volume                          = 0x0201,
    /**
     A host can cause a device to warm reset using this command. The device will transmit an acknowledgement and then do a warm reset.
     The host must be authenticated to use this command.
     */
    OTAUCommand_DeviceReset                     = 0x0202,
    /// Get the power state of the device
    OTAUCommand_GetPowerState                   = 0x0284,
    /// Set the power state of the device
    OTAUCommand_SetPowerState                   = 0x0204,
    /// Sets the orientation of the volume control buttons on the device
    OTAUCommand_SetVolumeOrientation            = 0x0205,
    /// Requests the current orientation of the volume control buttons on the device
    OTAUCommand_GetVolumeOrientation            = 0x0285,
    /// Enables or disables use of the vibrator in the headset, if one is present
    OTAUCommand_SetVibratorControl              = 0x0206,
    /// Requests the current setting of the vibrator
    OTAUCommand_GetVibratorControl              = 0x0286,
    /// Enables or disables LEDs (or equivalent indicators) on the headset
    OTAUCommand_SetLEDControl                   = 0x0207,
    /// Establishes whether LED indicators are enabled
    OTAUCommand_GetLEDControl                   = 0x0287,
    /// Sent from a headset to control an FM receiver on the phone, or from a handset to control a reciever in a headset.
    OTAUCommand_FMControl                       = 0x0208,
    /// Play a tone
    OTAUCommand_PlayTone                        = 0x0209,
    /// Enables or disables voice prompts on the headset
    OTAUCommand_SetVoicePromptControl           = 0x020A,
    /// Establishes whether voice prompts are enabled
    OTAUCommand_GetVoicePromptControl           = 0x028A,
    /// Selects the next available language for Text-to-Speech functions
    OTAUCommand_ChangeTTSLanguage               = 0x020B,
    /// Enables or disables simple speech recognition on the headset
    OTAUCommand_SetSpeechRecognitionControl     = 0x020C,
    /// Establishes whether speech recognition is enabled
    OTAUCommand_GetSpeechRecognitionControl     = 0x028C,
    /// Undocumented
    OTAUCommand_AlertLEDs                       = 0x020D,
    /// Undocumented
    OTAUCommand_AlertTone                       = 0x020E,
    /// Undocumented
    OTAUCommand_AlertEvent                      = 0x0210,
    /// Undocumented
    OTAUCommand_AlertVoice                      = 0x0211,
    /// Undocumented
    OTAUCommand_SetTextToSpeechLanguage         = 0x0212,
    /// Undocumented
    OTAUCommand_GetTextToSpeechLanguage         = 0x0292,
    /// Undocumented
    OTAUCommand_StartSpeechRecognition          = 0x0213,
    /// Selects an audio equaliser preset
    OTAUCommand_SetEQControl                    = 0x0214,
    /// Gets the currently selected audio equaliser preset
    OTAUCommand_GetEQControl                    = 0x0294,
    /// Enables or disables bass boost on the headset
    OTAUCommand_SetBassBoostControl             = 0x0215,
    /// Establishes whether bass boost is enabled
    OTAUCommand_GetBassBoostControl             = 0x0295,
    /// Enables or disables 3D sound enhancement on the headset
    OTAUCommand_Set3DEnhancementControl         = 0x0216,
    /// Establishes whether 3D Enhancement is enabled
    OTAUCommand_Get3DEnhancementControl         = 0x0296,
    /// Switches to the next available equaliser preset. If issued while the last available preset is selected, switches to the first.
    OTAUCommand_SwitchEQControl                 = 0x0217,
    /// Turns on the Bass Boost effect if it was turned off; turns Bass Boost off if it was on.
    OTAUCommand_ToggleBassBoostControl          = 0x0218,
    /// Turns on the 3D Enhancement effect if it was turned off; turns 3D Enhancement off if it was on.
    OTAUCommand_Toggle3DEnhancementControl      = 0x0219,
    /// Sets a parameter of the parametric equaliser and optionally recalculates the filter coefficients.
    OTAUCommand_SetEQParameter                  = 0x021A,
    /// Gets a parameter of the parametric equaliser.
    OTAUCommand_GetEQParameter                  = 0x029A,
    /// Sets a group of parameters of the parametric equaliser.
    OTAUCommand_SetEQGroupParameter             = 0x021B,
    /// Gets a group of parameters of the parametric equaliser.
    OTAUCommand_GetEQGroupParameter             = 0x029B,
    /// Undocumented
    OTAUCommand_DisplayControl                  = 0x021C,
    /// Puts a Bluetooth device into pairing mode, making it discoverable and connectable.
    OTAUCommand_EnterBluetoothPairingMode       = 0x021D,
    /// Sends an AVRC command to the device
    OTAUCommand_AVRemoteControl                 = 0x021F,
    /// Enables or disables the User-configured parametric equaliser on the device (compare Set EQ Control)
    OTAUCommand_SetUserEQControl                = 0x0220,
    /// Establishes whether User EQ is enabled
    OTAUCommand_GetUserEQControl                = 0x02A0,
    /// Turns on the User EQ if it was turned off; turns User EQ off if it was on.
    OTAUCommand_ToggleUserEQControl             = 0x0221,
    /// Controls the routing of True Wireless Stereo channels
    OTAUCommand_SetTWSAudioRouting              = 0x0224,
    /// Returns the current routing of True Wireless Stereo channels
    OTAUCommand_GetTWSAudioRouting              = 0x02A4,
    /// Controls the volume of True Wireless Stereo output
    OTAUCommand_SetTWSVolume                    = 0x0225,
    /// Returns the current volume setting of True Wireless Stereo
    OTAUCommand_GetTWSVolume                    = 0x02A5,
    /// Trims the volume of True Wireless Stereo output
    OTAUCommand_TrimTWSVolume                   = 0x0226,
    /// Requests the peer in a True Wireless Stereo session to begin Advertising. The command payload length will be 1 if no target address is specified or 8 if a Typed Bluetooth Device Address is specified.
    OTAUCommand_TWSPeerStartAdvertising         = 0x022A,
    
    /// Find my remote command
    OTAUCommand_FindMe                          = 0x022B,
    
    /// Gets the current audio source
    OTAUCommand_GetAudioSource                  = 0x029E,
    /// Set the current audio source
    OTAUCommand_SetAudioSource                  = 0x021E,
    
    /// Get the OTAU Protocol and API version numbers from the device.
    OTAUCommand_GetAPIVersion                   = 0x0300,
    /// Get the current RSSI value for the Bluetooth link from the device. The RSSI is specified in dBm using 2's compliment representation, e.g. -20 = 0xEC.
    OTAUCommand_GetCurrentRSSI                  = 0x0301,
    /// Get the current battery level from the device. Battery level is specified in mV stored as a uint16, e.g. 3,300mV = 0x0CE4.
    OTAUCommand_GetCurrentBatteryLevel          = 0x0302,
    /// Requests the BlueCore hardware, design and module identification.
    OTAUCommand_GetModuleID                     = 0x0303,
    /**
     Requests the application software to identify itself. The acknowledgement payload contains eight octets of application identification optionally followed by nul-terminated human-readable text. The identification information is application dependent; the headset copies fields from the Bluetooth Device ID.
     */
    OTAUCommand_GetApplicationVersion           = 0x0304,
    /// Requests the logic state of the chip PIOs
    OTAUCommand_GetPIOState                     = 0x0306,
    /// Requests the value read by a given analogue-to-digital converter.
    OTAUCommand_ReadADC                         = 0x0307,
    /// Requests the Bluetooth device address of the peer
    OTAUCommand_GetPeerAddress                  = 0x030A,
    /// Requests the status of the last completed DFU operation.
    OTAUCommand_GetDFUStatus                    = 0x0310,
    
    /// Initiate a OTAU Authentication exchange.
    OTAUCommand_AuthenticateRequest             = 0x0501,
    /// Provide authentication credentials
    OTAUCommand_AuthenticateResponse            = 0x0502,
    /// The host can use this command to enable or disable a feature which it is authenticated to use.
    OTAUCommand_SetFeature                      = 0x0503,
    /// The host can use this command to request the status of a feature.
    OTAUCommand_GetFeature                      = 0x0583,
    /// Undocumented
    OTAUCommand_EnableSession                   = 0x0504,
    
    /**
     Initialise a data transfer session.
     The host provides a uint16 Session ID identifying the data session. The Session ID must be used by both host and device in the Host To Device Data and Device To Host Data commands.
     An acknowledgement containing a 'Success' (0x00) command status indicates the device has successfully initialised data transfer for the Session ID.
     If a Session ID outside the valid range, or a duplicate of an existing Session ID is used by the host, the acknowledgement packet will indicate failure with 'Invalid Parameter' (0x05) command status.
     If Data Transfer Setup command is correct, but the device cannot initialise a data session, the acknowledgement packet will indicate failure with 'Failed Insufficient Resources' (0x03) command status.
     If the host is not authenticated it will receive an acknowledgement containing a 'Failed Not Authenticated' (0x02) command status.
     */
    OTAUCommand_DataTransferSetup               = 0x0601,
    /**
     The host uses this command to indicate closure of a data transfer session, providing the Session ID in the packet payload. The device can release any resources required to maintain a data transfer session at this point, as the host must perform another Data Transfer Setup before sending any more data.
     If the Session ID is outside the valid range, or is not an existing open Session ID, the acknowledgement packet will indicate failure with 'Invalid Parameter' (0x05) command status.
     An acknowledgement containing a 'Success' (0x00) command status indicates the device has successfully closed data transfer for the Session ID.
     If the host is not authenticated it will receive an acknowledgement containing a 'Failed Not Authenticated' (0x02) command status.
     */
    OTAUCommand_DataTransferClose               = 0x0602,
    /**
     A host can use this command to transfer data to a device.
     This command can only be used following a successful acknowledgement by the device to a Data Transfer Setup command.
     The host can transfer upto 252 bytes of data in a single packet.
     An acknowledgement containing 'Success' (0x00) command status indicates the host successfully received the data transfer. The device is then permitted to make another transfer.
     */
    OTAUCommand_HostToDeviceData                = 0x0603,
    /**
     A device can use this command to transfer data to the host.
     This command can only be used following a successful acknowledgement by the device to a Data Transfer Setup command.
     The device can transfer upto 252 bytes of data in a single packet.
     An acknowledgement containing 'Success' (0x00) command status indicates the host successfully received the data transfer. The device is then permitted to make another transfer.
     */
    OTAUCommand_DeviceToHostData                = 0x0604,
    /// Retrieves information on a storage partition.
    OTAUCommand_GetStoragePartitionStatus       = 0x0610,
    /// Prepares a device storage partition for access from the host.
    OTAUCommand_OpenStoragePartition            = 0x0611,
    /// Prepares a UART for access from the host.
    OTAUCommand_OpenUART                        = 0x0612,
    /// Writes raw data to an open storage partition.
    OTAUCommand_WriteStoragePartition           = 0x0615,
    /// Writes data to an open stream.
    OTAUCommand_WriteStream                     = 0x0617,
    /// Closes a storage partition.
    OTAUCommand_CloseStoragePartition           = 0x0618,
    /// Mounts a device storage partition for access from the device.
    OTAUCommand_MountStoragePartition           = 0x061A,
    /// Undocumented
    OTAUCommand_GetFileStatus                   = 0x0620,
    /// Closes a file.
    OTAUCommand_OpenFile                        = 0x0621,
    /// Reads data from an open file.
    OTAUCommand_ReadFile                        = 0x0624,
    /// Closes a file.
    OTAUCommand_CloseFile                       = 0x0628,
    /// Indicates to the host that the device wishes to recieve a Device Firmware Upgrade image.
    OTAUCommand_DFURequest                      = 0x0630,
    /// Readies the device to recieve a Device Firmware Upgrade image. The payload will be 8 or 136 octets depending on the message digest type
    OTAUCommand_DFUBegin                        = 0x0631,
    /// Commands the device to install the DFU image and restart.
    OTAUCommand_DFUCommit                       = 0x0633,
    /// Requests the status of the last completed DFU operation.
    OTAUCommand_DFUGetResult                    = 0x0634,
    /// Begins a VM Upgrade session over OTAU, allowing VM Upgrade Protocol packets to be sent using the VM Upgrade Control and VM Upgrade Data commands.
    OTAUCommand_VMUpgradeConnect                = 0x0640,
    /// Ends a VM Upgrade session over OTAU
    OTAUCommand_VMUpgradeDisconnect             = 0x0641,
    /// Tunnels a VM Upgrade Protocol packet
    OTAUCommand_VMUpgradeControl                = 0x0642,
    /// Introduces VM Upgrade Protocol data
    OTAUCommand_VMUpgradeData                   = 0x0643,
    
    /// Requests the device to perform no operation; serves to establish that the OTAU protocol handler is alive.
    OTAUCommand_NoOperation                     = 0x0700,
    /// Requests the values of the device debugging flags.
    OTAUCommand_GetDebugFlags                   = 0x0701,
    /// Sets the values of the device debugging flags.
    OTAUCommand_SetDebugFlags                   = 0x0702,
    /// Retrieves the value of the indicated PS key. Note that the key is interpreted as an index into PSKEY_USR0, ... PSKEY_USR49, PSKEY_DSP0 ... PSKEY_DSP49
    OTAUCommand_RetrievePSKey                   = 0x0710,
    /// Retrieves the value of the indicated PS key. Note that this uses full CSR PS key numbering, not the 0..99 space used by the other PS functions.
    OTAUCommand_RetrieveFullPSKey               = 0x0711,
    /**
     Sets the value of the indicated PS key. Note that the key is interpreted as an index into PSKEY_USR0, ... PSKEY_USR49, PSKEY_DSP0 ... PSKEY_DSP49
     The PS key value is stored in 16-bit words. It is an error to attempt to store an odd number of bytes.
     */
    OTAUCommand_StorePSKey                      = 0x0712,
    /// Flood fill the store to force a defragment at next boot.
    OTAUCommand_FloodPersistentStore            = 0x0713,
    /// Results in a OTAU_DEBUG_MESSAGE being sent up from the OTAU library to the application task. Its interpretation is entirely user defined.
    OTAUCommand_SendDebugMessage                = 0x0720,
    /// Sends an arbitrary message to the onchip application.
    OTAUCommand_SendApplicationMessage          = 0x0721,
    /// Sends an arbitrary message to the Kalimba DSP (essentially KalimbaSendMessage(message, a, b, c, d))
    OTAUCommand_SendKalimbaMessage              = 0x0722,
    /// Retrieves the number of available malloc() slots and the space available for PS keys.
    OTAUCommand_GetMemorySlots                  = 0x0730,
    /// Retrieves the value of the specified 16-bit debug variable.
    OTAUCommand_GetDebugVariable                = 0x0740,
    /// Sets the value of the specified 16-bit debug variable.
    OTAUCommand_SetDebugVariable                = 0x0741,
    /// Removes all authenticated devices from the paired device list and any associated attribute data.
    OTAUCommand_DeletePairedDeviceList          = 0x0750,
    /// Sent to a BLE slave device, causing it to request a new set of connection parameters.
    OTAUCommand_SetBLEConnectionParameters      = 0x0752,
    
    /**
     Hosts register for notifications using the Register Notification command, specifying an Event Type from table below as the first byte of payload, with optional parameters as defined per event in successive payload bytes.
     The host will receive a standard acknowledgement (top-bit set), with the first byte of the payload indicating command status of the event registration, and the second byte indicating the Event Type.
     */
    OTAUCommand_RegisterNotification            = 0x4001,
    /**
     Requests the current status of an event type. For threshold type events where multiple levels may be registered, the response indicates how many notifications are registered. Where an event may be simply registered or not the number will be 1 or 0.
     */
    OTAUCommand_GetNotification                 = 0x4081,
    /**
     A host can cancel event notification by sending a Cancel Notification command, the first byte of payload will be the Event Type being cancelled.
     The cancel event command is acknowledged, in the same manner as for the Register Notification command; byte 1 indicating command status, byte 2 indicating Event Type.
     */
    OTAUCommand_CancelNotification              = 0x4002,
    /**
     Assuming successful registration, the host will asynchronously receive one or more Event Notification command(s) (Command ID 0x4003). The first byte of the Event Notification command payload will be the Event Type code, indicating the notification type. For example, 0x03 indicating a battery level low threshold event notification. Further data in the Event Notification payload is dependent on the notification type and defined on a per-notification basis below.
     The host must send an acknowledgement packet. The acknowledgement packet specifies an Event Notification Command ID with the top-bit set (0xC003). The packet payload has a success command status in the first byte, and the Event Type code as the second byte.
     */
    OTAUCommand_EventNotification               = 0x4003
};

/**
 @enum OTAUCommandStatus - Response to a command
 */
typedef NS_ENUM(NSInteger, OTAUCommandStatus) {
    /// The command succeeded.
    OTAUStatus_Success                          = 0x00,
    /// An invalid Command ID was specified.
    OTAUStatus_FailedNotSupported               = 0x01,
    /// The host is not authenticated to use a Command ID orcontrol a Feature Type.
    OTAUStatus_FailedNotAuthenticated           = 0x02,
    /// The command was valid, but the device could not successfully carry out the command.
    OTAUStatus_FailedInsufficientResources      = 0x03,
    /// The device is in the process of authenticating the host.
    OTAUStatus_Authenticating                   = 0x04,
    /// An invalid parameter was used in the command.
    OTAUStatus_InvalidParameter                 = 0x05,
    /// The device is not in the correct state to process the command.
    OTAUStatus_IncorrectState                   = 0x06,
    /// The command is in progress
    OTAUStatus_InProgress                       = 0x07,
    /// Undocumented
    OTAUStatus_NoStatusAvailable                = 0xFF
};

/**
 @enum OTAUCommandUpdate - OTAU commands
 */
typedef NS_ENUM(NSInteger, OTAUCommandUpdate) {
    OTAUUpdate_Unknown                          = 0x00,
    OTAUUpdate_StartRequest                     = 0x01,
    OTAUUpdate_StartConfirm                     = 0x02,
    OTAUUpdate_DataBytesRequest                 = 0x03,
    OTAUUpdate_Data                             = 0x04,
    OTAUUpdate_SuspendIndicator                 = 0x05,
    OTAUUpdate_ResumeIndicator                  = 0x06,
    OTAUUpdate_AbortRequest                     = 0x07,
    OTAUUpdate_AbortConfirm                     = 0x08,
    OTAUUpdate_ProgressRequest                  = 0x09,
    OTAUUpdate_ProgressConfirm                  = 0x0A,
    OTAUUpdate_TransferCompleteIndicator        = 0x0B,
    OTAUUpdate_TransferCompleteResult           = 0x0C,
    OTAUUpdate_InProgressIndicator              = 0x0D,
    OTAUUpdate_InProgressResult                 = 0x0E,
    OTAUUpdate_CommitRequest                    = 0x0F,
    OTAUUpdate_CommitConfirm                    = 0x10,
    OTAUUpdate_ErrorWarnIndicator               = 0x11,
    OTAUUpdate_CompleteIndicator                = 0x12,
    OTAUUpdate_SyncRequest                      = 0x13,
    OTAUUpdate_SyncConfirm                      = 0x14,
    OTAUUpdate_StartDataRequest                 = 0x15,
    OTAUUpdate_IsValidationDoneRequest          = 0x16,
    OTAUUpdate_IsValidationDoneConfirm          = 0x17,
    OTAUUpdate_SyncAferRebootRequest            = 0x18,
    OTAUUpdate_VersionRequest                   = 0x19,
    OTAUUpdate_VersionConfirm                   = 0x1A,
    OTAUUpdate_VariantRequest                   = 0x1B,
    OTAUUpdate_VariantConform                   = 0x1C,
    OTAUUpdate_HostEraseSquifRequest            = 0x1D,
    OTAUUpdate_HostEraseSquifConfirm            = 0x1E,
    OTAUUpdate_ErrorWarnResponse                = 0x1F
};

/**
 @enum OTAUCommandUpdateResponse - OTAU command responses
 */
typedef NS_ENUM(NSInteger, OTAUCommandUpdateResponse) {
    OTAUUpdateResponse_Success                          = 0x00,
    OTAUUpdateResponse_ErrorUnknownId                   = 0x11,
    OTAUUpdateResponse_ErrorBadLength                   = 0x12,
    OTAUUpdateResponse_ErrorWrongVariant                = 0x13,
    OTAUUpdateResponse_ErrorWrongPartitionNumber        = 0x14,
    OTAUUpdateResponse_ErrorPartitionSizeMismatch       = 0x15,
    OTAUUpdateResponse_ErrorPartitionTypeNotFound       = 0x16,
    OTAUUpdateResponse_ErrorPartitionOpenFailed         = 0x17,
    OTAUUpdateResponse_ErrorPartitionWriteFailed        = 0x18,
    OTAUUpdateResponse_ErrorPartitionCloseFailed        = 0x19,
    OTAUUpdateResponse_ErrorSFSValidationFailed         = 0x1A,
    OTAUUpdateResponse_ErrorOEMValidationFailed         = 0x1B,
    OTAUUpdateResponse_ErrorUpdateFailed                = 0x1C,
    OTAUUpdateResponse_ErrorAppNotReady                 = 0x1D,
    OTAUUpdateResponse_ErrorLoaderError                 = 0x1E,
    OTAUUpdateResponse_ErrorUnexpectedLoaderMessage     = 0x1F,
    OTAUUpdateResponse_ErrorMissingLoaderMessage        = 0x20,
    OTAUUpdateResponse_ErrorBatteryLow                  = 0x21,
    OTAUUpdateResponse_WarnAppConfigVersionIncompatible = 0x80,
    OTAUUpdateResponse_ForceSync                        = 0x81
};

/**
 @enum OTAUEvent - Events that you can recieve notifications for
 */
typedef NS_ENUM(NSInteger, OTAUEvent) {
    OTAUEvent_RSSILowThreshold                  = 0x01,
    OTAUEvent_RSSIHighThreshold                 = 0x02,
    OTAUEvent_BatteryLowThreshold               = 0x03,
    OTAUEvent_BatteryHighThreshold              = 0x04,
    OTAUEvent_DeviceStateChanged                = 0x05,
    OTAUEvent_PioChanged                        = 0x06,
    OTAUEvent_DebugMessage                      = 0x07,
    OTAUEvent_BatteryCharged                    = 0x08,
    OTAUEvent_ChargerConnection                 = 0x09,
    OTAUEvent_CapsenseUpdate                    = 0x0A,
    OTAUEvent_UserAction                        = 0x0B,
    OTAUEvent_SpeechRecognition                 = 0x0C,
    OTAUEvent_AVCommand                         = 0x0D,
    OTAUEvent_RemoteBatteryIndication           = 0x0E,
    OTAUEvent_KeyEvent                          = 0x0F,
    OTAUEvent_DFUState                          = 0x10,
    OTAUEvent_UARTReceivedData                  = 0x11,
    OTAUEvent_VMUpgradeProtocolPacket           = 0x12,
    OTAUEvent_UnknownEvent                      = 0xFF
};

/**
 @enum OTAUCommandFeature - Enable or disable a feature
 */
typedef NS_ENUM(NSInteger, OTAUCommandFeature) {
    OTAUCommandFeature_Enable                   = 0x00,
    OTAUCommandFeature_Disable                  = 0x01
};

/**
 @enum OTAUCommandAction - continue or abort
 */
typedef NS_ENUM(NSInteger, OTAUCommandAction) {
    OTAUCommandAction_Continue                  = 0x00,
    OTAUCommandAction_Abort                     = 0x01
};

/**
 @enum OTAUCommandAction - continue or abort
 */
typedef NS_ENUM(NSInteger, OTAUUpdateResumePoint) {
    OTAUUpdateResumePoint_Start,
    OTAUUpdateResumePoint_Validate,
    OTAUUpdateResumePoint_Reboot,
    OTAUUpdateResumePoint_PostReboot,
    OTAUUpdateResumePoint_Commit
};

/**
 @enum OTAUAVControlOperation - AV commands
 */
typedef NS_ENUM(NSInteger, OTAUAVControlOperation) {
    OTAUAVControlOperation_Power                = 0x40,
    OTAUAVControlOperation_VolumeUp             = 0x41,
    OTAUAVControlOperation_VolumeDown           = 0x42,
    OTAUAVControlOperation_Mute                 = 0x43,
    OTAUAVControlOperation_Play                 = 0x44,
    OTAUAVControlOperation_Stop                 = 0x45,
    OTAUAVControlOperation_Pause                = 0x46,
    OTAUAVControlOperation_SkipForward          = 0x4B,
    OTAUAVControlOperation_SkipBackward         = 0x4C
};

/**
 @enum OTAUAudioSource - Audio sources.
 */
typedef NS_ENUM(NSInteger, OTAUAudioSource) {
    OTAUAudioSourceNone = 0,
    OTAUAudioSourceFM,
    OTAUAudioSourceANALOG,
    OTAUAudioSourceSPDIF,
    OTAUAudioSourceUSB,
    OTAUAudioSourceAG1,
    OTAUAudioSourceAG2,
    OTAUAudioSourceEndOfList
};

/// @class CSROTAUGattCommand encapsulates a data packet containing a frame and some data.
@interface CSROTAUGattCommand : NSObject

/// @brief The raw data of the command
@property (nonatomic) NSMutableData *command;

/// @brief The command type @see //apple_ref/doc/OTAUCommandType
@property (nonatomic) OTAUCommandType command_id;

/// @brief the vendor id
@property (nonatomic) uint16_t vendor_id;

/*!
 @brief Create a command with some data
 @param data The data for the command
 */
- (id)initWithNSData:(NSData *)data;

/*!
 @brief Create a command with a length. Note that the data must be set separately
 @param length The length of the complete command packet
 */
- (id)initWithLength:(NSInteger)length;

/// @brief the length of the packet.
- (NSUInteger)length;

/// @brief the data for the packet
- (NSData *)getPacket;

/*!
 @brief Set the command type
 @param type The command to send. @see //apple_ref/doc/OTAUCommandType
 */
- (void)setCommandId:(OTAUCommandType)type;

/*!
 @brief Get the command type
 @return The command type. @see //apple_ref/doc/OTAUCommandType
 */
- (OTAUCommandType)getCommandId;

/*!
 @brief Set the vendor id
 @param vendor_id The vendor id
 */
- (void)setVendorId:(uint16_t)vendor_id;

/*!
 @brief Get the vendor id
 @return The vendor id
 */
- (uint16_t)getVendorId;

/*!
 @brief Add a payload to a OTAU command
 @param payload The data to send with the command
 */
- (void)addPayload:(NSData *)payload;

/*!
 @brief Return an NSData object containing a copy of the OTAUCommand payload
 */
- (NSData *)getPayload;

/*!
 @brief Determine if a OTAUCommand is an acknowledgement or not
 @return true of the command is an acknowledgement
 */
- (BOOL)isAcknowledgement;

/*!
 @brief Determine if a OTAUCommand is an control command or not
 @return true of the command is an control command
 */
- (BOOL)isControl;

/*!
 @brief Determine if a OTAUCommand is an configuration command or not
 @return true of the command is an configuration command
 */
- (BOOL)isConfiguration;

/*!
 @brief Read the command status
 @return The command status. @see //apple_ref/doc/OTAUCommandStatus
 */
- (OTAUCommandStatus)status;

/*!
 @brief Get event type from notification
 @return The OTAU event. @see //apple_ref/doc/OTAUEvent
 */
- (OTAUEvent)event;

/*!
 @brief Read the status of an OTAU command response
 @return The command response. @see //apple_ref/doc/OTAUCommandUpdate
 */
- (OTAUCommandUpdate)updateStatus;

/*!
 @brief Read the status of an OTAU command response
 @return The command response. @see //apple_ref/doc/OTAUCommandUpdateResponse
 */
- (OTAUCommandUpdateResponse)updateResponse;

@end
