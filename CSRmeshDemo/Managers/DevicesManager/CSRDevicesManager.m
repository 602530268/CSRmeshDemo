//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CSRDevicesManager.h"
#import "CSRDatabaseManager.h"
#import "CSRBluetoothLE.h"
#import "CSRUtilities.h"
#import "CSRConstants.h"
//#import "CSRDevicesListViewController.h"
#import "CSRAppStateManager.h"
#import <CSRmesh/SensorModelApi.h>
#import <CSRmesh/ActuatorModelApi.h>
#import "CSRConstants.h"
#import "CSRWatchManager.h"
#import <CSRmeshRestClient/CSRRestMeshConfigApi.h>

@interface CSRDevicesManager()

@property (atomic)  NSMutableDictionary *meshRequests;
@property (nonatomic) NSMutableData *m1Data;
@property (nonatomic) NSData *localHash;

@end

@implementation CSRDevicesManager

//static CSRDevicesManager *this	= nil;

#pragma mark - Singleton methods

+ (CSRDevicesManager*)sharedInstance
{
    static dispatch_once_t token;
    static CSRDevicesManager *shared = nil;
    
    dispatch_once(&token, ^{
        shared = [[CSRDevicesManager alloc] init];
    });
    
    return shared;
}

- (id)init
{
    if (self = [super init]) {
        
        _unassociatedMeshDevices = [NSMutableArray new];
        _scannedMeshDevices = [NSMutableArray new];
        _meshDevices = [NSMutableArray new];
        _meshAreas = [NSMutableArray new];
        _deviceDictionary = [NSMutableDictionary new];
        [[SensorModelApi sharedInstance] addDelegate:self];
        
        [NSTimer scheduledTimerWithTimeInterval:0.12 target:self selector:@selector(nsTimerMainQCall) userInfo:nil repeats:YES];
        
        _m1Data = [NSMutableData new];
        
    }
    return self;
}

#pragma mark - NSOperationQueue methods

-(void) nsTimerMainQCall {
    
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        [self timerInMainLoop];
    }];
}


- (void) timerInMainLoop
{
    @synchronized (self) {
        for (CSRmeshDevice *meshDevice in _meshDevices) {
            if (meshDevice.isAssociated) {
                [meshDevice timedMethods];
                
            }
        }
        for (CSRmeshArea *meshArea in _meshAreas) {
            CSRmeshDevice *meshDevice = meshArea.areaDevice;
            if (meshDevice.isAssociated) {
                [meshDevice timedMethods];
                
            }
        }
        
    }
    
}


#pragma mark - Device

- (void)createDeviceFromProperties:(NSDictionary *)deviceProperties
{
    
    CSRmeshDevice *device;
    BOOL isNewDevice = NO;
    @synchronized (self) {
    
        if (deviceProperties[kDEVICE_HASH]) {
            
            NSData *deviceHash = deviceProperties[kDEVICE_HASH];
            device = _deviceDictionary[deviceHash];
            if (device == nil) {
                
                device = [[CSRmeshDevice alloc] initDatabaseDevice:deviceProperties];
                [_deviceDictionary setObject:device forKey:deviceHash];
                
                isNewDevice = YES;
                
            } else {
                
                device = [device initDatabaseDevice:deviceProperties];
                

                
            }
            
            if (device.isAssociated) {
                [_meshDevices addObject:device];
            } else {
                [_scannedMeshDevices addObject:device];
            }
        }
        
        if (device && deviceProperties[kDEVICE_NUMBER]) {
            NSNumber *deviceNumber = deviceProperties[kDEVICE_NUMBER];
            if (_deviceDictionary[deviceNumber]  == nil || isNewDevice)
                [_deviceDictionary setObject:device forKey:deviceNumber];
        }
    }
}

- (CSRmeshDevice *)getDeviceWithDevicePredicate:(NSData*)value
{
    CSRmeshDevice *meshDevice;
    if (value) {
     meshDevice = _deviceDictionary [value];
        
    }
    
    return meshDevice;
}

- (void)addScannedDevice:(CSRmeshDevice*)mDevice
{
    [_scannedMeshDevices addObject:mDevice];
}

