//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import "CSROTAUManager.h"
#import "CSROTAUGattCommand.h"
#import <CommonCrypto/CommonDigest.h>
#import "CSRPeripheral.h"

@interface CSROTAUManager ()

@property (nonatomic) NSData *fileData;
@property (nonatomic) NSInteger fileIndex;
@property (nonatomic) BOOL waitingForReconnect;
@property (nonatomic) BOOL disconnected;
@property (nonatomic) CSRPeripheral *connectedPeripheral;
@property (nonatomic) NSTimeInterval startTime;
@property (nonatomic) OTAUUpdateResumePoint resumePoint;
@property (nonatomic) uint16_t lastError;
@property (nonatomic) BOOL restart;
@property (nonatomic) BOOL aborted;
@property (nonatomic) NSMutableArray *dataBuffer;

@end

@implementation CSROTAUManager

@synthesize aborted;
@synthesize connectedPeripheral;
@synthesize dataBuffer;
@synthesize delegate;
@synthesize disconnected;
@synthesize fileData;
@synthesize fileIndex;
@synthesize lastError;
@synthesize resumePoint;
@synthesize restart;
@synthesize startTime;
@synthesize updateFileName;
@synthesize updateInProgress;
@synthesize updateProgress;
@synthesize waitingForReconnect;

+ (CSROTAUManager *)sharedInstance {
    static dispatch_once_t pred;
    static CSROTAUManager *shared = nil;
    
    dispatch_once(&pred, ^{
        shared = [[CSROTAUManager alloc] init];
    });
    
    return shared;
}

- (id)init {
    if (self = [super init]) {
        self.aborted = NO;
        self.fileData = nil;
        self.updateFileName = nil;
        self.updateInProgress = NO;
        self.waitingForReconnect = NO;
        self.disconnected = NO;
        self.updateProgress = 0.0;
        self.fileIndex = 0;
        self.restart = NO;
        self.connectedPeripheral = nil;
        self.resumePoint = OTAUUpdateResumePoint_Start;
        self.dataBuffer = [NSMutableArray array];
    }
    
    return self;
}

- (void)start:(NSString *)fileName {
    self.aborted = NO;
    
    if (!self.updateInProgress) {
        self.updateFileName = fileName;
        self.fileData = [[NSData alloc] initWithContentsOfFile:fileName];
        self.fileIndex = 0;
        self.restart = NO;
        [self.dataBuffer removeAllObjects];
        
        if (!self.fileData) {
            NSString *msg = [NSString stringWithFormat:@"Unable to open: %@", fileName];
            
            [delegate didAbortWithError:[NSError
                                         errorWithDomain:CSROTAUError
                                         code:0
                                         userInfo:@{CSROTAUErrorParam: msg}]];
            
            return;
        } else {
            [CSROTAU sharedInstance].fileMD5 = [self MD5:self.fileData];
        }
        
        [CSROTAU sharedInstance].delegate = self;
        [[CSRConnectionManager sharedInstance] addDelegate:self];
        self.connectedPeripheral = [CSRConnectionManager sharedInstance].connectedPeripheral;
        self.updateInProgress = YES;
    }
    
    NSLog(@"OTAUEvent_VMUpgradeProtocolPacket > registerNotifications - start");
    [[CSROTAU sharedInstance] registerNotifications:OTAUEvent_VMUpgradeProtocolPacket];
}

- (void)connect {
    [CSROTAU sharedInstance].delegate = self;
    [[CSRConnectionManager sharedInstance] addDelegate:self];
    self.connectedPeripheral = [CSRConnectionManager sharedInstance].connectedPeripheral;
}

- (void)disconnect {
    [[CSRConnectionManager sharedInstance] disconnectPeripheral];
    [[CSROTAU sharedInstance] disconnectPeripheral];
    
    self.connectedPeripheral = nil;
}

- (void)abort {
    self.aborted = YES;
    
    [self stop];
}

- (void)abortAndRestart {
    self.restart = YES;
    
    [self stop];
}

- (void)stop {
    if (self.updateInProgress) {
        NSLog(@"OTAUUpdate_AbortRequest > vmUpgradeControl");
        [self.dataBuffer removeAllObjects];
        [[CSROTAU sharedInstance] abort];
    }
}

