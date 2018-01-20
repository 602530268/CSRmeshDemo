//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#import "CSRApp.h"
#import "CSRCommonToolbar.h"
#import "CSRMeshDevicesTest.h"
#import <XCTest/XCTestAssertions.h>


@implementation CSRMeshDevicesTest


+ (CSRMeshDevicesTest *) sharedInstance{
    
    static dispatch_once_t block;
    
    static CSRMeshDevicesTest *csrMeshDevicesTest;
    
    dispatch_once(&block, ^{
        csrMeshDevicesTest = [[CSRMeshDevicesTest alloc] init];
    });
    
    return csrMeshDevicesTest;
}

- (instancetype) init {
    
    self = [super init];
    
    return self;
}

- (NSString *) getTitle{
    
    return @"CSRmesh Devices";
}

- (void) openMenu {
    
    [app.buttons[@"menu"] tap];
}

- (BOOL) addDeviceFromDetectedList:(NSString *)appearanceName authCode:(NSString *)authCode testInstance:(XCTestCase *)tc error:(NSString **)errorDescription
{
    
    [app.buttons[@"ADD"] tap];
    
    [app.buttons[@"Detected Devices List"] tap];
    
    XCUIElement *label = app.staticTexts[appearanceName];
    
    CGFloat deviceMaxWaitTime = [[config getDataWithKey:@"deviceExistWait"] floatValue];
    
    NSPredicate *exists = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    [tc expectationForPredicate:exists evaluatedWithObject:label handler:nil];
    
    [tc waitForExpectationsWithTimeout:deviceMaxWaitTime handler:nil];
    
    BOOL performedOperation = NO;
    
    int maxTapAttempts = 3;
    
    NSUInteger count1, count2;
    
    while( !performedOperation && (maxTapAttempts > 0)) {
        
        @try{
            
            count1 = [app.staticTexts count];
            
            [NSThread sleepForTimeInterval:1.0];
            
            count2 = [app.staticTexts count];
            
            if (count1 == count2) {
                    
                   [app.staticTexts[appearanceName] tap];
                
                    performedOperation = YES;
                    
            }
        }
        
        @catch(NSException *ex){
            
            NSLog(@"Exception msg : %@", [ex debugDescription]);
            
            maxTapAttempts--;
            
            [NSThread sleepForTimeInterval : 1.0];
        }
    }
    
    if( !performedOperation ){
        *errorDescription = [NSString stringWithFormat:@"Device '%@' not tapped", appearanceName];
        return NO;
    }
    
    //Click 'Associate' button once device is tapped
    NSPredicate *associateButtonEnabledPredicate = [NSPredicate predicateWithFormat:@"label='ASSOCIATE' AND enabled=1"];
    XCUIElementQuery *associateButtonQuery = [app.buttons matchingPredicate:associateButtonEnabledPredicate];
    if(![associateButtonQuery element].exists){
        *errorDescription = @"'Associate' button either doesn't exist or not enabled";
        return NO;
    }
    
    [[associateButtonQuery element]tap];
    
    //Enter Authorisation code
    XCUIElement *authorisationCodeTextField = app.textFields[@"Authorisation code"];
    [authorisationCodeTextField tap];
    [authorisationCodeTextField typeText:authCode];
    
    
    //Click 'NEXT' button after typing authorisation code
    NSPredicate *nextButtonPredicate = [NSPredicate predicateWithFormat:@"label='NEXT' AND enabled=1"];
    XCUIElementQuery *nextButtonQuery = [app.buttons matchingPredicate:nextButtonPredicate];
    if([nextButtonQuery element].exists){
        [[nextButtonQuery elementBoundByIndex:0] tap];
    }
    
    //Wait for 'Associating' alert to dismiss. This is being ensured by checking for presence of 'CANCEL' button
    NSPredicate *buttonCancelVanish = [NSPredicate predicateWithFormat:@"exists == 0"];
    XCUIElement *buttonCancel = app.windows.buttons[@"CANCEL"];
    [tc expectationForPredicate:buttonCancelVanish evaluatedWithObject:buttonCancel handler:nil];
    CGFloat objectWaitTime = [[config getDataWithKey:@"ObjectExistWait"] floatValue];
    [tc waitForExpectationsWithTimeout:(objectWaitTime + 10) handler:nil];
    return YES;
    
}

