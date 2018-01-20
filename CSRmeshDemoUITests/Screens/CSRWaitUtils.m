//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "CSRWaitUtils.h"
#import "CSRApp.h"

@implementation CSRWaitUtils


-(void) waitForElementToDisplay:(XCTestCase *)tc element:(XCUIElement *)element maxTime:(CGFloat)mTime{
    
    NSPredicate *elementExistPredicate = [NSPredicate predicateWithFormat:@"exists=1"];
    [tc expectationForPredicate:elementExistPredicate evaluatedWithObject:element handler:nil];
    [tc waitForExpectationsWithTimeout:mTime handler:nil];
    
}


@end
