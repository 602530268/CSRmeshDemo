//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <UIKit/UIKit.h>

extern NSString * const CSREventConfigurationCellIdentifier;

@interface CSREventConfigurationCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UIImageView *eventImageView;
@property (weak, nonatomic) IBOutlet UILabel *eventConfigurationLabel;
@property (weak, nonatomic) IBOutlet UILabel *eventStateLabel;
@property (weak, nonatomic) IBOutlet UILabel *eventSubStateLabel;
@property (weak, nonatomic) IBOutlet UIView *eventStateView;

@end