- (BOOL) addDeviceFromDetectedList:(NSString *)uuid appearanceName:(NSString *)appearanceName authCode:(NSString *)authCode testInstance:(XCTestCase *)tc error:(NSString **)errorDescription
{
    
    [app.buttons[@"ADD"] tap];
    
    [app.buttons[@"Detected Devices List"] tap];
    
    XCUIElement *label = app.staticTexts[appearanceName];
    
    XCUIElement *uuidElement = app.staticTexts[uuid];
    
    NSPredicate *exists = [NSPredicate predicateWithFormat:@"exists == 1"];
    
    if( (uuid != nil) && ([uuid length] != 0)){
        [tc expectationForPredicate:exists evaluatedWithObject:uuidElement handler:nil];
    }else{
    
        [tc expectationForPredicate:exists evaluatedWithObject:label handler:nil];
    }
    
    CGFloat deviceDisplayMaxWaitTime = [[config getDataWithKey:@"deviceDisplayMaxWaitTime"] floatValue];
    [tc waitForExpectationsWithTimeout:deviceDisplayMaxWaitTime handler:nil];
    
    BOOL performedOperation = NO;
    
    int maxTapAttempts = 3;
    
    NSUInteger count1, count2;
    
    while( !performedOperation && (maxTapAttempts > 0)) {
        
        @try{
            
            count1 = [app.staticTexts count];
            
            [NSThread sleepForTimeInterval:1.0];
            
            count2 = [app.staticTexts count];
            
            if (count1 == count2) {
                
                if((uuid != nil) && ([uuid length] != 0)){
                    [app.staticTexts[uuid] tap];
                }else{
                    [app.staticTexts[appearanceName] tap];
                }
                
                performedOperation = YES;
                
            }
        }
        
        @catch(NSException *ex){
            
            NSLog(@"Exception msg : %@", [ex debugDescription]);
            
            maxTapAttempts--;
            
            [NSThread sleepForTimeInterval : 1.0];
        }
    }
    
    if( !performedOperation ){
        *errorDescription = [NSString stringWithFormat:@"Device '%@' not tapped", appearanceName];
        return NO;
    }
    
    //Click 'Associate' button once device is tapped
    NSPredicate *associateButtonEnabledPredicate = [NSPredicate predicateWithFormat:@"label='ASSOCIATE' AND enabled=1"];
    XCUIElementQuery *associateButtonQuery = [app.buttons matchingPredicate:associateButtonEnabledPredicate];
    if(![associateButtonQuery element].exists){
        *errorDescription = @"'Associate' button either doesn't exist or not enabled";
        return NO;
    }
    
    [[associateButtonQuery element]tap];
    
    //Enter Authorisation code
    XCUIElement *authorisationCodeTextField = app.textFields[@"Authorisation code"];
    [authorisationCodeTextField tap];
    [authorisationCodeTextField typeText:authCode];
    
    
    //Click 'NEXT' button after typing authorisation code
    NSPredicate *nextButtonPredicate = [NSPredicate predicateWithFormat:@"label='NEXT' AND enabled=1"];
    XCUIElementQuery *nextButtonQuery = [app.buttons matchingPredicate:nextButtonPredicate];
    if([nextButtonQuery element].exists){
        [[nextButtonQuery elementBoundByIndex:0] tap];
    }
    
    //Wait for 'Associating' alert to dismiss. This is being ensured by checking for presence of 'CANCEL' button
    NSPredicate *buttonCancelVanish = [NSPredicate predicateWithFormat:@"exists == 0"];
    XCUIElement *buttonCancel = app.windows.buttons[@"CANCEL"];
    [tc expectationForPredicate:buttonCancelVanish evaluatedWithObject:buttonCancel handler:nil];
    CGFloat associationCompletionTime = [[config getDataWithKey:@"associationCompletionTime"] floatValue];
    [tc waitForExpectationsWithTimeout:associationCompletionTime handler:nil];
    return YES;
    
}

