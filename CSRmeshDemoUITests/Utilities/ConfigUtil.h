//
//  ConfigUtil.h
//  CSRmeshDemo
//
//  Created by Harish Renukunta on 27/01/2016.
//  Copyright © 2016 Cambridge Silicon Radio Ltd. All rights reserved.
//

#ifndef ConfigUtil_h
#define ConfigUtil_h


#endif /* ConfigUtil_h */
#import <XCTest/XCTest.h>

@interface ConfigUtil : NSObject{
    NSDictionary *configDataDict;
    XCTestCase *tc;
}

+ (id) sharedInstance;

- (NSString *) getDataWithKey:(NSString *)dataKey;

-(void) setCurrentTestCase:(XCTestCase *) tc;

-(XCTestCase *) getCurrentTestCase;

@end
