//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSREventRepeatCell.h"
#import "CSREventTimeSelectorVC.h"

NSString * const CSREventRepeatCellIdentifier = @"eventRepeatCellIdentifier";

@implementation CSREventRepeatCell

- (void)awakeFromNib {
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (IBAction)repeatAction:(UISwitch*)sender {
}



@end