- (void)commitConfirm:(BOOL)value {
    [self commitConfirmRequest:value];
}

- (void)eraseSqifConfirm {
    [self eraseSquifConf];
}

- (void)confirmError {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint16_t last_error = CFSwapInt16(self.lastError);
    
    [payload appendBytes:&last_error length:sizeof(uint16_t)];
    
    NSLog(@"OTAUUpdate_ErrorWarnResponse");
    
    [[CSROTAU sharedInstance] vmUpgradeControl:OTAUUpdate_ErrorWarnResponse
                                        length:sizeof(uint16_t)
                                          data:payload];
}

- (void)syncRequest {
    self.fileIndex = 0;
    self.restart = NO;
    self.updateInProgress = YES;
    self.resumePoint = OTAUUpdateResumePoint_Start;
    NSLog(@"OTAUCommand_VMUpgradeConnect > OTAUUpdate_SyncRequest");
    [[CSROTAU sharedInstance] vmUpgradeControl:OTAUUpdate_SyncRequest];
}

- (void)getLED {
    [[CSROTAU sharedInstance] getLEDState];
}

- (void)setLED:(BOOL)value {
    [[CSROTAU sharedInstance] setLED:value];
}

- (void)setVolume:(NSInteger)value {
    [[CSROTAU sharedInstance] setVolume:value];
}

- (void)getPower {
    [[CSROTAU sharedInstance] getPower];
}

- (void)setPowerOn:(BOOL)value {
    [[CSROTAU sharedInstance] setPowerOn:value];
}

- (void)getBattery {
    [[CSROTAU sharedInstance] getBattery];
}

- (void)getApiVersion {
    [[CSROTAU sharedInstance] getApiVersion];
}

- (void)avControl:(OTAUAVControlOperation)operation {
    [[CSROTAU sharedInstance] avControl:operation];
}

- (void)trimTWSVolume:(NSInteger)device volume:(NSInteger)value {
    [[CSROTAU sharedInstance] trimTWSVolume:device volume:value];
}

- (void)getTWSVolume:(NSInteger)device {
    [[CSROTAU sharedInstance] getTWSVolume:device];
}

- (void)setTWSVolume:(NSInteger)device volume:(NSInteger)value {
    [[CSROTAU sharedInstance] setTWSVolume:device volume:value];
}

- (void)getTWSRouting:(NSInteger)device {
    [[CSROTAU sharedInstance] getTWSRouting:device];
}

- (void)setTWSRouting:(NSInteger)device routing:(NSInteger)value {
    [[CSROTAU sharedInstance] setTWSRouting:device routing:value];
}

- (void)getBassBoost {
    [[CSROTAU sharedInstance] getBassBoost];
}

- (void)setBassBoost:(BOOL)value {
    [[CSROTAU sharedInstance] setBassBoost:value];
}

- (void)get3DEnhancement {
    [[CSROTAU sharedInstance] get3DEnhancement];
}

- (void)set3DEnhancement:(BOOL)value {
    [[CSROTAU sharedInstance] set3DEnhancement:value];
}

- (void)getAudioSource {
    [[CSROTAU sharedInstance] getAudioSource];
}

- (void)setAudioSource:(OTAUAudioSource)value {
    [[CSROTAU sharedInstance] setAudioSource:value];
}

- (void)findMe:(NSUInteger)value {
    [[CSROTAU sharedInstance] findMe:value];
}

- (void)getEQControl {
    [[CSROTAU sharedInstance] getEQControl];
}

- (void)setEQControl:(NSInteger)value {
    [[CSROTAU sharedInstance] setEQControl:value];
}

- (void)setFilterType:(NSInteger)bank band:(NSInteger)band value:(NSInteger)value {
    [[CSROTAU sharedInstance] setFilterType:bank band:band value:value];
}

- (void)setFilterFrequency:(NSInteger)bank band:(NSInteger)band value:(double)value {
    [[CSROTAU sharedInstance] setFilterFrequency:bank band:band value:value];
}

- (void)setFilterGain:(NSInteger)bank band:(NSInteger)band value:(double)value {
    [[CSROTAU sharedInstance] setFilterGain:bank band:band value:value];
}

