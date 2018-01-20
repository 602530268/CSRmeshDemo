//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CSRConnectionManager.h"
#import "CSRCallbacks.h"
#import "CSRUtilities.h"
#import "CBPeripheral+Info.h"

#define CSRBluetoothErrorDomain         @"com.csr.bt"
#define CSRBluetoothErrorParam          @"name"
#define CSRBluetoothErrorService        @"The service named %@ could not be found"
#define CSRBluetoothErrorCharacter      @"The characteristic named %@ could not be found"

@interface CSRConnectionManager ()

@property (nonatomic) CBCentralManager *centralManager;
@property (nonatomic) NSMutableArray *serviceQueue;
@property (nonatomic) NSMutableDictionary *characteristicQueue;
@property (nonatomic) NSMutableDictionary *listening;
@property (nonatomic) NSArray *serviceUUIDs;

@end

@implementation CSRConnectionManager

@synthesize delegates;
@synthesize devices;
@synthesize connectedPeripheral;
@synthesize centralManager;
@synthesize isShuttingDown=_isShuttingDown;
@synthesize listening;
@synthesize serviceQueue;

+ (CSRConnectionManager *)sharedInstance {
    static dispatch_once_t pred;
    static CSRConnectionManager *shared = nil;
    
    dispatch_once(&pred, ^{
        shared = [[CSRConnectionManager alloc] init];
        
    });
    
    return shared;
}

- (id)init {
    if (self = [super init]) {
        self.centralManager = [[CBCentralManager alloc] initWithDelegate:self
                                                                   queue:nil];
        self.devices = [[NSMutableDictionary alloc] init];
        self.serviceQueue = [NSMutableArray array];
        self.characteristicQueue = [NSMutableDictionary dictionary];
        self.listening = [NSMutableDictionary dictionary];
        self.delegates = [NSMutableSet set];
        _isShuttingDown = NO;
    }
    
    return self;
}

- (void)shutDown {
    _isShuttingDown = YES;
    [self stopScan];
    [self clearListeners];
    
    NSDate *timeout = [NSDate dateWithTimeIntervalSinceNow:3];
    
    while ([[timeout laterDate:[NSDate date]] isEqualToDate:timeout]) {
        [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:1.0]];
    }
    
    [self disconnectPeripheral];
}

- (void)listenerRemovedNotification:(NSNotification *)notification {
    if ([[self.listening allKeys] count] > 0) {
        [self clearListener];
    } else {
        if (self.isShuttingDown) {
            [self disconnectPeripheral];
        }
    }
}

- (void)centralManager:(CBCentralManager *)central
      willRestoreState:(NSDictionary *)state {
    CBPeripheral *peripheral = [state[CBCentralManagerRestoredStatePeripheralsKey] firstObject];
    CSRPeripheral *p = [[CSRPeripheral alloc]
                        initWithCBPeripheral:peripheral
                        advertisementData:nil
                        rssi:0];
    
    [self.devices setObject:p forKey:peripheral.identifier];
    [self.serviceQueue removeAllObjects];
    [self.characteristicQueue removeAllObjects];
    [self.listening removeAllObjects];
    self.connectedPeripheral = p;
}

- (void)addDelegate:(id<CSRConnectionManagerDelegate>)delegate {
    if (![self.delegates containsObject:delegate]) {
        [self.delegates addObject:delegate];
    }
}

- (void)removeDelegate:(id<CSRConnectionManagerDelegate>)delegate {
    [self.delegates removeObject: delegate];
}

- (void)connectPeripheral:(CSRPeripheral *)peripheral {
    if (   self.connectedPeripheral
        && [self.connectedPeripheral.peripheral state] != CBPeripheralStateDisconnected) {
        [self disconnectPeripheral];
        self.connectedPeripheral = nil;
    }
    
    if (   peripheral && peripheral.peripheral
        && [connectedPeripheral.peripheral state] != CBPeripheralStateConnected) {
        [self.centralManager connectPeripheral:peripheral.peripheral
                                       options:nil];
    }
    
    [self.serviceQueue removeAllObjects];
    [self.characteristicQueue removeAllObjects];
    [self.listening removeAllObjects];
    self.connectedPeripheral = peripheral;
}

