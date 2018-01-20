//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import "CSRmeshSettings.h"
#import "CSRDatabaseManager.h"
#import "CSRSettingsEntity.h"

@interface CSRmeshSettings ()
{
    BleAutoConnectMode connectionMode;
}
@end

@implementation CSRmeshSettings

+ (id) sharedInstance {
    
    static dispatch_once_t token;
    static CSRmeshSettings *shared = nil;
    
    dispatch_once(&token, ^{
        shared = [[CSRmeshSettings alloc] init];
    });
    
    return shared;
}

- (void)setBleConnectMode:(BleAutoConnectMode)mode
{
    connectionMode = mode;
    
    CSRSettingsEntity * settings = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
    
    if (settings) {
        
        settings.concurrentConnections = [NSNumber numberWithInteger:connectionMode];
        [[CSRDatabaseManager sharedInstance] saveContext];
        [[NSNotificationCenter defaultCenter] postNotificationName:CSR_BLE_CONNECTION_MODE object:self userInfo:@{CSR_BLE_CONNECTION_MODE:[NSNumber numberWithInteger:connectionMode]}];

    }
}

- (BleAutoConnectMode)getBleConnectMode
{
    BleAutoConnectMode connections= CSR_BLE_CONNECTIONS_MANUAL;
    
    CSRSettingsEntity * settings = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
    
    if (settings) {
        
        connections = (BleAutoConnectMode)[[[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace].concurrentConnections integerValue];
        
    }
    
    return (connections);
}

- (void)setBleListenMode:(CSRBleListenMode)segmentValue
{
    CSRSettingsEntity * settings = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
    
    if (settings) {
        
        settings.listeningMode = [NSNumber numberWithInteger:segmentValue];
        [[CSRDatabaseManager sharedInstance] saveContext];
        [[NSNotificationCenter defaultCenter] postNotificationName:CSR_BLE_LISTEN_MODE object:self userInfo:@{CSR_BLE_LISTEN_MODE:[NSNumber numberWithInteger:segmentValue]}];
    }
}

- (CSRBleListenMode)getBleListenMode
{
    CSRBleListenMode listenNumber = CSRBleListenMode_ScanNotificationListen;
   
    CSRSettingsEntity * settings = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
    
    if (settings) {
        
        listenNumber = (CSRBleListenMode)[[[CSRDatabaseManager sharedInstance] fetchSettingsEntity].listeningMode integerValue];
        
    }

    return (listenNumber);
}

- (void)setRetryInterval:(NSNumber *)interval
{
    CSRSettingsEntity * settings = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
    
    if (settings) {
        
        settings.retryInterval = interval;
        [[CSRDatabaseManager sharedInstance] saveContext];
        [[NSNotificationCenter defaultCenter] postNotificationName:CSR_RETRY_INTERVAL_NUMBER object:self userInfo:@{CSR_RETRY_INTERVAL_NUMBER:interval}];
        
    }
}

- (void)setRetryCount:(NSNumber *)count
{
    CSRSettingsEntity * settings = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
    
    if (settings) {
        
        settings.retryCount = count;
        [[CSRDatabaseManager sharedInstance] saveContext];
        [[NSNotificationCenter defaultCenter] postNotificationName:CSR_RETRY_COUNT_NUMBER object:self userInfo:@{CSR_RETRY_COUNT_NUMBER:count}];
        
    }
}

- (void)setHostID:(NSNumber *)hostID
{
    //[[CSRDatabaseManager sharedInstance] saveContext];
    [[NSNotificationCenter defaultCenter] postNotificationName:CSR_HOST_ID_NUMBER object:self userInfo:@{CSR_HOST_ID_NUMBER:hostID}];
    
}

- (void)setCloudTenancyID:(NSString*)tenancyId
{
    CSRSettingsEntity * settings = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
    
    if (settings) {
        
        settings.cloudTenancyID = tenancyId;
        [[CSRDatabaseManager sharedInstance] saveContext];
        [[NSNotificationCenter defaultCenter] postNotificationName:CSR_CLOUD_TENANCY_NUMBER object:self userInfo:@{CSR_CLOUD_TENANCY_NUMBER:tenancyId}];
    }
}

- (void)setCloudMeshID:(NSString*)meshId
{
    CSRSettingsEntity * settings = [[CSRDatabaseManager sharedInstance] settingsForCurrentlySelectedPlace];
    
    if (settings) {
        
        settings.cloudTenancyID = meshId;
        [[CSRDatabaseManager sharedInstance] saveContext];
        [[NSNotificationCenter defaultCenter] postNotificationName:CSR_CLOUD_MESH_NUMBER object:self userInfo:@{CSR_CLOUD_MESH_NUMBER:meshId}];
    }
}

@end
