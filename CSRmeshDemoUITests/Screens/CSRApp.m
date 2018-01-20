//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>
#import "CSRApp.h"

@implementation CSRApp
    
+ (id) sharedInstance {
    
    static dispatch_once_t block;
    
    static XCUIApplication *app;
    
    dispatch_once(&block, ^{
        
        app = [[XCUIApplication alloc] init];
        
    });
    return app;
}

@end
