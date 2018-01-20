//
//  OTAU.m
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
// Transfer the given Application image to the given device replacing the on Chip Application.
//
// OTAU Interface methods
//  - initOTAU
//  - parseCsKeyJson
//  - startOTAU
//  - abortOTAU
//  - getCsKey
//

#import "OTAU.h"
#import "ApplicationImage.h"
#import "CBPeripheral+CallbackQ.h"
#import "PCM.h"
#import "AppDelegate.h"
#import <CommonCrypto/CommonCrypto.h>



/****************************************************************************/
/*               Ble Delegate identifier                                    */
/****************************************************************************/
#define kDidDiscoverServices                @"didDiscoverServices"
#define kDidDiscoverCharacteristicsForService   @"didDiscoverCharacteristicsForService"
#define kDidUpdateNotificationStateForCharacteristic @"didUpdateNotificationStateForCharacteristic"
#define kDidWriteValueForCharacteristic     @"didWriteValueForCharacteristic"
#define kDidUpdateValueForCharacteristic    @"didUpdateValueForCharacteristic"
#define kPeripheralDidUpdateName            @"peripheralDidUpdateName"
#define kDidModifyServices                  @"didModifyServices"
#define kBleDidDiscoverPeripheral           @"BleDidDiscoverPeripheral"
#define kBleDidConnectPeripheral            @"BleDidConnectPeripheral"
#define kBleDidDiscoverServices             @"BleDidDiscoverServices"
#define kBleDidInvalidateServices           @"BleDidInvalidateServices"
#define kBleDidDisconnectPeripheral         @"BleDidDisconnectPeripheral"

/****************************************************************************/
/*              Private Methods and Properties                              */
/****************************************************************************/
@interface OTAU () {
    // This flag changes the behaviour of didWriteValueForCharacteristic when a transfer is in progress.
    bool transferInProgress;
    // Used to keep track of number of calls to didWriteValueForCharacteristic when a transfer is in progress.
    NSInteger transferCount;
    // The total number of expected calls to didWriteValueForCharacteristic when a transfer is in progress.
    NSInteger transferTotal;
    // The percentage of the transfer complete when a transfer is in progress.
    uint8_t transferPercent;
    // Flag that indicates when an OTAU operation is in progress. This includes reading CS keys.
    bool otauRunning;
    // Flag that indicates that the user selected abort during the OTA update.
    bool didAbort;
    // The application number to update.
    NSInteger   applicationNumber;
    // When a disconnect is expected (e.g. when switching mode) set waitForDisconnect to avoid a call to Abort.
    bool waitForDisconnect;
    // Discovered OTAU version.
    uint8_t otauVersion;
    // Discovered application version.
    NSString *appVersion;
    // Flag that indicates if challenge response is enabled on target.
    bool targetHasChallengeResponse;
    // Registered application that will receive delegate callbacks from this module.
    AppDelegate *appDelegate;

    
}

@property (strong, nonatomic) CBPeripheral *targetPeripheral;
@property (strong, nonatomic) NSString *sourceFilename;
@property (strong, nonatomic) NSData *targetFilename;
@property (strong, nonatomic) NSData *crystalTrim, *btMacAddress, *iRoot, *eRoot;
@property (strong, nonatomic) NSDictionary* csKeyDb;
@property (strong, nonatomic) NSString* peripheralBuildId;
@end

/****************************************************************************/
/*              OTAU implementation                                         */
/****************************************************************************/

@implementation OTAU

@synthesize OTAUDelegate;
@synthesize targetPeripheral, sourceFilename, targetFilename;
// CS key cache. These should be cleared when an OTA update is completed.
@synthesize crystalTrim, btMacAddress, iRoot, eRoot;
// Dictionary for looking up cs key offsets.
@synthesize csKeyDb;
// Build id of target peripheral, uesd when looking up cs key offsets.
@synthesize peripheralBuildId;

/****************************************************************************/
/*								Initialise                                  */
/****************************************************************************/
// We expect there to be only the one instance hence the use of singleton
+ (id) sharedInstance {
    static OTAU	*this	= nil;
    
    if (!this)
        this = [[OTAU alloc] init];
    
    return this;
}


- (id) init {
    self = [super init];
    otauRunning = NO;
    otauVersion = 0;
    appVersion = nil;
    appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    

    return self;
}

/****************************************************************************/
/*								Public Interface                            */
/****************************************************************************/

//=========================================================================
// Set the peripheral and discover the version and mode in a new thread.
// This must be called before reading cs keys and before calling startOTAU.
//
-(void) initOTAU:(CBPeripheral *) peripheral {
    targetPeripheral = peripheral;
    targetPeripheral.delegate = self;
    peripheralBuildId = nil;
    
    CBUUID *uuid = [CBUUID UUIDWithString:serviceApplicationOtauUuid];
    CBUUID *bl_uuid = [CBUUID UUIDWithString:serviceBootOtauUuid];
    CBUUID *devInfoUuid = [CBUUID UUIDWithString:serviceDeviceInfoUuid];
    
    for (CBService *service in targetPeripheral.services) {
        if ([service.UUID isEqual:uuid] || [service.UUID isEqual:bl_uuid]) {
            appDelegate.targetService = service;
        }
        else if ([service.UUID isEqual:devInfoUuid]) {
            appDelegate.devInfoService = service;
        }
    }
    
    [[Discovery sharedInstance] setDiscoveryDelegate:self];
    
    [targetPeripheral deleteQueue];
    
    if (!otauRunning) {
        [self performSelectorInBackground:@selector(initMain) withObject: nil];
    }
}

//=========================================================================
// Parse and cache the cskey_db json file so that it can later be accessed
// by getCsKeyDbEntry.
//
-(bool) parseCsKeyJson : (NSString*) csKeyXmlFile {
    NSString* filePath = [[NSBundle mainBundle] pathForResource:csKeyXmlFile ofType:@"json"];
    NSError *error = nil;
    
    NSData *JSONData = [NSData dataWithContentsOfFile:filePath options:NSDataReadingMappedIfSafe error:&error];
    if (error != nil) {
        return NO;
    }
    // Create object from JSON data.
    csKeyDb = [NSJSONSerialization JSONObjectWithData:JSONData options:NSJSONReadingAllowFragments error:&error];
    if (error != nil) {
        return NO;
    }
    return YES;
}

//===========================================================================
// Set up the OTAU process, start it in a new thread, then return to caller.
// The OTAU process is run in a seperate thread as it involves putting the thread to sleep
// while waiting for a callback.
//
-(void) startOTAU:(NSString *) firmwareFilepath {
    if (targetPeripheral == nil) {
        [self terminateOTAU:@"Failed: start OTAU" : OTAUErrorDeviceNotSelected];
    }
    sourceFilename = firmwareFilepath;
    applicationNumber = 1;
    transferInProgress = NO;
    didAbort = NO;
    [[Discovery sharedInstance] setDiscoveryDelegate:self];
    
    if (!otauRunning)
        [self performSelectorInBackground:@selector(otauMain) withObject:nil];
}

//=========================================================================
// Abort a running OTAU process.
// The background thread is stopped by sent a message telling it to terminate, rather than
// killing it as this allows the thread to clean up, resulting in a controlled and orderly thread kill.
//
-(void) abortOTAU:(CBPeripheral *) peripheral {
    didAbort = YES;
}

