//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#ifndef CSRCommonToolbar_h
#define CSRCommonToolbar_h


#endif /* CSRCommonToolbar_h */
#import <XCTest/XCTest.h>
#import "ConfigUtil.h"

@interface CSRCommonToolbar : NSObject{

    XCUIApplication *app;
    ConfigUtil *config;
}

- (void) search : (NSString *) searchText;

- (void) cancelSearch ;

- (void) openMenu;

- (void) back;

-(NSString *) getTitle;

-(void) save;

-(ConfigUtil *) getConfig;


@end
