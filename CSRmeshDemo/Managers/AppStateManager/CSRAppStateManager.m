//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CSRAppStateManager.h"
#import "CSRDatabaseManager.h"
#import "CSRUtilities.h"
#import <CSRmesh/CSRMeshUserManager.h>
#import "CSRmeshSettings.h"
#import "CSRBluetoothLE.h"
#import "CSRDevicesManager.h"
#import "AFHTTPRequestOperationManager.h"
#import <CSRmesh/CSRGatewayNetService.h>

@interface CSRAppStateManager() <CSRBluetoothLEDelegate, MeshServiceApiDelegate>

@end


@implementation CSRAppStateManager

#pragma mark - Singleton methods

+ (CSRAppStateManager*)sharedInstance
{
    static dispatch_once_t token;
    static CSRAppStateManager *shared = nil;
    
    dispatch_once(&token, ^{
        shared = [[CSRAppStateManager alloc] init];
    });
    
    return shared;
}

- (id)init
{
    if (self = [super init]) {
        
        _bearerType = (CSRSelectedBearerType)0;
        _isBearerModeAutomatic = NO;
        [self callBonjour];
        
    }
    
    [[MeshServiceApi sharedInstance] addDelegate:self];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleDataModelChange:)
                                                 name:NSManagedObjectContextDidSaveNotification
                                               object:[[CSRDatabaseManager sharedInstance] managedObjectContext]];
    
    return self;
}

- (void)callBonjour
{
    [[CSRNetServiceBrowser sharedInstance] addDelegate:self];
    
    [[CSRNetServiceBrowser sharedInstance] startBrowsing:@"_csrmeshgw._tcp." domain:@"local"];

}

- (void)handleDataModelChange:(NSNotification *)note
{
}

#pragma mark - Connection switch

- (void)switchConnectionForSelectedBearerType:(CSRSelectedBearerType)bearerType
{
    
    _bearerType = bearerType;
    
    switch (_bearerType) {
            
        case CSRSelectedBearerType_Bluetooth: {
            
            [[CSRBluetoothLE sharedInstance] powerOnCentralManager];
            [[CSRmeshSettings sharedInstance] setBleConnectMode:(BleAutoConnectMode)1];
            [[MeshServiceApi sharedInstance] setBluetoothBearerEnabled];
            [[CSRBluetoothLE sharedInstance] setBleDelegate:self];
            
        }
        
            break;
            
        case CSRSelectedBearerType_Cloud: {
            
            [[CSRBluetoothLE sharedInstance] powerOffCentralManager];
            [[CSRmeshSettings sharedInstance] setBleConnectMode:(BleAutoConnectMode)0];
            [[MeshServiceApi sharedInstance] setRestBearerEnabled];
            [[CSRBluetoothLE sharedInstance] setBleDelegate:nil];
            [self setupCloudWithEndpoint:CSRMeshRestEndpoint_Cloud withMode:CSRMeshRestMode_CNC];
            
        }
        
            break;
            
        case CSRSelectedBearerType_Gateway: {
            
            [[CSRBluetoothLE sharedInstance] powerOffCentralManager];
            [[CSRmeshSettings sharedInstance] setBleConnectMode:(BleAutoConnectMode)0];
            [[MeshServiceApi sharedInstance] setRestBearerEnabled];
            [[CSRBluetoothLE sharedInstance] setBleDelegate:nil];
            [self setupCloudWithEndpoint:CSRMeshRestEndpoint_Gateway withMode:CSRMeshRestMode_CNC];
            
        }
        
            break;
            
        default:
            break;
    }
    
    if (_bearerType == CSRSelectedBearerType_Gateway) {
        
        [self setupCloudWithEndpoint:CSRMeshRestEndpoint_Gateway withMode:CSRMeshRestMode_AUTH];
        [[MeshServiceApi sharedInstance] authenticateRest:[[[UIDevice currentDevice] identifierForVendor] UUIDString] dhmkey:[CSRUtilities reverseData:_currentGateway.dhmKey]];
        
    }
    
}

#pragma mark - Cloud setup

