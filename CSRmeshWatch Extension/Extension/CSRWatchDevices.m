//
//  CSRWatchDevices.m
//  CSRmeshDemo
//
//  Created by sa24 on 21/01/2016.
//  Copyright © 2016 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "CSRWatchDevices.h"
#import "WatchSharedConsts.h"
#import "CSRConstants.h"

@implementation CSRWatchDevices
@synthesize wcSession, devices, selectedDevice, sortedFavourites, csrWatchDevicesDelegate, connectionState;

+ (id) sharedInstance
{
    
    static dispatch_once_t token;
    static CSRWatchDevices *shared = nil;
    
    dispatch_once(&token, ^{
        shared = [[CSRWatchDevices alloc] init];
    });
    
    return shared;
}

- (id)init {
    if (self = [super init]) {
        if ([WCSession isSupported]) {
            wcSession = [WCSession defaultSession];
            wcSession.delegate = self;
            [wcSession activateSession];
            
        }
        devices = [NSMutableDictionary dictionary];
        selectedDevice = nil;
    }
    return self;
}

#pragma mark - Private methods
-(void) sortFavourites {
    NSMutableArray *devicesArray = [NSMutableArray array];
    NSMutableArray *areasArray = [NSMutableArray array];
    NSMutableArray *activitiesArray = [NSMutableArray array];
    [devices enumerateKeysAndObjectsUsingBlock:^(id key, CSRWatchDevice *device, BOOL* stop) {
        if (device.isDevice)
            [devicesArray addObject:device];
        else if (device.isArea)
            [areasArray addObject:device];
        else if (device.isActivity)
            [activitiesArray addObject:device];
    }];
    NSSortDescriptor *sort = [NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES]; //@"name"
    [devicesArray sortUsingDescriptors:[NSArray arrayWithObject:sort]];
    [areasArray sortUsingDescriptors:[NSArray arrayWithObject:sort]];
    [activitiesArray sortUsingDescriptors:[NSArray arrayWithObject:sort]];
    
    sortedFavourites = nil;
    sortedFavourites = [areasArray arrayByAddingObjectsFromArray:devicesArray];
    sortedFavourites = [sortedFavourites arrayByAddingObjectsFromArray:activitiesArray];
}


#pragma mark - Public methods
-(CSRWatchDevice *) setChosenDevice:(NSInteger) index {
    @synchronized(self) {
        if (sortedFavourites && sortedFavourites.count>0 && index<sortedFavourites.count) {
            selectedDevice = sortedFavourites[index];
            return (selectedDevice);
        }
    }
    return(nil);
}


#pragma mark - WCSession Delegates

-(void)session:(WCSession *)session didReceiveApplicationContext:(NSDictionary<NSString *,id> *)applicationContext {
    @synchronized(self) {
        // callback when iOS sends data
        NSLog (@"WatchDevices new data");
        if (applicationContext[kCSRWATCH_DEVICEID]) {
            NSNumber *deviceId = applicationContext[kCSRWATCH_DEVICEID];
            if (applicationContext[kCSRWATCH_DELETE_DEVICE]) {
                if (devices[deviceId]) {
                    [devices removeObjectForKey:deviceId];
                }
            }
            else {
                CSRWatchDevice *device = devices[deviceId];
                if (!device) {
                    device = [[CSRWatchDevice alloc] init];
                    device.deviceId=deviceId;
                }
                if (applicationContext[kCSRWATCH_FAVOURITE]) {
                    // set favourite object type (Device, Area, Activity)
                    if (applicationContext[kCSRWATCH_IS_DEVICE])
                        device.isDevice=YES;
                    else if (applicationContext[kCSRWATCH_IS_AREA])
                        device.isArea=YES;
                    else if (applicationContext[kCSRWATCH_IS_ACTIVITY])
                        device.isActivity=YES;
                    
                    // Set Name and appearance
                    if (applicationContext[kCSRWATCH_DEVICE_NAME])
                        device.name=applicationContext[kCSRWATCH_DEVICE_NAME];
                    if (applicationContext[kCSRWATCH_APPEARANCE]) {
                        NSString *appearance = applicationContext[kCSRWATCH_APPEARANCE];
                        if (appearance && appearance.length>0) {
                            NSArray *appearances = [appearance componentsSeparatedByString:@","];
                            for (NSString *str in appearances) {
                                if ([str intValue] == CSRApperanceNameLight)
                                    device.isLight=YES;
                                if ([str intValue] == CSRApperanceNameHeater)
                                    device.isHeater=YES;
                            }
                        }
                    }
                    // set sensor desired or actual values
                    if (applicationContext[kCSRWATCH_DESIRED_TEMP]) {
                        device.desiredTemp = applicationContext[kCSRWATCH_DESIRED_TEMP];
                    }
                    if (applicationContext[kCSRWATCH_ACTUAL_TEMP]) {
                        device.actualTemp = applicationContext[kCSRWATCH_ACTUAL_TEMP];
                    }
                    if (!devices[deviceId])
                        [devices setObject:device forKey:deviceId];
                }
                else {
                    [devices removeObjectForKey:deviceId];
                    if (selectedDevice && [selectedDevice.deviceId isEqual:deviceId])
                        selectedDevice = nil;
                }
            }
            [self sortFavourites];            
            [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
                if(csrWatchDevicesDelegate && [csrWatchDevicesDelegate respondsToSelector:@selector(refreshUi)])
                    [csrWatchDevicesDelegate refreshUi];
            }];
        }
        else if (applicationContext[kCSRWATCH_DELETE_ALL_DATA]) {
            devices = [NSMutableDictionary dictionary];
            sortedFavourites = [NSMutableArray array];
            selectedDevice = nil;
            [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
                if(csrWatchDevicesDelegate && [csrWatchDevicesDelegate respondsToSelector:@selector(refreshUi)])
                    [csrWatchDevicesDelegate refreshUi];
            }];
        }
        else if (applicationContext[kCSRWATCH_CONNECTION_STATUS]) {
            connectionState = applicationContext[kCSRWATCH_CONNECTION_STATUS];
            [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
                if(csrWatchDevicesDelegate && [csrWatchDevicesDelegate respondsToSelector:@selector(connectionStateChanged:)])
                    [csrWatchDevicesDelegate connectionStateChanged:connectionState];
            }];
        }
    }
}

-(void)sessionWatchStateDidChange:(WCSession *)session {
    NSString *message = [NSString stringWithFormat:@"Watch State changed"];
    [self log:message];
}

-(void)sessionReachabilityDidChange:(WCSession *)session {
    NSString *message = [NSString stringWithFormat:@"Watch Reaxchibility changed = %@",@(session.reachable)];
    [self log:message];
}


#pragma mark - Send to Phone
-(void) sendMessageToPhone:(NSDictionary *)message {
    if (wcSession) {
        if (message && message.count) {
            [wcSession updateApplicationContext:message error:nil];
        }
    }
}


-(void) requestFavourites {
    // request latest data
    NSDictionary *message = @{kCSRWATCH_FORCE_REFRESH: @(YES)};
    [self sendMessageToPhone:message];
}

#pragma mark - Debug methods

-(void)log:(NSString *) message {
    NSLog (@"%@",message);
}



@end
