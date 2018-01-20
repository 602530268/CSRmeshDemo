//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CSRAlertView.h"

@implementation CSRAlertView

- (void)showWithCompletionHandler:(CSRAlertCompletion)aBlock {
    self.delegate = self;
    completionBlock = [aBlock copy];
    [self show];
}

- (void)alertView:(UIAlertView *)alertView willDismissWithButtonIndex:(NSInteger)buttonIndex {
    completionBlock(buttonIndex);
    completionBlock = nil;
}

@end
