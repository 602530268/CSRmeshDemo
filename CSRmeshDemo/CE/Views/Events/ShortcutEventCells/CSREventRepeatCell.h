//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <UIKit/UIKit.h>

extern NSString * const CSREventRepeatCellIdentifier;

@interface CSREventRepeatCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *repeatTextLabel;
@property (weak, nonatomic) IBOutlet UISwitch *repeatSwitch;
- (IBAction)repeatAction:(id)sender;

@end