// ADD a new device if required.
- (CSRmeshDevice *)addDeviceWithUUID:(CBUUID *)uuid andRSSI:(NSNumber *)rssi
{
    NSData *deviceHash = [[MeshServiceApi sharedInstance] getDeviceHashFromUuid:uuid];
    if (!_deviceDictionary[deviceHash]) {
        CSRmeshDevice *meshDevice = [[CSRmeshDevice alloc] init];
        [meshDevice setUuid:uuid];
        [meshDevice setRssi:rssi];
        [meshDevice setDeviceHash:deviceHash];
        
        [_deviceDictionary setObject:meshDevice forKey:uuid];
        [_deviceDictionary setObject:meshDevice forKey:deviceHash];
        return (meshDevice);
        
    } else {
        return _deviceDictionary[deviceHash];
    }
}

-(void) updateAppearance :(NSData *) deviceHash appearanceValue:(NSNumber *) appearanceValue shortName:(NSData *) shortName
{
    CSRmeshDevice *device = _deviceDictionary[deviceHash];
    
    if (device) {
        
        [device setAppearanceValue :appearanceValue];
        [device setAppearanceShortname :shortName];
        
        if (![[[NSString alloc] initWithData:device.appearanceShortname encoding:NSUTF8StringEncoding] isEqualToString:@"CSRmeshGW"])
        {
            if (!device.isAssociated) {
                [_unassociatedMeshDevices addObject:device];
            }
            NSLog(@"device: %@,deviceName: %@",device,device.name);
            
        }
    }
}


-(NSInteger) getTotalAssociatedDevices {
    NSInteger total = 0;
    for (CSRmeshDevice *meshDevice in _meshDevices) {
        if (meshDevice.isAssociated)
            total+=1;
    }
    return (total);
}

// return the associated device at the given offset.
- (CSRmeshDevice *)getDeviceFromAssociatedList:(NSInteger)offset
{
    NSInteger total = 0;
    
    NSArray *sortedDevicesArray = [NSArray arrayWithArray:_meshDevices];
    NSSortDescriptor *sort = [NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES];
    _meshDevices = (NSMutableArray*)[sortedDevicesArray sortedArrayUsingDescriptors:@[sort]];
    _meshDevices = [_meshDevices mutableCopy];
    
    for (CSRmeshDevice *meshDevice in _meshDevices) {
        if (meshDevice.isAssociated) {
            if (offset == total)
                return (meshDevice);
            total+=1;
        }
    }
    return (nil);
}

- (NSArray*)getMeshDevicesArray
{
    return [NSArray arrayWithArray:_meshDevices];
}


-(CSRmeshDevice *) didAssociateDevice :(NSNumber *) deviceId deviceHash:(NSData *) deviceHash {
    CSRmeshDevice *meshDevice = _deviceDictionary [deviceHash];
    if (meshDevice) {
        [_deviceDictionary setObject:meshDevice forKey:deviceId];
        [meshDevice didAssociateDevice:deviceId];
        return meshDevice;
    }
    return nil;
}

- (CSRmeshDevice *) addDeviceWithDeviceHash :(NSData *) deviceHash authCode:(NSData *) authCode {
    CSRmeshDevice *meshDevice = _deviceDictionary [deviceHash];
    if (meshDevice == nil) {
        meshDevice = [[CSRmeshDevice alloc] init];
        [_deviceDictionary setObject:meshDevice forKey:deviceHash];
        [_scannedMeshDevices addObject:meshDevice];
        [meshDevice setDeviceHash:deviceHash];
    }
    
    [meshDevice setAuthCode:authCode];
    
    return (meshDevice);
}

-(CSRmeshDevice *) getDeviceFromDeviceId :(NSNumber *) deviceId
{
    CSRmeshDevice *meshDevice;
    if (_deviceDictionary[deviceId])
    {
       meshDevice = _deviceDictionary [deviceId];
    } else {
        meshDevice = nil;//[self addDeviceWithDeviceHash:<#(NSData *)#> authCode:<#(NSData *)#>];
    }
    return (meshDevice);
}