- (void)disconnectPeripheral {
    if (self.connectedPeripheral) {
        [self clearListeners];
        [self.centralManager
         cancelPeripheralConnection:self.connectedPeripheral.peripheral];
        self.connectedPeripheral = nil;
    }
}

- (void)startScan:(NSArray *)serviceUUIDs {
    if (serviceUUIDs) {
        _serviceUUIDs = serviceUUIDs;
    }
    
    if ([self.centralManager state] == CBCentralManagerStatePoweredOn) {
        // Show devices that are currently connected
        CBUUID *deviceInfoUUID = [CBUUID UUIDWithString:@"180F"];
        NSArray *array = [self.centralManager retrieveConnectedPeripheralsWithServices:@[deviceInfoUUID]];
        
        if (array && array.count > 0) {
            for (CBPeripheral *per in array) {
                CSRPeripheral *p = [[CSRPeripheral alloc]
                                    initWithCBPeripheral:per
                                    advertisementData:nil
                                    rssi:[NSNumber numberWithInteger:0]];
                [self.devices setObject:per forKey:per.name];
                
                [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
                    if ([obj respondsToSelector:@selector(didDiscoverPeripheral:)]) {
                        [obj didDiscoverPeripheral:p];
                    }
                }];
            }
        }
        
        [self.centralManager scanForPeripheralsWithServices:serviceUUIDs
                                                    options:nil];
    }
}

- (void)stopScan {
    [self.centralManager stopScan];
}

- (uint16_t)readDescriptor:(CBDescriptor *)descriptor {
    uint16_t value = 0;
    
    [self.connectedPeripheral.peripheral
     readValueForDescriptor:descriptor];
    
    [descriptor.value getBytes:&value range:NSMakeRange(5, sizeof(uint16_t))];
    
    return CFSwapInt16BigToHost(value);
}

- (void)getValueForService:(CBService *)service
            characteristic:(NSString *)charactaristic_uuid
                   failure:(void (^)(NSError *error))failure {
    if (service) {
        CBCharacteristic *characteristic = [self findCharacteristic:service characteristic:charactaristic_uuid];
        
        if (characteristic) {
            [self.connectedPeripheral.peripheral
             readValueForCharacteristic:characteristic];
        } else {
            [self.characteristicQueue removeObjectForKey:charactaristic_uuid];
            
            if (failure) failure([NSError errorWithDomain:CSRBluetoothErrorDomain
                                                     code:0
                                                 userInfo:@{CSRBluetoothErrorParam:
                                                                [NSString stringWithFormat:
                                                                 CSRBluetoothErrorCharacter,
                                                                 charactaristic_uuid]}]);
        }
    } else {
        [self.characteristicQueue removeObjectForKey:charactaristic_uuid];
        
        if (failure) failure([NSError errorWithDomain:CSRBluetoothErrorDomain
                                                 code:0
                                             userInfo:@{CSRBluetoothErrorParam:
                                                            [NSString stringWithFormat:
                                                             CSRBluetoothErrorService,
                                                             service.UUID.UUIDString]}]);
    }
}