- (void)setFilterQ:(NSInteger)bank band:(NSInteger)band value:(double)value {
    [[CSROTAU sharedInstance] setFilterQ:bank band:band value:value];
}

- (void)setFilterPreGain:(NSInteger)bank band:(NSInteger)band value:(double)value {
    [[CSROTAU sharedInstance] setFilterPreGain:bank band:band value:value];
}

- (void)getGroupEQParam:(NSData *)data {
    [[CSROTAU sharedInstance] getGroupEQParam:data];
}

- (void)setGroupEQParam:(NSData *)data {
    [[CSROTAU sharedInstance] setGroupEQParam:data];
}

- (void)getUserEQ {
    [[CSROTAU sharedInstance] getUserEQ];
}

- (void)setUserEQ:(BOOL)value {
    [[CSROTAU sharedInstance] setUserEQ:value];
}

#pragma mark CSRConnectionManagerDelegate

- (void)discoveredPripheralDetails {
    if (self.delegate && [self.delegate respondsToSelector:@selector(didUpdateStatus:)]) {
        [self.delegate didUpdateStatus:CSRStatusPairingString];
    }
    
    [CSROTAU sharedInstance].delegate = self;
    [[CSROTAU sharedInstance]
     connectPeripheral:[CSRConnectionManager sharedInstance].connectedPeripheral];
    
    if (self.disconnected) {
        NSLog(@"OTAUEvent_VMUpgradeProtocolPacket > registerNotifications - discoveredPripheralDetails");
        [[CSROTAU sharedInstance] registerNotifications:OTAUEvent_VMUpgradeProtocolPacket];
    }
}

- (void)chracteristicChanged:(CBCharacteristic *)characteristic {
    if (self.waitingForReconnect) {
        self.waitingForReconnect = NO;
        
        if (self.delegate && [self.delegate respondsToSelector:@selector(didUpdateStatus:)]) {
            [self.delegate didUpdateStatus:CSRStatusFinalisingString];
        }
        
        NSLog(@"OTAUEvent_VMUpgradeProtocolPacket > registerNotifications - chracteristicChanged");
        [[CSROTAU sharedInstance] registerNotifications:OTAUEvent_VMUpgradeProtocolPacket];
    } else {
        [[CSROTAU sharedInstance] handleResponse:characteristic];
    }
}

- (void)peripheral:(CBPeripheral *)peripheral
didWriteValueForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error {
    if (error) {
        NSLog(@"didWriteValueForCharacteristic Error:%@\n\nThe Phone will now disconnect.", error.localizedDescription);
        [[CSRConnectionManager sharedInstance] disconnectPeripheral];
        
        return;
    }
    
    if (   [characteristic isEqual:[CSROTAU sharedInstance].commandCharacteristic]
        && [self.dataBuffer count] > 0) {
        NSData *data = [self.dataBuffer firstObject];
        
        [[CSROTAU sharedInstance] sendData:data];
        
        [self.dataBuffer removeObjectAtIndex:0];
    }
}

- (void)didConnectToPeripheral:(CSRPeripheral *)peripheral {
    if (self.updateInProgress) {
        if (!self.disconnected) {
            [[CSROTAU sharedInstance] registerNotifications:OTAUEvent_VMUpgradeProtocolPacket];
        }
        
        // Discover services and characteristics.
        if (self.delegate && [self.delegate respondsToSelector:@selector(didUpdateStatus:)]) {
            [self.delegate didUpdateStatus:CSRStatusReconnectedString];
        }
    }
}

- (void)didPowerOff {
    [self didDisconnectFromPeripheral];
}

- (void)didPowerOn {
    [[CSRConnectionManager sharedInstance] connectPeripheral:self.connectedPeripheral];
}

- (void)didDisconnectFromPeripheral:(CBPeripheral *)peripheral {
    [self didDisconnectFromPeripheral];
}

- (void)didDisconnectFromPeripheral {
    if (self.updateInProgress) {
        self.waitingForReconnect = YES;
        
        if (self.delegate && [self.delegate respondsToSelector:@selector(didUpdateStatus:)]) {
            [self.delegate didUpdateStatus:CSRStatusReconnectingString];
        }
        
        self.disconnected = YES;
        self.fileIndex = 0;
        [[CSRConnectionManager sharedInstance] connectPeripheral:self.connectedPeripheral];
    }
}

