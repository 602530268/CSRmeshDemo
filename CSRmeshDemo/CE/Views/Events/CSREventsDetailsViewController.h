//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <UIKit/UIKit.h>
#import "CSRMainViewController.h"
#import "CSREventEntity.h"

@interface CSREventsDetailsViewController : CSRMainViewController <UITableViewDataSource, UITableViewDelegate, UITextFieldDelegate>
@property (weak, nonatomic) IBOutlet UIView *topView;
@property (weak, nonatomic) IBOutlet UITableView *eventsDetailTableView;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *doneButton;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *editButton;
@property (weak, nonatomic) IBOutlet UIImageView *topImageView;
@property (weak, nonatomic) IBOutlet UILabel *eventTypeLabel;
//@property (weak, nonatomic) IBOutlet UILabel *eventNameLabel;
@property (weak, nonatomic) IBOutlet UITextField *eventNameTextField;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *deleteEventBarButton;
@property (weak, nonatomic) IBOutlet UIToolbar *deleteToolBar;

@property (nonatomic, strong) CSREventEntity *eventEntity;

- (IBAction)deleteEventAction:(id)sender;
- (IBAction)doneAction:(id)sender;
- (IBAction)editAction:(id)sender;

@end
