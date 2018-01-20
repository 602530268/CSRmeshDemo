//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CSROTAU.h"

@interface CSROTAU ()

@property (nonatomic) CSRPeripheral *connectedPeripheral;

@end

@implementation CSROTAU

@synthesize connectedPeripheral;

@synthesize fileMD5;

+ (CSROTAU *)sharedInstance {
    static dispatch_once_t pred;
    static CSROTAU *shared = nil;
    
    dispatch_once(&pred, ^{
        shared = [[CSROTAU alloc] init];
    });
    
    return shared;
}

- (void)connectPeripheral:(CSRPeripheral *)peripheral {
    self.connectedPeripheral = peripheral;
    self.service = [[CSRConnectionManager sharedInstance] findService:UUID_OTAU_SERVICE];
    
    if (self.service) {
        self.commandCharacteristic = [[CSRConnectionManager sharedInstance]
                                      findCharacteristic:self.service
                                      characteristic:UUID_OTAU_COMMAND_ENDPOINT];
        self.responseCharacteristic = [[CSRConnectionManager sharedInstance]
                                       findCharacteristic:self.service
                                       characteristic:UUID_OTAU_RESPONSE_ENDPOINT];
        self.dataCharacteristic = [[CSRConnectionManager sharedInstance]
                                   findCharacteristic:self.service
                                   characteristic:UUID_OTAU_DATA_ENDPOINT];
        
        if (self.responseCharacteristic) {
            [[CSRConnectionManager sharedInstance]
             listenFor:UUID_OTAU_SERVICE
             characteristic:UUID_OTAU_RESPONSE_ENDPOINT];
        }
    }
}

- (void)disconnectPeripheral {
    self.connectedPeripheral = nil;
    self.service = nil;
    self.commandCharacteristic = nil;
    self.responseCharacteristic = nil;
    self.dataCharacteristic = nil;
}

#pragma mark public OTAU commands

- (void)handleResponse:(CBCharacteristic *)characteristic {
    if ([characteristic isEqual:self.responseCharacteristic]) {
        [self processIncomingResponse:characteristic.value];
    }
}