-(void) setDeviceDiscoveryFilter:(id)obj mode:(BOOL) mode
{
    static NSMutableSet *filterSetToYesObjects;
    if (filterSetToYesObjects==nil)
        filterSetToYesObjects = [NSMutableSet set];
    NSInteger totalObjects = [filterSetToYesObjects count];
    if (mode==YES)
        [filterSetToYesObjects addObject:obj];
    else
        [filterSetToYesObjects removeObject:obj];
    
    if (totalObjects==0 && [filterSetToYesObjects count])
        [[CSRDevicesManager sharedInstance] setDeviceDiscoveryFilterEnabled:YES];
    else if ([filterSetToYesObjects count]==0 && totalObjects)
        [[CSRDevicesManager sharedInstance] setDeviceDiscoveryFilterEnabled:NO];
}



- (void)updateDeviceAssociationInfo:(NSData *)deviceHash withStepsCompleted:(NSNumber *)stepsCompleted ofTotalSteps:(NSNumber *)totalSteps
{
    CSRmeshDevice *meshDevice = _deviceDictionary [deviceHash];
    if (meshDevice) {
        [meshDevice updateAssociationStatusWithNumberofStepsCompleted:stepsCompleted ofTotalSteps:totalSteps];
    }

}

- (CSRmeshDevice *)checkPreviouslyScannedDevicesWithDeviceHash:(NSData*)deviceHash
{
    __block CSRmeshDevice *foundDevice;
    [_scannedMeshDevices enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        CSRmeshDevice *scannedDevice = (CSRmeshDevice *)obj;
        
        if ([scannedDevice.deviceHash isEqualToData:deviceHash]) {
            foundDevice = scannedDevice;
            *stop = YES;
        }
    }];
    
    if (foundDevice) {
        return foundDevice;
    }
    
    return nil;
}

- (CSRmeshDevice*)getAllDevices
{
//    return (_allDevicesArea.areaDevice);
    return nil;
}

#pragma mark ----
#pragma mark - AREA related Functions

-(void) createAreaFromProperties : (NSDictionary *) areaProperties {
    
    NSNumber *areaNumber = areaProperties [kAREA_NUMBER];
    NSString *areaName = areaProperties [kAREA_NAME];
    
    @synchronized (self) {
        CSRmeshArea *area = [[CSRmeshArea alloc] initWithNumber:areaNumber andName:areaName];
        [_meshAreas addObject:area];
        
//        [area setAreaName:areaName];
    }
}

- (NSInteger) getTotalAreas {
    return (_meshAreas.count);
}


- (CSRAreaEntity*) addMeshArea:(NSString *)name {
    
    NSNumber *areaIdNumber = [[CSRDatabaseManager sharedInstance] getNextFreeIDOfType:@"CSRAreaEntity"];
    CSRmeshArea *area = [[CSRmeshArea alloc] initWithNumber:areaIdNumber andName:name];
    [_meshAreas addObject:area];
    
    CSRAreaEntity *areaObj = [[CSRDatabaseManager sharedInstance] saveNewArea:areaIdNumber areaName:name];

    return areaObj;
}

-(CSRmeshArea *) getArea :(NSInteger) offset {
    
    CSRmeshArea *meshArea = nil;
    
    NSArray *sortedArray = [NSArray arrayWithArray:_meshAreas];
    NSSortDescriptor *sort = [NSSortDescriptor sortDescriptorWithKey:@"areaName" ascending:YES];
    _meshAreas = (NSMutableArray*)[sortedArray sortedArrayUsingDescriptors:@[sort]];
    _meshAreas = [_meshAreas mutableCopy];
    
    if (offset <= _meshAreas.count)
        meshArea = _meshAreas[offset];
    return (meshArea);
}

- (CSRmeshArea *) getAreaFromId :(NSNumber *) areaIdNumber {
    for (CSRmeshArea *meshArea in _meshAreas) {
        if ([areaIdNumber isEqualToNumber:meshArea.areaNumber])
            return (meshArea);
    }
    return (nil);
}

#pragma mark ------
#pragma mark Remove Devices

