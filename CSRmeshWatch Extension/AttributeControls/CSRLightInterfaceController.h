//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <WatchKit/WatchKit.h>
#import <Foundation/Foundation.h>

@interface CSRLightInterfaceController : WKInterfaceController

- (IBAction)lightOn;
- (IBAction)lightOff;
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceButton *lightOffImage;
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceButton *lightOnImage;
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceLabel *lightName;
@end
