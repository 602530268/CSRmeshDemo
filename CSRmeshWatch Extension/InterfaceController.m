//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "InterfaceController.h"
#import "ExtensionDelegate.h"
#import "CSRFavouriteRow.h"
#import "CSRWatchDevice.h"
#import "StyleKitName.h"

@interface InterfaceController() {
    NSArray *allObjects;
}
@end


@implementation InterfaceController

@synthesize favouritesTable;

- (void)awakeWithContext:(id)context {
    [super awakeWithContext:context];
    
    // activate watch
    [CSRWatchDevices sharedInstance];
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
    [[CSRWatchDevices sharedInstance] setCsrWatchDevicesDelegate:self];
    [[CSRWatchDevices sharedInstance] requestFavourites];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
    [[CSRWatchDevices sharedInstance] setCsrWatchDevicesDelegate:nil];
}



-(void) tableRefresh {
    NSLog (@"Interface tableRefresh");
    allObjects = [[[CSRWatchDevices sharedInstance]sortedFavourites] copy];
    [favouritesTable setNumberOfRows:[allObjects count] withRowType:@"WatchFavouriteRow"];
    for (NSInteger i = 0; i < self.favouritesTable.numberOfRows; i++) {
        CSRFavouriteRow *theRow = [favouritesTable rowControllerAtIndex:i];
        CSRWatchDevice *dataObj = [allObjects objectAtIndex:i];
        
        [theRow.nameOfFavourite setText:dataObj.name];
        // set the iCon
        if (dataObj.isArea)
            [theRow.imgeOfFavourite setImage:[StyleKitName imageOfWatch_table_group]];
        else if (dataObj.isDevice) {
            if (dataObj.isLight)
                [theRow.imgeOfFavourite setImage:[StyleKitName imageOfWatch_table_light]];
            else if (dataObj.isHeater)
                [theRow.imgeOfFavourite setImage:[StyleKitName imageOfWatch_table_heater]];
            else if (dataObj.isLock)
                [theRow.imgeOfFavourite setImage:[StyleKitName imageOfWatch_table_lock]];
            
        }
    }
}

-(void)table:(WKInterfaceTable *)table didSelectRowAtIndex:(NSInteger)rowIndex {
    if (rowIndex <allObjects.count) {
        CSRWatchDevice *wd = [[CSRWatchDevices sharedInstance] setChosenDevice:rowIndex];
        if (wd) {
            NSArray *views = [wd getViews];
            if([views count]==1)
                [self presentControllerWithName:views[0] context:nil];
            else
                [self presentControllerWithNames:views contexts:nil];
        }
    }
}

-(void)refreshUi {
    [self tableRefresh];
}

-(void)connectionStateChanged:(NSNumber *)connectionState {
    if (connectionState && [connectionState boolValue]==NO) {
        [self presentControllerWithName:@"CSRConnectionState" context:nil];
    }
}


@end