- (void)initiateRemoveDevice:(CSRmeshDevice *)meshDevice
{
    [[CSRBluetoothLE sharedInstance] setScanner:YES source:meshDevice];
    [self setDeviceDiscoveryFilter:meshDevice mode:YES];
    
    __block BOOL flag;
    
    NSNumber *copyDeviceId = meshDevice.deviceId;

    [[ConfigModelApi sharedInstance] discoverDevice:meshDevice.deviceId
                                            success:^(NSNumber * _Nullable deviceId, NSData * _Nullable deviceHash) {
                                                NSLog(@"SJ21 deviceHash :%@", deviceHash);
                                                
                                                NSData *data = [UDManager getDhmKeyWith:deviceId];
                                                meshDevice.dhmKey = data;
                                                
                                            [self resetDevice:meshDevice.deviceId withDeviceHash:deviceHash andDHMKey:meshDevice.dhmKey];
                                                [meshDevice setResetRetriesRemaining:20];
                                                [meshDevice setResetTimer:[NSTimer scheduledTimerWithTimeInterval:0.5
                                                                                                           target:self
                                                                                                         selector:@selector(resetRetryEngine:)
                                                                                                         userInfo:meshDevice
                                                                                                          repeats:YES]];
//                                                meshDevice.uuid = nil;
                                                
                                                NSLog(@"删除成功,%@",meshDevice.deviceId);
                                                
                                                meshDevice.pendingRemoval = YES;
                                                flag = YES;
                                                
                                                NSMutableDictionary *objects = [NSMutableDictionary new];
                                                [objects setObject:@(flag) forKey:@"boolFlag"];
                                                [objects setObject:copyDeviceId forKey:@"deviceId"];
                                                [[NSNotificationCenter defaultCenter] postNotificationName:kCSRDeviceManagerDeviceFoundForReset object:self userInfo:objects];
                                                
                                            } failure:^(NSError * _Nullable error) {
                                                NSLog(@"删除失败");
                                                flag = NO;
                                                
                                                NSMutableDictionary *objects = [NSMutableDictionary new];
                                                [objects setObject:@(flag) forKey:@"boolFlag"];
                                                [objects setObject:copyDeviceId forKey:@"deviceId"];                                                [[NSNotificationCenter defaultCenter] postNotificationName:kCSRDeviceManagerDeviceFoundForReset object:self userInfo:objects];

                                            }];
}

-(void) resetRetryEngine :(NSTimer *) timer
{
    CSRmeshDevice *meshDevice = timer.userInfo;
    if (meshDevice != nil && meshDevice.uuid == nil) {
        if (meshDevice.resetRetriesRemaining) {
            [self didResetDevice:meshDevice.deviceId];
            meshDevice.resetRetriesRemaining -= 1;
        }
        else {
            if (meshDevice.resetTimer)
                [meshDevice.resetTimer invalidate];
            else
                [timer invalidate];
        }
    } else {
        [self removeDevice:meshDevice];
    }
}

- (void) removeDevice:(CSRmeshDevice *)meshDevice
{
    [self setDeviceDiscoveryFilter:meshDevice mode:NO];
    if (meshDevice.resetTimer)
        [meshDevice.resetTimer invalidate];
    [self didResetDevice:meshDevice.deviceId];
    
    NSArray *keys = [_deviceDictionary allKeys];
    for (id key in keys) {
        if ([_deviceDictionary[key] isEqual:meshDevice]) {
            [_deviceDictionary removeObjectForKey:key];
        }
    }
    [[CSRBluetoothLE sharedInstance] setScanner:NO source:meshDevice];
    [_meshDevices removeObject:meshDevice];
    meshDevice.pendingRemoval = NO;
}


-(void) didResetDevice :(NSNumber *) deviceId
{
    CSRmeshDevice *meshDevice = _deviceDictionary [deviceId];
    if (meshDevice) {
        [_deviceDictionary removeObjectForKey:deviceId];
        [meshDevice didResetDevice];
    }
}

#pragma mark ------
#pragma mark Remove Areas

- (void) removeAreaWithAreaId:(NSNumber *)areaId
{
    CSRmeshArea *meshArea = [self getAreaFromId:areaId];
    [_meshAreas removeObject:meshArea];
    [[CSRDatabaseManager sharedInstance] removeAreaFromDatabaseWithAreaId:areaId];
}

#pragma mark ------
#pragma mark Remove Areas

- (void) removeEventWithEventId:(NSNumber *)eventId
{
    [[CSRAppStateManager sharedInstance].selectedPlace.events enumerateObjectsUsingBlock:^(id  _Nonnull obj, BOOL * _Nonnull stop) {
        
        CSREventEntity *eventEntity = (CSREventEntity *)obj;
        
        if ([eventEntity.eventid isEqualToNumber:eventId]) {
            
            [[CSRAppStateManager sharedInstance].selectedPlace removeEventsObject:eventEntity];
            *stop = YES;
            }
    }];
}