- (void)setupCloudWithEndpoint:(CSRMeshRestEndpoint)endpoint withMode:(CSRMeshRestMode)mode;
{
    
    [CSRMeshUserManager sharedInstance].applicationId = kAppCode;
    [CSRMeshUserManager sharedInstance].tenant.tenantId = _selectedPlace.settings.cloudTenancyID;
    [CSRMeshUserManager sharedInstance].site.siteId = _selectedPlace.cloudSiteID;
    
    if ([CSRUtilities isStringEmpty:_selectedPlace.settings.cloudMeshID]) {
    
        _selectedPlace.settings.cloudMeshID = [CSRMeshUserManager sharedInstance].meshId;
        
    }
    switch (endpoint) {
        case CSRMeshRestEndpoint_Cloud:
            
            switch (mode) {
                    
                case CSRMeshRestMode_AUTH:
                    [[CSRMeshUserManager sharedInstance] setupCloud:kCloudServerUriScheme
                                                               host:_globalCloudHost //kCloudServerUrl
                                                               port:kCloudServerPort
                                                           basePath:kCNCServerBasePath
                                                          serverURL:CSRRestServerComponent_AUTH
                                                  connectionChannel:CSRRestConnectionChannel_CLOUD];
                    break;
                    
                    
                case CSRMeshRestMode_Config:
                    
                    [[CSRMeshUserManager sharedInstance] setupCloud:kCloudServerUriScheme
                                                               host:_globalCloudHost //kCloudServerUrl
                                                               port:kCloudServerPort
                                                           basePath:kConfigServerBasePath
                                                          serverURL:CSRRestServerComponent_CONFIG
                                                  connectionChannel:CSRRestConnectionChannel_CLOUD];
                    break;
                    
                case CSRMeshRestMode_CNC:
                    
                    [[CSRMeshUserManager sharedInstance] setupCloud:kCloudServerUriScheme
                                                               host:_globalCloudHost //kCloudServerUrl
                                                               port:kCloudServerPort
                                                           basePath:kCNCServerBasePath
                                                          serverURL:CSRRestServerComponent_CNC
                                                  connectionChannel:CSRRestConnectionChannel_CLOUD];
                    break;
                    
                default:
                    break;
            }
            
            break;
            
            
        case CSRMeshRestEndpoint_Gateway:
            
            switch (mode) {
                    
                case CSRMeshRestMode_AUTH:
                    
                    [[CSRMeshUserManager sharedInstance] setupCloud:kGatewayServerUriScheme
                                                               host:_currentGateway.host
                                                               port:[NSString stringWithFormat:@"%@", _currentGateway.port]
                                                           basePath:[NSString stringWithFormat:@"/cgi-bin%@", kAuthServerBasePath]
                                                          serverURL:CSRRestServerComponent_AUTH
                                                  connectionChannel:CSRRestConnectionChannel_GATEWAY];
                    break;
                    
                case CSRMeshRestMode_Config:
                    
                    [[CSRMeshUserManager sharedInstance] setupCloud:kGatewayServerUriScheme
                                                               host:_currentGateway.host
                                                               port:[NSString stringWithFormat:@"%@", _currentGateway.port]
                                                           basePath:[NSString stringWithFormat:@"/cgi-bin%@", kConfigServerBasePath]
                                                          serverURL:CSRRestServerComponent_CONFIG
                                                  connectionChannel:CSRRestConnectionChannel_GATEWAY];
                    break;
                    
                case CSRMeshRestMode_CNC:
                    
                    [[CSRMeshUserManager sharedInstance] setupCloud:kGatewayServerUriScheme
                                                               host:_currentGateway.host
                                                               port:[NSString stringWithFormat:@"%@", _currentGateway.port]
                                                           basePath:[NSString stringWithFormat:@"/cgi-bin%@", kCNCServerBasePath]
                                                          serverURL:CSRRestServerComponent_CNC
                                                  connectionChannel:CSRRestConnectionChannel_GATEWAY];
                    
                    break;
                    
                default:
                    break;
            }
            
            break;
            
            
        default:
            break;
    }
    
}

#pragma mark - Place setup

- (void)createDefaultPlace
{
    NSArray *places = [[CSRDatabaseManager sharedInstance] fetchObjectsWithEntityName:@"CSRPlaceEntity" withPredicate:nil];
    
    if ([places count] <= 0) {
        
        CSRPlaceEntity *defaultPlace = [NSEntityDescription insertNewObjectForEntityForName:@"CSRPlaceEntity" inManagedObjectContext:[CSRDatabaseManager sharedInstance].managedObjectContext];
        
        defaultPlace.name = @"iOSHouse";
        defaultPlace.passPhrase = @"sj21";  //默认组网密码
        defaultPlace.color = @([CSRUtilities rgbFromColor:[CSRUtilities colorFromHex:@"#2196f3"]]);
        defaultPlace.iconID = @(8);
        defaultPlace.owner = @"My place";
        
        [[CSRDatabaseManager sharedInstance] saveContext];
        
        [CSRUtilities saveObject:[[[defaultPlace objectID] URIRepresentation] absoluteString] toDefaultsWithKey:@"kCSRLastSelectedPlaceID"];
        
    }
}

