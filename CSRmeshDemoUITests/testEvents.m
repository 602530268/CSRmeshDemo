//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <XCTest/XCTest.h>
#import "ConfigUtil.h"
#import "CSRApp.h"
#import "CSRMeshLeftMenu.h"
#import "CSRMeshDevicesTest.h"
#import "CSRMeshEventsList.h"

@interface testEvents : XCTestCase{
    
    XCUIApplication *app;
    ConfigUtil *config;
    
}


@end

@implementation testEvents

- (void)setUp {
    [super setUp];
    
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    // In UI tests it is usually best to stop immediately when a failure occurs.
    self.continueAfterFailure = YES;
    // UI tests must launch the application that they test. Doing this in setup will make sure it happens for each test method.
    //[[[XCUIApplication alloc] init] launch];

    // In UI tests it’s important to set the initial state - such as interface orientation - required for your tests before they run. The setUp method is a good place to do this.
    config = [ConfigUtil sharedInstance];
    [config setCurrentTestCase:self];
    app = [CSRApp sharedInstance];
    [app launch];
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    [config setCurrentTestCase:nil];
}

- (void)testEventsSampleTest {
    // Use recording to get started writing UI tests.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    CSRMeshDevicesTest *devicesList = [[CSRMeshDevicesTest alloc] init];
    [devicesList openMenu];
    
    CSRMeshLeftMenu *leftMenu = [[CSRMeshLeftMenu alloc] init];
    [leftMenu gotoEvents];
    
    CSRMeshEventsList *eventsList = [[CSRMeshEventsList alloc] init];
    [eventsList selectDeviceType:Light_Color];

    BOOL isEventSwitchedOff = [eventsList switchOffEventByName:@"Test"];
    XCTAssertTrue(isEventSwitchedOff, @"Event not successfully switched off");
    
    BOOL isEventSwitchedOn = [eventsList switchOnEventByName:@"Test"];
    XCTAssertTrue(isEventSwitchedOn, @"Event not switched on");
    
    [eventsList addEvent:Light eventName:@"Light New Event"];
    
    //Work in Progress
    
    [NSThread sleepForTimeInterval:5.0];
}

@end
