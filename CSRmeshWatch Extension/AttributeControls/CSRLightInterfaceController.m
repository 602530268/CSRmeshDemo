//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRLightInterfaceController.h"
#import "CSRWatchDevice.h"
#import "CSRWatchDevices.h"
#import "StyleKitName.h"
#import "WatchSharedConsts.h"


@implementation CSRLightInterfaceController
@synthesize lightOffImage, lightOnImage, lightName;

- (void)awakeWithContext:(id)context {
    [super awakeWithContext:context];
    // Configure interface objects here.
    CSRWatchDevice *wd = [[CSRWatchDevices sharedInstance]selectedDevice];
    [lightName setText:wd.name];
    [lightOffImage setBackgroundImage:[StyleKitName imageOfWatch_light_off]];
    [lightOnImage setBackgroundImage:[StyleKitName imageOfWatch_light_on]];    
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
    
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
}

- (IBAction)lightOn {
    [self setLightState:YES];
}

- (IBAction)lightOff {
    [self setLightState:NO];
}

-(void) setLightState:(BOOL)state{
    CSRWatchDevice *wd = [[CSRWatchDevices sharedInstance]selectedDevice];
    if (wd) {
        NSDictionary *message = @{kCSRWATCH_SET_LIGHT_STATE: @(state),
                                  kCSRWATCH_DEVICEID: wd.deviceId};
        [[CSRWatchDevices sharedInstance] sendMessageToPhone:message];
    }
}



@end



