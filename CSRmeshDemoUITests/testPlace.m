//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRBaseUITest.h"

@interface TestPlace : CSRBaseUITest
@end

@implementation TestPlace

- (void)setUp {
    [super setUp];

    // In UI tests it is usually best to stop immediately when a failure occurs.
    self.continueAfterFailure = NO;
    [[[XCUIApplication alloc] init] launch];
}

- (void)testAddPlace {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElementQuery *toolbarsQuery = app.toolbars;
    
    [[[app.navigationBars[@"CSRmesh Devices"] childrenMatchingType:XCUIElementTypeButton] elementBoundByIndex:0] tap];
    [app.buttons[@"menuSwitch"] tap];
    [toolbarsQuery.buttons[@"Manage places"] tap];
    [toolbarsQuery.buttons[@"ADD"] tap];
    [self enterText:@"placeName" value:@"kitchen"];
    [self enterSecureText:@"networkKey" value:@"disco"];
    [app.navigationBars[@"Create a new place"].buttons[@"Save"] tap];
    
    XCUIElement *newPlace = [app.tables.cells containingType:XCUIElementTypeStaticText identifier:@"kitchen"].staticTexts[@"My place"];
    
    XCTAssertTrue(newPlace.exists, @"%s error: 'kitchen not created'", __PRETTY_FUNCTION__);
}

- (void)testRemovePlace {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    
    [[[app.navigationBars[@"CSRmesh Devices"] childrenMatchingType:XCUIElementTypeButton] elementBoundByIndex:0] tap];
    [app.buttons[@"menuSwitch"] tap];
    [app.toolbars.buttons[@"Manage places"] tap];
    [[[app.tables containingType:XCUIElementTypeSearchField identifier:@"Search"].cells containingType:XCUIElementTypeStaticText identifier:@"kitchen"].staticTexts[@"My place"] tap];
    [app.buttons[@"delete"] tap];
    
    XCUIElement *newPlace = [app.tables.cells containingType:XCUIElementTypeStaticText identifier:@"kitchen"].staticTexts[@"My place"];
    
    XCTAssertFalse(newPlace.exists, @"%s error: 'kitchen not created'", __PRETTY_FUNCTION__);
}

@end