- (void)setupPlace
{
    id placeIdURLString = [CSRUtilities getValueFromDefaultsForKey:@"kCSRLastSelectedPlaceID"];
    NSManagedObjectID *placeID = [[CSRDatabaseManager sharedInstance].persistentStoreCoordinator managedObjectIDForURIRepresentation:[NSURL URLWithString:placeIdURLString]];
    
    if ([placeID isKindOfClass:[NSManagedObjectID class]]) {
        
        NSArray *placesArray = [[CSRDatabaseManager sharedInstance] fetchObjectsWithEntityName:@"CSRPlaceEntity" withPredicate:nil];
        
        [placesArray enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
            
            CSRPlaceEntity *place = (CSRPlaceEntity *)obj;
            
            if ([[place objectID] isEqual:placeID]) {
                
                _selectedPlace = place;
                                
                NSString *passPhrase = [[NSUserDefaults standardUserDefaults] valueForKey:UD_Passcode];
                if (passPhrase) {
                    _selectedPlace.passPhrase = passPhrase;
                }
                NSLog(@"_selectedPlace.passPhrase: %@",_selectedPlace.passPhrase);
                
                if (_selectedPlace.passPhrase) {
                    
                    [[CSRDevicesManager sharedInstance] setNetworkPassPhrase:_selectedPlace.passPhrase];
                } else {
                    [[CSRDevicesManager sharedInstance] setNetworkKey:_selectedPlace.networkKey];
                }
                _selectedPlace.settings.cloudMeshID = [CSRMeshUserManager sharedInstance].meshId;
                [[CSRDatabaseManager sharedInstance] loadDatabase];
                
                *stop = YES;
                
            }
            
        }];
        
    }
}

- (void)selectGatewayCommunicationChannel
{
    if (_currentGateway) {
        
        if ([_currentGateway.state intValue] == CSRGateWayState_Cloud) {
            
            [self setupCloudWithEndpoint:CSRMeshRestEndpoint_Cloud withMode:CSRMeshRestMode_CNC];
            
        } else if ([_currentGateway.state intValue] == CSRGateWayState_Local) {
            
            [self setupCloudWithEndpoint:CSRMeshRestEndpoint_Gateway withMode:CSRMeshRestMode_CNC];
            
        }
        
    }
}


#pragma mark - User methods

- (CSRUserEntity *)createUserForCurrentlyLoggedInUser
{
    
    __block NSString *email, *name, *userId;
    
    CSRUserEntity *user = [[[CSRDatabaseManager sharedInstance] fetchObjectsWithEntityName:@"CSRUserEntity" withPredicate:@"userId == %@", userId] firstObject];
    
    if (user) {
        
        
    } else {

        user = [NSEntityDescription insertNewObjectForEntityForName:@"CSRUserEntity" inManagedObjectContext:[CSRDatabaseManager sharedInstance].managedObjectContext];
        user.token = nil;
        user.name = name;
        user.email = email;
        user.userId = userId;

    }
    
    [[CSRDatabaseManager sharedInstance] saveContext];
    
    return user;
    
}

#pragma mark - Available bearers

- (NSArray *)getAvaialableBearersList
{
    
    __block NSMutableDictionary *bearersDict = [NSMutableDictionary new];
    
    [self.selectedPlace.gateways enumerateObjectsUsingBlock:^(id  _Nonnull obj, BOOL * _Nonnull stop) {
        
        CSRGatewayEntity *gateway = (CSRGatewayEntity*)obj;
        
        if ([gateway.state isEqualToNumber:@2]) {
            
            if (![bearersDict valueForKey:@"gateway"]) {
                
                [bearersDict setValue:@1 forKey:@"gateway"];
                
            }
            
        }
        
        if ([gateway.state isEqualToNumber:@3]) {
            
            if (![bearersDict valueForKey:@"gateway"]) {
                
                [bearersDict setValue:@1 forKey:@"gateway"];
                
            }
            
            if (![bearersDict valueForKey:@"cloud"]) {
                
                [bearersDict setValue:@1 forKey:@"cloud"];
                
            }
        }
        
    }];
    
    NSMutableArray *availableBearers = [NSMutableArray new];
    [availableBearers addObject:@"Bluetooth"];
    
    if ([bearersDict valueForKey:@"gateway"]) {
        
        [availableBearers addObject:@"Gateway"];
        
    }
    
    if ([bearersDict valueForKey:@"cloud"]) {
        
        [availableBearers addObject:@"Cloud"];
        
    }
    
    return (NSArray *)availableBearers;
    
}