//============================================================================
// Public interface to get a cs key.
//
-(void) getCsKey: (uint8_t) csKeyIndex {
    if (!otauRunning) {
        [self performSelectorInBackground:@selector(getCsKeySelector:) withObject:[NSNumber numberWithUnsignedInt:csKeyIndex]];
    }
}

/****************************************************************************/
/*   					Public Interface Helper methods                     */
/* Functions executed on a new thread to perform work for public methods    */
/****************************************************************************/

//===========================================================================
// Discover version and important CS keys and notify delegate.
//
-(BOOL) initMain {
    bool success = NO;
    do {
        // Find OTAU and application version.
        if (![self discoverOtauVersion]) {
            break;
        }
        // Failing to discover application version is not fatal.
        // It may not be supported so continue anyway.
        [self discoverAppVersion];
        // Make sure we don't use cached values as we are initialising.
        [self clearOtauKeys];
        // Get BT address, crystal trim, identity root and encryption root.
        if (![self getOtauKeys]) {
            break;
        }
        success = YES;
    } while(0);
    
    if (!success && !otauRunning) {
        // If this was the first initialise after selecting a device
        // then disconnect and report error to view controller.
        // The other case is when initMain is called after completing an
        // update. That error is handled within otauMain.
        [[Discovery sharedInstance] disconnectPeripheral: targetPeripheral];
        targetPeripheral.delegate = nil;
        [[Discovery sharedInstance] setDiscoveryDelegate:nil];

        [self reportError: OTAUErrorFailedQueryDevice];
    }
    
    return (success);
}

//============================================================================
// Function to be called from a selector to get a CS key on a new thread
// and post the result to the mainQueue.
//
-(void) getCsKeySelector : (NSNumber*) csKey {
    uint8_t csKeyIndex = [csKey unsignedIntValue];
    NSData *result = [self getCsKeyMain: csKeyIndex];
    if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(didGetCsKeyValue:)]) {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [OTAUDelegate didGetCsKeyValue: result];
        }];
    }
}



/****************************************************************************/
/*   					    CS Key methods                                  */
/****************************************************************************/

//=========================================================================
// Look up a cs key db entry by build id and name. Must have previously called parseCsKeyJson.
// Returns a dictionary with fields ID, OFFSET and LENGTH or nil if buildId or keyId not found.
//
-(NSDictionary*) getCsKeyDbEntry : (NSString*) buildId : (uint8_t) keyId {
    if (csKeyDb == nil) {
        return nil;
    }
    NSString* keyIdAsString = [NSString stringWithFormat:@"%d", keyId];
    NSArray *allBuilds = [[csKeyDb objectForKey: @"PSKEY_DATABASE"] objectForKey:@"PSKEYS"];
    for (NSDictionary *build in allBuilds) {
        if ([build[@"BUILD_ID"] isEqualToString:buildId]) {
            NSArray *keysForThisBuild = build[@"PSKEY"];
            for (NSDictionary *csKey in keysForThisBuild) {
                if ([csKey[@"ID"] isEqualToString: keyIdAsString]) {
                    return csKey;
                }
            }
        }
    }
    return nil;
}

//============================================================================
// Main function to get a cs key that is called locally and from
// public function getCsKey which will run it in the background.
// Returns the value of the cs key as NSData or nil if the read failed.
//
-(NSData*) getCsKeyMain : (uint8_t) csKeyIndex {
    NSData *result = nil;
    
    bool otauRunningOld = otauRunning;

    if (targetPeripheral && otauVersion >= 4) {
        
        otauRunning = YES;
        
        do {
            if (targetPeripheral.state != CBPeripheralStateConnected) {
                if (![self connect:serviceApplicationOtauUuid]) {
                    break;
                }
            }
            
            targetPeripheral.delegate = self;
            
            // There are two different Characteristics used to get cs keys from the target
            // device. The legacy characteristic only supports a limited number of cs keys.
            // The following code will use the version and mode to determine which CS
            // key characteristic is supported and set the flag useLegacy.
            bool useLegacy = NO;
            if ([appDelegate.peripheralInBoot boolValue]) {
                if (otauVersion >= 5) {
                    // If in bootloader and v5 then use getCsKeyLegacy (if index in range).
                    useLegacy = YES;
                }
                else {
                    // If in bootloader and v4 then no way to get keys.
                    break;
                }
            }
            else {
                if (otauVersion == 4) {
                    // If in bootloader and v5 then use getCsKeyLegacy (if index in range).
                    useLegacy = YES;
                }
                // Otherwise we will use getCsKeyFromBlock
            }
            if (useLegacy) {
                bool success = YES;
                if (otauVersion < 5) {
                    // Only version 4 supports notify when using legacy characteristic.
                    success = [self createNotifyForCSKey];
                }
                if (success) {
                    PCM *pcm = [self getCsKeyLegacy:(otauVersion >= 5) : [appDelegate.peripheralInBoot boolValue] : csKeyIndex];
                    if (pcm && (pcm.PCMError == NULL)) {
                        result = pcm.PCMCharacteristic.value;
                    }
                }
            }
            else {
                if ([self createNotifyForCSKey]) {
                    result = [self getCsKeyFromBlock:csKeyIndex];
                }
                else {
                    [self statusMessage: @"Failed to register for cs key notification\n"];
                }
            }
            break;
        } while(0);
    }
    otauRunning = otauRunningOld;
    return result;
}

//============================================================================
// Get a CS key value using the legacy "Read CS Key" characteristic (1017).
// Only supports a limited number of keys.
//
-(PCM *) getCsKeyLegacy :(BOOL) isOTAUv5 :(BOOL) isBootMode :(uint8_t) csKeyIndex {
    PCM *retVal = NULL;
    
    CBUUID *getCsKeyCharUuid = [CBUUID UUIDWithString:characteristicGetKeysUuid];
    
    CBUUID *dataTransferCharUuid = [CBUUID UUIDWithString:characteristicDataTransferUuid];
    
    CBCharacteristic *dataTransferCharacteristic = NULL;
    CBCharacteristic *getCsKeyCharacteristic = NULL;
    
    for (CBCharacteristic *characteristic in appDelegate.targetService.characteristics) {
        if ([characteristic.UUID isEqual:dataTransferCharUuid]) {
            // Is the data transfer characterisitic found, update pointer
            dataTransferCharacteristic = characteristic;
        }
        else if ([characteristic.UUID isEqual:getCsKeyCharUuid]) {
            // Is the Read CsKey characteristic discovered
            getCsKeyCharacteristic = characteristic;
        }
        if ( getCsKeyCharacteristic && dataTransferCharacteristic ) {
            // If both the required characterisitics have been discovered
            // Ask for the key specified in the index.
            NSData *csCommand = [NSData dataWithBytes:(void *)&csKeyIndex
                                               length:sizeof(csKeyIndex)];
            [targetPeripheral writeValue:csCommand
                       forCharacteristic:getCsKeyCharacteristic
                                    type:CBCharacteristicWriteWithResponse];
            if ( isOTAUv5 && isBootMode ) {
                PCM *pcm = [self waitForDelegate:kDidWriteValueForCharacteristic];
                if (pcm == nil) {
                    [self statusMessage: @"Failed: No write response requesting cs key from boot loader\n"];
                    break;
                }
                /* OTAU v5 bootloader doesn't support notifications on data transfer
                 characterisitic. We need to read the value */
                [targetPeripheral readValueForCharacteristic:dataTransferCharacteristic];
            }
            if (otauRunning) {
                NSLog(@"OTAU is running");
            }
            else {
                NSLog(@"OTAU is not running");
            }
            retVal = [self waitForDelegate:kDidUpdateValueForCharacteristic];
            break;
        }
    }
    
    return retVal;
}

