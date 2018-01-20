//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//
#import <Foundation/Foundation.h>
#import "CSRMeshAreaListPage.h"
#import "CSRMeshAreaDetailScreen.h"
#import "CSRApp.h"
#import "CSRWaitUtils.h"

@implementation CSRMeshAreaListPage

-(NSString *) getTitle {
    return @"Areas";
}

-(BOOL) isAreaScreenDisplayed {
    return app.staticTexts[[self getTitle]].exists;
}


- (void) addArea : (NSDictionary *)areaDetails{
    
    NSString *areaName = areaDetails[@"areaname"];
    
    [app.toolbars.buttons[@"ADD"] tap];
    
    XCUIElement *areaNameTextField = app.textFields[@"areaTitle"];
    
    [areaNameTextField doubleTap];
    
    [app.menuItems[@"Select All"] tap];
    
    [app.menuItems[@"Cut"] tap];
    
    [NSThread sleepForTimeInterval : 1];
    
    [areaNameTextField typeText: areaName];
    
    [app.buttons[@"Save"] tap];
}

- (void) openConfigurationOf : (NSString *) areaName {
    
    XCUIElement *areaElement = app.buttons[areaName];
    
    if( areaElement) {
        
        [areaElement tap];
        
        return;
    }
}

- (void) deleteArea : (NSString *) areaName {
    
    [self openConfigurationOf: areaName];
    
    [app.buttons[@"DELETE"] tap];
}

- (BOOL) isAreaPresent : (NSString *) areaName{
    
    XCUIElement *areaElement = app.staticTexts[areaName];
    
    if(areaElement && [areaElement exists]){
        return YES;
    }else{
        return NO;
    }
}

- (void) addDeviceToArea:(NSString*)areaName deviceName:(NSString*)deviceName error:(NSString **)errorDescription{
    
    [self openConfigurationOf:areaName];
    
    CSRMeshAreaDetailScreen *areaDetailScreen = [[CSRMeshAreaDetailScreen alloc] init];
    
    errorDescription = nil;
    NSString *error1;
    [areaDetailScreen addDevice:deviceName error:&error1];
    if(error1 != nil){
        *errorDescription = [NSString stringWithFormat:@"Error when adding device '%@' to area", deviceName];
        return;
    }
    
    CSRWaitUtils *waitUtils = [[CSRWaitUtils alloc] init];
    [NSThread sleepForTimeInterval:5.0];
    CGFloat objectWaitTime = [[config getDataWithKey:@"ObjectExistWait"] floatValue];
    [waitUtils waitForElementToDisplay:[config getCurrentTestCase] element:app.staticTexts[@"Area"] maxTime:objectWaitTime];
    [app.buttons[@"Save"] tap];
        
}

-(void)openMenu{
    [app.buttons[@"menu"] tap];
}

-(NSInteger) getNoOfDevicesFromArea:(NSString *)areaName{
    NSUInteger tableViewsCount = app.tables.count;
    XCUIElement *areasTableView = [app.tables elementBoundByIndex:(tableViewsCount-1)];
    XCUIElement *areaTableCell = areasTableView.cells[areaName];
    NSUInteger cellCount = [areasTableView.cells count];
    int desiredCell = 0;
    for(int i = 0; i < cellCount; i++){
        if([[areasTableView.cells elementBoundByIndex:i].staticTexts[areaName] exists]){
            NSLog(@"Found the string");
            NSInteger textCount = [[areasTableView.cells elementBoundByIndex:i].staticTexts count];
            NSLog(@"text count:%i", textCount);
            desiredCell = i;
            break;
        }
    }
    areaTableCell = [areasTableView.cells elementBoundByIndex:desiredCell];
    NSString *deviceCountLabel = [[areaTableCell.staticTexts elementBoundByIndex:1] label];
    NSUInteger deviceStringLocation = [deviceCountLabel rangeOfString:@"Device"].location;
    NSString  *deviceCountString = [deviceCountLabel substringWithRange:NSMakeRange(0,deviceStringLocation-1)];
    NSUInteger deviceCount = [deviceCountString integerValue];
    return deviceCount;
}
@end