#pragma mark - Connectivity

- (void)connectivityCheck
{
    AFHTTPRequestOperationManager *_manager = [[AFHTTPRequestOperationManager alloc] initWithBaseURL:[NSURL URLWithString:@"www.qualcomm.com"]];
    __weak AFHTTPRequestOperationManager *manager = _manager;
    
    [manager.reachabilityManager setReachabilityStatusChangeBlock:^(AFNetworkReachabilityStatus status)
     {
         switch (status)
         {
             case AFNetworkReachabilityStatusReachableViaWiFi:
             {
                 [[CSRNetServiceBrowser sharedInstance] addDelegate:self];

                 [[CSRNetServiceBrowser sharedInstance] startBrowsing:@"_csrmeshgw._tcp." domain:@"local"];
                 
             }
                 break;
             default:
             {
                 break;
             }
         }
     }];
    
    [_manager.reachabilityManager startMonitoring];
    
}

#pragma mark - <CSRNetServiceBrowserDelegate>

- (void)didFindService:(CSRNetService *)service
{
    if (service) {
        
        CSRGatewayNetService *gateway = (CSRGatewayNetService *)service;
        
        [[CSRAppStateManager sharedInstance].selectedPlace.gateways enumerateObjectsUsingBlock:^(id  _Nonnull obj, BOOL * _Nonnull stop) {
            CSRGatewayEntity *gatewayEntity = (CSRGatewayEntity *)obj;
            NSLog(@"GWE :%@ and BGW :%@", gatewayEntity.uuid, gateway.gatewayUUID);
            if ([gatewayEntity.uuid isEqualToString:gateway.gatewayUUID]) {
                
                _currentGateway = [[[CSRDatabaseManager sharedInstance] fetchObjectsWithEntityName:@"CSRGatewayEntity" withPredicate:@"uuid == %@", gateway.gatewayUUID] firstObject];
                
                [self setupCloudWithEndpoint:CSRMeshRestEndpoint_Gateway withMode:CSRMeshRestMode_AUTH];
                [[MeshServiceApi sharedInstance] authenticateRest:[[[UIDevice currentDevice] identifierForVendor] UUIDString] dhmkey:[CSRUtilities reverseData:_currentGateway.dhmKey]];

            }
            
        }];
    }
}

- (void)didNotifyAuthenticationState:(CSRRestAuthenticationState)status
{
    switch (status) {
        
        case CSRRestAuthenticated: {
            
            NSLog(@"Auth completed [%s]", __PRETTY_FUNCTION__);
            
            if (_bearerType == CSRSelectedBearerType_Gateway) {
                
                [self setupCloudWithEndpoint:CSRMeshRestEndpoint_Gateway withMode:CSRMeshRestMode_CNC];
                
            } else if (_bearerType == CSRSelectedBearerType_Cloud) {
                
                [self setupCloudWithEndpoint:CSRMeshRestEndpoint_Cloud withMode:CSRMeshRestMode_CNC];
                
            }
            
        }
        
            break;
            
        case CSRRestAuthenticationInProgress:
            NSLog(@"Auth in progress [%s]", __PRETTY_FUNCTION__);
            break;
            
        case CSRRestAuthenticationExpired:
            NSLog(@"Authentication expired [%s]", __PRETTY_FUNCTION__);
            [[MeshServiceApi sharedInstance] authenticateRest:[[[UIDevice currentDevice] identifierForVendor] UUIDString] dhmkey:[CSRUtilities reverseData:_currentGateway.dhmKey]];
            break;
            
        default:
            break;
    }
}

#pragma mark - Filter gateways

- (BOOL)isGatewayAlreadySaved:(NSString *)uuid
{
    
    __block BOOL gatewayAlreadySaved = NO;
    
    [[CSRAppStateManager sharedInstance].selectedPlace.gateways enumerateObjectsUsingBlock:^(id  _Nonnull obj, BOOL * _Nonnull stop) {
        CSRGatewayEntity *gatewayEntity = (CSRGatewayEntity *)obj;
        
        if ([gatewayEntity.uuid isEqualToString:uuid]) {
            
            gatewayAlreadySaved = YES;
            
        }
        
    }];
    
    return gatewayAlreadySaved;
}



@end
