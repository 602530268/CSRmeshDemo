//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <UIKit/UIKit.h>

typedef void (^CSRAlertCompletion)(NSInteger);

@interface CSRAlertView : UIAlertView<UIAlertViewDelegate> {
    CSRAlertCompletion completionBlock;
}

- (void)showWithCompletionHandler:(CSRAlertCompletion)aBlock;

@end
