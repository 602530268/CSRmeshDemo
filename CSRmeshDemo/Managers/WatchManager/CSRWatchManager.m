//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRWatchManager.h"
#import "CSRDeviceEntity.h"
#import "CSRAreaEntity.h"
#import "WatchSharedConsts.h"
#import "CSRDatabaseManager.h"
#import "CSRDevicesManager.h"
#import "CSRMeshDevice.h"
#import "CSRmeshArea.h"

    // Favourite Device to be cached
@interface LocalDevice: NSObject
@property   NSNumber *deviceId;
@property   NSString *name;
@property   NSString *appearance;
@property   NSNumber *actualTemp;
@property   NSNumber *desiredTemp;
@property   NSNumber *isDevice;
@property   NSNumber *isArea;
@property   NSNumber *isActivity;
@end

@implementation LocalDevice
@synthesize deviceId, name, actualTemp, desiredTemp;
@synthesize appearance, isDevice, isArea, isActivity;

-(id) init {
    self = [super init];
    return(self);
}
@end
    /////////////////////////////////


@interface  CSRWatchManager () {
    NSMutableArray *pendingSessionWrites;
    NSTimer *sensorTimer;
    NSMutableDictionary *delayedMessageWrite;
    NSMutableDictionary *favourtieDevicesCache;
}
@end


@implementation CSRWatchManager;


@synthesize wcSession;

+ (id) sharedInstance
{
    
    static dispatch_once_t token;
    static CSRWatchManager *shared = nil;
    
    dispatch_once(&token, ^{
        shared = [[CSRWatchManager alloc] init];
    });
    
    return shared;
}

- (id)init {
    if (self = [super init]) {
        if ([WCSession isSupported]) {
            wcSession = [WCSession defaultSession];
            wcSession.delegate = self;
            [wcSession activateSession];
            favourtieDevicesCache = [NSMutableDictionary dictionary];
        }
    }
    return self;
}

#pragma mark - Send Data to Watch
-(void) clearAllWatchData {
    if (wcSession) {
        NSMutableDictionary *messageToWatch = [NSMutableDictionary dictionary];
        [messageToWatch setObject:@(YES) forKey:kCSRWATCH_DELETE_ALL_DATA];
        [self sendMessageToWatch:messageToWatch];

        // Update Cache
        favourtieDevicesCache = [NSMutableDictionary dictionary];
    }
}

-(void) updateDesiredTemperature:(NSNumber *)deviceId desiredTemperature:(NSNumber *)temperature {
    if (wcSession) {
        CSRDeviceEntity *device = [[CSRDatabaseManager sharedInstance]getDeviceEntityWithId:deviceId];
        CSRAreaEntity *area = [[CSRDatabaseManager sharedInstance]getAreaEntityWithId:deviceId];
        if ((device && device.favourite) || (area && area.favourite)) {
            NSMutableDictionary *messageToWatch = [NSMutableDictionary dictionary];
            [messageToWatch setObject:temperature forKey:kCSRWATCH_DESIRED_TEMP];
            [messageToWatch setObject:deviceId forKey:kCSRWATCH_DEVICEID];
            [messageToWatch setObject:@(YES) forKey:kCSRWATCH_FAVOURITE];
            [self sendDelayedMessageToWatch:messageToWatch forDevice:deviceId];
        }

        // Update Cache
        LocalDevice *localDevice = [[LocalDevice alloc] init];
        localDevice.deviceId = deviceId;
        localDevice.desiredTemp=temperature;
        [favourtieDevicesCache setObject:localDevice forKey:deviceId];
    }
}


-(void) updateActualTemperature:(NSNumber *)deviceId actualTemperature:(NSNumber *)temperature {
    if (wcSession) {
        CSRDeviceEntity *device = [[CSRDatabaseManager sharedInstance]getDeviceEntityWithId:deviceId];
        CSRAreaEntity *area = [[CSRDatabaseManager sharedInstance]getAreaEntityWithId:deviceId];
        if ((device && device.favourite) || (area && area.favourite)) {
            NSMutableDictionary *messageToWatch = [NSMutableDictionary dictionary];
            [messageToWatch setObject:temperature forKey:kCSRWATCH_ACTUAL_TEMP];
            [messageToWatch setObject:deviceId forKey:kCSRWATCH_DEVICEID];
            [messageToWatch setObject:@(YES) forKey:kCSRWATCH_FAVOURITE];
            [self sendDelayedMessageToWatch:messageToWatch forDevice:deviceId];
        }
        // Update Cache
        LocalDevice *localDevice = [[LocalDevice alloc] init];
        localDevice.deviceId = deviceId;
        localDevice.desiredTemp=temperature;
        [favourtieDevicesCache setObject:localDevice forKey:deviceId];
    }
}



