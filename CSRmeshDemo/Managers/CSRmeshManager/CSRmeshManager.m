//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import "CSRmeshManager.h"
#import "CSRConstants.h"
#import "CSRDevicesManager.h"
#import "CSRDeviceEntity.h"
#import "CSRGatewayEntity.h"
#import "CSRDatabaseManager.h"
#import "CSRAppStateManager.h"
#import "CSRMeshUtilities.h"
#import "CSRmeshDevice.h"
#import "CSRUtilities.h"
#import "CSRMeshUtilities.h"

@implementation CSRmeshManager


+ (id) sharedInstance
{
    
    static dispatch_once_t token;
    static CSRmeshManager *shared = nil;
    
    dispatch_once(&token, ^{
        shared = [[CSRmeshManager alloc] init];
    });
    
    return shared;
}

- (id)init {
    if (self = [super init]) {
        
    }
    return self;
}

- (void)setUpDelegates
{
    [[MeshServiceApi sharedInstance] addDelegate:self];
    [[AttentionModelApi sharedInstance] addDelegate:self];
    [[BearerModelApi sharedInstance] addDelegate:self];
    [[ConfigModelApi sharedInstance] addDelegate:self];
    [[FirmwareModelApi sharedInstance] addDelegate:self];
    [[GroupModelApi sharedInstance] addDelegate:self];
    [[LightModelApi sharedInstance] addDelegate:self];
    [[PowerModelApi sharedInstance] addDelegate:self];
    [[DataModelApi sharedInstance] addDelegate:self];
    [[PingModelApi sharedInstance] addDelegate:self];
    [[BatteryModelApi sharedInstance] addDelegate:self];
    [[SensorModelApi sharedInstance] addDelegate:self];
    [[ActuatorModelApi sharedInstance] addDelegate:self];
}

-(void) setScannerEnabled:(NSNumber *)enabled {
    // Notify all listeners
    NSMutableDictionary *objects = [NSMutableDictionary dictionary];
    if (enabled)
        [objects setObject:enabled forKey:kScannerEnabledString];
    [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerWillSetScannerEnabledNotification object:self userInfo:objects];
}


-(void) didDiscoverDevice:(CBUUID *)uuid rssi:(NSNumber *)rssi
{
    // Notify all listeners
//    NSLog(@"uuid %@, rssi%@", uuid, rssi);
    NSMutableDictionary *objects = [NSMutableDictionary dictionary];
    if (uuid)
        [objects setObject:uuid forKey:kDeviceUuidString];
    if (rssi)
        [objects setObject:rssi forKey:kDeviceRssiString];
    [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDidDiscoverDeviceNotification object:self userInfo:objects];
}


-(void) didUpdateAppearance:(NSData *)deviceHash appearanceValue:(NSNumber *)appearanceValue shortName:(NSData *)shortName
{
    // Notify all listeners
//    NSLog(@"appearanceValue %@, shortName%@", appearanceValue, shortName);
    NSMutableDictionary *objects = [NSMutableDictionary dictionary];
    if (deviceHash)
        [objects setObject:deviceHash forKey:kDeviceHashString];
    if (appearanceValue)
        [objects setObject:appearanceValue forKey:kAppearanceValueString];
    if (shortName)
        [objects setObject:shortName forKey:kShortNameString];
    [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDidUpdateAppearanceNotification object:self userInfo:objects];
}


-(void) isAssociatingDevice:(NSData *)deviceHash stepsCompleted:(NSNumber *)stepsCompleted totalSteps:(NSNumber *)totalSteps meshRequestId:(NSNumber *)meshRequestId {
    [[CSRDevicesManager sharedInstance] updateDeviceAssociationInfo:deviceHash withStepsCompleted:stepsCompleted ofTotalSteps:totalSteps];
    
    // Notify all listeners
    NSMutableDictionary *objects = [NSMutableDictionary dictionary];
    if (deviceHash)
        [objects setObject:deviceHash forKey:kDeviceHashString];
    if (stepsCompleted)
        [objects setObject:stepsCompleted forKey:kStepsCompletedString];
    if (totalSteps)
        [objects setObject:totalSteps forKey:kTotalStepsString];
    if (meshRequestId)
        [objects setObject:meshRequestId forKey:kMeshRequestIdString];
    [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerIsAssociatingDeviceNotification object:self userInfo:objects];
    
}