- (void)getValue:(NSString *)service_uuid
  characteristic:(NSString *)charactaristic_uuid
         failure:(void (^)(NSError *error))failure {
    // Look up service and characteristic
    CBService *service = [self findService:service_uuid];
    
    if (service) {
        CBCharacteristic *characteristic = [self findCharacteristic:service characteristic:charactaristic_uuid];
        
        if (characteristic) {
            [self.connectedPeripheral.peripheral
             readValueForCharacteristic:characteristic];
        } else {
            [self.characteristicQueue removeObjectForKey:charactaristic_uuid];
            
            if (failure) failure([NSError errorWithDomain:CSRBluetoothErrorDomain
                                                     code:0
                                                 userInfo:@{CSRBluetoothErrorParam:
                                                                [NSString stringWithFormat:
                                                                 CSRBluetoothErrorCharacter,
                                                                 charactaristic_uuid]}]);
        }
    } else {
        [self.characteristicQueue removeObjectForKey:charactaristic_uuid];
        
        if (failure) failure([NSError errorWithDomain:CSRBluetoothErrorDomain
                                                 code:0
                                             userInfo:@{CSRBluetoothErrorParam:
                                                            [NSString stringWithFormat:
                                                             CSRBluetoothErrorService,
                                                             service_uuid]}]);
    }
}

- (void)setIntValue:(NSString *)service_uuid
     characteristic:(NSString *)charactaristic_uuid
              value:(NSInteger)value
            success:(void (^)())success
            failure:(void (^)(NSError *error))failure {
    // Look up service and characteristic
    CBService *service = [self findService:service_uuid];
    
    if (service) {
        CBCharacteristic *characteristic = [self findCharacteristic:service
                                                     characteristic:charactaristic_uuid];
        
        if (characteristic) {
            uint8_t val = value;
            NSData *valData = [NSData dataWithBytes:&val length:sizeof(val)];
            
            [self queueCharacteristicRequest:[[CSRCallbacks alloc]
                                              initWith:success
                                              failure:failure
                                              type:CSRCallbackType_SetInt]
                                        uuid:charactaristic_uuid];
            [self.connectedPeripheral.peripheral
             writeValue:valData
             forCharacteristic:characteristic
             type:CBCharacteristicWriteWithResponse];
        } else {
            [self.characteristicQueue removeObjectForKey:charactaristic_uuid];
            
            if (failure) failure([NSError errorWithDomain:CSRBluetoothErrorDomain
                                                     code:0
                                                 userInfo:@{CSRBluetoothErrorParam:
                                                                [NSString stringWithFormat:
                                                                 CSRBluetoothErrorCharacter,
                                                                 charactaristic_uuid]}]);
        }
    } else {
        [self.characteristicQueue removeObjectForKey:charactaristic_uuid];
        
        if (failure) failure([NSError errorWithDomain:CSRBluetoothErrorDomain
                                                 code:0
                                             userInfo:@{CSRBluetoothErrorParam:
                                                            [NSString stringWithFormat:
                                                             CSRBluetoothErrorService,
                                                             service_uuid]}]);
    }
}

- (void)setIntValue:(NSString *)service_uuid
     characteristic:(NSString *)charactaristic_uuid
              value:(NSInteger)value {
    CBService *service = [self findService:service_uuid];
    
    if (service) {
        CBCharacteristic *characteristic = [self findCharacteristic:service
                                                     characteristic:charactaristic_uuid];
        
        if (characteristic) {
            uint8_t val = value;
            NSData *valData = [NSData dataWithBytes:&val length:sizeof(val)];
            
            [self.connectedPeripheral.peripheral
             writeValue:valData
             forCharacteristic:characteristic
             type:CBCharacteristicWriteWithoutResponse];
        }
    }
}

- (void)setDataValue:(NSString *)service_uuid
      characteristic:(NSString *)charactaristic_uuid
               value:(NSData *)data {
    CBService *service = [self findService:service_uuid];
    
    if (service) {
        CBCharacteristic *characteristic = [self findCharacteristic:service
                                                     characteristic:charactaristic_uuid];
        
        if (characteristic) {
            [self.connectedPeripheral.peripheral
             writeValue:data
             forCharacteristic:characteristic
             type:CBCharacteristicWriteWithoutResponse];
        }
    }
}