- (void)noOperation {
    [self sendCommand:OTAUCommand_NoOperation
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)getApiVersion {
    [self sendCommand:OTAUCommand_GetApplicationVersion
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)getLEDState {
    [self sendCommand:OTAUCommand_GetLEDControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)setLED:(BOOL)enabled {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = 0;
    
    if (enabled) {
        payload_event = 1;
    }
    
    [payload appendBytes:&payload_event length:1];
    
    [self sendCommand:OTAUCommand_SetLEDControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)getBattery {
    [self sendCommand:OTAUCommand_GetCurrentBatteryLevel
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)setVolume:(NSInteger)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)value;
    
    [payload appendBytes:&payload_event length:1];
    
    [self sendCommand:OTAUCommand_Volume
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)trimTWSVolume:(NSInteger)device volume:(NSInteger)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t dev = (uint8_t)device;
    uint8_t volume = (uint8_t)value;
    
    [payload appendBytes:&dev length:1];
    [payload appendBytes:&volume length:1];
    
    [self sendCommand:OTAUCommand_TrimTWSVolume
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)getTWSVolume:(NSInteger)device {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t dev = (uint8_t)device;
    
    [payload appendBytes:&dev length:1];
    
    [self sendCommand:OTAUCommand_GetTWSVolume
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)setTWSVolume:(NSInteger)device volume:(NSInteger)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t dev = (uint8_t)device;
    uint8_t volume = (uint8_t)value;
    
    [payload appendBytes:&dev length:1];
    [payload appendBytes:&volume length:1];
    
    [self sendCommand:OTAUCommand_SetTWSVolume
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)getTWSRouting:(NSInteger)device {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t dev = (uint8_t)device;
    
    [payload appendBytes:&dev length:sizeof(uint8_t)];
    [self sendCommand:OTAUCommand_GetTWSAudioRouting
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)setTWSRouting:(NSInteger)device routing:(NSInteger)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t dev = (uint8_t)device;
    uint8_t routing = (uint8_t)value;
    
    [payload appendBytes:&dev length:1];
    [payload appendBytes:&routing length:1];
    
    [self sendCommand:OTAUCommand_SetTWSAudioRouting
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)getBassBoost {
    [self sendCommand:OTAUCommand_GetBassBoostControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)setBassBoost:(BOOL)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t boost = (uint8_t)value;
    
    [payload appendBytes:&boost length:1];
    
    [self sendCommand:OTAUCommand_SetBassBoostControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)get3DEnhancement {
    [self sendCommand:OTAUCommand_Get3DEnhancementControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)set3DEnhancement:(BOOL)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t boost = (uint8_t)value;
    
    [payload appendBytes:&boost length:1];
    
    [self sendCommand:OTAUCommand_Set3DEnhancementControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)getAudioSource {
    [self sendCommand:OTAUCommand_GetAudioSource
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)findMe:(NSUInteger)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t level = (uint8_t)value;
    
    [payload appendBytes:&level length:1];
    
    [self sendCommand:OTAUCommand_FindMe
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)setAudioSource:(OTAUAudioSource)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t boost = (uint8_t)value;
    
    [payload appendBytes:&boost length:1];
    
    [self sendCommand:OTAUCommand_SetAudioSource
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)getUserEQ {
    [self sendCommand:OTAUCommand_GetUserEQControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)setUserEQ:(BOOL)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t user_eq = (uint8_t)value;
    
    [payload appendBytes:&user_eq length:1];
    [self sendCommand:OTAUCommand_SetUserEQControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)getEQControl {
    [self sendCommand:OTAUCommand_GetEQControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)setEQControl:(NSInteger)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t boost = (uint8_t)value;
    
    [payload appendBytes:&boost length:1];
    
    [self sendCommand:OTAUCommand_SetEQControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}


- (void)getGroupEQParam:(NSData *)data {
    [self sendCommand:OTAUCommand_GetEQGroupParameter
               vendor:CSR_OTAU_VENDOR_ID
                 data:data];
}

- (void)setGroupEQParam:(NSData *)data {
    [self sendCommand:OTAUCommand_SetEQGroupParameter
               vendor:CSR_OTAU_VENDOR_ID
                 data:data];
}

- (void)getPower {
    [self sendCommand:OTAUCommand_GetPowerState
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)setPowerOn:(BOOL)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t boost = (uint8_t)value;
    
    [payload appendBytes:&boost length:1];
    [self sendCommand:OTAUCommand_SetPowerState
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)setFilterType:(NSInteger)bank band:(NSInteger)band value:(NSInteger)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t param = 0; // 0 - FilterType, 1 Frequency, 2 - Gain, Q - 3
    uint16_t paramId = CFSwapInt16(((((bank) & 0xf) << 8) ^ (((band) & 0xf) << 4) ^ (param & 0xf)));
    uint16_t writeValue = CFSwapInt16(value);
    uint8_t update = 1;
    
    [payload appendBytes:&paramId length:sizeof(uint16_t)];
    [payload appendBytes:&writeValue length:sizeof(uint16_t)];
    [payload appendBytes:&update length:sizeof(uint8_t)];
    
    [self sendCommand:OTAUCommand_SetEQParameter
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
    
}

- (void)setFilterFrequency:(NSInteger)bank band:(NSInteger)band value:(double)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t param = 1; // 0 - FilterType, 1 Frequency, 2 - Gain, Q - 3
    uint16_t paramId = CFSwapInt16(((((bank) & 0xf) << 8) ^ (((band) & 0xf) << 4) ^ (param & 0xf)));
    uint16_t writeValue = CFSwapInt16(value * 3.0);
    uint8_t update = 1;
    
    [payload appendBytes:&paramId length:sizeof(uint16_t)];
    [payload appendBytes:&writeValue length:sizeof(uint16_t)];
    [payload appendBytes:&update length:sizeof(uint8_t)];
    
    [self sendCommand:OTAUCommand_SetEQParameter
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)setFilterGain:(NSInteger)bank band:(NSInteger)band value:(double)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t param = 2; // 0 - FilterType, 1 Frequency, 2 - Gain, Q - 3
    uint16_t paramId = CFSwapInt16(((((bank) & 0xf) << 8) ^ (((band) & 0xf) << 4) ^ (param & 0xf)));
    uint16_t writeValue = CFSwapInt16(value * 60);
    uint8_t update = 1;
    
    [payload appendBytes:&paramId length:sizeof(uint16_t)];
    [payload appendBytes:&writeValue length:sizeof(uint16_t)];
    [payload appendBytes:&update length:sizeof(uint8_t)];
    
    [self sendCommand:OTAUCommand_SetEQParameter
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)setFilterQ:(NSInteger)bank band:(NSInteger)band value:(double)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t param = 3; // 0 - FilterType, 1 Frequency, 2 - Gain, Q - 3
    uint16_t paramId = CFSwapInt16(((((bank) & 0xf) << 8) ^ (((band) & 0xf) << 4) ^ (param & 0xf)));
    uint16_t writeValue = CFSwapInt16(value * 4095);
    uint8_t update = 1;
    
    [payload appendBytes:&paramId length:sizeof(uint16_t)];
    [payload appendBytes:&writeValue length:sizeof(uint16_t)];
    [payload appendBytes:&update length:sizeof(uint8_t)];
    
    [self sendCommand:OTAUCommand_SetEQParameter
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)setFilterPreGain:(NSInteger)bank band:(NSInteger)band value:(double)value {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t param = 1; // 0 - FilterType, 1 Frequency, 2 - Gain, Q - 3
    uint16_t paramId = CFSwapInt16(((((bank) & 0xf) << 8) ^ (param & 0xf)));
    uint16_t writeValue = CFSwapInt16(value * 60);
    uint8_t update = 1;
    
    [payload appendBytes:&paramId length:sizeof(uint16_t)];
    [payload appendBytes:&writeValue length:sizeof(uint16_t)];
    [payload appendBytes:&update length:sizeof(uint8_t)];
    
    [self sendCommand:OTAUCommand_SetEQParameter
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)avControl:(OTAUAVControlOperation)operation {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)operation;
    
    [payload appendBytes:&payload_event length:sizeof(uint8_t)];
    
    [self sendCommand:OTAUCommand_AVRemoteControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)transmitData:(NSData *)data {
    if (self.dataCharacteristic) {
        [self.connectedPeripheral.peripheral
         writeValue:data
         forCharacteristic:self.dataCharacteristic
         type:CBCharacteristicWriteWithoutResponse];
    }
}

- (void)registerNotifications:(OTAUEvent)eventType {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)eventType;
    
    [payload appendBytes:&payload_event length:1];
    
    [self sendCommand:OTAUCommand_RegisterNotification
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)cancelNotifications:(OTAUEvent)eventType {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)eventType;
    
    [payload appendBytes:&payload_event length:1];
    
    [self sendCommand:OTAUCommand_CancelNotification
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)vmUpgradeConnect {
    [self sendCommand:OTAUCommand_VMUpgradeConnect
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)vmUpgradeDisconnect {
    [self sendCommand:OTAUCommand_VMUpgradeDisconnect
               vendor:CSR_OTAU_VENDOR_ID
                 data:nil];
}

- (void)abort {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)OTAUUpdate_AbortRequest;
    uint16_t len = 0;
    
    [payload appendBytes:&payload_event length:sizeof(uint8_t)];
    [payload appendBytes:&len length:sizeof(uint16_t)];
    
    [self sendCommand:OTAUCommand_VMUpgradeControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)vmUpgradeControl:(OTAUCommandUpdate)command {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint16_t len = CFSwapInt16(4);
    uint8_t payload_event = (uint8_t)command;
    NSData *md5 = [self.fileMD5 subdataWithRange:NSMakeRange(12, 4)];
    
    [payload appendBytes:&payload_event length:1];
    [payload appendBytes:&len length:2];
    [payload appendData:md5];
    
    [self sendCommand:OTAUCommand_VMUpgradeControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)vmUpgradeControlNoData:(OTAUCommandUpdate)command {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)command;
    uint16_t len = 0;
    
    [payload appendBytes:&payload_event length:1];
    [payload appendBytes:&len length:2];
    
    [self sendCommand:OTAUCommand_VMUpgradeControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (void)vmUpgradeControl:(OTAUCommandUpdate)command
                  length:(NSInteger)length
                    data:(NSData *)data {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)command;
    uint16_t len = CFSwapInt16(length);
    
    [payload appendBytes:&payload_event length:1];
    [payload appendBytes:&len length:2];
    [payload appendData:data];
    
    [self sendCommand:OTAUCommand_VMUpgradeControl
               vendor:CSR_OTAU_VENDOR_ID
                 data:payload];
}

- (NSData *)vmUpgradeControlData:(OTAUCommandUpdate)command
                          length:(NSInteger)length
                            data:(NSData *)data {
    NSMutableData *payload = [[NSMutableData alloc] init];
    uint8_t payload_event = (uint8_t)command;
    uint16_t len = CFSwapInt16(length);
    
    [payload appendBytes:&payload_event length:1];
    [payload appendBytes:&len length:2];
    [payload appendData:data];
    
    return [self dataForCommand:OTAUCommand_VMUpgradeControl
                         vendor:CSR_OTAU_VENDOR_ID
                           data:payload];
}

#pragma mark private OTAU commands

- (NSData *)dataForCommand:(OTAUCommandType)command
                    vendor:(uint16_t)vendor_id
                      data:(NSData *)params {
    if (self.commandCharacteristic) {
        CSROTAUGattCommand *cmd = [[CSROTAUGattCommand alloc] initWithLength:OTAU_GATT_HEADER_SIZE];
        
        if (cmd) {
            [cmd setCommandId:command];
            [cmd setVendorId:vendor_id];
            
            if (params) {
                [cmd addPayload:params];
            }
            
            return [cmd getPacket];
        }
    }
    
    return nil;
}

- (void)sendCommand:(OTAUCommandType)command
             vendor:(uint16_t)vendor_id
               data:(NSData *)params {
    if (self.commandCharacteristic) {
        CSROTAUGattCommand *cmd = [[CSROTAUGattCommand alloc] initWithLength:OTAU_GATT_HEADER_SIZE];
        
        if (cmd) {
            [cmd setCommandId:command];
            [cmd setVendorId:vendor_id];
            
            if (params) {
                [cmd addPayload:params];
            }
            
            NSData *packet = [cmd getPacket];
            
            NSLog(@"Outgoing packet: %@", packet);
            
            [self.connectedPeripheral.peripheral
             writeValue:packet
             forCharacteristic:self.commandCharacteristic
             type:CBCharacteristicWriteWithResponse];
        }
    }
}

- (void)sendData:(NSData *)data {
    NSLog(@"Outgoing packet: %@", data);
    [self.connectedPeripheral.peripheral
     writeValue:data
     forCharacteristic:self.commandCharacteristic
     type:CBCharacteristicWriteWithResponse];
}

- (void)processIncomingResponse:(NSData *)data {
    if (self.delegate && [self.delegate respondsToSelector:@selector(didReceiveResponse:)]) {
        CSROTAUGattCommand *command = [[CSROTAUGattCommand alloc]
                                       initWithNSData:data];
        
        NSLog(@"Incoming packet: %@", data);
        
        [self.delegate didReceiveResponse:command];
    }
}

@end
