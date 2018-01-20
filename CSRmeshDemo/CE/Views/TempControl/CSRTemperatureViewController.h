//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

#import <UIKit/UIKit.h>
#import "CSRmeshDevice.h"
#import "CSRmeshArea.h"


@interface CSRTemperatureViewController : UIViewController

@property (weak, atomic) CSRmeshDevice *selectedDevice;
@property (weak, atomic) CSRmeshArea *selectedArea;

@property (weak, nonatomic) IBOutlet UILabel *actualTemperatureLabel;
@property (weak, nonatomic) IBOutlet UILabel *desiredTemperatureLabel;

@property (weak, nonatomic) IBOutlet UILabel *desiredTemperatureText;
@property (weak, nonatomic) IBOutlet UIImageView *temperatureCircle;

- (IBAction)increaseTemperature:(id)sender;
- (IBAction)decreaseTemperature:(id)sender;

//@property (weak, nonatomic) IBOutlet UINavigationBar *navigationBar;

@end