#pragma mark CSROTAUDelegate

- (void)didReceiveResponse:(CSROTAUGattCommand *)command {
    OTAUCommandType cmdType = [command getCommandId];
    
    if ([command isControl]) {
        if (self.delegate && [self.delegate respondsToSelector:@selector(didReceiveOTAUGattResponse:)]) {
            [self.delegate didReceiveOTAUGattResponse:command];
        }
    } else {
        if (self.updateInProgress) {
            if (self.disconnected) {
                if (cmdType == OTAUCommand_RegisterNotification) {
                    self.disconnected = NO;
                    self.startTime = [NSDate timeIntervalSinceReferenceDate];
                    NSLog(@"No longer skipping buffered commands");
                } else {
                    NSLog(@"Skipping command");
                    return;
                }
            }
            
            switch (cmdType) {
                case OTAUCommand_VMUpgradeConnect:
                    if ([self abortWithError:command] == 0) {
                        NSLog(@"OTAUCommand_VMUpgradeConnect > OTAUUpdate_SyncRequest");
                        [[CSROTAU sharedInstance] vmUpgradeControl:OTAUUpdate_SyncRequest];
                    }
                    break;
                case OTAUCommand_VMUpgradeControl:
                    [self abortWithError:command];
                    break;
                case OTAUCommand_EventNotification:
                    if ([command event] == OTAUEvent_VMUpgradeProtocolPacket) { // Read off the update status from the beginning of the payload
                        switch ([command updateStatus]) {
                            case OTAUUpdate_SyncConfirm: // Battery level is also included in the response
                                NSLog(@"OTAUUpdate_StartRequest");
                                [self handleSyncConfirm:command];
                                break;
                            case OTAUUpdate_StartConfirm:
                                [self handleStartConfirm:command];
                                break;
                            case OTAUUpdate_DataBytesRequest:
                                [self dataBytesReguest:command];
                                break;
                            case OTAUUpdate_AbortConfirm:
                                if (self.restart) {
                                    self.restart = NO;
                                    
                                    NSLog(@"OTAUEvent_VMUpgradeProtocolPacket > registerNotifications - didReceiveResponse");
                                    [[CSROTAU sharedInstance] registerNotifications:OTAUEvent_VMUpgradeProtocolPacket];
                                } else {
                                    [[CSROTAU sharedInstance] vmUpgradeDisconnect];
                                }
                                break;
                            case OTAUUpdate_ErrorWarnIndicator: // Any error will abort the upgrade.
                                [self abortWithError:command];
                                break;
                            case OTAUUpdate_ProgressConfirm:
                                [self readProgress:command];
                                break;
                            case OTAUUpdate_IsValidationDoneConfirm:
                                [self validationConfirm:command];
                                break;
                            case OTAUUpdate_TransferCompleteIndicator:
                                if (self.delegate && [self.delegate respondsToSelector:@selector(confirmTransferRequired)]) {
                                    [self.delegate confirmTransferRequired];
                                } else {
                                    [self updateTransferComplete];
                                }
                                break;
                            case OTAUUpdate_InProgressIndicator: // The device says it has rebooted.
                                [self updateComplete];
                                break;
                            case OTAUUpdate_CommitRequest:
                                if (self.delegate && [self.delegate respondsToSelector:@selector(confirmRequired)]) {
                                    [self.delegate confirmRequired];
                                } else {
                                    [self commitConfirmRequest:YES];
                                }
                                break;
                            case OTAUUpdate_HostEraseSquifRequest:
                                // Need to ask a question
                                if (self.delegate && [self.delegate respondsToSelector:@selector(okayRequired)]) {
                                    [self.delegate okayRequired];
                                } else {
                                    [self eraseSquifConf];
                                }
                                break;
                            case OTAUUpdate_CompleteIndicator:
                                NSLog(@"OTAUUpdate_CompleteIndicator > vmUpgradeDisconnect");
                                [[CSROTAU sharedInstance] vmUpgradeDisconnect];
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case OTAUCommand_VMUpgradeDisconnect:
                    NSLog(@"OTAUCommand_VMUpgradeDisconnect > cancelNotification");
                    [[CSROTAU sharedInstance] cancelNotifications:OTAUEvent_VMUpgradeProtocolPacket];
                    break;
                case OTAUCommand_RegisterNotification:
                    NSLog(@"OTAUCommand_RegisterNotification > vmUpgradeConnect");
                    [[CSROTAU sharedInstance] vmUpgradeConnect];
                    break;
                case OTAUCommand_CancelNotification:
                    NSLog(@"OTAUCommand_CancelNotification > upgrade complete...");
                    if (self.aborted) {
                        [self abortUpdate];
                        self.aborted = NO;
                    } else {
                        [self complete];
                    }
                    break;
                default:
                    break;
            }
        } else {
//            if (self.delegate && [self.delegate respondsToSelector:@selector(didReceiveOTAUGattResponse:)]) {
//                [self.delegate didReceiveOTAUGattResponse:command];
//            }
        }
    }
}

- (void)resetUpdate {
    self.updateFileName = nil;
    self.updateInProgress = NO;
    self.updateProgress = 0.0;
    self.fileIndex = 0;
}

- (void)dataBytesReguest:(CSROTAUGattCommand *)command {
    NSData *requestPayload = [command getPayload];
    uint16_t length = 0;
    uint32_t numberOfBytes = 0;
    uint32_t fileOffset = 0;
    
    [requestPayload getBytes:&length range:NSMakeRange(2, 2)];
    [requestPayload getBytes:&numberOfBytes range:NSMakeRange(4, 4)];
    [requestPayload getBytes:&fileOffset range:NSMakeRange(8, 4)];
    
    length = CFSwapInt16BigToHost(length);
    numberOfBytes = CFSwapInt32BigToHost(numberOfBytes);
    fileOffset = CFSwapInt32BigToHost(fileOffset);
    
    NSRange range = {fileOffset > 0 ? fileOffset + self.fileIndex : self.fileIndex, numberOfBytes};
    uint8_t dataBytes[numberOfBytes];
    NSInteger start = 0;
    NSInteger index = 0;
    NSInteger max_length = 12;
    
    if (fileOffset > 0) {
        self.fileIndex = self.fileIndex + fileOffset + numberOfBytes;
    } else {
        self.fileIndex += numberOfBytes;
    }
    
    // Put the file data into the temporary buffer
    [self.fileData getBytes:&dataBytes range:range];
    
    NSData *data = [NSData dataWithBytes:dataBytes length:numberOfBytes];
    
    while (index <= numberOfBytes) {
        if ((index - start) < max_length) {
            if (index == numberOfBytes) {
                NSMutableData *payload = [[NSMutableData alloc] init];
                uint8_t more_data = (uint8_t)OTAUCommandAction_Continue;
                NSRange range = {start, index - start};
                
                if (self.fileIndex + start >= self.fileData.length) {
                    more_data = (uint8_t)OTAUCommandAction_Abort; // More data to follow
                }
                
                [payload appendBytes:&more_data length:1];
                [payload appendData:[data subdataWithRange:range]];
                
                [self.dataBuffer addObject:
                 [[CSROTAU sharedInstance]
                  vmUpgradeControlData:OTAUUpdate_Data
                  length:range.length + 1
                  data:payload]];
                start = index;
            }
        } else {
            NSMutableData *payload = [[NSMutableData alloc] init];
            uint8_t more_data = (uint8_t)OTAUCommandAction_Continue;
            NSRange range = {start, start > 0 ? index - start : index};
            
            [payload appendBytes:&more_data length:1];
            [payload appendData:[data subdataWithRange:range]];
            
            [self.dataBuffer addObject:
             [[CSROTAU sharedInstance]
              vmUpgradeControlData:OTAUUpdate_Data
              length:range.length + 1
              data:payload]];
            
            start = index;
        }
        
        index++;
    }
    
    if ([self.dataBuffer count] > 0) {
        NSData *data = [self.dataBuffer firstObject];
        
        [[CSROTAU sharedInstance] sendData:data];
        
        [self.dataBuffer removeObjectAtIndex:0];
    }
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(didMakeProgress:eta:)]) {
        double fs = self.fileData.length;
        double fi = self.fileIndex;
        double progress = (fi / fs) * 100.0;
        NSString *eta = [self calculateEta:fs fileIndex:fi];
        
        [self.delegate didMakeProgress:progress eta:eta];
    }
    
    // Delay?
    if (self.fileIndex + start >= self.fileData.length) {
        if ([self.dataBuffer count] > 0) {
            [self.dataBuffer addObject:
             [[CSROTAU sharedInstance]
              vmUpgradeControlData:OTAUUpdate_IsValidationDoneRequest
              length:0
              data:nil]];
        } else {
            [[CSROTAU sharedInstance] vmUpgradeControl:OTAUUpdate_IsValidationDoneRequest];
        }
    }
}

