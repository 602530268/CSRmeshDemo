//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CSRParseAndLoad.h"
#import "CSRSettingsEntity.h"
#import "CSRDeviceEntity.h"
#import "CSRAreaEntity.h"
#import "CSRUtilities.h"
#import "CSRDatabaseManager.h"
#import "CSRPlaceEntity.h"
#import "CSRAppStateManager.h"
#import <CSRmesh/MeshServiceApi.h>

@interface CSRParseAndLoad()
{
    
    NSManagedObjectContext *managedObjectContext;
}
@end

@implementation CSRParseAndLoad

- (id) init {
    self = [super init];
    if (self) {
       
        managedObjectContext = [CSRDatabaseManager sharedInstance].managedObjectContext;
        
    }
    return self;
}

- (void) deleteEntitiesInSelectedPlace
{
    //Delete already devices, areas, gateway and (cloudTenancyID,cloudMeshID,cloudSiteID)
    [[CSRAppStateManager sharedInstance].selectedPlace removeAreas:[CSRAppStateManager sharedInstance].selectedPlace.areas];
    [[CSRAppStateManager sharedInstance].selectedPlace removeDevices:[CSRAppStateManager sharedInstance].selectedPlace.devices];
    [[CSRAppStateManager sharedInstance].selectedPlace removeGateways:[CSRAppStateManager sharedInstance].selectedPlace.gateways];
    [CSRAppStateManager sharedInstance].selectedPlace.settings.cloudTenancyID = nil;
    [CSRAppStateManager sharedInstance].selectedPlace.settings.cloudMeshID = nil;
    [CSRAppStateManager sharedInstance].selectedPlace.cloudSiteID = nil;
    
}

- (void) parseIncomingDictionary:(NSDictionary *)parsingDictionary
{
    if (parsingDictionary[@"areas_list"])
    {
        for (NSDictionary *areaDict in parsingDictionary[@"areas_list"]) {
            
            CSRAreaEntity *groupObj = [NSEntityDescription insertNewObjectForEntityForName:@"CSRAreaEntity" inManagedObjectContext:managedObjectContext];
            
            groupObj.areaName = areaDict[@"name"];
            groupObj.areaID = areaDict[@"areaID"];
            groupObj.favourite = areaDict[@"isFavourite"];
            
            if ([CSRAppStateManager sharedInstance].selectedPlace) {
                [[CSRAppStateManager sharedInstance].selectedPlace addAreasObject:groupObj];
            }
        }
    }
    
    if (parsingDictionary[@"devices_list"])
    {
        for (NSDictionary * deviceDict in parsingDictionary[@"devices_list"]) {
            
            CSRDeviceEntity *deviceEntity = [NSEntityDescription insertNewObjectForEntityForName:@"CSRDeviceEntity" inManagedObjectContext:managedObjectContext];
            
            NSData *devHash = [CSRUtilities IntToNSData:[deviceDict[@"hash"] unsignedLongLongValue]];
            NSData *modelHigh = [CSRUtilities IntToNSData:[deviceDict[@"modelHigh"] unsignedLongLongValue]];
            NSData *modelLow = [CSRUtilities IntToNSData:[deviceDict[@"modelLow"] unsignedLongLongValue]];
            
            __block NSMutableData *groups = [NSMutableData data];
            NSArray *groupsArray = deviceDict[@"groups"];
            
            
            [groupsArray enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
                
                uint16_t desiredValue = [obj unsignedShortValue];
                [groups appendBytes:&desiredValue length:sizeof(desiredValue)];
                CSRAreaEntity *areaEntity = [[CSRDatabaseManager sharedInstance] getAreaEntityWithId:@(desiredValue)];
                
                if (areaEntity) {
                    [deviceEntity addAreasObject:areaEntity];
                }
            }];
            NSData *authCode = [CSRUtilities IntToNSData:[deviceDict[@"authCode"] unsignedLongLongValue]];
            
            
            deviceEntity.deviceId = deviceDict[@"deviceID"];
            deviceEntity.deviceHash = devHash;
            deviceEntity.name = deviceDict[@"name"];
            deviceEntity.appearance = deviceDict[@"appearance"];
            deviceEntity.modelLow = modelLow;
            deviceEntity.modelHigh = modelHigh;
            deviceEntity.groups = groups;
            deviceEntity.authCode = authCode;
            deviceEntity.nGroups = deviceDict[@"numgroups"];
            deviceEntity.isAssociated = deviceDict[@"isAssociated"];
            deviceEntity.favourite = deviceDict[@"isFavourite"];
            
            //存储dhmKey、codingId、originName
            NSData *data = [BaseCommond converHexStrToData:deviceDict[@"dhmKey"]];
            NSString *codingId = deviceDict[@"codingId"];
            NSString *originName = deviceDict[@"originName"];
            
            [UDManager saveDhmKeyWith:deviceEntity.deviceId dhmKey:data];
            [UDManager saveDeviceCodingIdWith:deviceEntity.deviceId codingId:codingId];
            [UDManager saveDeviceOriginNameWith:deviceEntity.deviceId originName:originName];
            
            if ([CSRAppStateManager sharedInstance].selectedPlace) {
                [[CSRAppStateManager sharedInstance].selectedPlace addDevicesObject:deviceEntity];
            }
        }
        
        [[CSRDatabaseManager sharedInstance] loadDatabase];
    }
    
    if (parsingDictionary[@"gateways_list"])
    {
        for (NSDictionary *gatewayDict in parsingDictionary[@"gateways_list"]) {
            
            CSRGatewayEntity *gatewayObj = [NSEntityDescription insertNewObjectForEntityForName:@"CSRGatewayEntity" inManagedObjectContext:managedObjectContext];
            
            NSData *devHash = [CSRUtilities IntToNSData:[gatewayDict[@"deviceHash"] unsignedLongLongValue]];
            
            gatewayObj.basePath = gatewayDict[@"basePath"];
            gatewayObj.host = gatewayDict[@"host"];
            gatewayObj.name = gatewayDict[@"name"];
            
            if ([gatewayDict[@"port"] isKindOfClass:[NSString class]]) {
                NSNumberFormatter *formatter = [[NSNumberFormatter alloc] init];
                formatter.numberStyle = NSNumberFormatterDecimalStyle;
                NSNumber *portNumber = [formatter numberFromString:gatewayDict[@"port"]];
                gatewayObj.port = portNumber;
            } else {
                gatewayObj.port = gatewayDict[@"port"];
            }
            
            
            gatewayObj.uuid = gatewayDict[@"uuid"];
            gatewayObj.deviceId = gatewayDict[@"deviceID"];
            gatewayObj.state = gatewayDict[@"state"];
            gatewayObj.deviceHash = devHash;
            
            if ([CSRAppStateManager sharedInstance].selectedPlace) {
                [[CSRAppStateManager sharedInstance].selectedPlace addGatewaysObject:gatewayObj];
            }
        }
    }
    
    if (parsingDictionary[@"rest_list"])
    {
        for (NSDictionary *restDict in parsingDictionary[@"rest_list"]) {
            
            CSRSettingsEntity *settingsEntity = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
            settingsEntity.cloudMeshID = restDict[@"cloudMeshID"];
            settingsEntity.cloudTenancyID = restDict[@"cloudTenantID"];
            
            CSRPlaceEntity *placeEntity = [[CSRAppStateManager sharedInstance] selectedPlace];
            placeEntity.cloudSiteID = restDict[@"cloudSiteID"];
        }
    }
    [[CSRDatabaseManager sharedInstance] saveContext];
}