#pragma mark ------
#pragma mark Temperature Control Methods

//============================================================================
// Actuator message to set desired temperature
-(void) setDesiredTemperatureForArea :(CSRmeshArea *) meshArea
{
    if (meshArea.setTemperatureDelay) {
        [meshArea.setTemperatureDelay invalidate];
    }
    
    meshArea.setTemperatureDelay = [NSTimer scheduledTimerWithTimeInterval:0.5
                                                                     target:self
                                                                   selector:@selector(setTemperatureDelayed:)
                                                                   userInfo:meshArea
                                                                    repeats:NO];
}

-(void) setTemperatureDelayed :(NSTimer *) timer
{
    NSLog (@"Set Temp timer fired");
    CSRmeshArea *meshArea = timer.userInfo;
    if (meshArea) {
        NSNumber *actuatorType = CSRsensorType_Unknown;
        float centigrade = [meshArea.desiredTemperatureSetByUser floatValue];
        NSLog (@"Set Temp=%0.1f °C",centigrade);
        float kelvin = centigrade + 273.15;
        NSNumber *temperatureValue = @(kelvin);
        
        CSRsensorValue *actuatorValue = [CSRsensorValue initWithDesiredAirTemperature:temperatureValue];
        
        NSNumber *meshReq = [[ActuatorModelApi sharedInstance] setValue:meshArea.areaNumber
                                                          actuatorValue:actuatorValue
                                                                success:^(NSNumber *deviceId, CSRsensorValue *actuatorValue) {
                                                                    NSLog(@"deviceId :%@, Actuator Value %@", deviceId, actuatorValue);
                                                                } failure:^(NSError *error) {
                                                                    
                                                                }];
        
        
        [_meshRequests setObject:meshArea forKey:meshReq];
        
        // Remove previous unacknowledged requests
        NSMutableArray *removals = [NSMutableArray array];
        for (NSNumber *oldMeshRequestId in meshArea.meshRequests) {
            [removals addObject:oldMeshRequestId];
            [[MeshServiceApi sharedInstance] cancelTransaction:oldMeshRequestId];
        }
        
        if (removals.count>0) {
            for (NSNumber *oldMeshRequestId in removals) {
                [meshArea.meshRequests removeObjectForKey:oldMeshRequestId];
            }
        }
        
        // Create a record for this request so it can be paired with acknowledgement
        NSMutableDictionary *request = [NSMutableDictionary dictionary];
        request[AREA_MESH_REQUEST] = meshArea;
        request[AREA_SENSOR_TYPE] =  actuatorType;
        request[AREA_SENSOR_VALUE] = meshArea.desiredTemperatureSetByUser;
        request[AREA_SENSOR_CONVERTED_VALUE] = temperatureValue;
        [meshArea.meshRequests setObject:request forKey:meshReq];
        
        // remove NSTimer object as this is used to decide whether we should set deisred temp from received.
        meshArea.setTemperatureDelay=nil;
        
        // Update Watch
        [self updateDesiredTempInWatch:meshArea.areaNumber temp:centigrade];
    }
}

//============================================================================
// Sensor Actuator Notifications
-(void) didGetSensorTypes :(NSNotification *)notification
{
}

-(void) didGetSensorState :(NSNotification *)notification
{
}

//============================================================================
// Post a notification when a sensor changes so the UI can respond
-(void) postNotifcation
{
    [[NSNotificationCenter defaultCenter] postNotificationName:SENSOR_VALUE_CHANGED object:self userInfo:nil];
}