- (NSString *)calculateEta:(double)fs fileIndex:(double)fi {
    NSString *eta = nil;
    double speed = fi / ([NSDate timeIntervalSinceReferenceDate] - self.startTime);
    double remainingInSeconds = (fs - fi) / speed;
    long long int s = [[NSString stringWithFormat:@"%f", remainingInSeconds] longLongValue];
    
    if (s < 60) {
        eta = [NSString stringWithFormat:@"%lld s", s];
    } else {
        if (s < 3600) {
            eta = [NSString stringWithFormat:@"%lld minutes remaining", s / 60];
        } else {
            long long int moduloS = s % 3600;
            eta = [NSString stringWithFormat:@"%lld h, %lld m remaining", s / 3600, moduloS / 60];
        }
    }
    
    return eta;
}

- (CSROTAUGattCommand *)createCompleteCommand:(OTAUCommandUpdate)command
                                       length:(NSInteger)length
                                         data:(NSData *)data {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)command;
    uint16_t len = CFSwapInt16(length);
    
    [payload appendBytes:&payload_event length:1];
    [payload appendBytes:&len length:2];
    
    if (data) {
        [payload appendData:data];
    }
    
    CSROTAUGattCommand *cmd = [[CSROTAUGattCommand alloc]
                               initWithLength:OTAU_GATT_HEADER_SIZE];
    
    if (cmd) {
        [cmd setCommandId:OTAUCommand_VMUpgradeControl];
        [cmd setVendorId:CSR_OTAU_VENDOR_ID];
        
        if (data) {
            [cmd addPayload:payload];
        }
    }
    
    return cmd;
}

