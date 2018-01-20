//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (nonatomic, retain) NSURL *passingURL;
@property (nonatomic) BOOL updateInProgress;
@property (nonatomic) NSString *updateFileName;
@property (nonatomic) double updateProgress;

//OTAU升级
@property (strong, nonatomic) NSURL *urlImageFile;
@property (strong, atomic) NSNumber *peripheralInBoot;
@property (strong, nonatomic) CBService *targetService;
@property (strong, nonatomic) CBService *devInfoService;
@property (strong, atomic) NSNumber *discoveredChars;

@end


