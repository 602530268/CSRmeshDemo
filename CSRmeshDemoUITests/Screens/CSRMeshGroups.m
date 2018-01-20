//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "CSRMeshGroups.h"

@implementation CSRMeshGroups

-(id) init {
    self = [super init];
    return self;
}

-(NSString *) getTitle {
    return @"Groups";
}

-(XCUIElement *) groupsTable{
    
    int tablesCount = [app.tables count];
    
    return [app.tables elementBoundByIndex:(tablesCount-1)];
    
}

-(BOOL) isGroupsScreenDisplayed{
    return app.staticTexts[[self getTitle]].exists;
}

-(BOOL) isAreaPresent:(NSString *)areaName {
    
    NSUInteger areaRowNo = [self getAreaRowNo:areaName];
    
    return(areaRowNo != -1);
    
}

-(BOOL) isAreaSelected:(NSString *)areaName {
    
    NSUInteger areaRowNo = [self getAreaRowNo:areaName];
    
    if(areaRowNo == -1){
        return NO;
    }
    
    XCUIElement *areaTableCell = [[self groupsTable].cells elementBoundByIndex:areaRowNo];
    return([areaTableCell.value integerValue]==1);
}

-(NSUInteger) getAreaRowNo:(NSString *) areaName {
    
    XCUIElement *areaTable = [self groupsTable];
    
    XCUIElementQuery *areaTableCells = areaTable.cells;
    
    for(int index = 0; index < [areaTableCells count]; index++){
        XCUIElement *areaTableCell = [areaTableCells elementBoundByIndex:index];
        if([areaTableCell.staticTexts[areaName] exists]){
            return index;
        }
    }
    return -1;
}

-(void) back{
    [app.buttons[@"Back"] tap];
}

-(void) save{
    [app.buttons[@"Save"] tap];
}

-(void) selectArea:(NSString *)areaName error:(NSString **)errorDescription{
    
    NSString *error;
    
    [self clickAreaWithName:areaName error:&error];
    
    *errorDescription = error;
    
}

-(void) clickAreaWithName:(NSString *)areaName error:(NSString **)errorDescription{
    
    NSUInteger areaRowNo = [self getAreaRowNo:areaName];
    
    if(areaRowNo == -1){
        *errorDescription = [NSString stringWithFormat: @"Area '%@' not found", areaName];
        return;
    }
    
    [[[self groupsTable].cells elementBoundByIndex:areaRowNo] tap];
}

@end
