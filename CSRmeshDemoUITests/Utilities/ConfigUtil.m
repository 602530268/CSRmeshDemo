//
//  ConfigUtil.m
//  CSRmeshDemo
//
//  Created by Harish Renukunta on 27/01/2016.
//  Copyright © 2016 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ConfigUtil.h"

@implementation ConfigUtil

+ (id) sharedInstance {
    
    static dispatch_once_t block;
    
    static ConfigUtil *config;
    
    dispatch_once(&block, ^{
        
        config = [[ConfigUtil alloc] init];
        
    });
    return config;
}

- (id) init{
    
    NSString *configDataFile = [[NSBundle bundleForClass: [self class]] pathForResource:@"testConfig" ofType:@"plist"];
    
    configDataDict = [NSDictionary dictionaryWithContentsOfFile:configDataFile];
    
    return self;
    
}

- (NSString *) getDataWithKey:(NSString *)dataKey{
    
    return [configDataDict objectForKey:dataKey];
}

-(void) setCurrentTestCase:(XCTestCase *)testcase{
    tc = testcase;
}

-(XCTestCase *) getCurrentTestCase{
    return tc;
}


@end