-(void) didAssociateDevice:(NSNumber *)deviceId deviceHash:(NSData *)deviceHash dhmKey:(NSData*)dhmKey meshRequestId:(NSNumber *)meshRequestId
{
    CSRmeshDevice *meshDevice = [[CSRDevicesManager sharedInstance] didAssociateDevice:deviceId deviceHash:deviceHash];
    
    // Create hash from exisitng gateway
    __block BOOL isDeviceGateway = [CSRDevicesManager sharedInstance].isDeviceTypeGateway;
    
    if (!isDeviceGateway) {
        
        // Check if device already exists
        __block CSRDeviceEntity *deviceEntity = nil;
        
        [[CSRAppStateManager sharedInstance].selectedPlace.devices enumerateObjectsUsingBlock:^(id  _Nonnull obj, BOOL * _Nonnull stop) {
            
            CSRDeviceEntity *device = (CSRDeviceEntity *)obj;
            
            if ([device.deviceId isEqualToNumber:deviceId]) {
                
                deviceEntity = device;
                *stop = YES;
                
            }
            
        }];
        
        if (!deviceEntity && ![meshDevice.appearanceValue  isEqual:@(CSRApperanceNameController)]) {
            
            deviceEntity = [NSEntityDescription insertNewObjectForEntityForName:@"CSRDeviceEntity" inManagedObjectContext:[CSRDatabaseManager sharedInstance].managedObjectContext];
            
        }
        
        if (deviceEntity) {
            
            deviceEntity.deviceId = deviceId;
            deviceEntity.isAssociated = @(YES);
            deviceEntity.deviceHash = deviceHash;
            deviceEntity.dhmKey = dhmKey;
            
            if (meshDevice.appearanceValue) {
                deviceEntity.appearance = meshDevice.appearanceValue;
            }
            
            //设置设备名
            if (meshDevice.appearanceShortname) {
                NSString *shortName = [CSRUtilities stringFromData:meshDevice.appearanceShortname];
                [UDManager saveDeviceCodingIdWith:deviceId codingId:shortName]; //存储编码
                
                shortName = [DeviceDataHandle getDeviceNameWith:shortName];
                meshDevice.name = [NSString stringWithFormat:@"%@ %d", shortName, (int)([deviceId intValue]&0x7fff)];
                deviceEntity.name = meshDevice.name;
                
            }
            
            [[CSRAppStateManager sharedInstance].selectedPlace addDevicesObject:deviceEntity];
            [[CSRDatabaseManager sharedInstance] saveContext];
            
            //double add 手动存储设备的dhmKey值和原始设备名
            [UDManager saveDhmKeyWith:deviceId dhmKey:dhmKey];
            [UDManager saveDeviceOriginNameWith:deviceId originName:deviceEntity.name];
        }
        
        // request model info for this device.
        if (![meshDevice.appearanceValue  isEqual:@(CSRApperanceNameController)]) {
            [[CSRDevicesManager sharedInstance] getModelsAndGroupsCall:deviceId infoType:@(CSR_Model_low)];
            [NSThread sleepForTimeInterval:0.3];
            [[CSRDevicesManager sharedInstance] getModelsAndGroupsCall:deviceId infoType:@(CSR_Model_high)];
            [NSThread sleepForTimeInterval:0.3];
            if (meshDevice.appearanceValue == nil) {
                [[CSRDevicesManager sharedInstance] getModelsAndGroupsCall:deviceId infoType:@(CSR_Appearance)];
            }
        }
        
        // Notify all listeners
        NSMutableDictionary *objects = [NSMutableDictionary dictionary];
        if (deviceId)
            [objects setObject:deviceId forKey:kDeviceIdString];
        if (deviceHash)
            [objects setObject:deviceHash forKey:kDeviceHashString];
        if (meshRequestId)
            [objects setObject:meshRequestId forKey:kMeshRequestIdString];
        [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDidAssociateDeviceNotification object:self userInfo:objects];
        
        NSMutableDictionary *deviceDictionary = [NSMutableDictionary new];
        
        if (deviceEntity.deviceId) {
            [deviceDictionary setValue:deviceEntity.deviceId forKey:kDEVICE_NUMBER];
        }
        
        if (deviceEntity.deviceHash) {
            [deviceDictionary setValue:deviceEntity.deviceHash forKey:kDEVICE_HASH];
        }
        
        if (deviceEntity.authCode) {
            [deviceDictionary setValue:deviceEntity.authCode forKey:kDEVICE_AUTH_CODE];
        }
        
        if (deviceEntity.name) {
            [deviceDictionary setValue:[NSString stringWithFormat:@"%@ (%04x)",[[NSString alloc] initWithData:meshDevice.appearanceShortname encoding:NSUTF8StringEncoding], [deviceId unsignedShortValue]] forKey:kDEVICE_NAME];
        }
        
        if (deviceEntity.isAssociated) {
            [deviceDictionary setValue:deviceEntity.isAssociated forKey:kDEVICE_ISASSOCIATED];
        }
        
        if (deviceEntity.dhmKey) {
            [deviceDictionary setValue:deviceEntity.dhmKey forKey:kDEVICE_DHM];
        }
        
        [[CSRDevicesManager sharedInstance] createDeviceFromProperties:deviceDictionary];
        
    } else {
        
        NSMutableDictionary *objects = [NSMutableDictionary dictionary];
        if (deviceId)
            [objects setObject:deviceId forKey:kDeviceIdString];
        if (deviceHash)
            [objects setObject:deviceHash forKey:kDeviceHashString];
        if (dhmKey)
            [objects setObject:dhmKey forKey:kDeviceDHMString];
        if (meshRequestId)
            [objects setObject:meshRequestId forKey:kMeshRequestIdString];
        [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDidAssociateDeviceNotification object:self userInfo:objects];
        
    }
    
}

