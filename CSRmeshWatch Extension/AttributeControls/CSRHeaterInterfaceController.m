//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRHeaterInterfaceController.h"
#import "CSRWatchDevice.h"
#import "CSRWatchDevices.h"
#import "StyleKitName.h"
#import "WatchSharedConsts.h"
#import "CSRConstants.h"

@interface CSRHeaterInterfaceController () {
    CSRWatchDevice *wd;
}
@end

@implementation CSRHeaterInterfaceController
@synthesize coolerButton, warmerButton, heaterLabel, actualTemp, desiredTemp;

- (void)awakeWithContext:(id)context {
    [super awakeWithContext:context];    
    // Configure interface objects here.
    wd = [[CSRWatchDevices sharedInstance]selectedDevice];
    [coolerButton setBackgroundImage:[StyleKitName imageOfWatch_temp_minus]];
    [warmerButton setBackgroundImage:[StyleKitName imageOfWatch_temp_plus]];
    if(wd) {
        [heaterLabel setText:wd.name];
        [self displayTemperature];
    }
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
    [[CSRWatchDevices sharedInstance] setCsrWatchDevicesDelegate:self];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
    [[CSRWatchDevices sharedInstance] setCsrWatchDevicesDelegate:nil];
}


-(void) displayTemperature {
    NSString *actual = [NSString stringWithFormat:@"%.1f°",[wd.actualTemp floatValue]];
    NSString *desired = [NSString stringWithFormat:@"%.1f°",[wd.desiredTemp floatValue]];
    [actualTemp setText:actual];
    [desiredTemp setText:desired];
}


- (IBAction)cooler {
    if (wd && wd.desiredTemp) {
        float temperature = [wd.desiredTemp floatValue];
        if(temperature>kCSR_AirTemp_MIN) {
            temperature -= kCSR_AirTemp_Increment;
            [wd setDesiredTemp:@(temperature)];
            [self setDesiredTemperature:@(temperature)];
            [self displayTemperature];
        }
    }
}

- (IBAction)warmer {
    if (wd && wd.desiredTemp) {
        float temperature = [wd.desiredTemp floatValue];
        if (temperature<kCSR_AirTemp_MAX){
            temperature += kCSR_AirTemp_Increment;
            [wd setDesiredTemp:@(temperature)];
            [self setDesiredTemperature:@(temperature)];
            [self displayTemperature];
        }
    }
}


-(void)refreshUi {
    [self displayTemperature];
}

-(void)connectionStateChanged:(NSNumber *)connectionState {
    if (connectionState && [connectionState boolValue]==NO) {
        [self presentControllerWithName:@"CSRConnectionState" context:nil];
    }
}

-(void) setDesiredTemperature:(NSNumber *)temperature {
    if (wd) {
        NSDictionary *message = @{kCSRWATCH_SET_DESIRED_TEMP : temperature,
                                  kCSRWATCH_DEVICEID: wd.deviceId};
        [[CSRWatchDevices sharedInstance] sendMessageToPhone:message];
    }
}


@end



