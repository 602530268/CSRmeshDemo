//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRBaseUITest.h"
#import "TestDataUtility.h"
#import "ConfigUtil.h"

@interface testDevices : CSRBaseUITest

@property ConfigUtil *config;

@end

@implementation testDevices

- (void)setUp {
    [super setUp];
    
    self.continueAfterFailure = NO;
    _config = [ConfigUtil sharedInstance];
    [_config setCurrentTestCase:self];
    [[[XCUIApplication alloc] init] launch];
}

- (void)tearDown {
    [super tearDown];

    [_config setCurrentTestCase:nil];
}

- (void)testAddDetectedDevice {
    TestDataUtility *testDataUtil = [[TestDataUtility alloc] init];
    NSString *deviceName = [testDataUtil getDataWithKey:@"DeviceName1"];
    NSString *authCode = [testDataUtil getDataWithKey:@"AuthCode1"];
    NSString *deviceUUID = [testDataUtil getDataWithKey:@"Device1_UUID"];
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *element = app.tables.cells.staticTexts[deviceName];
    
    if (element.exists) {
        [self disassociateDevice:deviceName];
    }

    [self associateDevice:deviceName uuid:deviceUUID authCode:authCode];
}

- (void)testDeviceSwitchOffOn {
    TestDataUtility *testDataUtil = [[TestDataUtility alloc] init];
    NSString *deviceName = [testDataUtil getDataWithKey:@"DeviceName1"];
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *element = app.tables.cells.staticTexts[deviceName];
    
    if (!element.exists) {
        [self associateDevice:deviceName
                         uuid:[testDataUtil getDataWithKey:@"Device1_UUID"]
                     authCode:[testDataUtil getDataWithKey:@"AuthCode1"]];
    }

    XCUIApplication *app2 = [[XCUIApplication alloc] init];
    XCUIElement *element2 = app2.tables.cells.staticTexts[deviceName];
    
    if (element2.exists) {
        [element2 tap];
        
        [app.switches[@"1"] tap];
        [app.switches[@"0"] tap];
        
        // Now validate switch setting...
        XCUIElement *powerSwitch = [app2.switches elementBoundByIndex:0];
        
        if (powerSwitch.exists) {
            XCTAssertTrue([powerSwitch.value intValue], @"Light power not set");
        }
    }
}

- (void)testChangeLightIntensity {
    TestDataUtility *testDataUtil = [[TestDataUtility alloc] init];
    NSString *deviceName = [testDataUtil getDataWithKey:@"DeviceName1"];
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *element = app.tables.cells.staticTexts[deviceName];
    
    if (!element.exists) {
        [self associateDevice:deviceName
                         uuid:[testDataUtil getDataWithKey:@"Device1_UUID"]
                     authCode:[testDataUtil getDataWithKey:@"AuthCode1"]];
    }
    
    XCUIApplication *app2 = [[XCUIApplication alloc] init];
    XCUIElement *element2 = app2.tables.cells.staticTexts[deviceName];
    
    if (element2.exists) {
        [element2 tap];
        
        XCUIElement *intensitySlider = [app2.sliders elementBoundByIndex:0];
        
        if (intensitySlider.exists) {
            [intensitySlider tap];
            [intensitySlider swipeLeft];

            XCTAssertTrue(app2.sliders[@"5%"], @"Light intensity not set");
        }
    }
}

- (void)testDeviceFavourite {
    TestDataUtility *testDataUtil = [[TestDataUtility alloc] init];
    NSString *deviceName = [testDataUtil getDataWithKey:@"DeviceName1"];
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *element = app.tables.cells.staticTexts[deviceName];
    
    if (!element.exists) {
        [self associateDevice:deviceName
                         uuid:[testDataUtil getDataWithKey:@"Device1_UUID"]
                     authCode:[testDataUtil getDataWithKey:@"AuthCode1"]];
    }
    
    XCUIApplication *app2 = [[XCUIApplication alloc] init];
    XCUIElementQuery *tablesQuery = app2.tables;
    
    [[tablesQuery.cells childrenMatchingType:XCUIElementTypeButton].element tap];
    
    XCUIElement *favButton = tablesQuery.buttons[@"Favourites_On"];
    
    if (favButton.exists) {
        [favButton tap];
    }
    
    [tablesQuery.buttons[@"Favourites_Off"] tap];
    [app2.navigationBars[@"DeviceDetailsNavigationController"].buttons[@"back"] tap];
    [[[app2.navigationBars[@"CSRmesh Devices"] childrenMatchingType:XCUIElementTypeButton] elementBoundByIndex:0] tap];
    [tablesQuery.staticTexts[@"Favourites"] tap];
    [app2.buttons[@"Devices & Areas"] tap];
    
    XCUIApplication *app3 = [[XCUIApplication alloc] init];
    XCUIElement *newFav = app3.staticTexts[deviceName];
    
    XCTAssertTrue(newFav.exists, @"Favourite not created");
}

- (void)testDeviceUnFavourite {
    TestDataUtility *testDataUtil = [[TestDataUtility alloc] init];
    NSString *deviceName = [testDataUtil getDataWithKey:@"DeviceName1"];
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *element = app.tables.cells.staticTexts[deviceName];
    
    if (!element.exists) {
        [self associateDevice:deviceName
                         uuid:[testDataUtil getDataWithKey:@"Device1_UUID"]
                     authCode:[testDataUtil getDataWithKey:@"AuthCode1"]];
    }
    
    XCUIApplication *app2 = [[XCUIApplication alloc] init];
    XCUIElementQuery *tablesQuery = app2.tables;
    
    [[tablesQuery.cells childrenMatchingType:XCUIElementTypeButton].element tap];
    
    XCUIElement *favButton = tablesQuery.buttons[@"Favourites_On"];
    
    if (favButton.exists) {
        [favButton tap];
        
        XCUIElement *favButton2 = tablesQuery.buttons[@"Favourites_Off"];
        
        XCTAssertTrue(!favButton2.exists, @"Favourite not created");
    }
}

- (void)disassociateDevice:(NSString *)value {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    NSString *removeString = [NSString stringWithFormat:@"Remove %@?", value];
    
    [[app.tables.cells childrenMatchingType:XCUIElementTypeButton].element tap];
    [app.toolbars.buttons[@"DELETE"] tap];
    [app.alerts[removeString].collectionViews.buttons[@"Yes"] tap];
}

- (void)associateDevice:(NSString *)name uuid:(NSString *)uuid authCode:(NSString *)authCode {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    
    [app.toolbars.buttons[@"ADD"] tap];
    [app.sheets[@"DEVICE SELECTION"].collectionViews.buttons[@"Detected Devices List"] tap];
    
    [self waitForStaticTableText:uuid timeout:20];
    
    [app.tables.staticTexts[uuid] tap];
    [app.toolbars.buttons[@"ASSOCIATE"] tap];
    
    [self waitForStaticText:@"If your device has been provided with an authorisation code, you can type it in here. Otherwise you can skip this step by pressing 'Skip'." timeout:20];
    
    [self enterText:@"Authorisation code" value:authCode];
    
    // Create a new XCUIApplication object otherwise the next dialog is not visible.
    [[[[[[[[[[[[[[XCUIApplication alloc] init] childrenMatchingType:XCUIElementTypeWindow] elementBoundByIndex:0] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:1] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:2] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:0] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:1].buttons[@"NEXT"] tap];
    
    [self waitForStaticTableText:name timeout:20];
}

@end