- (NSInteger)abortWithError:(CSROTAUGattCommand *)command {
    NSData *payload = [command getPayload];
    const unsigned char *data = (const unsigned char *)[payload bytes];
    NSInteger error_code = payload.length == 6 ? data[5] : data[1];
    NSString *errorMessage = nil;
    BOOL abortUpdate = YES;
    self.lastError = error_code;
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(didAbortWithError:)]) {
        switch (error_code) {
            case OTAUUpdateResponse_Success:
                NSLog(@"Success response decoded.");
                break;
            case OTAUUpdateResponse_ErrorUnknownId:
                errorMessage = CSROTAUError_1;
                break;
            case OTAUUpdateResponse_ErrorBadLength:
                errorMessage = CSROTAUError_2;
                break;
            case OTAUUpdateResponse_ErrorWrongVariant:
                errorMessage = CSROTAUError_3;
                break;
            case OTAUUpdateResponse_ErrorWrongPartitionNumber:
                errorMessage = CSROTAUError_4;
                break;
            case OTAUUpdateResponse_ErrorPartitionSizeMismatch:
                errorMessage = CSROTAUError_5;
                break;
            case OTAUUpdateResponse_ErrorPartitionTypeNotFound:
                errorMessage = CSROTAUError_6;
                break;
            case OTAUUpdateResponse_ErrorPartitionOpenFailed:
                errorMessage = CSROTAUError_7;
                break;
            case OTAUUpdateResponse_ErrorPartitionWriteFailed:
                errorMessage = CSROTAUError_8;
                break;
            case OTAUUpdateResponse_ErrorPartitionCloseFailed:
                errorMessage = CSROTAUError_9;
                break;
            case OTAUUpdateResponse_ErrorSFSValidationFailed:
                errorMessage = CSROTAUError_10;
                break;
            case OTAUUpdateResponse_ErrorOEMValidationFailed:
                errorMessage = CSROTAUError_11;
                break;
            case OTAUUpdateResponse_ErrorUpdateFailed:
                errorMessage = CSROTAUError_12;
                break;
            case OTAUUpdateResponse_ErrorAppNotReady:
                errorMessage = CSROTAUError_13;
                break;
            case OTAUUpdateResponse_WarnAppConfigVersionIncompatible:
                errorMessage = CSROTAUError_14;
                break;
            case OTAUUpdateResponse_ErrorLoaderError:
                errorMessage = CSROTAUError_15;
                break;
            case OTAUUpdateResponse_ErrorUnexpectedLoaderMessage:
                errorMessage = CSROTAUError_16;
                break;
            case OTAUUpdateResponse_ErrorMissingLoaderMessage:
                errorMessage = CSROTAUError_17;
                break;
            case OTAUUpdateResponse_ErrorBatteryLow:
                errorMessage = CSROTAUError_18;
                abortUpdate = NO;
                break;
            case OTAUUpdateResponse_ForceSync:
                errorMessage = @"";
                abortUpdate = NO;
                break;
            default:
                errorMessage = [NSString stringWithFormat:CSROTAUError_Unknown, (long)error_code];
                break;
        }
        
        if (errorMessage) {
            NSLog(@"OTAU update error: %ld %@", (long)error_code, errorMessage);
            
            if (abortUpdate) {
                [self resetUpdate];
            }
            
            if (error_code == OTAUUpdateResponse_ForceSync) {
                if (self.delegate && [self.delegate respondsToSelector:@selector(confirmForceUpgrade)]) {
                    [self.delegate confirmForceUpgrade];
                }
            } else if (error_code == OTAUUpdateResponse_ErrorBatteryLow) {
                if (self.delegate && [self.delegate respondsToSelector:@selector(confirmBatteryOkay)]) {
                    [self.delegate confirmBatteryOkay];
                }
            } else {
                [self.delegate didAbortWithError:[NSError
                                                  errorWithDomain:CSROTAUError
                                                  code:error_code
                                                  userInfo:@{CSROTAUErrorParam: errorMessage}]];
            }
        }
    }
    
    return error_code;
}

