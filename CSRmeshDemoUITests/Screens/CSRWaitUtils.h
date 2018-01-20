//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#ifndef CSRWaitUtils_h
#define CSRWaitUtils_h


#endif /* CSRWaitUtils_h */
#import <XCTest/XCTest.h>
#import "CSRCommonToolbar.h"

@interface CSRWaitUtils : CSRCommonToolbar

-(void) waitForElementToDisplay:(XCTestCase *)tc element:(XCUIElement *)element maxTime:(CGFloat)mTime;

@end
