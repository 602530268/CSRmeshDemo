//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <XCTest/XCTest.h>
#import "CSRUtilities.h"
//#import <CommonCrypto/CommonDigest.h>
#import <CommonCrypto/CommonCrypto.h>


@interface CSRmeshDemoUITests : XCTestCase

@end

@implementation CSRmeshDemoUITests

- (void)setUp {
    [super setUp];
    
    // Put setup code here. This method is called before the invocation of each test method in the class.
    
    // In UI tests it is usually best to stop immediately when a failure occurs.
    self.continueAfterFailure = YES;
    // UI tests must launch the application that they test. Doing this in setup will make sure it happens for each test method.
    [[[XCUIApplication alloc] init] launch];
    
    // In UI tests it’s important to set the initial state - such as interface orientation - required for your tests before they run. The setUp method is a good place to do this.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}


- (void)testFirstDevice
{
    // Use recording to get started writing UI tests.
    // Use XCTAssert and related functions to verify your tests produce the correct results.
    
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [app.toolbars.buttons[@"ADD"] tap];
    [app.sheets[@"DEVICE SELECTION"].collectionViews.buttons[@"Detected Devices List"] tap];
    
    XCUIElementQuery *tablesQuery = app.tables;
    XCUIElement *label = app.staticTexts[@"3D4059C4-4A06-260E-BAEC-58CD702D0362"];
    NSPredicate *exists = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    [self expectationForPredicate:exists evaluatedWithObject:label handler:nil];
    [self waitForExpectationsWithTimeout:30 handler:nil];
    
    
    [tablesQuery.staticTexts[@"3D4059C4-4A06-260E-BAEC-58CD702D0362"] tap];
    
    
    XCUIElement *window = [[app childrenMatchingType:XCUIElementTypeWindow] elementBoundByIndex:0];
    [[[[[[[[window childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:2].toolbars.buttons[@"ASSOCIATE"] tap];
    [[[[[[[[[[window childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:1] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:2] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:0] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:3].buttons[@"NEXT"] tap];
    
    XCUIElement *label1 = app.staticTexts[@"Hello"];
    NSPredicate *exists1 = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    [self expectationForPredicate:exists1 evaluatedWithObject:label1 handler:nil];
    [self waitForExpectationsWithTimeout:15 handler:nil];
    
    
}

- (void) testSecondDevice {
    
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [app.toolbars.buttons[@"ADD"] tap];
    [app.sheets[@"DEVICE SELECTION"].collectionViews.buttons[@"Detected Devices List"] tap];
    
    XCUIElementQuery *tablesQuery = app.tables;
    XCUIElement *label = app.staticTexts[@"9E784358-2C0E-07CD-57A8-5BC420060046"];
    NSPredicate *exists = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    [self expectationForPredicate:exists evaluatedWithObject:label handler:nil];
    [self waitForExpectationsWithTimeout:20 handler:nil];
    
    
    [tablesQuery.staticTexts[@"9E784358-2C0E-07CD-57A8-5BC420060046"] tap];
    
    
    XCUIElement *window = [[app childrenMatchingType:XCUIElementTypeWindow] elementBoundByIndex:0];
    [[[[[[[[window childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:2].toolbars.buttons[@"ASSOCIATE"] tap];
    [[[[[[[[[[window childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:1] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:2] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:0] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:3].buttons[@"NEXT"] tap];
    
    XCUIElement *label1 = app.staticTexts[@"Hello"];
    NSPredicate *exists1 = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    [self expectationForPredicate:exists1 evaluatedWithObject:label1 handler:nil];
    [self waitForExpectationsWithTimeout:15 handler:nil];
    
}

- (void) testThirdDevice {
    
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [app.toolbars.buttons[@"ADD"] tap];
    [app.sheets[@"DEVICE SELECTION"].collectionViews.buttons[@"Detected Devices List"] tap];
    
    XCUIElementQuery *tablesQuery = app.tables;
    XCUIElement *label = app.staticTexts[@"3CF086B1-581C-0F9A-AF50-B788400C008C"];
    NSPredicate *exists = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    [self expectationForPredicate:exists evaluatedWithObject:label handler:nil];
    [self waitForExpectationsWithTimeout:20 handler:nil];
    
    
    [tablesQuery.staticTexts[@"3CF086B1-581C-0F9A-AF50-B788400C008C"] tap];
    
    
    XCUIElement *window = [[app childrenMatchingType:XCUIElementTypeWindow] elementBoundByIndex:0];
    [[[[[[[[window childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:2].toolbars.buttons[@"ASSOCIATE"] tap];
    [[[[[[[[[[window childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:1] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:2] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:0] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:3].buttons[@"NEXT"] tap];
    
    XCUIElement *label1 = app.staticTexts[@"Hello"];
    NSPredicate *exists1 = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    [self expectationForPredicate:exists1 evaluatedWithObject:label1 handler:nil];
    [self waitForExpectationsWithTimeout:15 handler:nil];
    
}


- (void) testFourthDevice {
    
    XCUIApplication *app = [[XCUIApplication alloc] init];
    [app.toolbars.buttons[@"ADD"] tap];
    [app.sheets[@"DEVICE SELECTION"].collectionViews.buttons[@"Detected Devices List"] tap];
    
    XCUIElementQuery *tablesQuery = app.tables;
    XCUIElement *label = app.staticTexts[@"E1B72050-415B-7990-9DC5-EB050461841B"];
    NSPredicate *exists = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    [self expectationForPredicate:exists evaluatedWithObject:label handler:nil];
    [self waitForExpectationsWithTimeout:20 handler:nil];
    
    
    [tablesQuery.staticTexts[@"E1B72050-415B-7990-9DC5-EB050461841B"] tap];
    
    
    XCUIElement *window = [[app childrenMatchingType:XCUIElementTypeWindow] elementBoundByIndex:0];
    [[[[[[[[window childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:2].toolbars.buttons[@"ASSOCIATE"] tap];
    [[[[[[[[[[window childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:1] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:2] childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:0] childrenMatchingType:XCUIElementTypeOther].element childrenMatchingType:XCUIElementTypeOther] elementBoundByIndex:3].buttons[@"NEXT"] tap];
    
    XCUIElement *label1 = app.staticTexts[@"Hello"];
    NSPredicate *exists1 = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    [self expectationForPredicate:exists1 evaluatedWithObject:label1 handler:nil];
    [self waitForExpectationsWithTimeout:15 handler:nil];
    
}

- (void) testAddArea
{

    
    
}


-(void) testEncryption {
    //NSData *data = [value dataUsingEncoding:NSUTF8StringEncoding];
    //    uint8_t dataBytes1 [] = {0x2e, 0x42, 0x2f, 0xbe, 0x46, 0xec, 0xf9, 0xed, 0x82, 0xc4};
    uint8_t dataBytes [] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0};
    NSData *data1 = [NSData dataWithBytes:&dataBytes length:10];
    
    uint8_t nwk = 1;
    NSData *nwkData = [NSData dataWithBytes:&nwk length:1];
    
    //    NSData *networkKeyHash = [[CSRDeviceManager sharedInstance] getReverseNetworkKeyHash];
    NSMutableData *encryptedData = [[NSMutableData alloc] initWithLength:data1.length + kCCBlockSizeAES128];
    size_t encryptedLength = 0;
    
    CCCryptorStatus result =  CCCrypt(kCCEncrypt,
                                      kCCAlgorithmAES128,
                                      kCCOptionPKCS7Padding | kCCModeCBC,
                                      nwkData.bytes, nwkData.length,
                                      nil,
                                      data1.bytes, data1.length,
                                      encryptedData.mutableBytes, encryptedData.length,
                                      &encryptedLength);
    
    if (result!=0)
        NSLog (@"result failed");
}
@end