- (void)readProgress:(CSROTAUGattCommand *)command {
    NSData *payload = [command getPayload];
    const unsigned char *data = (const unsigned char *)[payload bytes];
    NSInteger progress = data[1];
    
    self.updateProgress = (double)progress / 100.0;
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(didMakeProgress:eta:)]) {
        [self.delegate didMakeProgress:progress eta:@""];
    }
}

- (void)updateTransferComplete {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)OTAUCommandAction_Continue;
    
    [payload appendBytes:&payload_event length:1];
    
    // A warm reboot will follow
    self.connectedPeripheral = [CSRConnectionManager sharedInstance].connectedPeripheral;
    
    NSLog(@"OTAUUpdate_TransferCompleteResult");
    
    [[CSROTAU sharedInstance]
     vmUpgradeControl:OTAUUpdate_TransferCompleteResult
     length:1
     data:payload];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(didWarmBoot)]) {
        [self.delegate didWarmBoot];
    }
}

- (void)updateComplete {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)OTAUCommandAction_Continue;
    
    [payload appendBytes:&payload_event length:1];
    
    NSLog(@"OTAUUpdate_InProgressResult");
    
    [[CSROTAU sharedInstance]
     vmUpgradeControl:OTAUUpdate_InProgressResult
     length:1
     data:payload];
}

- (void)complete {
    [self resetUpdate];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(didCompleteUpgrade)]) {
        [self.delegate didCompleteUpgrade];
    }
    
    [[CSRConnectionManager sharedInstance] removeDelegate:self];
}

- (void)abortUpdate {
    [self resetUpdate];
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(didAbortUpgrade)]) {
        [self.delegate didAbortUpgrade];
    }
    
    [[CSRConnectionManager sharedInstance] removeDelegate:self];
}

- (void)eraseSquifConf {
    NSLog(@"OTAUUpdate_HostEraseSquifConfirm");
    
    [[CSROTAU sharedInstance]
     vmUpgradeControlNoData:OTAUUpdate_HostEraseSquifConfirm];
}

- (void)commitConfirmRequest:(BOOL)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = value ? (uint8_t)OTAUCommandAction_Continue : (uint8_t)OTAUCommandAction_Abort;
    
    [payload appendBytes:&payload_event length:1];
    
    NSLog(@"OTAUUpdate_CommitConfirm");
    
    [[CSROTAU sharedInstance]
     vmUpgradeControl:OTAUUpdate_CommitConfirm
     length:1
     data:payload];
}