//============================================================================
// Get any cs key using the read from block characteristic.
// Must have previously called parseCsKeyJson to load the cs key database.
// OTAv5 application and newer only. Not supported in bootloader and not supported in v4.
// Returns the value of the cs key as NSData or nil if the read failed.
//
-(NSData *) getCsKeyFromBlock : (uint8_t) csKeyId {
    PCM *pcm = NULL;
    
    CBUUID *getCsBlockUuid = [CBUUID UUIDWithString:characteristicGetKeyBlockUuid];
    CBUUID *dataTransferCharUuid = [CBUUID UUIDWithString:characteristicDataTransferUuid];
    
    CBCharacteristic *dataTransferCharacteristic = NULL;
    CBCharacteristic *csBlockCharacteristic = NULL;
    
    for (CBCharacteristic *characteristic in appDelegate.targetService.characteristics) {
        if ([characteristic.UUID isEqual:dataTransferCharUuid]) {
            // Is the data transfer characterisitic found, update pointer
            dataTransferCharacteristic = characteristic;
        }
        else if ([characteristic.UUID isEqual:getCsBlockUuid]) {
            // Is the Read CsKey characteristic discovered
            csBlockCharacteristic = characteristic;
        }
        if ( csBlockCharacteristic && dataTransferCharacteristic ) {
            // If both the required characterisitics have been discovered:
            
            // First get build id if we don't have it already
            // (this is reset to nil every time init is called after connecting to a new device).
            if (peripheralBuildId == nil) {
                NSLog(@"Getting build id");
                Byte bytes []  = { 0x00, 0x00, 0x02, 0x00 };
                NSMutableData *buildIdCommand = [NSMutableData dataWithBytes:bytes length:4];
                
                [targetPeripheral writeValue:buildIdCommand
                           forCharacteristic:csBlockCharacteristic
                                        type:CBCharacteristicWriteWithResponse];
                
                pcm = [self waitForDelegate:kDidWriteValueForCharacteristic];
                
                if (pcm == nil) {
                    [self statusMessage:@"Failed: no write response when trying to read build id\n"];
                    break;
                }
                else {
                    NSLog(@"Requested build id ok");
                }
                
                pcm = [self waitForDelegate:kDidUpdateValueForCharacteristic];
                
                if (pcm && (pcm.PCMError == NULL)) {
                    NSData *data = [NSData dataWithData: pcm.PCMCharacteristic.value];
                    uint16_t *build = (uint16_t *)[data bytes];
                    if (build!=nil) {
                        peripheralBuildId = [NSString stringWithFormat:@"%d", *build];
                        NSLog(@"Build id is %@", peripheralBuildId);
                    }
                    pcm = nil;
                }
            }
            
            if (peripheralBuildId != nil) {
                NSDictionary *csKeyEntry = [self getCsKeyDbEntry:peripheralBuildId :csKeyId];
                NSLog(@"Cs key entry is %@", csKeyEntry);
                if (csKeyEntry != nil) {
                    
                    uint16_t offset = [csKeyEntry[@"OFFSET"] intValue];
                    uint16_t lenBytes = [csKeyEntry[@"LENGTH"] intValue] * 2;

                    NSMutableData *csCommand = [[NSMutableData alloc] init];
                    [csCommand appendBytes:(void *)&offset length:sizeof(offset)];
                    [csCommand appendBytes:(void *)&lenBytes length:sizeof(lenBytes)];
                    
                    
                    [targetPeripheral writeValue:csCommand
                               forCharacteristic:csBlockCharacteristic
                                            type:CBCharacteristicWriteWithResponse];
    
                    pcm = [self waitForDelegate:kDidUpdateValueForCharacteristic];
                }
                else {
                    [self statusMessage:@"Failed: Build id or cs key id not found in cs key db\n"];
                }
            }
            else {
                [self statusMessage:@"Failed: Could not read build id\n"];
            }
            break;
        }
    }
    
    NSData *result = NULL;
    if (pcm && (pcm.PCMError == NULL)) {
        result = [NSData dataWithData: pcm.PCMCharacteristic.value];
    }
    else if (pcm) {
        NSLog(@"Error is %@", pcm.PCMError.localizedDescription);
    }
    return result;
}

//============================================================================
// Create notification for reading CS key value.
// Returns (YES) if notify was set or had previously been set.
// Returns (NO) if setting the notification failed.
//
-(BOOL) createNotifyForCSKey {
    NSLog(@"otauCreateNotifyForCSKey");
    CBUUID *uuid;
    if ([appDelegate.peripheralInBoot boolValue])
        uuid = [CBUUID UUIDWithString:characteristicTransferControlUuid];
    else
        uuid = [CBUUID UUIDWithString:characteristicDataTransferUuid];
    

    for (CBCharacteristic *characteristic in appDelegate.targetService.characteristics) {
        
        if ([characteristic.UUID isEqual:uuid]) {
            // Subscribe to Data transfer Char so we can be notified of CS key
            NSLog(@" -SetNotify for %@",characteristic.UUID);
            if (!characteristic.isNotifying) {
                [targetPeripheral setNotifyValue:YES forCharacteristic:characteristic];
                
                PCM *pcm = [self waitForDelegate:kDidUpdateNotificationStateForCharacteristic];
                if (pcm && ( pcm.PCMError == NULL ) )
                    return (YES);
                else
                    break;
            }
            else {
                NSLog(@"Notify already set");
                return (YES);
            }
        }
    }
    return (NO);
}

//============================================================================
// Get the keys that are needed for OTAU.
// That is Bluetooth address, crystal trim, identity root and encryption root.
// Returns (YES) if the keys were read OK, or there was a cached value available.
// Returns (NO) if we failed to get the keys and there are were no cached values.
//
-(BOOL) getOtauKeys {
    [self statusMessage:@"Start: Get CS keys.\n"];
    if (!targetPeripheral || targetPeripheral.state != CBPeripheralStateConnected || otauVersion == 0) {
        return (NO);
    }
    [self getBtMacAddress];
    if (btMacAddress == nil) {
        return (NO);
    }
    NSLog(@"Mac address: %@", btMacAddress);
    [self getCrystalTrim];
    if (crystalTrim == nil) {
        return (NO);
    }
    NSLog(@"Trim: %@", crystalTrim);
    [self getIdentityRoot];
    if (iRoot == nil) {
        return (NO);
    }
    NSLog(@"Identity root: %@", iRoot);
    [self getEncryptionRoot];
    if (eRoot == nil) {
        return (NO);
    }
    NSLog(@"Encryption root:%@:", eRoot);
    
    // If a delegate is registered with us then notify it about the address and trim.
    if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(didUpdateBtaAndTrim::)]) {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [OTAUDelegate didUpdateBtaAndTrim: btMacAddress: crystalTrim];
        }];
    }
    
    return (YES);
}

