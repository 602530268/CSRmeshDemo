//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRConnectionState.h"
#import "StyleKitName.h"

@interface CSRConnectionState ()

@end

@implementation CSRConnectionState

@synthesize noConnectionImage;

- (void)awakeWithContext:(id)context {
    [super awakeWithContext:context];
    [noConnectionImage setImage:[StyleKitName imageOfWatch_connection_lost]];
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
}


-(void)connectionStateChanged:(NSNumber *)connectionState {
    if (connectionState && [connectionState boolValue]==YES) {
        [self dismissController];
    }
}


@end



