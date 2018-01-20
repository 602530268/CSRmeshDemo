//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <UIKit/UIKit.h>

extern NSString * const CSREventTimeCellIdentifier;

@interface CSREventTimeCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *eventTextLabel;
@property (weak, nonatomic) IBOutlet UILabel *eventDateLabel;
@property (weak, nonatomic) IBOutlet UILabel *eventTimeLabel;

@end
