//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CSRCallbacks.h"

@implementation CSRCallbacks

- (id)initWith:(id)success
       failure:(id)failure
          type:(CSRCallbackType)type {
    if (self = [super init]) {
        self.successCallback = success;
        self.failureCallback = failure;
        self.callbackType = type;
    }
    
    return self;
}

@end
