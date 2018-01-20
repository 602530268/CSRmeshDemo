//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>
#import "CSRWatchDevice.h"
@import WatchConnectivity;

@protocol CSRWatchDevicesProtocol <NSObject>
@optional
-(void) refreshUi;
-(void)connectionStateChanged:(NSNumber *)connectionState;
@end


@interface CSRWatchDevices : NSObject <WCSessionDelegate>

+ (id) sharedInstance;
-(CSRWatchDevice *) setChosenDevice:(NSInteger) index;
-(void) sendMessageToPhone:(NSDictionary *)message;
-(void) requestFavourites;

@property (nonatomic)   WCSession   *wcSession;

// Device dictionary, key is NSNumber of deviceId or if this is an activity
@property (nonatomic)   NSMutableDictionary  *devices;
@property (nonatomic)   NSArray *sortedFavourites;

@property (nonatomic)  CSRWatchDevice *selectedDevice;

@property (nonatomic)  NSNumber *connectionState;

@property (nonatomic)  id<CSRWatchDevicesProtocol> csrWatchDevicesDelegate;
@end