-(BOOL) isDeviceDisplayedOnDevicesListScreen : (NSString *)appearanceName {

    
    XCUIElementQuery *cellsContainingDevices = app.tables.cells;
    
    for(int index = 0; index < [cellsContainingDevices count]; index++){
        
        XCUIElementQuery *staticTexts = cellsContainingDevices.staticTexts;
        
        NSString *deviceText = [staticTexts elementBoundByIndex:0].label;
        
        NSString *appearanceNameWithRowNo = [NSString stringWithFormat : @"%@ %i", appearanceName, (index+1)];
        
        if([appearanceNameWithRowNo isEqualToString:deviceText]){
            
            return YES;
        }
        
    }
    
    return NO;
}

- (BOOL) disassociateDeviceWithName : deviceNameOnListPage error:(NSString **) errorDescription {
    
    NSString *screenTitle = [self getTitle];
    
    if(![app.staticTexts[screenTitle] exists]){
        
        *errorDescription = [NSString stringWithFormat:@"'%@' screen not displayed", screenTitle];
        
        return NO;
    }
    
    [self openConfigOfDeviceWithName : deviceNameOnListPage error: errorDescription];
    
    if( *errorDescription != nil){
        
        return NO;
        
    }
    
    XCUIElementQuery *toolbarsQuery = app.toolbars;
    
    [toolbarsQuery.buttons[@"DELETE"] tap];
    
    XCUIElement *yesButton = [app.alerts elementBoundByIndex:0].collectionViews.buttons[@"Yes"];
    
    [yesButton tap];
    
    return YES;
    
}

-(void) openConfigOfDeviceWithName:(NSString *) deviceNameOnListPage error:(NSString **) errorDescription {
    
    //retrieve which cell has got the device
    int devicePosition = [self getDevicePosition : deviceNameOnListPage];
    
    if(devicePosition == -1) {
        
        *errorDescription = [NSString stringWithFormat:@"Device '%@' not found on devices list screen", deviceNameOnListPage];
        
        return;
        
    }
    
    //Click on 'Config' wheel button in cell once the cell containing desired device is located
    NSUInteger tablesCount = [app.tables count];
    XCUIElementQuery *tablesQuery = app.tables;
    
    XCUIElement *button = [[tablesQuery elementBoundByIndex:(tablesCount-1)].cells elementBoundByIndex: devicePosition].buttons.element;
    
    [button tap];
    
}



- (void) openDeviceWithName: deviceName error:(NSString **)errorDescription {
    
    int devicePosition = [self getDevicePosition : deviceName];
    
    if(devicePosition == -1) {
        
        *errorDescription = [NSString stringWithFormat:@"Device '%@' not found on devices list screen", deviceName];
        
        return;
        
    }
    
    //Click on 'Config' wheel button in cell once the cell containing desired device is located
    XCUIElementQuery *tablesQuery = app.tables;
    
    [[tablesQuery.cells elementBoundByIndex: devicePosition] tap];
    
}


- (int) getDevicePosition : (NSString *) appearanceName {
    
    NSUInteger tablesCount = [app.tables count];
    
    XCUIElementQuery *cellsContainingDevices = [app.tables elementBoundByIndex:(tablesCount-1)].cells;
    
    for(int index = 0; index < [cellsContainingDevices count]; index++){
        
        XCUIElementQuery *staticTexts = cellsContainingDevices.staticTexts;
        
        NSString *deviceText = [staticTexts elementBoundByIndex:0].label;
        
        NSString *appearanceNameWithRowNo = [NSString stringWithFormat: @"%@ %i", appearanceName, (index+1)];
        
        if([deviceText isEqualToString:appearanceNameWithRowNo]){
            
            return index;
        }
        
    }
    
    return -1;
}

- (BOOL) isDevicesListScreenDisplayed{
    
    return [app.staticTexts[[self getTitle]] exists];
}

@end