-(void) updateFavourite:(id)item {
    if (wcSession) {
        // Update Cache
        LocalDevice *localDevice = [[LocalDevice alloc] init];
        NSMutableDictionary *messageToWatch = [NSMutableDictionary dictionary];
        if ([item isKindOfClass:[CSRDeviceEntity class]]) {
            CSRDeviceEntity *device = item;
            [messageToWatch setObject:device.deviceId forKey:kCSRWATCH_DEVICEID];
            if (favourtieDevicesCache[device.deviceId])
                localDevice = favourtieDevicesCache[device.deviceId];
            [messageToWatch setObject:@(YES) forKey:kCSRWATCH_IS_DEVICE];
            if (device.favourite && [device.favourite boolValue]) {
                [messageToWatch setObject:device.favourite forKey:kCSRWATCH_FAVOURITE];
                if (device.appearance) {
                    NSString *appearance = [NSString stringWithFormat:@"%@",device.appearance];
                    [messageToWatch setObject:appearance forKey:kCSRWATCH_APPEARANCE];
                    localDevice.appearance=appearance;
                }
                if (device.name) {
                    [messageToWatch setObject:device.name forKey:kCSRWATCH_DEVICE_NAME];
                    localDevice.name=device.name;
                }

                // Update Cache
                localDevice.deviceId = device.deviceId;
                localDevice.isDevice = @(YES);
                localDevice.isArea = nil;
                localDevice.isActivity = nil;
                
                [favourtieDevicesCache setObject:localDevice forKey:device.deviceId];
            }
            else
                [favourtieDevicesCache removeObjectForKey:device.deviceId];
            
        }
        else if ([item isKindOfClass:[CSRAreaEntity class]]) {
            CSRAreaEntity *area = item;
            [messageToWatch setObject:area.areaID forKey:kCSRWATCH_DEVICEID];
            if (favourtieDevicesCache[area.areaID])
                localDevice = favourtieDevicesCache[area.areaID];
            [messageToWatch setObject:@(YES) forKey:kCSRWATCH_IS_AREA];
            if ([area.favourite boolValue]) {
                NSString *appearance;
                for (CSRDeviceEntity *device in area.devices) {
                    if (appearance)
                        appearance = [NSString stringWithFormat:@"%@,%@",appearance, device.appearance];
                    else
                        appearance = [NSString stringWithFormat:@"%@",device.appearance];
                }
                if (appearance) {
                    [messageToWatch setObject:area.favourite forKey:kCSRWATCH_FAVOURITE];
                    [messageToWatch setObject:appearance forKey:kCSRWATCH_APPEARANCE];
                    [messageToWatch setObject:area.areaName forKey:kCSRWATCH_DEVICE_NAME];
                    localDevice.appearance=appearance;
                    localDevice.name=area.areaName;
                }
                // Update Cache
                localDevice.deviceId = area.areaID;
                localDevice.isDevice = nil;
                localDevice.isArea = @(YES);
                localDevice.isActivity = nil;
                [favourtieDevicesCache setObject:localDevice forKey:area.areaID];

            }
            else
                [favourtieDevicesCache removeObjectForKey:area.areaID];

        }
        [self sendMessageToWatch:messageToWatch];
    }
}


-(void) deleteFavourite:(NSNumber *)deviceId {
    if (wcSession) {
        NSDictionary *message = @{kCSRWATCH_DEVICEID:deviceId,
                                  kCSRWATCH_DELETE_DEVICE:@(YES)};
        [self sendMessageToWatch:message];
        [favourtieDevicesCache removeObjectForKey:deviceId];
    }
}

-(void) updateConnectionStatus:(NSNumber *)state {
    if (wcSession) {
        NSDictionary *message = @{kCSRWATCH_CONNECTION_STATUS:state};
        [self sendMessageToWatch:message];
    }
}


-(void) sendMessageToWatch:(NSDictionary *)message {
    if (message && message.count) {
        if (wcSession.watchAppInstalled && wcSession.paired && wcSession.reachable) {
            [wcSession updateApplicationContext:message error:nil];
       }
        else {
            // watch is not available so save for later
            if (!pendingSessionWrites) {
                pendingSessionWrites = [NSMutableArray array];
            }
            // TODO: optimise, remove writes to same device before adding new
            [pendingSessionWrites addObject:message];
        }
    }
}

    // if no timer then create one to fire every 3 seconds
    // using deviceId as key, save message in a dictionary ad continue to do so until timer fires
    // this means new messages will overwrite old for three seconds
    // When timer fires send all latest messages
    // if afer 3 further seconds have elaped then invalidate timer.
-(void) sendDelayedMessageToWatch:(NSDictionary *)message forDevice:(NSNumber *)deviceId {
    if (!sensorTimer) {
        sensorTimer = [NSTimer scheduledTimerWithTimeInterval:3.0 target:self selector:@selector(sensorRefresh) userInfo:nil repeats:YES];
    }
    delayedMessageWrite = [NSMutableDictionary dictionary];
    [delayedMessageWrite setObject:message forKey:deviceId];
}