//============================================================================
// Assume desired temperture acknowledge has been received. Check that this is so and for the meshGroup that
// this acknowledge is related to the meshRequest, if its desiredTemperature is equal to the received then set its
// isDesiredTemperatureAcknowledged to YES.
-(void) didGetSensorValue:(NSNumber *)deviceId sensors:(NSArray *)sensors meshRequestId:(NSNumber *)meshRequest
{
//    if (meshRequest) {
//        CSRmeshArea *meshArea = _meshRequests [meshRequest];
//        [_meshRequests removeObjectForKey:meshRequest];
//        if (meshArea && [meshArea isKindOfClass:[CSRmeshArea class]]) {
//            for (CSRsensorValue *sensorValue in sensors) {
//                CSRsensorType type = [sensorValue getType];
//               if (type == CSRsensorType_Desired_Air_Temperature) {
//                    NSNumber *value = sensors[sensorType];
//                    float centigrade = (roundf(([value floatValue]-273.15)*10))/10;
//                    value = [NSNumber numberWithFloat:centigrade];
//                    meshArea.desiredTemperatureAcknowledged = value;
//                    [self postNotifcation];
//                    [self updateDesiredTempInWatch:deviceId temp:centigrade];
//                }
//                else if (type == CSRsensorType_Internal_Air_Temperature) {
//                    NSNumber *value = sensors[sensorType];
//                    float centigrade = (roundf(([value floatValue]-273.15)*10))/10;
//                    value = [NSNumber numberWithFloat:centigrade];
//                    meshArea.currentTemperature = value;
//                    [self postNotifcation];
//                    [self updateActualTempInWatch:deviceId temp:centigrade];
//                }
//            }
//        }
//    }
//    else {
//        if (deviceId) {
//            CSRmeshArea *meshArea = [self getAreaFromId:deviceId];
//            if (meshArea) {
//                if (sensors) {
//                    for (NSNumber *type in sensors) {
//                        if ([type isEqualToNumber:@(CSR_DESIRED_AIR_TEMPERATURE)]) {
//                            NSNumber *value = sensors[type];
//                            float centigrade = (roundf(([value floatValue]-273.15)*10))/10;
//                            value = [NSNumber numberWithFloat:centigrade];
//                            meshArea.desiredTemperatureAcknowledged = value;
//                            // Set the desired value from received but only if we are not waiting to send desired.
//                            if (meshArea.setTemperatureDelay == nil && meshArea.meshRequests.count == 0)
//                                meshArea.desiredTemperatureSetByUser = value;
//                            [self postNotifcation];
//                            [self updateDesiredTempInWatch:deviceId temp:centigrade];
//                        }
//                        else if ([type isEqualToNumber:@(CSR_INTERNAL_AIR_TEMPERATURE)]) {
//                            NSNumber *value = sensors[type];
//                            float centigrade = (roundf(([value floatValue]-273.15)*10))/10;
//                            value = [NSNumber numberWithFloat:centigrade];
//                            meshArea.currentTemperature = value;
//                            [self postNotifcation];
//                            [self updateActualTempInWatch:deviceId temp:centigrade];
//                        }
//                    }
//                }
//            }
//        }
//    }
}

-(void) didGetActuatorValueAck :(NSNotification *)notification
{
    NSNumber *meshRequest = notification.userInfo[kMeshRequestIdString];
    if (meshRequest) {
        CSRmeshArea *meshArea = _meshRequests [meshRequest];
        [_meshRequests removeObjectForKey:meshRequest];
        if (meshArea && [meshArea isKindOfClass:[CSRmeshArea class]]) {
            // retrieve record for this request
            NSMutableDictionary *request = meshArea.meshRequests[meshRequest];
            if (request) {
                NSNumber *rxSensorType = notification.userInfo[kActuatorTypeString];
                NSNumber *txSensorType = request[AREA_SENSOR_TYPE];
                if ([rxSensorType isEqualToNumber:txSensorType]) {
                    meshArea.desiredTemperatureAcknowledged = request[AREA_SENSOR_VALUE];
                    [self postNotifcation];
                }
                // remove record for this request
                [meshArea.meshRequests removeObjectForKey:meshRequest];
            }
        }
    }
}



-(void) didTimeoutNotification :(NSNotification *)notification {
    NSNumber *meshRequest = notification.userInfo[kMeshRequestIdString];
    if (meshRequest) {
        [_meshRequests removeObjectForKey:meshRequest];
        CSRmeshArea *meshArea = _meshRequests [meshRequest];
        if (meshArea && [meshArea isKindOfClass:[CSRmeshArea class]]) {
            [meshArea.meshRequests removeObjectForKey:meshRequest];
        }
    }
}