- (void)setDataValue:(NSString *)service_uuid
      characteristic:(NSString *)charactaristic_uuid
               value:(NSData *)data
             success:(void (^)())success
             failure:(void (^)(NSError *error))failure {
    // Look up service and characteristic
    CBService *service = [self findService:service_uuid];
    
    if (service) {
        CBCharacteristic *characteristic = [self findCharacteristic:service
                                                     characteristic:charactaristic_uuid];
        
        if (characteristic) {
            [self queueCharacteristicRequest:[[CSRCallbacks alloc] initWith:success
                                                                    failure:failure
                                                                       type:CSRCallbackType_SetData]
                                        uuid:charactaristic_uuid];
            
            [self.connectedPeripheral.peripheral writeValue:data
                                          forCharacteristic:characteristic
                                                       type:CBCharacteristicWriteWithResponse];
        } else {
            [self.characteristicQueue removeObjectForKey:charactaristic_uuid];
            
            if (failure) failure([NSError errorWithDomain:CSRBluetoothErrorDomain
                                                     code:0
                                                 userInfo:@{CSRBluetoothErrorParam:[NSString stringWithFormat:CSRBluetoothErrorCharacter,charactaristic_uuid]}]);
        }
    } else {
        [self.characteristicQueue removeObjectForKey:charactaristic_uuid];
        
        if (failure) failure([NSError errorWithDomain:CSRBluetoothErrorDomain
                                                 code:0
                                             userInfo:@{CSRBluetoothErrorParam:[NSString stringWithFormat:CSRBluetoothErrorService,service_uuid]}]);
    }
}

- (void)queueCharacteristicRequest:(CSRCallbacks *)cbs uuid:(NSString *)uuid {
    if ([uuid hasPrefix:@"0x"]) {
        [self.characteristicQueue setObject:cbs
                                     forKey:[uuid
                                             stringByReplacingOccurrencesOfString:@"0x"
                                             withString:@""
                                             options:1
                                             range:NSMakeRange(0, 2)]];
    } else {
        [self.characteristicQueue setObject:cbs forKey:uuid];
    }
}

- (void)getBoolValue:(NSString *)service_uuid
      characteristic:(NSString *)charactaristic_uuid
             success:(void (^)(BOOL value))success
             failure:(void (^)(NSError *error))failure {
    CSRCallbacks *cbs = [[CSRCallbacks alloc]
                         initWith:success
                         failure:failure
                         type:CSRCallbackType_Bool];
    
    [self queueCharacteristicRequest:cbs uuid:charactaristic_uuid];
    [self getValue:service_uuid characteristic:charactaristic_uuid failure:failure];
}

- (void)getIntValue:(NSString *)service_uuid
     characteristic:(NSString *)charactaristic_uuid
            success:(void (^)(NSInteger value))success
            failure:(void (^)(NSError *error))failure {
    CSRCallbacks *cbs = [[CSRCallbacks alloc]
                         initWith:success
                         failure:failure
                         type:CSRCallbackType_Int];
    
    [self queueCharacteristicRequest:cbs uuid:charactaristic_uuid];
    [self getValue:service_uuid characteristic:charactaristic_uuid failure:failure];
}

- (void)getIntValueForService:(CBService *)service
               characteristic:(NSString *)charactaristic_uuid
                      success:(void (^)(NSInteger value))success
                      failure:(void (^)(NSError *error))failure {
    CSRCallbacks *cbs = [[CSRCallbacks alloc]
                         initWith:success
                         failure:failure
                         type:CSRCallbackType_Int];
    
    [self queueCharacteristicRequest:cbs uuid:charactaristic_uuid];
    [self getValueForService:service characteristic:charactaristic_uuid failure:failure];
}

- (void)getDoubleValue:(NSString *)service_uuid
        characteristic:(NSString *)charactaristic_uuid
               success:(void (^)(double value))success
               failure:(void (^)(NSError *error))failure {
    CSRCallbacks *cbs = [[CSRCallbacks alloc]
                         initWith:success
                         failure:failure
                         type:CSRCallbackType_Double];
    
    [self queueCharacteristicRequest:cbs uuid:charactaristic_uuid];
    [self getValue:service_uuid characteristic:charactaristic_uuid failure:failure];
}

