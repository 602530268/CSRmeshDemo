//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "AppDelegate.h"
#import "CSRDatabaseManager.h"
#import "CSRAppStateManager.h"
#import "CSRUtilities.h"
#import "CSRmeshSettings.h"
#import "CSRWatchManager.h"
#import "CSRMesh/TimeModelApi.h"
#import "CSRAppStateManager.h"

#import "IQKeyboardManager.h"
#import "SharePlaceManager.h"
#import "BridgeStateManager.h"

#import <Bugly/Bugly.h>

@interface AppDelegate ()

@end

@implementation AppDelegate

/*
 本项目基于CSRMesh2.1官方demo开发，移除了demo的UI，其他基本一致，所有的英文注释下的代码均为demo代码，未完全了解功能前不建议修改；
 该项目目前支持以下功能:
     扫描连接、单灯/灯组的开关、色温状态调节、RGB状态调节、
     灯组的组网和移除、
     OTA升级、
     分享、
 可从文件名前缀看出哪些为demo源文件，哪些为添置文件
 */

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    //判断上一个版本是不是mesh1.3，是的话删除所有缓存记录
    [self checkLastVersion];
    
    [[UINavigationBar appearance] setTintColor:[UIColor whiteColor]];
    
    // Set the global cloud host URL
    if ([CSRUtilities getValueFromDefaultsForKey:kCSRGlobalCloudHost]) {
        
        [CSRAppStateManager sharedInstance].globalCloudHost = [CSRUtilities getValueFromDefaultsForKey:kCSRGlobalCloudHost];
        
    } else {
        
        [CSRAppStateManager sharedInstance].globalCloudHost = kCloudServerUrl;
        
    }
    
    // Check if there is a place in DB
    [[CSRAppStateManager sharedInstance] createDefaultPlace];

    // Setup current place to be available from the start
    [[CSRAppStateManager sharedInstance] setupPlace];

    [[CSRAppStateManager sharedInstance] switchConnectionForSelectedBearerType:CSRSelectedBearerType_Bluetooth];
    
    // Check for externally passed URL - place import
    if (launchOptions[@"UIApplicationLaunchOptionsURLKey"])
    {
        [self application:application openURL:launchOptions[@"UIApplicationLaunchOptionsURLKey"] sourceApplication:nil annotation:launchOptions];
    }
    
    [self completionHandleIQKeyboard];  //一键处理键盘被遮挡问题
    
    [Bugly startWithAppId:@"29295aa681"];
    
    [[UINavigationBar appearance] setTitleTextAttributes:@{
                                                           NSForegroundColorAttributeName : [UIColor lightGrayColor],
                                                           NSFontAttributeName : [UIFont fontWithName:GeneralFontName size:20]
                                                           }];
    
    //开启自定义logView
    [CClogManager ccLogEnable:YES];
    
    return YES;
}

- (void)checkLastVersion {
    //就根据是否有存储过组网密码来判断好了
    NSString *password = [[NSUserDefaults standardUserDefaults] valueForKey:UD_Passcode];
    if (password == nil || password.length == 0) {
        
        CCLog(@"从旧版本更新，删除旧版本存储数据.");
        NSString *documents = [BaseCommond pathByDocument];
        NSString *library = [BaseCommond pathByLibrary];
        
        NSFileManager *fileManager = [[NSFileManager alloc] init];
        [fileManager removeItemAtPath:documents error:nil];
        [fileManager removeItemAtPath:library error:nil];
        
        [fileManager createDirectoryAtPath:documents withIntermediateDirectories:YES attributes:nil error:nil];
        [fileManager createDirectoryAtPath:library withIntermediateDirectories:YES attributes:nil error:nil];
        
        [NSThread sleepForTimeInterval:2.0f];
    }
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Broadcast time
    [self broadcastTime];
    
    [[BridgeStateManager shareInstance] scanBridgeAndConnect];
}

//- (void)applicationDidEnterBackground:(UIApplication *)application
//{
//    
//}
- (void)applicationWillEnterForeground:(UIApplication *)application
{
    [[CSRDatabaseManager sharedInstance] saveContext];
    [[CSRAppStateManager sharedInstance] connectivityCheck];
}


- (void)applicationWillTerminate:(UIApplication *)application
{
//    [[CSRConnectionManager sharedInstance] shutDown];
    [[CSRDatabaseManager sharedInstance] saveContext];
}

- (BOOL) application:(UIApplication *)application handleOpenURL:(NSURL *)url {
    
    return YES;
}

//通过airdrop接收共享设备信息
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{

    if (url != nil && [url isFileURL]) {
//        _managePlacesViewController = [[CSRManagePlacesViewController alloc] init];
//        [_managePlacesViewController setImportedURL:url];
        
        _passingURL = url;
        [[SharePlaceManager shareInstance] setImportedURL:url];
        [[SharePlaceManager shareInstance] saveImportPlace];
    }

    return YES;
}

#define SecondsPerHour  3600

-(void)broadcastTime {
    
    // Compute timezone, BST -> GMT=1 | Delhi=+5.5
    
    [[TimeModelApi sharedInstance] broadcastTimeWithCurrentTime:@([[NSDate date] timeIntervalSince1970] * 1000)
                                                       timeZone:@(([[NSTimeZone localTimeZone] secondsFromGMT]) / SecondsPerHour)
                                                     masterFlag:@1];
    
}

#pragma mark - Abou Keyboard
- (void)completionHandleIQKeyboard {
    IQKeyboardManager *manager = [IQKeyboardManager sharedManager];
    manager.enable = YES;
    manager.shouldResignOnTouchOutside = YES;
    manager.shouldToolbarUsesTextFieldTintColor = YES;
    manager.enableAutoToolbar = YES;
}


@end
