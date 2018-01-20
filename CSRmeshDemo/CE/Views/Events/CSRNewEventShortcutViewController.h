//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <UIKit/UIKit.h>
#import "CSRMainViewController.h"
#import "CSREventTimeSelectorVC.h"
#import "CSREventEntity.h"

@interface CSRNewEventShortcutViewController :  UIViewController <UITableViewDataSource, UITableViewDelegate, UITextFieldDelegate, UIPopoverPresentationControllerDelegate, CSREventTimesDelegate>

//TableView
@property (weak, nonatomic) IBOutlet UITableView *eventCreationTableView;

//Property values we get from other view controllers
@property (nonatomic) NSUInteger typeOfEvent;

//Event Entity
@property (nonatomic, retain) CSREventEntity *eventEntity;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *deleteEventItem;
@property (weak, nonatomic) IBOutlet UIToolbar *deleteEventToolbar;


- (IBAction)saveEventAction:(id)sender;
- (IBAction)closeEventAction:(id)sender;


- (IBAction)deleteEventAction:(id)sender;


@end