- (void)getStringValue:(NSString *)service_uuid
        characteristic:(NSString *)charactaristic_uuid
               success:(void (^)(NSString *value))success
               failure:(void (^)(NSError *error))failure {
    CSRCallbacks *cbs = [[CSRCallbacks alloc]
                         initWith:success
                         failure:failure
                         type:CSRCallbackType_String];
    
    [self queueCharacteristicRequest:cbs uuid:charactaristic_uuid];
    [self getValue:service_uuid characteristic:charactaristic_uuid failure:failure];
}

- (BOOL)listenForService:(CBService *)service
          characteristic:(NSString *)charactaristic_uuid {
    if (service) {
        CBCharacteristic *characteristic = [self findCharacteristic:service characteristic:charactaristic_uuid];
        
        if (characteristic && !characteristic.isNotifying) {
            [self.listening setObject:characteristic forKey:characteristic.UUID.UUIDString];
            [self.connectedPeripheral.peripheral
             setNotifyValue:YES
             forCharacteristic:characteristic];
            return YES;
        } else {
            return NO;
        }
    } else {
        return NO;
    }
}

- (BOOL)listenFor:(NSString *)service_uuid
   characteristic:(NSString *)charactaristic_uuid {
    CBService *service = [self findService:service_uuid];
    
    if (service) {
        CBCharacteristic *characteristic = [self findCharacteristic:service characteristic:charactaristic_uuid];
        
        if (characteristic) {
            if (![self.listening objectForKey:characteristic.UUID.UUIDString]) {
                [self.listening setObject:characteristic forKey:characteristic.UUID.UUIDString];
                [self.connectedPeripheral.peripheral
                 setNotifyValue:YES
                 forCharacteristic:characteristic];
            }
            return YES;
        } else {
            return NO;
        }
    } else {
        return NO;
    }
}


- (void)clearListener {
    if (self.connectedPeripheral.peripheral.state == CBPeripheralStateConnected) {
        NSString *uuid = [[self.listening allKeys] firstObject];
        CBCharacteristic *characteristic = [self findCharacteristic:uuid];
        
        if (characteristic) {
            [self.connectedPeripheral.peripheral
             setNotifyValue:NO
             forCharacteristic:characteristic];
        }
    }
}

- (void)clearListener:(NSString *)service_uuid
       characteristic:(NSString *)charactaristic_uuid {
    CBService *service = [self findService:service_uuid];
    
    if (service) {
        CBCharacteristic *characteristic = [self findCharacteristic:service characteristic:charactaristic_uuid];
        
        if (characteristic) {
            [self.connectedPeripheral.peripheral
             setNotifyValue:NO
             forCharacteristic:characteristic];
        }
    }
}

- (void)clearListeners {
    if (self.connectedPeripheral.peripheral.state == CBPeripheralStateConnected) {
        for (NSString *uuid in self.listening) {
            CBCharacteristic *characteristic = [self findCharacteristic:uuid];
            
            if (characteristic && characteristic.isNotifying) {
                [self.connectedPeripheral.peripheral
                 setNotifyValue:NO
                 forCharacteristic:characteristic];
            }
        }
    }
    
    [self.listening removeAllObjects];
}

- (void)updateRSSI {
    if (self.connectedPeripheral.peripheral.state == CBPeripheralStateConnected) {
        [self.connectedPeripheral.peripheral readRSSI];
    }
}

#pragma mark CBCentralManager delegate

- (void)centralManagerDidUpdateState:(CBCentralManager *)central {
    switch ([central state]) {
        case CBCentralManagerStatePoweredOn:
            NSLog(@"Central powered ON");
            [self startScan:_serviceUUIDs];
            [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
                if ([obj respondsToSelector:@selector(didPowerOn)]) {
                    [obj didPowerOn];
                }
            }];
            break;
        case CBCentralManagerStatePoweredOff:
            NSLog(@"Central Powered OFF");
            [self stopScan];
            [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
                if ([obj respondsToSelector:@selector(didPowerOff)]) {
                    [obj didPowerOff];
                }
            }];
            break;
        case CBCentralManagerStateUnauthorized:
        case CBCentralManagerStateUnknown:
        case CBCentralManagerStateUnsupported:
        case CBCentralManagerStateResetting:
            break;
    }
}

