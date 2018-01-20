//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "TestDataUtility.h"

@implementation TestDataUtility

- (id) init {
    
    NSString *testDataFile = [[NSBundle bundleForClass: [self class]] pathForResource:@"testData" ofType:@"plist"];
    
    testDataDict = [NSDictionary dictionaryWithContentsOfFile:testDataFile];
    
    return self;
    
}

- (NSString *) getDataWithKey:(NSString *)dataKey{

    return [testDataDict objectForKey:dataKey];
}

@end
