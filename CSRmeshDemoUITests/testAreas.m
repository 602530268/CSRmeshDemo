//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//
#import "CSRBaseUITest.h"
#import "CSRMeshDevicesTest.h"
#import "CSRApp.h"
#import "CSRMeshLeftMenu.h"
#import "CSRMeshAreaListPage.h"
#import "TestDataUtility.h"
#import "CSRMeshAreaDetailScreen.h"
#import "CSRWaitUtils.h"

@interface TestAreas : CSRBaseUITest

@property ConfigUtil *config;

@end

@implementation TestAreas

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

- (void)testAddArea {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    
    [[[app.navigationBars[@"CSRmesh Devices"] childrenMatchingType:XCUIElementTypeButton] elementBoundByIndex:0] tap];
    [app.tables.staticTexts[@"Areas"] tap];
    
    XCUIElement *area = app.staticTexts[@"Area 1"];

    if (area.exists) {
        [app.tables.buttons[@"Area 1"] tap];
        [app.toolbars.buttons[@"DELETE"] tap];
    }
    
    [app.toolbars.buttons[@"ADD"] tap];
    [app.navigationBars[@"Area"].buttons[@"Save"] tap];
    
    XCUIElement *newArea = app.staticTexts[@"Area 1"];
    
    XCTAssertTrue(newArea.exists, @"Area not created");
}

-(void) testAddDeviceToArea {
    XCUIApplication *app = [[XCUIApplication alloc] init];

    // Use recording to get started writing UI tests.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    TestDataUtility *testDataUtil = [[TestDataUtility alloc] init];
    NSString *areaName = [testDataUtil getDataWithKey:@"AreaName1"];
    NSString *deviceName = [testDataUtil getDataWithKey:@"DeviceName1"];
    NSString *authCode = [testDataUtil getDataWithKey:@"AuthCode1"];
    NSString *deviceUUID = [testDataUtil getDataWithKey:@"Device1_UUID"];
    
    NSString *errorDescription;
    
    
    CSRMeshDevicesTest *devicesList = [[CSRMeshDevicesTest alloc] init];
    //Check if associated. If not, associate it and proceed
    if(![devicesList isDeviceDisplayedOnDevicesListScreen:deviceName]){
        BOOL isDeviceAdded = [devicesList addDeviceFromDetectedList:deviceUUID appearanceName:deviceName  authCode:authCode testInstance:self error:&errorDescription];
        XCTAssertTrue(isDeviceAdded,@"%@", errorDescription);
        BOOL isDeviceDisplayedOnListScreen = [devicesList isDeviceDisplayedOnDevicesListScreen: deviceName];
        XCTAssertTrue(isDeviceDisplayedOnListScreen, @"Device '%@' not displayed on devices list screen", deviceName);
        [NSThread sleepForTimeInterval:3.0];
    }
    
    [devicesList openMenu];
    CSRMeshLeftMenu *leftMenu = [[CSRMeshLeftMenu alloc] init];
    [leftMenu gotoAreas];
 
    NSDictionary *areaDetails = @{@"areaname" : areaName};

    CSRMeshAreaListPage *areaListPage = [[CSRMeshAreaListPage alloc]  init];
    
    if(![areaListPage isAreaPresent:areaName]){
        [areaListPage addArea : areaDetails];
        XCTAssertTrue([areaListPage isAreaPresent: areaName], @"Area '%@' not found on list page", areaName);
    }
    
    NSInteger initialDeviceCount = [areaListPage getNoOfDevicesFromArea:areaName];
    
    BOOL isDeviceDeleted = NO;
    
    //check if device is already associated to area. If yes, then delete and then add it
    errorDescription = nil;
    CSRMeshAreaDetailScreen *areaDetailScreen = [[CSRMeshAreaDetailScreen alloc] init];
    [areaListPage openConfigurationOf:areaName];
    if([areaDetailScreen isDevicePresent: deviceName]){
        [areaDetailScreen deleteDevice:deviceName error:&errorDescription ];
        XCTAssertNil(errorDescription, "Device '%@' could not be deleted. Error:%@", deviceName, errorDescription);
        [NSThread sleepForTimeInterval:2.0];
        CSRWaitUtils *waitUtils = [[CSRWaitUtils alloc] init];
        CGFloat objectWaitTime = [[_config getDataWithKey:@"ObjectExistWait"] floatValue];
        [waitUtils waitForElementToDisplay:self element:app.staticTexts[@"Area"] maxTime:objectWaitTime];
        
        XCTAssertFalse([areaDetailScreen isDevicePresent: deviceName], @"Device '%@' found in area '%@' detail screen even after deleting it from area", deviceName, areaName);
        isDeviceDeleted = YES;
    }

    errorDescription = nil;
    [areaDetailScreen addDevice:deviceName error:&errorDescription];
    XCTAssertNil(errorDescription, @"%@", errorDescription);
    [NSThread sleepForTimeInterval:2.0];
    CSRWaitUtils *waitUtils = [[CSRWaitUtils alloc] init];
    CGFloat objectWaitTime = [[_config getDataWithKey:@"ObjectExistWait"] floatValue];
    [waitUtils waitForElementToDisplay:self element:app.staticTexts[@"Area"] maxTime:objectWaitTime];
    
    //Click on 'Save' to go to list page
    [areaDetailScreen save];
    
    NSInteger finalDeviceCount = [areaListPage getNoOfDevicesFromArea:areaName];
    if(isDeviceDeleted){
        XCTAssertTrue(initialDeviceCount == finalDeviceCount, @"Initial and final device count should be same. Initial:%i Final:%i", initialDeviceCount, finalDeviceCount);
    }else{
        XCTAssertTrue(finalDeviceCount == (initialDeviceCount+1), @"Final device count should have been increased by 1. Initial:%i Final:%i", initialDeviceCount, finalDeviceCount);
    }
        
    [areaListPage openConfigurationOf:areaName];
    XCTAssertTrue([areaDetailScreen isDevicePresent: deviceName], @"Device '%@' not found in devices list of area", deviceName);
}