#pragma mark watch stuff
-(void) updateActualTempInWatch:(NSNumber *)md temp:(float)centigrade {
    [[CSRWatchManager sharedInstance] updateActualTemperature:md actualTemperature:@(centigrade)];
}

-(void) updateDesiredTempInWatch:(NSNumber *)md temp:(float)centigrade {
    [[CSRWatchManager sharedInstance] updateDesiredTemperature:md desiredTemperature:@(centigrade)];
}


#pragma mark ------
#pragma mark API Calls

- (void)associateDeviceFromCSRDeviceManager:(NSData *)deviceHash authorisationCode:(NSData *)authCode
{
    
    // get the next free device ID
    NSNumber *deviceId;
    
    if (_isDeviceTypeGateway) {
        
        deviceId = [[CSRDatabaseManager sharedInstance] getNextFreeGatewayDeviceId];
        
    } else {
        
        deviceId = [[CSRDatabaseManager sharedInstance] getNextFreeIDOfType:@"CSRDeviceEntity"];
        
    }
    
    [[MeshServiceApi sharedInstance] associateDevice:deviceHash
                                   authorisationCode:authCode
                                            deviceId:deviceId
                                             success:^(NSNumber *deviceId, NSData *deviceHash, NSData *dhmKey, NSNumber *meshRequestId) {
        
//        [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDeviceAssociationSuccessNotification
//                                                            object:self
//                                                          userInfo:@{@"deviceId": deviceId, @"deviceHash":deviceHash}];
        
    } progress:^(NSData *deviceHash, NSNumber *stepsCompleted, NSNumber *totalSteps, NSNumber *meshRequestId) {
        
        [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDeviceAssociationProgressNotification
                                                            object:self
                                                          userInfo:@{@"stepsCompleted": stepsCompleted, @"totalSteps":totalSteps, @"meshRequestId": meshRequestId}];
        
    } failure:^(NSError *error) {
        
        [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDeviceAssociationFailedNotification
                                                            object:self
                                                          userInfo:@{@"error":error}];
        
    }];
    
}

#pragma mark - double add,手动指定deviceId，所有设备同时连接，加快连接速度
- (void)new_associateDeviceFromCSRDeviceManager:(NSData *)deviceHash authorisationCode:(NSData *)authCode deviceId:(NSNumber *)deviceId {
    // get the next free device ID
    [[MeshServiceApi sharedInstance] associateDevice:deviceHash
                                   authorisationCode:authCode
                                            deviceId:deviceId
                                             success:^(NSNumber *deviceId, NSData *deviceHash, NSData *dhmKey, NSNumber *meshRequestId) {
                                                 
                                                 [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDeviceAssociationSuccessNotification
                                                                                                     object:self
                                                                                                   userInfo:@{@"deviceId": deviceId, @"deviceHash":deviceHash}];

                                             } progress:^(NSData *deviceHash, NSNumber *stepsCompleted, NSNumber *totalSteps, NSNumber *meshRequestId) {
                                                 
                                                 [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDeviceAssociationProgressNotification
                                                                                                     object:self
                                                                                                   userInfo:@{@"stepsCompleted": stepsCompleted, @"totalSteps":totalSteps, @"meshRequestId": meshRequestId}];
                                                 
                                             } failure:^(NSError *error) {
                                                 
                                                 [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDeviceAssociationFailedNotification
                                                                                                     object:self
                                                                                                   userInfo:@{@"error":error}];
                                                 
                                             }];
}


- (void)getModelsAndGroupsCall:(NSNumber *)deviceId infoType:(NSNumber *)infoType
{
    [[ConfigModelApi sharedInstance] getInfo:deviceId infoType:infoType success:^(NSNumber *deviceId, NSNumber *infoType, NSData *info) {
        //
    } failure:^(NSError *error) {
        //
    }];
}

- (void)setDeviceDiscoveryFilterEnabled:(BOOL)enabled
{
    [[MeshServiceApi sharedInstance] setDeviceDiscoveryFilterEnabled:enabled
                                                                uuid:^(CBUUID *uuid, NSNumber *rssi) {
                                                                    //        NSLog (@"uuid=%@",uuid);
                                                                } appearance:^(NSData *deviceHash, NSNumber *appearanceValue, NSData *shortName) {
                                                                    
                                                                }];
}

