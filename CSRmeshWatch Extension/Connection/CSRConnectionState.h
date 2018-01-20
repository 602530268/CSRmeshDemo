//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <WatchKit/WatchKit.h>
#import <Foundation/Foundation.h>
#import "CSRWatchDevices.h"

@interface CSRConnectionState : WKInterfaceController <CSRWatchDevicesProtocol>

@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceImage *noConnectionImage;
@end