//============================================================================
// Clear cached OTAU keys
//
-(void) clearOtauKeys {
    btMacAddress = nil;
    crystalTrim = nil;
    iRoot = nil;
    eRoot = nil;
}

//============================================================================
// Retrieve bluetooth mac address from cs key.
// Address is saved in btMacAddress variable.
// Return value indicates success or failure.
//
-(BOOL) getBtMacAddress {
    NSData *result = [self getCsKeyMain: csKeyIndexBluetoothAddress];
    if (result != nil) {
        if (otauVersion < 5) {
            btMacAddress = [result subdataWithRange:NSMakeRange(0, 6)];
        }
        else {
            // For version 5 and above, bluetooth address is returned in reverse order so we must reverse.
            Byte b[] = {0, 0, 0, 0, 0, 0};
            NSUInteger length = 6;
            if ( length > result.length ) {
                length = result.length;
            }
            for ( NSUInteger i = 0; ( i < length ); ++i ) {
                NSRange range = {length - i - 1, 1};
                [result getBytes:&b[i] range:range];
            }
            btMacAddress = [NSData dataWithBytes:b length:length];
        }
        return (YES);
    }
    else {
        NSLog(@"Failed: Get BT Mac address");
    }
    
    return (NO);
}

//============================================================================
//
-(BOOL) getCrystalTrim  {
    NSData *result = [self getCsKeyMain: csKeyIndexCrystalTrim];
    if (result != nil) {
        crystalTrim = [result subdataWithRange:NSMakeRange(0, result.length)];
        return (YES);
    }
    else {
        NSLog(@"Failed: Get Crystal Trim");
    }
    
    return (NO);
}

//============================================================================
//
-(BOOL) getIdentityRoot {
    NSData *result = [self getCsKeyMain: csKeyIndexIdentityRoot];
    if (result != nil) {
        iRoot = [result subdataWithRange:NSMakeRange(0, result.length)];
        return (YES);
    }
    else {
        NSLog(@"Failed: Get Identity Root");
        return (NO);
    }
}

//============================================================================
//
-(BOOL) getEncryptionRoot {
    NSData *result = [self getCsKeyMain: csKeyIndexEncryptionRoot];
    if (result != nil) {
        eRoot = [result subdataWithRange:NSMakeRange(0, result.length)];
        return (YES);
    }
    else {
        NSLog(@"Failed: Get Encryption Root");
        return (NO);
    }
}



/****************************************************************************/
/*								Main OTAU transfer                          */
/****************************************************************************/

//============================================================================
// Main OTAU function.
// Call terminateOTAU if a timeout occurs.
//
-(void) otauMain {
    [self statusMessage:@"Start: Application Update\n"];
    
    otauRunning = YES;
    targetPeripheral.delegate = self;
    
    
    BOOL completedSuccessfuly = NO;
    
    do {
        // Connect to peripheral, if required
        if (targetPeripheral && targetPeripheral.state == CBPeripheralStateConnecting) {
            // stop connecting
            
            if (![self stopConnecting])
                break;
        }
        
        if (didAbort) {
            break;
        }

        if (targetPeripheral && targetPeripheral.state != CBPeripheralStateConnected) {
            // then discover the characteristics for the given service
            if (![self connect:serviceApplicationOtauUuid]) {
                break;
            }
        }
        
        if (didAbort) {
            break;
        }

        // Get OTAU version.
        if (![self discoverOtauVersion]) {
            break;
        }
        
        if (didAbort) {
            break;
        }

        [self updateProgress: 25];
        

        // If the device is not already in boot-mode, then switch it to boot mode and perform
        // challenge response if required.
        if (![appDelegate.peripheralInBoot boolValue]) {
            
            // Switch device to Boot mode and discover Services and Characteristics.
            [self statusMessage:@"Start: Enter Boot\n"];
            if ([self enterBoot]==NO ||
                otauRunning == NO) {
                [self statusMessage:@"Failed: Enter Boot\n"];
                break;
            }
            [self statusMessage:@"Success: Enter Boot\n"];
            
            if (didAbort) {
                break;
            }
            
            // Now that we are in boot check the version of the boot loader.
            if (![self discoverOtauVersion]) {
                break;
            }
            
            if (didAbort) {
                break;
            }
            
            // Find out if challenge response is supported
            if (![self detectChallengeResponse]) {
                break;
            };
            
            if (didAbort) {
                break;
            }
            
            // Expect Challenge response.
            if ([self hostValidation]==NO) {
                break;
            }
            
            if (didAbort) {
                break;
            }
            
            // We have switched mode so we should try to read the keys again.
            // This is not possible for versions earlier than 5 though.
            if (otauVersion >= 5) {
                // We want to ensure that we get the boot keys in case they
                // are different to the application keys. So clear the cached keys first.
                [self clearOtauKeys];
                if (![self getOtauKeys]) {
                    // Couldn't get keys so fail.
                    [self statusMessage:@"Failed: Get CS keys.\n"];
                    break;
                }
            }
        }
        else if (btMacAddress == nil || crystalTrim == nil || iRoot == nil || eRoot == nil) {
            // If we were already in boot and don't have all the required keys then try to get them.
            if (![self getOtauKeys]) {
                // Couldn't get keys so fail.
                [self statusMessage:@"Failed: Get CS keys.\n"];
                break;
            }
        }
        
        if (didAbort) {
            break;
        }
        
        // 50% on the progress bar indicates All OTAU preperation successfuly completed and just the
        // image file to update and transfer to do.
        [self updateProgress: 50];
        
        // Prepare the application file using the OTAU keys.
        // Update application image file with read values of
        // crystal trim, BT address, identity root and encryption root,
        // then generate CRC for data and header blocks.
        [self statusMessage:@"Start: Prepare Application image\n"];
        NSData *newApplication = [[ApplicationImage sharedInstance] prepareFirmwareWith:crystalTrim
                                                                                    and:btMacAddress
                                                                                    and:iRoot
                                                                                    and:eRoot
                                                                                forFile:sourceFilename];
        [self statusMessage:@"Success: Prepare Application image\n"];
        
        if (didAbort) {
            break;
        }
        
        // Transfer image file to Device, replacing on chip application.
        if (![self transferNewApplication:newApplication]) {
            if (!didAbort) {
                [self statusMessage:@"Failed: Transfer image\n"];
            }
            else {
                NSLog(@"Aborted during transfer");
            }
            break;
        }
        
        completedSuccessfuly = YES;
        
        // Wait for Disconnect - From this it can be inferred that the Application successfuly transferred
        // Note: There is no timeout, user must use the Abort button to quit the operation
        waitForDisconnect = YES;
        NSLog (@"Start waitforDisconnect");
        while (waitForDisconnect);
        NSLog (@"End waitforDisconnect");
        [NSThread sleepForTimeInterval: 2];
        [self statusMessage:@"Success: Image transferred\n"];
        
    } while (0); // one time loop. So that we can use break to terminate instead of Goto.
    
    if (!completedSuccessfuly) {
        if (didAbort) {
            [self terminateOTAU:@"OTA update aborted" :0];
        }
        else {
            [self terminateOTAU:@"Failed: Application Update" :OTAUErrorFailedUpdate];
        }
        transferInProgress = NO;
    }
    else {
        if (![self connect:serviceApplicationOtauUuid]) {
            [self terminateOTAU:@"Failed: Could not reconnect" :OTAUErrorFailedUpdate];
        }
        else {
            if (![self initMain]) {
                [self terminateOTAU:@"Failed: Could not query device" :OTAUErrorFailedUpdate];
            }
            [self statusMessage:@"Success: Application Update\n\n"];
            [self terminateOTAU:@"Success: Application Update" :0];
        }
    }
    otauRunning = NO;
}