- (void)didGetDeviceInfo:(NSNumber * _Nonnull)deviceId  infoType:(NSNumber * _Nonnull)infoType information:(NSData * _Nonnull)information meshRequestId:(NSNumber * _Nonnull)meshRequestId
{
    CSRmeshDevice *meshDevice = [[CSRDevicesManager sharedInstance] getDeviceFromDeviceId:deviceId];
    
    CSRDeviceEntity *deviceEntity = [[CSRDatabaseManager sharedInstance] getDeviceEntityWithId:deviceId];
    
    if (!deviceEntity) {
        
        deviceEntity = [NSEntityDescription insertNewObjectForEntityForName:@"CSRDeviceEntity" inManagedObjectContext:[CSRDatabaseManager sharedInstance].managedObjectContext];
    }
    
    NSDictionary *info = [self infoDictionary:information type:[infoType intValue]];
    
//    if ([infoType intValue] == CSR_UUID_low) {
//        NSLog(@"Dict0 :%@", info);
//    }
//    if ([infoType intValue] == CSR_UUID_high) {
//        NSLog(@"Dict1 :%@", info);
//    }
    
    NSData *data;
    
    if ([infoType intValue] == CSR_Model_low) {
        
        data = info[kDEVICE_MODELS_LOW];
        deviceEntity.modelLow = data;
    }
    if ([infoType intValue] == CSR_Model_high){
        
        data = info[kDEVICE_MODELS_HIGH];
        deviceEntity.modelHigh = data;
    }
    
    if (meshDevice) {
        
        [meshDevice createModelsWithModelNumber:data withInfoType:infoType];
    }
    
    if ([infoType intValue] == CSR_Appearance) {
        
        NSData *appearanceData = info[kDEVICE_APPEARANCE];
        NSData *revData = [CSRUtilities reverseData:appearanceData];
        NSUInteger appValue = 0;
        [revData getBytes:&appValue length:sizeof(appValue)];
        
        if (appValue) {
            NSString *name;
            switch (appValue) {
                case CSRApperanceNameLight:
                    name = [NSString stringWithFormat:@"Light %d",(int)([deviceId intValue]&0x7fff)];
                    break;
                case CSRApperanceNameSensor:
                    name = [NSString stringWithFormat:@"Sensor %d",(int)([deviceId intValue]&0x7fff)];
                    break;
                case CSRApperanceNameHeater:
                    name = [NSString stringWithFormat:@"Heater %d",(int)([deviceId intValue]&0x7fff)];
                    break;
                case CSRApperanceNameSwitch:
                    name = [NSString stringWithFormat:@"Switch %d",(int)([deviceId intValue]&0x7fff)];
                    break;
                case CSRApperanceNameController:
                    name = [NSString stringWithFormat:@"Controller %d", (int)([deviceId intValue]&0x7fff)];
                    break;
                default:
                    break;
            }
            
            meshDevice.name = name;
            
            if (deviceEntity) {
                deviceEntity.name = name;
                deviceEntity.appearance = @(appValue);
            }
        }
    }
    
    [[CSRDatabaseManager sharedInstance] saveContext];
    
    if (info) {
        NSMutableDictionary *objects = [NSMutableDictionary dictionaryWithDictionary:info];
        if (meshRequestId)
            [objects setObject:meshRequestId forKey:kMeshRequestIdString];
        if (deviceId)
            [objects setObject:deviceId forKey:kDeviceIdString];
        if (infoType)
            [objects setObject:infoType forKey:kInfoTypeString];
        [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDidGetDeviceInfoNotification object:self userInfo:objects];
    }
}


