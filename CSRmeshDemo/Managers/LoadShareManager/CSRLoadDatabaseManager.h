//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>

@interface CSRLoadDatabaseManager : NSObject <UIAlertViewDelegate>

+ (id)sharedInstance;
- (void) handleOpenURL:(NSURL *)url;

@end
