//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "CSRMeshLeftMenu.h"
#import "CSRApp.h"


#define kManagePlacesTitle @"Manage places"

@implementation CSRMeshLeftMenu

+ (CSRMeshLeftMenu *)sharedInstance{
    
    static dispatch_once_t block;
    
    static CSRMeshLeftMenu *leftMenu;
    
    dispatch_once(&block, ^{
        leftMenu = [[CSRMeshLeftMenu alloc] init];
    });
    
    return leftMenu;
}

- (instancetype) init {
    
    app = [CSRApp sharedInstance];
    
    return self;
}

- (BOOL) isLeftMenuDisplayed{
    
    return [app.buttons[@"menuSwitch"] exists];
}

- (XCUIElement *)managePlaces{
    return app.buttons[kManagePlacesTitle];
}


- (void) showManagePlacesMenu{
    
    //[[[self app].buttons elementBoundByIndex:1] tap];
    [app.buttons[@"menuSwitch"] tap];
    
}

- (void) selectManagePlaces {
    
    XCUIElementQuery *toolbarsQuery = app.toolbars;
    
    [toolbarsQuery.buttons[@"Manage places"] tap];
    
}

- (void) gotoAreas {
    
    [app.staticTexts[@"Areas"] tap];
}

- (void) gotoActivities {
    
    [app.staticTexts[@"Activities"] tap];
    
}

-(void) gotoEvents{
    [app.staticTexts[@"Events"] tap];
}

-(void) gotoFavourites {
    
    [app.staticTexts[@"Favourites"] tap];
    
}

-(void)gotoDevices {
    
    [app.staticTexts[@"CSRmesh devices"] tap];
    
}

- (void) selectPlace : (NSString *) placeToSelect {
    
    [self showManagePlacesMenu];
    
    XCUIElement *placeElement = app.staticTexts[placeToSelect];
    
    if( placeElement ) {
        
        [placeElement tap];
    }
    
}

- (NSString *) getActivePlace {
    
    return [app.staticTexts[@"placeName"] value];
    
}

@end