-(void) sensorRefresh {
    if (delayedMessageWrite && delayedMessageWrite.count) {
        if (wcSession.watchAppInstalled && wcSession.paired && wcSession.reachable) {
            [delayedMessageWrite enumerateKeysAndObjectsUsingBlock:^(id key, NSDictionary *message, BOOL* stop) {
                [wcSession updateApplicationContext:message error:nil];
            }];
        }
    }
    else
        [sensorTimer invalidate];
}

#pragma mark - WCSession Delegates

-(void)sessionWatchStateDidChange:(WCSession *)session {
    // When watch becomes available, send pending writes
    if (pendingSessionWrites && session.watchAppInstalled && session.paired && session.reachable) {
        for (NSMutableDictionary *messageToWatch in pendingSessionWrites) {
            [wcSession updateApplicationContext:messageToWatch error:nil];
        }
        pendingSessionWrites = nil;
    }
    
    NSString *message = [NSString stringWithFormat:@"Watch state installed=%@ paired=%@ reachable=%@",@(wcSession.watchAppInstalled),@(wcSession.paired),@(wcSession.reachable)];
    NSLog (@"%@",message);
}

-(void)sessionReachabilityDidChange:(WCSession *)session {
    // When watch becomes available, send pending writes
    if (pendingSessionWrites && session.watchAppInstalled && session.paired && session.reachable) {
        for (NSMutableDictionary *messageToWatch in pendingSessionWrites) {
            [wcSession updateApplicationContext:messageToWatch error:nil];
        }
        pendingSessionWrites = nil;
    }
    
    NSString *message = [NSString stringWithFormat:@"Watch Reaxchibility changed = %@",@(session.reachable)];
    NSLog (@"%@",message);
}


-(void)session:(WCSession *)session didReceiveApplicationContext:(NSDictionary<NSString *,id> *)applicationContext {

    if(applicationContext[kCSRWATCH_SET_LIGHT_STATE] && applicationContext[kCSRWATCH_DEVICEID]) {
        NSNumber *deviceId = applicationContext[kCSRWATCH_DEVICEID];
        CSRmeshDevice *device;
        CSRmeshArea *area = [[CSRDevicesManager sharedInstance] getAreaFromId:deviceId];
        if (area)
            device = area.areaDevice;
        else
            device = [[CSRDevicesManager sharedInstance] getDeviceFromDeviceId:deviceId];
        
        if(device)
            [device setPower:[applicationContext[kCSRWATCH_SET_LIGHT_STATE] boolValue]];
    }
    else if (applicationContext[kCSRWATCH_SET_DESIRED_TEMP] && applicationContext[kCSRWATCH_DEVICEID]) {
        NSNumber *deviceId = applicationContext[kCSRWATCH_DEVICEID];
        NSNumber *temperature = applicationContext[kCSRWATCH_SET_DESIRED_TEMP];
        CSRmeshArea *area = [[CSRDevicesManager sharedInstance] getAreaFromId:deviceId];
        if (area) {
            [area setDesiredTemperatureSetByUser:temperature];
            dispatch_async(dispatch_get_main_queue(), ^(void){
                [[CSRDevicesManager sharedInstance] setDesiredTemperatureForArea:area];
            });
       }
    }
    else if (applicationContext[kCSRWATCH_FORCE_REFRESH]) {
        for (NSNumber *deviceId in favourtieDevicesCache) {
            LocalDevice *ld = favourtieDevicesCache[deviceId];
            NSMutableDictionary *messageToWatch = [NSMutableDictionary dictionary];
            [messageToWatch setObject:ld.deviceId forKey:kCSRWATCH_DEVICEID];
            [messageToWatch setObject:@(YES) forKey:kCSRWATCH_FAVOURITE];
            if(ld.name)
                [messageToWatch setObject:ld.name forKey:kCSRWATCH_DEVICE_NAME];
            if(ld.appearance)
                [messageToWatch setObject:ld.appearance forKey:kCSRWATCH_APPEARANCE];
            if(ld.actualTemp)
                [messageToWatch setObject:ld.actualTemp forKey:kCSRWATCH_ACTUAL_TEMP];
            if(ld.desiredTemp)
                [messageToWatch setObject:ld.desiredTemp forKey:kCSRWATCH_DESIRED_TEMP];
            if(ld.isDevice)
                [messageToWatch setObject:@(YES) forKey:kCSRWATCH_IS_DEVICE];
            if(ld.isArea)
                [messageToWatch setObject:@(YES) forKey:kCSRWATCH_IS_AREA];
            if(ld.isActivity)
                [messageToWatch setObject:@(YES) forKey:kCSRWATCH_IS_ACTIVITY];
            [self sendMessageToWatch:messageToWatch];
        }
    }
}




@end