- (void)centralManager:(CBCentralManager *)central
 didDiscoverPeripheral:(CBPeripheral *)peripheral
     advertisementData:(NSDictionary *)advertisementData
                  RSSI:(NSNumber *)RSSI {
    if (peripheral.name) {
        NSLog(@"Identifer: %@, name: %@, services: %@, description: %@",
              [peripheral identifier],
              [peripheral name],
              [peripheral services],
              [advertisementData description]);
        CSRPeripheral *p = [[CSRPeripheral alloc]
                            initWithCBPeripheral:peripheral
                            advertisementData:advertisementData
                            rssi:RSSI];
        [self.devices setObject:p forKey:peripheral.identifier];
        
        [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
            if ([obj respondsToSelector:@selector(didDiscoverPeripheral:)]) {
                [obj didDiscoverPeripheral:p];
            }
        }];
    }
}

- (void)centralManager:(CBCentralManager *)central
  didConnectPeripheral:(CBPeripheral *)peripheral {
    NSLog(@"Connected to peripheral: %@", peripheral.identifier.UUIDString);
    
    if (self.connectedPeripheral && self.connectedPeripheral.peripheral != peripheral) {
        [self disconnectPeripheral];
        connectedPeripheral = nil;
    }
    
    self.connectedPeripheral.peripheral = peripheral;
    
    peripheral.delegate = self;
    
    [peripheral discoverServices:nil];
    
    [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
        if ([obj respondsToSelector:@selector(didConnectToPeripheral:)]) {
            CSRPeripheral *p = [self.devices objectForKey:peripheral.identifier];
            
            [obj didConnectToPeripheral:p];
        }
    }];
}

- (void)centralManager:(CBCentralManager *)central
didDisconnectPeripheral:(CBPeripheral *)peripheral
                 error:(NSError *)error {
    NSLog(@"Disconnecting from peripheral: %@\n%@",
          peripheral.identifier.UUIDString,
          error ? error.localizedDescription : @"");
    [self clearListeners];
    
    [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
        if ([obj respondsToSelector:@selector(didDisconnectFromPeripheral:)]) {
            [obj didDisconnectFromPeripheral:peripheral];
        }
    }];
}

#pragma mark Peripheral delegate methods

- (void)peripheral:(CBPeripheral *)peripheral
didDiscoverServices:(NSError *)error {
    if (!error) {
        if (peripheral.state == CBPeripheralStateConnected) {
            [self.serviceQueue removeAllObjects];
            [self.serviceQueue addObjectsFromArray:peripheral.services];
            
            for (CBService *service in peripheral.services) {
                NSLog(@"Service %@", service.UUID);
                [peripheral discoverCharacteristics:nil forService:service];
            }
        }
    } else {
        NSLog(@"didDiscoverServices error: %@", error.localizedDescription);
    }
}

- (void)peripheral:(CBPeripheral *)peripheral
didDiscoverCharacteristicsForService:(CBService *)service
             error:(NSError *)error  {
    if (!error) {
        for (CBCharacteristic *characteristic in service.characteristics) {
            NSLog(@"Charcteristic %@",characteristic.UUID);
            [peripheral discoverDescriptorsForCharacteristic:characteristic];
        }
    } else {
        NSLog(@"didDiscoverCharacteristicsForService error: %@", error.localizedDescription);
    }
    
    [self.serviceQueue removeObject:service];
    
    if (self.serviceQueue.count == 0) {
        [self.connectedPeripheral.peripheral readRSSI];
        
        [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
            if ([obj respondsToSelector:@selector(discoveredPripheralDetails)]) {
                [obj discoveredPripheralDetails];
            }
        }];
    }
}

