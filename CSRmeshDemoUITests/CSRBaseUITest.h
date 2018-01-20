//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

@interface CSRBaseUITest : XCTestCase

- (void)tap;
- (BOOL)tapTableCellButton:(NSString *)identifier;
- (BOOL)tapButton:(NSString *)identifier;
- (BOOL)tapImage:(NSString *)identifier;
- (BOOL)tapToolbar:(NSString *)identifier;
- (BOOL)enterText:(NSString *)identifier value:(NSString *)value;
- (BOOL)enterSecureText:(NSString *)identifier value:(NSString *)value;
- (void)waitForStaticText:(NSString *)value timeout:(NSInteger)timeout;
- (void)waitForStaticTableText:(NSString *)value timeout:(NSInteger)timeout;

@end