-(void) testAADeleteDeviceFromArea{
    
    TestDataUtility *testDataUtil = [[TestDataUtility alloc] init];
    NSString *areaName = [testDataUtil getDataWithKey:@"AreaName1"];
    NSString *deviceName = [testDataUtil getDataWithKey:@"DeviceName1"];
    NSString *authCode = [testDataUtil getDataWithKey:@"AuthCode1"];
    NSString *deviceUUID = [testDataUtil getDataWithKey:@"Device1_UUID"];
    NSString *errorDescription;
    
    
    CSRMeshDevicesTest *devicesList = [[CSRMeshDevicesTest alloc] init];
    //Check if associated. If not, associate it and proceed
    if(![devicesList isDeviceDisplayedOnDevicesListScreen:deviceName]){
        BOOL isDeviceAdded = [devicesList addDeviceFromDetectedList:deviceUUID appearanceName:deviceName  authCode:authCode testInstance:self error:&errorDescription];
        XCTAssertTrue(isDeviceAdded,@"%@", errorDescription);
        BOOL isDeviceDisplayedOnListScreen = [devicesList isDeviceDisplayedOnDevicesListScreen: deviceName];
        XCTAssertTrue(isDeviceDisplayedOnListScreen, @"Device '%@' not displayed on devices list screen", deviceName);
    }
    
    [devicesList openMenu];
    CSRMeshLeftMenu *leftMenu = [[CSRMeshLeftMenu alloc] init];
    [leftMenu gotoAreas];
    
    //Create area if desired area is not there
    NSDictionary *areaDetails = @{@"areaname" : areaName};
    CSRMeshAreaListPage *areaListPage = [[CSRMeshAreaListPage alloc]  init];
    if(![areaListPage isAreaPresent:areaName]){
        [areaListPage addArea : areaDetails];
        XCTAssertTrue([areaListPage isAreaPresent: areaName], @"Area '%@' not found on list page", areaName);
    }
    
    
    //If device is not there then add it
    errorDescription = nil;
    CSRMeshAreaDetailScreen *areaDetailScreen = [[CSRMeshAreaDetailScreen alloc] init];
    [areaListPage openConfigurationOf:areaName];
    if(![areaDetailScreen isDevicePresent: deviceName]){
        [areaDetailScreen addDevice:deviceName error:&errorDescription];
        XCTAssertNil(errorDescription, @"%@", errorDescription);
        XCTAssertTrue([areaDetailScreen isDevicePresent: deviceName], @"Device '%@' not found in devices list of area", deviceName);
    }
    
    //Delete device from area and check
    errorDescription =nil;
    [areaDetailScreen deleteDevice: deviceName error:&errorDescription];
    XCTAssertNil(errorDescription, "Device '%@' still appears in area '%@'", deviceName, areaName);
    [NSThread sleepForTimeInterval:2.0];
   
    //CSRWaitUtils *waitUtils = [[CSRWaitUtils alloc] init];
    //[waitUtils waitForElementToDisplay:app.staticTexts[@"Area"] pollTime:1.0 maxTime:15.0];
    
    NSPredicate *areaExistPredicate = [NSPredicate predicateWithFormat:@"exists=1"];
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *areaText = app.staticTexts[@"Area"];
    [self expectationForPredicate:areaExistPredicate evaluatedWithObject:areaText handler:nil];
    [self waitForExpectationsWithTimeout:15 handler:nil];

    
    XCTAssertFalse([areaDetailScreen isDevicePresent: deviceName], @"Device '%@' found in area '%@' detail screen", deviceName, areaName);
    [areaDetailScreen back];
    [areaListPage openConfigurationOf:areaName];
    XCTAssertFalse([areaDetailScreen isDevicePresent: deviceName], @"Device '%@' found in area '%@' detail screen", deviceName, areaName);

}

@end