- (void)peripheral:(CBPeripheral *)peripheral
didDiscoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error {
    if (error) {
        NSLog(@"Charcteristic %@ Error: %@",characteristic.UUID, error.localizedDescription);
    }
}

- (void)peripheral:(CBPeripheral *)peripheral
didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error {
    CSRCallbacks *cbs = [self.characteristicQueue objectForKey:characteristic.UUID.UUIDString];
    
    if (!error) {
        // First notify anything listening for updates
        if ([self.listening objectForKey:characteristic.UUID.UUIDString]) {
            [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
                if ([obj respondsToSelector:@selector(chracteristicChanged:)]) {
                    [obj chracteristicChanged:characteristic];
                }
            }];
        }
        
        if (cbs) {
            if (cbs.successCallback) {
                switch (cbs.callbackType) {
                    case CSRCallbackType_Bool: {
                        CSRGetBoolCompletion cb = cbs.successCallback;
                        
                        cb([CSRUtilities boolValue:characteristic.value]);
                        break;
                    }
                    case CSRCallbackType_Int: {
                        CSRGetIntCompletion cb = cbs.successCallback;
                        
                        cb([CSRUtilities intValue:characteristic.value]);
                        break;
                    }
                    case CSRCallbackType_Double: {
                        CSRGetIntCompletion cb = cbs.successCallback;
                        
                        cb([CSRUtilities doubleValue:characteristic.value offset:0]);
                        break;
                    }
                    case CSRCallbackType_String: {
                        CSRGetStringCompletion cb = cbs.successCallback;
                        
                        cb([CSRUtilities stringValue:characteristic.value]);
                        break;
                    }
                    case CSRCallbackType_SetInt:
                    case CSRCallbackType_SetBool:
                    case CSRCallbackType_SetData:
                    case CSRCallbackType_SetString: {
                        CSRSetValueCompletion cb = cbs.successCallback;
                        
                        cb();
                        break;
                    }
                }
            }
            
            [self.characteristicQueue removeObjectForKey:characteristic.UUID.UUIDString];
        }
    } else {
        NSLog(@"didUpdateValueForCharacteristic error: %@", error.localizedDescription);
        
        if (cbs) {
            if (cbs.failureCallback) {
                CSRErrorCompletion cc = cbs.failureCallback;
                
                cc(error);
            }
            
            [self.characteristicQueue removeObjectForKey:characteristic.UUID.UUIDString];
        }
    }
}

- (void)peripheral:(CBPeripheral *)peripheral
didWriteValueForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error {
    CSRCallbacks *cbs = [self.characteristicQueue objectForKey:characteristic.UUID.UUIDString];
    
    if (error) {
        NSLog(@"didWriteValueForCharacteristic error: %@", error.localizedDescription);
        
        if (cbs) {
            if (cbs.failureCallback) {
                CSRErrorCompletion cc = cbs.failureCallback;
                
                cc(error);
            }
            
            [self.characteristicQueue removeObjectForKey:characteristic.UUID.UUIDString];
        }
    } else {
        if (cbs) {
            if (cbs.successCallback) {
                CSRSetValueCompletion sv = cbs.successCallback;
                
                sv();
            }
            
            [self.characteristicQueue removeObjectForKey:characteristic.UUID.UUIDString];
        }
    }
    
    [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
        if ([obj respondsToSelector:@selector(peripheral:didWriteValueForCharacteristic:error:)]) {
            CSRPeripheral *p = [self.devices objectForKey:peripheral.identifier];
            
            [obj peripheral:p didWriteValueForCharacteristic:characteristic error:error];
        }
    }];
}