/****************************************************************************/
/*								OTAU Helper Methods                         */
/*                          Functions used by otauMain                      */
/****************************************************************************/

//============================================================================
//
-(bool) discoverOtauVersion {
    [self statusMessage:@"Start: Get version.\n"];
    
    // We want to restore the original value of otau running afterwards.
    bool otauRunningOld = otauRunning;
    otauRunning = YES;
    bool returnVal = NO;
    do {
        // Check the version
        if (![self checkForCharacteristic: characteristicVersionUuid]) {
            // Check if application supports OTAU v5 characteristics (i.e. to look for
            // a possibility that we may have a OTAU v5 bootloader)
            if (![self checkForCharacteristic:characteristicGetKeyBlockUuid] || otauRunning == NO) {
                otauVersion = 4;
            }
            else {
                otauVersion = 5;
            }
            returnVal = YES;
        }
        else {
            // Read OTAU version using version characteristic. This is supported in v6+ application and boot loader.
            // In versions prior to v6 it is only supported in the boot loader.
            
            NSData* otauVer = [self readCharacteristic:characteristicVersionUuid
                                           fromService: appDelegate.targetService];
            if ( !otauVer ) {
                [self statusMessage:@"Failed: Read Bootloader Version Characteristics\n"];
                
                break;
            }
            [otauVer getBytes:&otauVersion length:sizeof(otauVersion)];
            
            // When the device switches back to application but doesn't provide GATT status changed
            // indication, iOS still thinks the device is in the bootloader. It could be a reason why
            // we get to this point. In this case the value read into the OTAU version number
            // may possibly be invalid (as the same handle may have been used by something else in
            // the application). So the least we can do is check if we have a valid OTAU bootloader
            // version and report to the user if an invalid value is found.
            if (otauVersion < 4)  {
                [self statusMessage:[NSString stringWithFormat:@"Failed: Invalid bootloader version specified: %hhu\n", otauVersion]];
                
                break;
            }
            [self statusMessage:@"Success: Read Bootloader Version Characteristics\n"];
            returnVal = YES;
        }
    } while (0); // one time loop. So that we can use break to terminate instead of Goto.
    
    // Restore original value.
    otauRunning = otauRunningOld;
    
    // If a delegate is registered with us then notify it about the version read.
    if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(didUpdateVersion:)]) {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [OTAUDelegate didUpdateVersion: otauVersion];
        }];
    }
    
    return returnVal;
}

//============================================================================
//
-(bool) discoverAppVersion {
    [self statusMessage:@"Start: Get app version.\n"];
    
    // We want to restore the original value of otau running afterwards.
    bool otauRunningOld = otauRunning;
    otauRunning = YES;
    
    bool returnVal = NO;
    
    CBUUID *uuid = [CBUUID UUIDWithString:characteristicAppVersionUuid];
    NSLog(@"Check against: %@", uuid.UUIDString);
    if (appDelegate.devInfoService != nil) {
        NSData* appVer = [self readCharacteristic:characteristicAppVersionUuid fromService: appDelegate.devInfoService];
        if ( !appVer ) {
            [self statusMessage:@"Failed: Read Application Version Characteristics\n"];
        }
        else {
            appVersion = [[NSString alloc] initWithData: appVer encoding:NSASCIIStringEncoding];
            returnVal = YES;
        }
    }

    // Restore original value.
    otauRunning = otauRunningOld;
    
    // If a delegate is registered with us then notify it about the version read.
    if (returnVal == YES && OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(didUpdateAppVersion:)]) {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [OTAUDelegate didUpdateAppVersion: appVersion];
        }];
    }
    
    return returnVal;
}

//============================================================================
// Detect if challenge response is enabled on the target by reading the transfer
// control characteristic.
// If this value is zero then challenge response is enabled.
-(BOOL) detectChallengeResponse {
    [self statusMessage:@"Start: Detect if target challenge response enabled.\n"];
    
    bool returnVal = NO;
    do {
        if ([self checkForCharacteristic: characteristicTransferControlUuid]) {
            NSData* value = [self readCharacteristic:characteristicTransferControlUuid fromService: appDelegate.targetService];
            if (!value) {
                [self statusMessage:@"Failed: Detect challenge response setting.\n"];

                break;
            }
            uint8_t intVal = 0;
            [value getBytes:&intVal length:1];
            targetHasChallengeResponse = (intVal == 0 ? YES : NO);
            
            if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(didUpdateChallengeResponse:)]) {
                [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                    [OTAUDelegate didUpdateChallengeResponse: targetHasChallengeResponse];
                }];
            }
            
            returnVal = (YES);
        }
    } while (0); // one time loop. So that we can use break to terminate instead of goto.
    
    return returnVal;
}

//============================================================================
// Set device to boot mode so that we can acces the relevant service for application transfer
// 1. issue the command to Enter Boot Mode, then sleep for 2 seconds.
// 2. Once in boot, Device should advertise a new set of services.
// 3. Discover boot mode services and characteristics.
// 4. Return NO if failed to enter boot, otherwise YES.
//
-(BOOL) enterBoot {
    CBUUID *uuid = [CBUUID UUIDWithString:characteristicCurrentAppUuid];
    BOOL success = NO;
    NSUUID  *targetPeripheralID = targetPeripheral.identifier;
    
    // As we expect there will be a disconnect, set waitForDisconnect to avoid a call to Abort.
    waitForDisconnect = YES;
    
    for (CBCharacteristic *characteristic in appDelegate.targetService.characteristics)
    {
        // Is this our characteristic
        if ([characteristic.UUID isEqual:uuid])
        {
            // Put into Boot Mode
            uint8_t appCommandValue = 0;
            NSData *appCommand      = [NSData dataWithBytes:(void *)&appCommandValue
                                                     length:sizeof(appCommandValue)];
            [targetPeripheral setDelegate:self];
            [targetPeripheral writeValue:appCommand forCharacteristic:characteristic
                                    type:CBCharacteristicWriteWithResponse];
            
            PCM *pcm = [self waitForDelegate:kDidWriteValueForCharacteristic];
            if ( (!pcm) || (pcm.PCMError != NULL) ) {
                if ( pcm ) {
                    NSLog(@" Enter bootmode, write characteristic status: %@", pcm.PCMError.localizedDescription);
                }
                break;
            }
            
            // Sleep for some time to allow the device to enter boot and for it to Advertise OTAU Boot service.
            [NSThread sleepForTimeInterval:2];
            
            
            [[Discovery sharedInstance] disconnectPeripheral:targetPeripheral];
            
            [[Discovery sharedInstance] setDiscoveryDelegate:self];
            
            
            NSArray *peripherals = [[Discovery sharedInstance]retrievePeripheralsWithIdentifier:targetPeripheralID];
            
            if (peripherals && [peripherals count]==1)
            {
                targetPeripheral = (CBPeripheral *)[peripherals objectAtIndex:0];
                targetPeripheral.delegate = self;
                
                // Connect to the target Peripheral then discover characteristics for the given Service.
                success = [self connect:serviceBootOtauUuid];
                break;
            }
            [[Discovery sharedInstance] setDiscoveryDelegate:nil];
            break;
        }
    }
    
    waitForDisconnect = NO;
    return (success);
}

