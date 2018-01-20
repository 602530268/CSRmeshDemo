//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "CSRMeshAreaDetailScreen.h"
#import "CSRWaitUtils.h"

@implementation CSRMeshAreaDetailScreen

- (NSArray *) getDevices {
    
    return nil;
    
}

- (BOOL) isDevicePresent:(NSString *) deviceName {
    
    XCUIElementQuery *devicesTable = app.tables;
    
    NSUInteger devicesCount = [devicesTable.cells count];
    
    for(int index = 0; index < devicesCount; index++){
        
        XCUIElementQuery *deviceElement = [devicesTable.cells elementBoundByIndex:index].staticTexts;
        
        if([[deviceElement element].label containsString:deviceName]){
            return YES;
        }
    }
    return NO;
}

- (void) back {
    [app.buttons[@"back"] tap]; 
}

- (void)addDevice:(NSString *)deviceName error:(NSString **)errorDescription {
    
    [app.buttons[@"EDIT"] tap];
    
    //selecting a device
    XCUIElementQuery *devicesTable = app.tables;
    NSUInteger cellsCount = [devicesTable.cells count];
    BOOL isDeviceFound = NO;
    
    for(int index = 0; index < cellsCount; index++){
        
        NSString *deviceAppearanceName = [NSString stringWithFormat:@"%@ %i", deviceName, (index+1)];
        XCUIElement *deviceCell = [devicesTable.cells elementBoundByIndex:index].staticTexts[deviceAppearanceName];
        if([deviceCell exists] ){
            [deviceCell tap];
            isDeviceFound = YES;
            break;
        }
    }
    
    if(isDeviceFound == NO){
        *errorDescription = [NSString stringWithFormat:@"Device '%@' not found in list", deviceName];
        [app.buttons[@"back"] tap];
    }
    [self save];
    
}

- (void)deleteDevice:(NSString *)deviceName error:(NSString **)errorDescription{
    [app.buttons[@"EDIT"] tap];
    
    //selecting a device
    XCUIElementQuery *devicesTable = app.tables;
    NSUInteger cellsCount = [devicesTable.cells count];
    BOOL isDeviceFound = NO;
    
    for(int index = 0; index < cellsCount; index++){
        
        NSString *deviceAppearanceName = [NSString stringWithFormat:@"%@ %i", deviceName, (index+1)];
        XCUIElement *deviceCell = [devicesTable.cells elementBoundByIndex:index].staticTexts[deviceAppearanceName];
        if([deviceCell exists] ){
            [deviceCell tap];
            isDeviceFound = YES;
            break;
        }
    }
    
    if(isDeviceFound == NO){
        *errorDescription = [NSString stringWithFormat:@"Device '%@' not found in list", deviceName];
        [app.buttons[@"back"] tap];
    }
    [self save];
}

@end