// Listening for values updated on the peripheral
- (void)peripheral:(CBPeripheral *)peripheral
didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error {
    if (!error) {
        NSLog(@"didUpdateNotificationStateForCharacteristic %@ %@", characteristic, characteristic.UUID);
        
        // If the state is listening...
        if (characteristic.isNotifying) {
            // If there is no value then force a read
            if (!characteristic.value) {
                [peripheral
                 readValueForCharacteristic:characteristic];
            } else { // If there is a value then check for listeners and callbacks and continue
                if ([self.listening objectForKey:characteristic.UUID.UUIDString]) {
                    [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
                        if ([obj respondsToSelector:@selector(chracteristicChanged:)]) {
                            [obj chracteristicChanged:characteristic];
                        }
                    }];
                }
            }
        }
    } else {
        NSLog(@"Update peripheral: %@ Error: %@", characteristic.UUID.UUIDString, error.localizedDescription);
    }
}

- (void)peripheralDidUpdateRSSI:(CBPeripheral *)peripheral
                          error:(NSError *)error {
    self.connectedPeripheral.signalStrength = peripheral.rssi;
    
    [self.delegates enumerateObjectsUsingBlock:^(id obj, BOOL *stop) {
        if ([obj respondsToSelector:@selector(didUpdateRSSI)]) {
            [obj didUpdateRSSI];
        }
    }];
}

#pragma mark Private methods

- (CBService *)findService:(CBPeripheral *)peripheral
                      uuid:(NSString *)service_uuid {
    @try {
        CBUUID *serviceUUID = [CBUUID UUIDWithString:service_uuid];
        
        for (CBService *service in peripheral.services) {
            if ([service.UUID isEqual:serviceUUID]) {
                return service;
            }
        }
    } @catch(NSException *ex) {
        for (CBService *service in peripheral.services) {
            if ([service.UUID.UUIDString isEqualToString:service_uuid]) {
                return service;
            }
        }
    }
    
    return nil;
}

- (CBService *)findService:(NSString *)service_uuid {
    return [self findService:self.connectedPeripheral.peripheral
                        uuid:service_uuid];
}

- (CBCharacteristic *)findCharacteristic:(NSString *)characteristic_uuid {
    @try {
        CBUUID *characteristicUUID = [CBUUID UUIDWithString:characteristic_uuid];
        
        for (CBService *service in self.connectedPeripheral.peripheral.services) {
            for (CBCharacteristic *character in service.characteristics) {
                if ([character.UUID isEqual:characteristicUUID]) {
                    return character;
                }
            }
        }
    } @catch(NSException *ex) {
        for (CBService *service in self.connectedPeripheral.peripheral.services) {
            for (CBCharacteristic *character in service.characteristics) {
                if ([character.UUID.UUIDString isEqualToString:characteristic_uuid]) {
                    return character;
                }
            }
        }
    }
    
    return nil;
}

- (CBCharacteristic *)findCharacteristic:(CBService *)service
                          characteristic:(NSString *)characteristic_uuid {
    @try {
        CBUUID *characteristicUUID = [CBUUID UUIDWithString:characteristic_uuid];
        
        for (CBCharacteristic *character in service.characteristics) {
            if ([character.UUID isEqual:characteristicUUID]) {
                return character;
            }
        }
    } @catch(NSException *ex) {
        for (CBCharacteristic *character in service.characteristics) {
            if ([character.UUID.UUIDString isEqualToString:characteristic_uuid]) {
                return character;
            }
        }
    }
    
    return nil;
}

- (CBCharacteristic *)findServiceCharacteristic:(NSString *)service_uuid
                                 characteristic:(NSString *)characteristic_uuid {
    CBUUID *serviceUUID = [CBUUID UUIDWithString:service_uuid];
    CBUUID *characteristicUUID = [CBUUID UUIDWithString:characteristic_uuid];
    
    for (CBService *service in self.connectedPeripheral.peripheral.services) {
        if ([service.UUID isEqual:serviceUUID]) {
            for (CBCharacteristic *character in service.characteristics) {
                if ([character isEqual:characteristicUUID]) {
                    return character;
                }
            }
        }
    }
    
    return nil;
}

@end