//============================================================================
// Validation of Host by way of encrypted Challenge Value exchange.
// This function first checks that challenge response is expected.
// Return (YES) if challenge response is expected and passes or if it isn't
// expected.
// Return (NO) if challenge response is expected but fails.
//
const uint8_t sharedSecretKey[] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

-(BOOL) hostValidation {
    
    if (targetHasChallengeResponse) {
        [self statusMessage:@"Start: Obtain Challenge Value\n"];
        NSData *challenge = [self readCharacteristic:characteristicDataTransferUuid fromService: appDelegate.targetService];
        if (challenge) {
            [self statusMessage:@"Success: Obtain Challenge Value\n"];
            
            NSData *key = [[NSData alloc] initWithBytes:sharedSecretKey length:sizeof(sharedSecretKey)];
            size_t outLength;
            NSMutableData *cipherData = [NSMutableData dataWithLength:challenge.length +
                                         kCCBlockSizeAES128];
            
            CCCryptorStatus result = CCCrypt(kCCEncrypt, // operation
                                             kCCAlgorithmAES128, // Algorithm
                                             kCCOptionPKCS7Padding, // options
                                             key.bytes, // key
                                             key.length, // keylength
                                             nil, // (*iv).bytes,// iv
                                             challenge.bytes, // dataIn
                                             challenge.length, // dataInLength,
                                             cipherData.mutableBytes, // dataOut
                                             cipherData.length, // dataOutAvailable
                                             &outLength); // dataOutMoved
            
            if (result == kCCSuccess) {
                cipherData.length = outLength;
                NSData *destination = [NSData dataWithBytes:((char *)cipherData.bytes) length:16];
                
                [self statusMessage:@"Start: Return Encrypted Challenge Value\n"];
                [self writeCharacteristic:characteristicDataTransferUuid withValue:destination];
                [NSThread sleepForTimeInterval:5];
                [self statusMessage:@"Success: Return Encrypted Challenge Value\n"];
                return (YES);
            }
        }
        [self statusMessage:@"Failed: Obtain Challenge Value\n"];
        return (NO);
    }
    
    // return YES because challenge response is not expected
    return (YES);
}

//============================================================================
// Transfer Application to target device
// 1. Assume device is in boot mode and Boot services & Characteristics have been discovered.
// 2. Assume challenge-response, if expected, has been completed.
// 3. Transmit new Application image.
// 4. Once complete, switch to the new application and run it.
//
// return NO if there was an Error, otherwise YES.
//
-(BOOL) transferNewApplication:(NSData *) application {
    
    BOOL returnVal = YES;
    
    // Provide a notification path from target to Host
    [self statusMessage:@"Start: Subscribe for Notification\n"];
    if (![self createNotifyForAppTransfer]) {
        [self statusMessage:@"Failed: Subscribe for Notification\n"];
        return (NO);
    }
    [self statusMessage:@"Success: Subscribe for Notification\n"];
    
    if (didAbort) return (NO);

    // Transmit new image
    do {
        // Write applicationNumber -> kOtaCurAppCharUuid == Select the application to overwrite.
        uint8_t charValue8 = (uint8_t) applicationNumber;
        
        NSData *charValue = [NSData dataWithBytes:(void *)&charValue8
                                           length:sizeof(charValue8)];
        [self writeCharacteristic:characteristicCurrentAppUuid withValue:charValue];
        
        // Check if the update app image ID was set successfuly
        PCM *appIdPcm = [self waitForDelegate:kDidWriteValueForCharacteristic];
        if ((!appIdPcm) || (appIdPcm.PCMError != NULL)) {
            if (appIdPcm && (appIdPcm.PCMError != NULL)) {
                NSLog(@"Setting the update application ID failed: %@, proceeding anyway!", appIdPcm.PCMError.localizedDescription);
            }
            [self statusMessage:@"Warning: Failed to set updated application ID.. proceeding anyway!\n"];
        }
        
        if (didAbort) break;
        
        // Write 2 -> kOtaTransCtrlCharUuid == Transfer in progress
        uint16_t charValue16 = transferControlInProgress;
        charValue = [NSData dataWithBytes:(void *)&charValue16
                                   length:sizeof(charValue16)];
        [self writeCharacteristic:characteristicTransferControlUuid withValue:charValue];
        
        // Check if the transfer control was set successfuly
        PCM *transControlPcm = [self waitForDelegate:kDidWriteValueForCharacteristic];
        if ((!transControlPcm) || (transControlPcm.PCMError != NULL)) {
            if (transControlPcm) {
                NSLog(@"Setting app image transfer in progress failed: %@", transControlPcm.PCMError.localizedDescription);
            }
            [self statusMessage:@"Failed: Set app image transfer in progress\n"];
            returnVal = NO;
            break;
        }
        
        [self statusMessage:@"Start: Transferring image\n"];
        
        // Application Transfer - Loop
        // TX 20 bytes at a time from the application file.
        const uint8_t PacketLength = 20;
        transferInProgress = YES;
        transferPercent = 0;
        transferCount = 0;
        int total = (int) [application length];
        
        transferTotal = (total + (PacketLength-1)) / PacketLength;
        int index=0, length=PacketLength;
        while (returnVal && !didAbort && index<total) {
            if ((total-index)<20) {
                length=total-index;
            }

            NSData *chunkOfAppData = [application subdataWithRange:NSMakeRange(index, length)];
            [self writeCharacteristic:characteristicDataTransferUuid withValue:chunkOfAppData];
            
            PCM *writePcm = nil;
            do {
                // Wait for notify that characteristic was written.
                // Check every 100ms, but timeout after 1000 checks.
                // Usually the delegate call back is seen very fast but we have a long timeout as
                // it can take longer on some devices.
                for (int i=0; i<1000; i++) {
                    usleep(100);
                    if (targetPeripheral) {
                        writePcm = [targetPeripheral getCallback];
                        if (writePcm) {
                            if ([writePcm.PCMName isEqualToString:kDidWriteValueForCharacteristic]) {
                                break;
                            }
                        }
                    }
                    if (didAbort)
                        break;
                }
                // If notify was never seen then fail.
                if ((!writePcm) || (writePcm.PCMError != NULL)) {
                    [self statusMessage:@"Failed: while completing OTAU transfer\n"];
                    if (writePcm) {
                        NSLog(@"Write data failed: %@", writePcm.PCMError.localizedDescription);
                    }
                    returnVal = NO;
                    break;
                }
                // If the last notify was not for the data transfer characteristic then try again as long as there hasn't been an abort.
            } while (![writePcm.PCMCharacteristic.UUID isEqual:[CBUUID UUIDWithString: characteristicDataTransferUuid]] && didAbort == NO);
            index += PacketLength;
        }
    } while (0); // One time loop
    
    if (didAbort) {
        returnVal = (NO);
        uint16_t charValue16 = transferControlAbort;
        NSData *charValue = [NSData dataWithBytes:(void *)&charValue16
                                   length:sizeof(charValue16)];
        [self writeCharacteristic:characteristicTransferControlUuid withValue:charValue];
    }
    else if (returnVal) {
        // Write 4 -> kOtaTransCtrlCharUuid == Transfer Completed
        uint16_t charValue16 = transferControlComplete;
        NSData *charValue = [NSData dataWithBytes:(void *)&charValue16
                                   length:sizeof(charValue16)];
        [self writeCharacteristic:characteristicTransferControlUuid withValue:charValue];
    }
    
    return (returnVal);
}