#pragma mark -
#pragma mark Compose Database

- (NSData *) composeDatabase
{
    NSMutableDictionary *jsonDictionary = [NSMutableDictionary new];
    NSMutableArray *devicesArray = [NSMutableArray new];
    NSMutableArray *areasArray = [NSMutableArray new];
    NSMutableArray *gatewayArray = [NSMutableArray new];
    NSMutableArray *restArray = [NSMutableArray new];
    
    ///////////////////Devices//////////////////////////////////////
        
        NSSet *devices = [CSRAppStateManager sharedInstance].selectedPlace.devices;
        if (devices) {
            for (CSRDeviceEntity *device in devices) {
                
                uint64_t hash = [CSRUtilities NSDataToInt:device.deviceHash];
                uint64_t modelLow = [CSRUtilities NSDataToInt:device.modelLow];
                uint64_t modelHigh = [CSRUtilities NSDataToInt:device.modelHigh];
                NSString *dhmKey = [[NSString alloc] initWithData:device.dhmKey encoding:NSUTF8StringEncoding];
                
                uint16_t *choppedValue = (uint16_t*)device.groups.bytes;
                NSMutableArray *groupsInArray = [NSMutableArray array];
                for (int i = 0; i < device.groups.length/2; i++) {
                    NSNumber *group = @(*choppedValue++);
                    [groupsInArray addObject:group];
                }
                
                uint16_t authCode = [CSRUtilities NSDataToInt:device.authCode];

                //dhmKey
                dhmKey = [self converDataToHexString:[UDManager getDhmKeyWith:device.deviceId]];

                //codingId
                NSString *codingId = [UDManager getDeviceCodingId:device.deviceId];
                
                //originName
                NSString *originName = [UDManager getDeviceOriginName:device.deviceId];
                
                [devicesArray addObject:@{@"deviceID":(device.deviceId) ? (device.deviceId) : @0,
                                          @"name":(device.name) ? (device.name) : @"",
                                          @"appearance":(device.appearance) ? (device.appearance) : @0,
                                          @"hash":[NSNumber numberWithUnsignedLongLong:hash] ? [NSNumber numberWithUnsignedLongLong:hash] : @0,
                                          @"modelLow":[NSNumber numberWithUnsignedLongLong:modelLow] ? [NSNumber numberWithUnsignedLongLong:modelLow] : @0,
                                          @"modelHigh":[NSNumber numberWithUnsignedLongLong:modelHigh] ? [NSNumber numberWithUnsignedLongLong:modelHigh] : @0,
                                          @"numgroups":(device.nGroups) ? (device.nGroups) : @0,
                                          @"groups":groupsInArray,
                                          @"authCode":([NSNumber numberWithUnsignedLongLong:authCode]) ? [NSNumber numberWithUnsignedLongLong:authCode] : @0,
                                          @"isAssociated":(device.isAssociated) ? (device.isAssociated) : @0,
                                          @"isFavourite":(device.favourite) ? (device.favourite) : @0,
                                          @"dhmKey" : dhmKey ? dhmKey : @"",
                                          @"codingId":codingId ? codingId : @"",
                                          @"originName":originName ? originName : @"",
                                          }
                 ];
            }
        }
        if (devicesArray) {
            [jsonDictionary setObject:devicesArray forKey:@"devices_list"];
        }
        
        ///////////////////Areas//////////////////////////////////////
        
        NSSet *areas = [CSRAppStateManager sharedInstance].selectedPlace.areas;
        
        for (CSRAreaEntity *area in areas) {
            
            [areasArray addObject:@{@"areaID":(area.areaID) ? (area.areaID) : @0,
                                    @"name":(area.areaName) ? (area.areaName) : @"",
                                    @"isFavourite":(area.favourite) ? (area.favourite) : @0}];
            
        }
        
        [jsonDictionary setObject:areasArray forKey:@"areas_list"];
        
        ///////////////////Gateway//////////////////////////////////////
        
        NSSet *gateways = [CSRAppStateManager sharedInstance].selectedPlace.gateways;
        
        for (CSRGatewayEntity *gateway in gateways) {
            uint64_t hash = [CSRUtilities NSDataToInt:gateway.deviceHash];
            [gatewayArray addObject:@{@"basePath":(gateway.basePath) ? (gateway.basePath) : @"",
                                      @"host":(gateway.host) ? (gateway.host) : @"",
                                      @"name":(gateway.name) ? (gateway.name) : @"",
                                      @"port":(gateway.port) ? (gateway.port) : @0,
                                      @"uuid":(gateway.uuid) ? (gateway.uuid) : @"",
                                      @"deviceID":(gateway.deviceId) ? (gateway.deviceId) : @0,
                                      @"state":(gateway.state) ? (gateway.state) : @0,
                                      @"deviceHash":[NSNumber numberWithUnsignedLongLong:hash] ? [NSNumber numberWithUnsignedLongLong:hash] : @0}];
        }
        
        [jsonDictionary setObject:gatewayArray forKey:@"gateways_list"];
        
        ///////////////////Rest//////////////////////////////////////
        
        CSRSettingsEntity *settingEntity = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
        CSRPlaceEntity *placeEntity = [CSRAppStateManager sharedInstance].selectedPlace;
    
        //TODO: Temporary fix to get cloudMeshID
        NSString *meshId = [[MeshServiceApi sharedInstance] getMeshId];
    
        [restArray addObject:@{@"cloudMeshID": meshId,//(settingEntity.cloudMeshID) ? (settingEntity.cloudMeshID) : @"",
                               @"cloudTenantID": (settingEntity.cloudTenancyID) ? (settingEntity.cloudTenancyID) : @"",
                               @"cloudSiteID": (placeEntity.cloudSiteID) ? (placeEntity.cloudSiteID) : @""}];
        
        [jsonDictionary setObject:restArray forKey:@"rest_list"];
    
    /////////////////////////////////////////////////////////////
    NSError *error;
    NSData* jsonData = [NSJSONSerialization dataWithJSONObject:jsonDictionary
                                                       options:0
                                                         error:&error];
    return jsonData;
    
}

//NSData转十六进制字符串
- (NSString *) converDataToHexString:(NSData *)data {
    if (data == nil) {
        return nil;
    }
    NSMutableString* hexString = [NSMutableString string];
    const unsigned char *p = [data bytes];
    for (int i=0; i < [data length]; i++) {
        [hexString appendFormat:@"%02x", *p++];
    }
    return hexString;
}

@end
