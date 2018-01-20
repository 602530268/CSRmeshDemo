//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#ifndef CSRMeshLeftMenu_h
#define CSRMeshLeftMenu_h


#endif /* CSRMeshLeftMenu_h */
#import <XCTest/XCTest.h>


@interface CSRMeshLeftMenu : NSObject{
    
    XCUIElementQuery *managePlaces;
    
    XCUIApplication *app;
}

+ (CSRMeshLeftMenu *) sharedInstance;

-(instancetype) init;

- (BOOL) isLeftMenuDisplayed;

- (void) showManagePlacesMenu;

- (void) selectManagePlaces;

- (void) gotoAreas;

- (void) gotoActivities;

-(void) gotoFavourites;

-(void) gotoDevices;

-(void) gotoEvents;

- (void) selectPlace : (NSString *) placeToSelect;

- (NSString *) getActivePlace;

@end