- (void)setAttention:(NSData *)deviceHash attentionState:(NSNumber *)attentionState withDuration:(NSNumber *)duration
{
    [[MeshServiceApi sharedInstance] setAttentionPreAssociation:deviceHash attentionState:attentionState withDuration:duration];
}

- (void)getNumberOfModelGroupIds:(NSNumber *)deviceId modelNo:(NSNumber *)modelNo
{
    [[GroupModelApi sharedInstance] getNumModelGroupIds:deviceId modelNo:modelNo success:^(NSNumber *deviceId, NSNumber *modelNo, NSNumber *numberOfModelGroupIds) {
        
    } failure:^(NSError *error) {
        //
    }];
}

- (void)setSiteID:(NSString *) siteID
{
    [[MeshServiceApi sharedInstance] setNetworkPassPhrase:siteID];
}

- (void)setNetworkPassPhrase:(NSString *)passPhrase
{
    [[MeshServiceApi sharedInstance] setNetworkPassPhrase:passPhrase];
}

- (void) setNetworkKey:(NSData *)networkKey
{
    [[MeshServiceApi sharedInstance] setNetworkKey:networkKey];
}

-(void) setAttentionPreAssociation:(NSData *)deviceHash attentionState:(NSNumber *)attentionState withDuration:(NSNumber *) duration
{
    [[MeshServiceApi sharedInstance] setAttentionPreAssociation:deviceHash attentionState:attentionState withDuration:duration];
}

-(void) resetDevice:(NSNumber *)deviceId withDeviceHash:deviceHash andDHMKey:dhmKey
{
    [[ConfigModelApi sharedInstance] resetDevice:deviceId withDeviceHash:deviceHash andDHMKey:dhmKey failure:nil];
//    [[MeshServiceApi sharedInstance] resetDevice:deviceId dhmKey:dhmKey];
}

- (void) setNextDeviceID:(NSNumber *)deviceNo
{
//    [[MeshServiceApi sharedInstance] setNextDeviceId:deviceNo];
}

- (id)getStateForDeviceWithId:(NSNumber *)deviceId
{
    
    CSRmeshDevice *device = [self getDeviceFromDeviceId:deviceId];
    
    if (device) {
        
        return device.stateValue;
        
    }
    
    return nil;
}

#pragma mark ---
#pragma mark SetLightColor API's

- (void) setColor:(NSNumber*)deviceId color:(UIColor*)actualColor duration:(NSNumber*)duration {
    
    [[LightModelApi sharedInstance] setColor:deviceId
                                       color:actualColor
                                    duration:@0
                                     success:nil // no acknowledge required so success is set to nil
                                     failure:nil];

}


- (void) setWhite:(NSNumber *)deviceId level:(NSNumber *)level duration:(NSNumber *)duration {
    
    [[LightModelApi sharedInstance] setWhite:deviceId level:level duration:duration success:^(NSNumber *deviceId, NSNumber *whiteLevel) {
        
    } failure:^(NSError *error) {
        
    }];
}

- (void) setColorTemperature:(NSNumber *)deviceId temperature:(NSNumber *)temperature duration:(NSNumber *)duration {
    
    [[LightModelApi sharedInstance] setColorTemperature:deviceId
                                            temperature:temperature
                                               duration:duration
                                                success:^(NSNumber *deviceId, UIColor *color, NSNumber *powerState, NSNumber *colorTemperature, NSNumber *supports) {
                                                    
                                                    NSLog(@"color %@ and colorTemperature %@", color, colorTemperature);
                                                    
                                                } failure:^(NSError *error) {
                                                    
                                                }];
}

#pragma mark ---
#pragma mark Power API's

- (void) setPowerState:(NSNumber *)deviceId state:(NSNumber *)state {
    
    [[PowerModelApi sharedInstance] setPowerState:deviceId
                                            state:state
                                          success:^(NSNumber * _Nullable deviceId, NSNumber * _Nullable state) {
                                              NSLog(@"state :%@", state);
                                          } failure:^(NSError * _Nullable error) {
                                              NSLog(@"error %@", error);
                                          }];
 }


- (void) deleteDevicesInArray
{
    [[CSRDevicesManager sharedInstance].unassociatedMeshDevices removeAllObjects];
}

@end