//=========================================================================
// OTAU Termination. Calls the OTAU delegate with the result of the OTAU.
// If error code is non nil then there has been a timeout or some unexpected error.
// If error code is nil then OTA update completed successfully.
//
-(void) terminateOTAU:(NSString *) message :(int) errorCode {
    if (errorCode) {
        // Disconnect
        [[Discovery sharedInstance] disconnectPeripheral: targetPeripheral];
        targetPeripheral.delegate = nil;
        [[Discovery sharedInstance] setDiscoveryDelegate:nil];
        [self statusMessage: message];
        [self reportError: errorCode];
    }
    else {
        if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(completed:)]) {
            [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                [OTAUDelegate completed:[message capitalizedString]];
            }];
        }
    }
    otauRunning = NO;
}


/****************************************************************************/
/*				    Bluetooth helper methods                                */
/****************************************************************************/

//============================================================================
// Connect to the targetPeripheral and then discover the characteristics for the given service.
//
-(BOOL) connect:(NSString *) service {
    BOOL    success = NO;
    
    [self statusMessage:@"Start: Connect\n"];
    [[Discovery sharedInstance] setDiscoveryDelegate: self];
    [[Discovery sharedInstance] connectPeripheral:targetPeripheral];
    targetPeripheral.delegate = self;
    PCM *pcm = [self waitForDelegate:kBleDidConnectPeripheral];
    if (pcm) {
        [self statusMessage:@"Success: Connect\n"];
        
        // Wait for characteristics to be discovered.
        int timeout = 300;
        while (![appDelegate.discoveredChars boolValue] && timeout--) {
            [NSThread sleepForTimeInterval: 0.1];
        }
        if (timeout > 0) {
            success = YES;
            targetPeripheral.delegate = self;
        }
    }
    else {
        [self statusMessage:@"Failed: Connect\n"];
    }
    
    return (success);
}

//============================================================================
// We seem to be in connecting mode, escape from this mode by atempting to disconnect.
//
-(BOOL) stopConnecting {
    BOOL    success = NO;
    
    [self statusMessage:@"Start: Stop Connecting \n"];
    [[Discovery sharedInstance] disconnectPeripheral:targetPeripheral];
    targetPeripheral.delegate = self;
    PCM *pcm = [self waitForDelegate:kBleDidDisconnectPeripheral];
    if (pcm) {
        [self statusMessage:@"Success: Disconnected\n"];
        success = YES;
    }
    else {
        [self statusMessage:@"Failed: Disconnect\n"];
    }
    
    return (success);
}

//============================================================================
// Setup notification to allow simple flow control when transferring Application.
//
-(BOOL) createNotifyForAppTransfer {
    NSLog(@"otauCreateNotifyForAppTx");
    CBUUID *uuid = [CBUUID UUIDWithString:characteristicTransferControlUuid];
    
    for (CBCharacteristic *characteristic in appDelegate.targetService.characteristics) {
        
        if ([characteristic.UUID isEqual:uuid])
        {
            NSLog(@" -SetNotify for %@",characteristic.UUID);
            [targetPeripheral setNotifyValue:YES forCharacteristic:characteristic];
            
            PCM *pcm = [self waitForDelegate:kDidUpdateNotificationStateForCharacteristic];
            if (pcm && ( pcm.PCMError == NULL ) ) {
                return (YES);
            }
            else
                break;
        }
    }
    return (NO);
    
}

//============================================================================
// Write the given data to the given characteristic, providing of course
// that the characteristic has been previously discovered.
//
-(void) writeCharacteristic:(NSString *)characteristicName withValue:(NSData *) data {
    CBUUID *uuid = [CBUUID UUIDWithString:characteristicName];
    
    for (CBCharacteristic *characteristic in appDelegate.targetService.characteristics) {
        // Is this the characteristic we have discovered
        if ([characteristic.UUID isEqual:uuid]) {
            
            [targetPeripheral writeValue:data forCharacteristic:characteristic
                                    type:CBCharacteristicWriteWithResponse];
        }
    }
}

//============================================================================
// Read the given data from the given characteristic and service.
// Discover characteristics from service if not already available.
//
-(NSData *) readCharacteristic:(NSString *)characteristicName fromService:(CBService*) service {
    CBUUID *uuid = [CBUUID UUIDWithString:characteristicName];
    
    if (service.characteristics == nil) {
        [self discoverCharacteristics:[service.UUID UUIDString]];
    }
    
    for (CBCharacteristic *characteristic in service.characteristics) {
        // Is this the characteristic we are interested in?
        if ([characteristic.UUID isEqual:uuid]) {
            NSLog(@"Request Characteristic %@ Value", characteristicName);
            [self statusMessage:@"Request Characteristic Value\n"];
            [targetPeripheral readValueForCharacteristic:characteristic];
            PCM *pcm= [self waitForDelegate:kDidUpdateValueForCharacteristic];
            if (pcm && (pcm.PCMError == NULL)) {
                NSLog(@"Success: Request Characteristic %@ Value", characteristicName);
                [self statusMessage:@"Success: Request Characteristic Value\n"];
                return (pcm.PCMCharacteristic.value);
            }
            else {
                if (pcm.PCMError) {
                    NSLog(@"Failed: Request Characteristic %@ Value, status:%@",
                          characteristicName, pcm.PCMError.localizedDescription);
                }
                [self statusMessage:@"Failed: Request Characteristic Value\n"];
            }
        }
    }
    return (nil);
}

//============================================================================
// Look for a specific characterisitic from a list of characterisitics
// previously discovered.
//
-(BOOL) checkForCharacteristic:(NSString *)characteristicName {
    BOOL ret = false;
    CBUUID *uuid = [CBUUID UUIDWithString:characteristicName];
    
    for (CBCharacteristic *characteristic in appDelegate.targetService.characteristics) {
        // Is this the characteristic we have discovered
        if ([characteristic.UUID isEqual:uuid]) {
            ret = true;
            break;
        }
    }
    return ret;
}

