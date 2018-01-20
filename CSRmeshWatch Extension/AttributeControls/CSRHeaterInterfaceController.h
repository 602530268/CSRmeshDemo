//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <WatchKit/WatchKit.h>
#import <Foundation/Foundation.h>
#import "CSRWatchDevices.h"


@interface CSRHeaterInterfaceController : WKInterfaceController <CSRWatchDevicesProtocol>

- (IBAction)cooler;
- (IBAction)warmer;
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceButton *coolerButton;
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceButton *warmerButton;
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceLabel *heaterLabel;
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceLabel *desiredTemp;
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceLabel *actualTemp;
@end