- (void)handleStartConfirm:(CSROTAUGattCommand *)command {
    if (self.resumePoint == OTAUUpdateResumePoint_Start) {
        NSData *requestPayload = [command getPayload];
        uint16_t length = 0;
        uint8_t status = 0;
        uint16_t batt = 0;
        
        [requestPayload getBytes:&length range:NSMakeRange(3, 2)];
        [requestPayload getBytes:&status range:NSMakeRange(4, 1)];
        [requestPayload getBytes:&batt range:NSMakeRange(5, 2)];
        
        if (status != OTAUUpdateResponse_Success) {
            [self abortWithError:command];
            [self resetUpdate];
        } else {
            NSLog(@"OTAUUpdate_StartDataRequest");
            self.startTime = [NSDate timeIntervalSinceReferenceDate];
            [[CSROTAU sharedInstance] vmUpgradeControlNoData:OTAUUpdate_StartDataRequest];
        }
    } else {
        switch (self.resumePoint) {
            case OTAUUpdateResumePoint_Start:
                [[CSROTAU sharedInstance] vmUpgradeControlNoData:OTAUUpdate_StartRequest];
                break;
            case OTAUUpdateResumePoint_Validate:
                [[CSROTAU sharedInstance] vmUpgradeControl:OTAUUpdate_IsValidationDoneRequest];
                break;
            case OTAUUpdateResumePoint_Reboot:
                if (self.delegate && [self.delegate respondsToSelector:@selector(confirmTransferRequired)]) {
                    [self.delegate confirmTransferRequired];
                } else {
                    [self updateTransferComplete];
                }
                break;
            case OTAUUpdateResumePoint_PostReboot:
                [self updateComplete];
                break;
            case OTAUUpdateResumePoint_Commit:
                [self commitConfirmRequest:YES];
                break;
            default:
                if (self.delegate && [delegate respondsToSelector:@selector(didAbortWithError:)]) {
                    NSString *msg = [NSString stringWithFormat:CSROTAUError_UnknownResponse, (long)self.resumePoint];
                    
                    self.updateInProgress = NO;
                    [self.delegate didAbortWithError:[NSError
                                                      errorWithDomain:CSROTAUError
                                                      code:0
                                                      userInfo:@{CSROTAUErrorParam: msg}]];
                }
                break;
        }
    }
}

- (void)handleSyncConfirm:(CSROTAUGattCommand *)command {
    NSData *requestPayload = [command getPayload];
    uint8_t state = 0;
    
    [requestPayload getBytes:&state range:NSMakeRange(4, 1)];
    
    // TODO: The protocol version number may be sent
    
    [[CSROTAU sharedInstance] vmUpgradeControlNoData:OTAUUpdate_StartRequest];
    
    self.resumePoint = state;
}

- (void)validationConfirm:(CSROTAUGattCommand *)command {
    NSData *requestPayload = [command getPayload];
    uint16_t delay = 0;
    
    [requestPayload getBytes:&delay range:NSMakeRange(4, 2)];
    
    delay = CFSwapInt16HostToBig(delay);
    
    if (delay > 0) {
        [NSTimer scheduledTimerWithTimeInterval:delay
                                         target:self
                                       selector:@selector(validationDone:)
                                       userInfo:nil
                                        repeats:NO];
    }
}

- (void)validationDone:(NSTimer *)timer {
    NSLog(@"OTAUUpdate_IsValidationDoneRequest");
    [[CSROTAU sharedInstance] vmUpgradeControl:OTAUUpdate_IsValidationDoneRequest];
}

- (NSData *)MD5:(NSData *)data {
    unsigned char buffer[CC_MD5_DIGEST_LENGTH];
    
    // Create 16 byte MD5 hash value, store in buffer
    CC_MD5(data.bytes, (CC_LONG)data.length, buffer);
    
    NSMutableData *hv = [[NSMutableData alloc] init];
    
    for (int i = 0; i < CC_MD5_DIGEST_LENGTH; i++) {
        [hv appendBytes:&buffer[i] length:sizeof(uint8_t)];
    }
    
    return hv;
}

@end