//============================================================================
// Discover Characteristics for given service.
//
-(BOOL) discoverCharacteristics:(NSString *)serviceUUID {
    BOOL success=NO;
    [self statusMessage:@"Start: Discover Characteristics\n"];
    CBUUID *uuid = [CBUUID UUIDWithString:serviceUUID];
    for (CBService *service in targetPeripheral.services) {
        if ([service.UUID isEqual:uuid]) {
            appDelegate.targetService = service;
            [targetPeripheral discoverCharacteristics:nil forService:service];
            PCM *pcm = [self waitForDelegate:kDidDiscoverCharacteristicsForService];
            if (pcm && (pcm.PCMError == NULL)) {
                [self statusMessage:@"Success: Discover Characteristics\n"];
                success = YES;
            }
            else {
                success = NO;
            }
        }
    }
    return (success);
}



/****************************************************************************/
/*				CoreBluetooth Peripheral delegates                          */
/****************************************************************************/

//============================================================================
//
-(void) peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error {
    NSLog(@"didDiscoverServices for peripheral %@",peripheral.name);
    PCM *pcm = [[PCM alloc] init:peripheral :nil :nil :error :kDidDiscoverServices];
    [peripheral saveCallback:pcm];
}

//============================================================================
//
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error {
    NSLog(@"didDiscoverCharacteristicsForService for peripheral %@ & Service %@",peripheral.name, service.UUID);
    PCM *pcm = [[PCM alloc] init:peripheral :service :nil :error :kDidDiscoverCharacteristicsForService];
    [peripheral saveCallback:pcm];
}

//============================================================================
//
- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    NSLog(@"didUpdateNotificationStateForCharacteristic for peripheral %@ & Characteristic %@",peripheral.name, characteristic.UUID);
    PCM *pcm = [[PCM alloc] init:peripheral :nil :characteristic :error :kDidUpdateNotificationStateForCharacteristic];
    [peripheral saveCallback:pcm];
}

//============================================================================
//
- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    if (transferInProgress) {
        transferCount++;
        uint8_t percent = 50 + (50 * transferCount) / transferTotal;
        if (percent > transferPercent) {
            [self updateProgress: percent];
            transferPercent = percent;
        }
        if (transferCount == transferTotal) {
            transferInProgress = NO;
        }
    }
    
    NSLog(@"didWriteValueForCharacteristic for peripheral %@ & Characteristic %@",peripheral.name, characteristic.UUID);
    PCM *pcm = [[PCM alloc] init:peripheral :nil :characteristic :error :kDidWriteValueForCharacteristic];
    [peripheral saveCallback:pcm];
    
}

//============================================================================
//
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error {
    NSLog(@"didUpdateValueForCharacteristic for peripheral %@ & Characteristic %@ value=%@",peripheral.name, characteristic.UUID, characteristic.value);
    PCM *pcm = [[PCM alloc] init:peripheral :nil :characteristic :error :kDidUpdateValueForCharacteristic];
    [peripheral saveCallback:pcm];
    
}



/****************************************************************************/
/*								Discovery delegates                         */
/****************************************************************************/

//============================================================================
// Reuse the DiscoveryDelegate singleton to route callbacks from CBCentral
//
- (void) didDiscoverPeripheral:(CBPeripheral *)peripheral {
    if ([peripheral.identifier isEqual:targetPeripheral.identifier])
    {
        NSLog(@"didDiscoverPeripheral peripheral %@",peripheral.name);
        PCM *pcm = [[PCM alloc] init:peripheral :nil :nil :nil :kBleDidDiscoverPeripheral];
        [peripheral saveCallback:pcm];
    }
}


//============================================================================
//
- (void) didConnectPeripheral:(CBPeripheral *)peripheral {
    NSLog(@"didConnectPeripheral peripheral %@",peripheral.name);
    PCM *pcm = [[PCM alloc] init:peripheral :nil :nil :nil :kBleDidConnectPeripheral];
    [peripheral saveCallback:pcm];
    if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(didChangeConnectionState:)]) {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [OTAUDelegate didChangeConnectionState: true];
        }];
    }
}


//============================================================================
//
-(void) didDisconnect:(CBPeripheral *)peripheral error:(NSError *)error {
    if (peripheral == targetPeripheral) {
        if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(didChangeConnectionState:)]) {
            [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                [OTAUDelegate didChangeConnectionState: false];
            }];
        }
        NSLog(@"Target Peripheral Disconnect With Error = %@",error);
        if (waitForDisconnect==NO) {
            // Abort OTAU if the peripheral disconnected
            [self terminateOTAU:@"Failed: Peripheral Disconnected": OTAUErrorFailedDisconnected];
        }
        else
            waitForDisconnect = NO;
    }
    else {
        NSLog(@"%@ peripheral Disconnected with error %@",peripheral.name, error);
    }
}

//============================================================================
//
-(void) didChangeMode {
    // Notify OTAU delegate that Boot/App mode changed
    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
        if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(didChangeMode:)]) {
            [OTAUDelegate didChangeMode: [appDelegate.peripheralInBoot boolValue]];
        }
    }];
}


/****************************************************************************/
/*								General Helper Methods                      */
/****************************************************************************/

//============================================================================
// Wait for the given delegate to be called and if this occurs within 30 seconds then
// return the PCM object, otherwise return (nil).
//
// One check a second is sufficient.
//
// Ignore callbacks other than given.
//
-(PCM *) waitForDelegate:(NSString *) delegate {
    // Test every Second, timeout afer 30 seconds
    for (int i=0; i<30; i++) {
        [NSThread sleepForTimeInterval:1];
        if (targetPeripheral) {
            // This removes a delegate from the queue of received delegates.
            PCM *pcm = [targetPeripheral getCallback];
            if (pcm) {
                if ([pcm.PCMName isEqualToString:delegate]) {
                    return (pcm);
                }
            }
        }
        if (otauRunning==NO)
            return(nil);
    }
    return (nil);
}

//============================================================================
// Send status messages to main thread.
// This can be used as a progress indicator.
//
-(void) statusMessage:(NSString *) message {
    @synchronized (self) {
        if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(statusMessage:)]) {
            [[NSOperationQueue mainQueue] addOperationWithBlock:^{
                [OTAUDelegate statusMessage:[message capitalizedString]];
            }];
        }
    }
}

//============================================================================
// Send progress update to main thread.
//
-(void) updateProgress:(uint8_t) percent {
    if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(didUpdateProgress:)]) {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [OTAUDelegate didUpdateProgress: percent];
        }];
    }
}
         
//============================================================================
// Inform delegate of Error
//
-(void) reportError:(NSInteger) errorCode {
    
    // Convert error code to 4 character string
    // this will be used to lookup Error Message
    NSString *errorCodeString = [NSString stringWithFormat:@"%4d",(int)errorCode];
    
    // Lookup Error string from error code
    NSString *errorString = NSLocalizedStringFromTable (errorCodeString, @"ErrorCodes", nil);
    
    // Construct error object
    NSError *error = [[NSError alloc] initWithDomain:[[NSBundle mainBundle] bundleIdentifier]
                                                code:errorCode
                                            userInfo:@{errorCodeString: errorString} ];
    
    // Perform callback to Main View (in main thread)
    if (OTAUDelegate && [OTAUDelegate respondsToSelector: @selector(otauError:)]) {
        [[NSOperationQueue mainQueue] addOperationWithBlock:^{
            [OTAUDelegate otauError:error];
        }];
    }
}
@end
