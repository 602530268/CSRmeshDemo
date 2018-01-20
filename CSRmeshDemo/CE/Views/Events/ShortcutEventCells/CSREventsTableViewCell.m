//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSREventsTableViewCell.h"

NSString * const CSREventsTableViewCellIdentifier = @"eventsTableViewCellIdentifier";

@implementation CSREventsTableViewCell
@synthesize eventImageView, eventNameLabel, eventDetailLabel, onOffSwitch;

- (void)awakeFromNib {
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (IBAction)switchAction:(id)sender {
}
@end
