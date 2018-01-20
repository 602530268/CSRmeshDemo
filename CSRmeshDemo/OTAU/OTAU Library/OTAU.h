//
//  OTAU.h
//  OTAU
//
/******************************************************************************
 *  Copyright (C) Cambridge Silicon Radio Limited 2014
 *
 *  This software is provided to the customer for evaluation
 *  purposes only and, as such early feedback on performance and operation
 *  is anticipated. The software source code is subject to change and
 *  not intended for production. Use of developmental release software is
 *  at the user's own risk. This software is provided "as is," and CSR
 *  cautions users to determine for themselves the suitability of using the
 *  beta release version of this software. CSR makes no warranty or
 *  representation whatsoever of merchantability or fitness of the product
 *  for any particular purpose or use. In no event shall CSR be liable for
 *  any consequential, incidental or special damages whatsoever arising out
 *  of the use of or inability to use this software, even if the user has
 *  advised CSR of the possibility of such damages.
 *
 ******************************************************************************/
//
// Over-The-Air-Update Process
//
#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "Discovery.h"

/****************************************************************************/
/*						OTAU Service for Boot & Application					*/
/****************************************************************************/
// service UUID exposed by the Boot module
#define     serviceBootOtauUuid     @"00001010-d102-11e1-9b23-00025b00a5a5"

/****************************************************************************/
/*				 Boot Loader Service and Characteristics                    */
/****************************************************************************/
// OTAU protocol version.
#define characteristicVersionUuid   @"00001011-d102-11e1-9b23-00025b00a5a5"

#define serviceDeviceInfoUuid       @"0000180a-0000-1000-8000-00805f9b34fb"

// Application version
#define characteristicAppVersionUuid   @"00002a28-0000-1000-8000-00805f9b34fb"

//  - Characteristic : Application number to be updated
// Write 0 to switch Application to Boot Loader
// Write 1 for Application 1, 2 for Application 2, etc.
#define characteristicCurrentAppUuid    @"00001013-d102-11e1-9b23-00025b00a5a5"


// Data transfer char UUID
// Set up this char for notifications
#define characteristicDataTransferUuid  @"00001014-d102-11e1-9b23-00025b00a5a5"


// Transfer control char UUID
// Setup this for Notifications
// 1 - Ready
// 2-Transfer In Progress
// 3-Transfer Paused
// 4-Transfer Complete
// 5-Transfer failed
// 6-Transfer Aborted
#define characteristicTransferControlUuid @"00001015-d102-11e1-9b23-00025b00a5a5"

/****************************************************************************/
/* Application Service and characteristics related to OTAU                  */
/****************************************************************************/
// This service exposes Over-the-Air update capabilities of CSR μEnergy applications.
#define serviceApplicationOtauUuid  @"00001016-d102-11e1-9b23-00025b00a5a5"


// Read CS-key char UUID
// Subscribe to kOtaDataTransCharUuid
// Write 1 for Bluetooth Mac address
// Write 2 for Crystal Trim
// Notification will be received on kOtaDataTransCharUuid
#define characteristicGetKeysUuid @"00001017-d102-11e1-9b23-00025b00a5a5"

// Read CS-key block char UUID
// Only used to see if the application supports OTAU v5 library
// This way we determine if we expect to see a OTAU v5 bootloader
// which can be directly queried for relevant CS Keys
#define characteristicGetKeyBlockUuid @"00001018-d102-11e1-9b23-00025b00a5a5"

#define csKeyIndexBluetoothAddress 1
#define csKeyIndexCrystalTrim 2
#define csKeyIndexIdentityRoot 17
#define csKeyIndexEncryptionRoot 18

#define transferControlReady 1
#define transferControlInProgress 2
#define transferControlPaused 3
#define transferControlComplete 4
#define transferControlFailed 5
#define transferControlAbort 6

/****************************************************************************/
/*                  Error reporting typedefs                                */
/****************************************************************************/
typedef enum OtauErrorTypes {
    OTAUErrorFailedQueryDevice = 1000,
    OTAUErrorFailedUpdate,
    OTAUErrorFailedDisconnected,
    OTAUErrorDeviceNotSelected
} OtauErrors;

/****************************************************************************/
/*						OTAU Class Delegates                                */
/****************************************************y************************/
@protocol OTAUDelegate <NSObject>
@optional
-(void) didUpdateProgress: (uint8_t) percent;
-(void) completed:(NSString *) message;
-(void) statusMessage:(NSString *)message;
-(void) otauError:(NSError *) error;
-(void) didUpdateVersion: (uint8_t) otauVersion;
-(void) didUpdateAppVersion: (NSString*) appVersion;
-(void) didUpdateBtaAndTrim: (NSData*) btMacAddress :(NSData*) crystalTrim;
-(void) didGetCsKeyValue: (NSData *) value;
-(void) didChangeConnectionState: (bool) isConnected;
-(void) didChangeMode: (bool) isBootMode;
-(void) didUpdateChallengeResponse: (bool) challengeEnabled;
@end


/****************************************************************************/
/*						OTAU Class Interface                                */
/****************************************************************************/
@interface OTAU : NSObject <CBPeripheralDelegate, DiscoveryDelegate>


@property (strong, nonatomic) id<OTAUDelegate> OTAUDelegate;

+ (id) sharedInstance;

-(void) startOTAU: (NSString *) firmwareFilepath;

-(void) abortOTAU: (CBPeripheral *) peripheral;

-(void) reportError: (NSInteger) errorCode;

-(bool) parseCsKeyJson: (NSString*) csKeyJsonFile;

-(void) initOTAU: (CBPeripheral *) peripheral;

-(void) getCsKey: (uint8_t) csKeyIndex;
@end
