//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//
#ifndef TestDataUtilities_h
#define TestDataUtilities_h


#endif /* TestDataUtilities_h */

@interface TestDataUtility : NSObject{
    NSDictionary *testDataDict;
}

- (id) init;

- (NSString *) getDataWithKey:(NSString *)dataKey;


@end
