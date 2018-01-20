//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <UIKit/UIKit.h>
#import "CSREventsCheckbox.h"

extern NSString * const CSREventDevicesCellIdentifier;

@interface CSREventDevicesCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UIImageView *deviceImage;
@property (weak, nonatomic) IBOutlet UILabel *deviceNameLabel;
@property (nonatomic, weak) IBOutlet CSREventsCheckbox *checkBox;

@end