- (NSDictionary *)infoDictionary:(NSData *)data type:(NSInteger)infoType {
    
    switch (infoType) {
        case CSR_UUID_low:
            return @{kCSR_UUID_LOW: data};
        case CSR_UUID_high:
            return @{kCSR_UUID_HIGH: data};
        case CSR_Model_low:
            return @{kCSR_MODEL_LOW: data};
        case CSR_Model_high:
            return @{kCSR_MODEL_HIGH: data};
        case CSR_VID_PID_Version:
            return @{kCSR_PRODUCT_IDENTIFIER: data};
        case CSR_Appearance:
            return @{kCSR_APPEARANCE: data};
        case CSR_LastETag:
            return @{kCSR_LAST_ETAG: data};
        default:
            return nil;
    }
}

-(void) didTimeoutMessage:(NSNumber *)meshRequestId
{
    // Notify all listeners
    NSMutableDictionary *objects = [NSMutableDictionary dictionary];
    
    if (meshRequestId) {
        
        [objects setObject:meshRequestId forKey:kMeshRequestIdString];
        
    }
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDidTimeoutMessageNotification object:self userInfo:objects];
}

#pragma mark models and groups notifications

-(void) didGetNumModelGroupIds:(NSNumber *)deviceId modelNo:(NSNumber *)modelNo numberOfModelGroupIds:(NSNumber *)numberOfModelGroupIds meshRequestId:(NSNumber *)meshRequestId{
    
    NSMutableDictionary *objects = [NSMutableDictionary dictionary];
    if (deviceId)
        [objects setObject:deviceId forKey:kDEVICE_NUMBER];
    if (modelNo)
        [objects setObject:modelNo forKey:kDEVICE_MODEL_NUMBER_STRING];
    if (numberOfModelGroupIds)
        [objects setObject:numberOfModelGroupIds forKey:kDEVICE_NUMBER_OF_MODEL_GROUP_ID_STRING];
    if (meshRequestId)
        [objects setObject:meshRequestId forKey:kDEVICE_MESH_REQUEST_ID_STRING];
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kCSRmeshManagerDidGetNumberOfModelGroupIdsNotification object:self userInfo:objects];
}

#pragma mark - DataModelApi Delegate
- (void)didSendData:(NSNumber *)deviceId
               data:(NSData *)data
      meshRequestId:(NSNumber *)meshRequestId {
    NSLog(@"didSendData: %@",data);
}

- (void)didReceiveBlockData:(NSNumber *)destinationDeviceId
             sourceDeviceId:(NSNumber *)sourceDeviceId
                       data:(NSData *)data {
    NSLog(@"didReceiveBlockData: %@",data);
    
    //发送给所有监听者
    [[NSNotificationCenter defaultCenter] postNotificationName:Notify_ReceivePowerConsumptionData object:nil userInfo:@{@"info":data}];
}

- (void)didReceiveStreamData:(NSNumber *)deviceId
                streamNumber:(NSNumber *)streamNumber
                        data:(NSData *)data {
    NSLog(@"didReceiveStreamData: %@",data);
}

- (void)didReceiveStreamDataEnd:(NSNumber *)deviceId
                   streamNumber:(NSNumber *)streamNumber {
    NSLog(@"didReceiveStreamDataEnd: %@",streamNumber);
}



@end
