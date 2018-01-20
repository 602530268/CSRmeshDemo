//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "CSRCommonToolbar.h"
#import "CSRApp.h"

@implementation CSRCommonToolbar

- (instancetype) init {
    
    app = [CSRApp sharedInstance];
    config = [ConfigUtil sharedInstance];
    
    return self;
}

- (void) back{
    
    [app.images[@"back"] tap];
}

- (void) search : (NSString *) searchText{
    
    
}

- (NSString *) getTitle{
    
    return @"Dummy title";
}

- (void) cancelSearch{
    
}

- (void) save {
    [app.buttons[@"Save"] tap];
}

-(ConfigUtil *) getConfig{
    return config;
}

@end
