//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRBaseUITest.h"

@implementation CSRBaseUITest

- (void)tap {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    
    [app tap];
}

- (BOOL)tapButton:(NSString *)identifier {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElementQuery *buttons = [app buttons];
    
    if (buttons) {
        XCUIElement *button = buttons[identifier];
        
        if (button) {
            [button tap];
            
            return YES;
        }
    }
    
    return NO;
}

- (BOOL)tapTableCellButton:(NSString *)identifier {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElementQuery *tables = app.tables;
    XCUIElementQuery *cellQuery = [tables.cells containingType:XCUIElementTypeStaticText
                                                    identifier:identifier];
    XCUIElementQuery *cell = [cellQuery childrenMatchingType:XCUIElementTypeStaticText];
    XCUIElement *element = cell.element;

    if (element.exists) {
        if (element.isHittable) {
            [element tap];
        } else {
            [element pressForDuration:0.05];
        }
        
        return YES;
    }
    
    return NO;
}

- (BOOL)tapImage:(NSString *)identifier {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *image = app.images[identifier];
    
    if (image) {
        [image tap];
        
        return YES;
    }
    
    return NO;
}

- (BOOL)tapToolbar:(NSString *)identifier {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElementQuery *toolbars = app.toolbars;
    
    if (toolbars) {
        XCUIElement *button = toolbars.buttons[identifier];
        
        if (button) {
            [button tap];
            
            return YES;
        }
    }
    
    return NO;
}

- (BOOL)enterText:(NSString *)identifier value:(NSString *)value {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *field = app.textFields[identifier];
    
    if (field) {
        [field tap];
        [field typeText: value];
        
        return YES;
    }
    
    return NO;
}

- (BOOL)enterSecureText:(NSString *)identifier value:(NSString *)value {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *field = app.secureTextFields[identifier];
    
    if (field) {
        [field tap];
        [field typeText: value];
        
        return YES;
    }
    
    return NO;
}

- (void)waitForHittableText:(XCUIElement *)element timeout:(NSInteger)timeout {
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"hittable == 1"];
    XCTestExpectation *expect = [self expectationForPredicate:predicate evaluatedWithObject:element handler:nil];
    
    [self waitForExpectationsWithTimeout:timeout handler:^(NSError * _Nullable error) {
        if (error != nil) {
            XCTAssert(expect, @"%s error: %@", __PRETTY_FUNCTION__, error);
        }
    }];
}

- (void)waitForStaticText:(NSString *)value timeout:(NSInteger)timeout {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *element = app.staticTexts[value];
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"exists == 1"];
    XCTestExpectation *expect = [self expectationForPredicate:predicate evaluatedWithObject:element handler:nil];

    [self waitForExpectationsWithTimeout:timeout handler:^(NSError * _Nullable error) {
        if (error != nil) {
            XCTAssert(expect, @"%s error: %@", __PRETTY_FUNCTION__, error);
        }
    }];
}

- (void)waitForStaticTableText:(NSString *)value timeout:(NSInteger)timeout {
    XCUIApplication *app = [[XCUIApplication alloc] init];
    XCUIElement *element = app.tables.cells.staticTexts[value];
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"exists == 1"];
    XCTestExpectation *expect = [self expectationForPredicate:predicate evaluatedWithObject:element handler:nil];
    
    [self waitForExpectationsWithTimeout:timeout handler:^(NSError * _Nullable error) {
        if (error != nil) {
            XCTAssert(expect, @"%s error: %@", __PRETTY_FUNCTION__, error);
        }
    }];
}

@end
