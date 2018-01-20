//
//  SharePlaceManager.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/30.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "SharePlaceManager.h"
#import "CSRParseAndLoad.h"
#import "ZipArchive.h"
#import "AppDelegate.h"
#import "AlertControllerManager.h"

@implementation SharePlaceManager

+ (SharePlaceManager *)shareInstance {
    static SharePlaceManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[SharePlaceManager alloc] init];
    });
    return manager;
}


- (void)exportPlaceTo:(UIViewController *)vc {
    
    CSRParseAndLoad *parseLoad = [[CSRParseAndLoad alloc] init];
    
    NSData *jsonData = [parseLoad composeDatabase];
    
    NSError *error;
    NSString *jsonString;
    if (jsonData) {
        jsonString = [CSRUtilities stringFromData:jsonData];
    } else {
        NSLog(@"Got an error while NSJSONSerialization:%@", error);
    }
    
    CSRPlaceEntity *placeEntity = [[CSRAppStateManager sharedInstance] selectedPlace];
    
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString* dPath = [paths objectAtIndex:0];
    NSString* zipfile = [dPath stringByAppendingPathComponent:@"test.zip"] ;
    
    NSString *appFile = [NSString stringWithFormat:@"%@_%@", placeEntity.name, @"Database.qti"];
    NSString *realPath = [dPath stringByAppendingPathComponent:appFile] ;
    [jsonString writeToFile:realPath atomically:YES encoding:NSUTF8StringEncoding error:&error];
    
    
    ZipArchive* zip = [[ZipArchive alloc] init];
//    if([zip CreateZipFile2:zipfile Password:[[MeshServiceApi sharedInstance] getMeshId]]) {
    //自定义压缩包密码，因为当两台设备组网密码不一致时获取的meshId是错误的，即解压失败，现在手动设置保证解压稳定
    if([zip CreateZipFile2:zipfile Password:@"12345"]) {

        NSLog(@"Zip File Created");
        if([zip addFileToZip:realPath newname:@"MyFile.qti"])
        {
            NSLog(@"File Added to zip");
        }
    }
    
    NSURL *jsonURL = [NSURL fileURLWithPath:zipfile];
    
    UIActivityViewController *activityVC = [[UIActivityViewController alloc] initWithActivityItems:@[jsonURL]
                                                                             applicationActivities:nil];
    [activityVC setValue:@"JSON Attached" forKey:@"subject"];
    
    activityVC.completionWithItemsHandler = ^(NSString *activityType, BOOL completed, NSArray *returnedItems, NSError *activityError) {
        if (completed) {
            NSLog(@"Activity completed");
        } else {
            if (activityType == NULL) {
                NSLog(@"User dismissed the view controller without making a selection");
            } else {
                NSLog(@"Activity was not performed");
            }
        }
    };
    
    [vc presentViewController:activityVC animated:YES completion:nil];
    if ([activityVC respondsToSelector:@selector(popoverPresentationController)]) {
        UIPopoverPresentationController *activity = [activityVC popoverPresentationController];
        activity.sourceRect = CGRectMake(10, 10, 200, 100);
        activity.sourceView = vc.view;
    }
}

- (void)saveImportPlace {
    
    [self checkPlaceEntity];
    
    if (!_placeEntity) {
        NSLog(@"找不到默认的place，无法接收共享数据");
        return;
    }
    
    NSLog(@"MeshID :%@", [[MeshServiceApi sharedInstance] getMeshId]);

    if (_placeEntity && ![CSRUtilities isStringEmpty:_placeEntity.passPhrase] && !_importedURL) { //detail, configure
        
        if (![CSRUtilities isStringEmpty:_placeEntity.name] && ![CSRUtilities isStringEmpty:_placeEntity.passPhrase]) {
//            _placeEntity.color = @([CSRUtilities rgbFromColor:_placeColorSelectionButton.backgroundColor]);   //一个颜色标记，暂不需要
//            _placeEntity.iconID = @(placeIconId); //icon索引，也不需要
            _placeEntity.owner = @"My place";
            _placeEntity.networkKey = nil;
            
            [self checkForSettings];
            [[CSRDatabaseManager sharedInstance] saveContext];
            [CSRUtilities saveObject:[[[[CSRAppStateManager sharedInstance].selectedPlace objectID] URIRepresentation] absoluteString] toDefaultsWithKey:@"kCSRLastSelectedPlaceID"];
            [[CSRAppStateManager sharedInstance] setupPlace];
            
            //完成
            [self saveFinish];
        } else {
            [self showAlert];
        }
        
        
    } else if (!_placeEntity && !_importedURL) { //new place
        
        if (![CSRUtilities isStringEmpty:_placeEntity.name] && ![CSRUtilities isStringEmpty:_placeEntity.passPhrase]) {
            _placeEntity = [NSEntityDescription insertNewObjectForEntityForName:@"CSRPlaceEntity"
                                                         inManagedObjectContext:[CSRDatabaseManager sharedInstance].managedObjectContext];
            
//            _placeEntity.color = @([CSRUtilities rgbFromColor:_placeColorSelectionButton.backgroundColor]);
//            _placeEntity.iconID = @(placeIconId);
            _placeEntity.owner = @"My place";
            _placeEntity.networkKey = nil;
            
            [self checkForSettings];
            [[CSRDatabaseManager sharedInstance] saveContext];
            [[CSRAppStateManager sharedInstance] setupPlace];
            
            //完成
            [self saveFinish];
        } else {
            [self showAlert];
        }
    } else if (_placeEntity && [CSRUtilities isStringEmpty:_placeEntity.passPhrase] && !_importedURL) { //from MASP
        
        if (![CSRUtilities isStringEmpty:_placeEntity.name]) {
//            _placeEntity.color = @([CSRUtilities rgbFromColor:_placeColorSelectionButton.backgroundColor]);
//            _placeEntity.iconID = @(placeIconId);
            
            [self checkForSettings];
            [[CSRDatabaseManager sharedInstance] saveContext];
            
            //完成
            [self saveFinish];
        } else {
            [self showAlert];
        }
        
    } else if (_placeEntity && _importedURL && ![CSRUtilities isStringEmpty:_placeEntity.passPhrase]) {
        
        if (![CSRUtilities isStringEmpty:_placeEntity.name] ) {
//            _placeEntity.color = @([CSRUtilities rgbFromColor:_placeColorSelectionButton.backgroundColor]);
//            _placeEntity.iconID = @(placeIconId);
            _placeEntity.owner = @"My place";
            _placeEntity.networkKey = nil;
            
            [self checkForSettings];
            [[CSRAppStateManager sharedInstance] setSelectedPlace:_placeEntity];
            [self unZipDecrypt];
            [[MeshServiceApi sharedInstance] setNetworkPassPhrase:_placeEntity.passPhrase];
            
            ((AppDelegate*)[UIApplication sharedApplication].delegate).passingURL = nil;
            
            //完成
            [self saveFinish];
        } else {
            [self showAlert];
        }
    } else if (!_placeEntity && _importedURL) {
        if (![CSRUtilities isStringEmpty:_placeEntity.name] && ![CSRUtilities isStringEmpty:_placeEntity.passPhrase]) {
            CSRPlaceEntity *newPlace = [NSEntityDescription insertNewObjectForEntityForName:@"CSRPlaceEntity"
                                                                     inManagedObjectContext:[CSRDatabaseManager sharedInstance].managedObjectContext];
            
            newPlace.name = _placeEntity.name;
            newPlace.passPhrase = _placeEntity.passPhrase;
//            newPlace.color = @([CSRUtilities rgbFromColor:_placeColorSelectionButton.backgroundColor]);
//            newPlace.iconID = @(placeIconId);
            newPlace.owner = @"My place";
            newPlace.networkKey = nil;
            
            [self checkForSettings];
            [[CSRAppStateManager sharedInstance] setSelectedPlace:newPlace];
            [self unZipDecrypt];
            [[MeshServiceApi sharedInstance] setNetworkPassPhrase:_placeEntity.passPhrase];
            
            ((AppDelegate*)[UIApplication sharedApplication].delegate).passingURL = nil;
            
            //完成
            [self saveFinish];
        } else {
            [self showAlert];
        }
        
    } else if (_placeEntity && _importedURL && [CSRUtilities isStringEmpty:_placeEntity.passPhrase]) {
        if (![CSRUtilities isStringEmpty:_placeEntity.name]) {
//            _placeEntity.color = @([CSRUtilities rgbFromColor:_placeColorSelectionButton.backgroundColor]);
//            _placeEntity.iconID = @(placeIconId);
            
            [self checkForSettings];
            [self unZipDecrypt];
            
            [[MeshServiceApi sharedInstance] setNetworkKey:_placeEntity.networkKey];
            
            ((AppDelegate*)[UIApplication sharedApplication].delegate).passingURL = nil;
            
            //完成
            [self saveFinish];
        } else {
            [self showAlert];
        }
        
    }
}

#pragma mark - APIs(private)
- (void)checkPlaceEntity {
    NSMutableArray *placesArray = [[[CSRDatabaseManager sharedInstance] fetchObjectsWithEntityName:@"CSRPlaceEntity" withPredicate:nil] mutableCopy];
    for (CSRPlaceEntity *placeEntity in placesArray) {
        if ([placeEntity.name isEqualToString:@"iOSHouse"]) {
            _placeEntity = placeEntity;
            break;
        }
    }
}

- (void) unZipDecrypt {
    
    NSError *error = nil;
    NSString *zipPath = [_importedURL path];
    
    NSString *outputPath = [CSRUtilities createFile:@"Regular"];
    ZipArchive* zip = [[ZipArchive alloc] init];
//    if([zip UnzipOpenFile:zipPath Password:[[MeshServiceApi sharedInstance] getMeshId]]) {
    if([zip UnzipOpenFile:zipPath Password:@"12345"]) {
        if([zip UnzipFileTo:outputPath overWrite:YES])
        {
            NSLog(@"success");
        } else {
            //TODO: crash fix
            NSLog(@"Zip is Wrong!!");
        }
        [zip UnzipCloseFile];
    }
    
    NSArray * directoryContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:outputPath error:&error];
    if (directoryContents.count == 0) {
        [AlertControllerManager alertWithTitle:@"Fail!"
                                       message:@"File is Wrong!!"
                                         style:UIAlertControllerStyleAlert
                                  actionTitles:@[@"OK"]
                                  actionStyles:@[@(UIAlertActionStyleDefault)]
                                        target:[BaseCommond getCurrentVC]
                                      handlers:nil];
        return;
    }
    
    NSString *fullURLString = [outputPath stringByAppendingString:[NSString stringWithFormat:@"/%@", [directoryContents objectAtIndex:0]]];
    NSString *validStr = [NSString stringWithFormat:@"file:///%@", fullURLString];
    NSData *jsonDataImported = [NSData dataWithContentsOfURL:[NSURL URLWithString:validStr]];
    
    NSDictionary *jsonDictionary = [NSJSONSerialization JSONObjectWithData:jsonDataImported options:NSJSONReadingMutableLeaves error:&error];
    
    [CSRUtilities saveObject:[[[[CSRAppStateManager sharedInstance].selectedPlace objectID] URIRepresentation] absoluteString] toDefaultsWithKey:@"kCSRLastSelectedPlaceID"];
    
    [[CSRAppStateManager sharedInstance] setupPlace];
    
    CSRParseAndLoad *parseLoad = [[CSRParseAndLoad alloc] init];
    [parseLoad deleteEntitiesInSelectedPlace]; //Delete Core data Entities
    [parseLoad parseIncomingDictionary:jsonDictionary]; //parse and load fresh data
}

- (void)checkForSettings
{
    if (_placeEntity.settings) {
        
        _placeEntity.settings.retryInterval = @500;
        _placeEntity.settings.retryCount = @10;
        _placeEntity.settings.concurrentConnections = @1;
        _placeEntity.settings.listeningMode = @1;
        
    } else {
        
        CSRSettingsEntity *settings = [NSEntityDescription insertNewObjectForEntityForName:@"CSRSettingsEntity"
                                                                    inManagedObjectContext:[CSRDatabaseManager sharedInstance].managedObjectContext];
        settings.retryInterval = @500;
        settings.retryCount = @10;
        settings.concurrentConnections = @1;
        settings.listeningMode = @1;
        
        _placeEntity.settings = settings;
        
    }
}

- (void) showAlert {
    
    __block UIViewController *vc = [BaseCommond getCurrentVC];
    
    if ([vc isKindOfClass:[UIAlertController class]]) { //将UIAlertController隐藏
        [vc dismissViewControllerAnimated:NO completion:^{
            
            vc = [BaseCommond getCurrentVC];
            
            UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Alert!"
                                                                                     message:@"Name and Pass Phrase should not be empty, please enter some values"
                                                                              preferredStyle:UIAlertControllerStyleAlert];
            
            UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK"
                                                               style:UIAlertActionStyleDefault
                                                             handler:^(UIAlertAction *action) {
                                                                 [self saveFinish];
                                                             }];
            
            [alertController addAction:okAction];
            [vc presentViewController:alertController animated:YES completion:nil];
        }];
    }
    
}

- (void)saveFinish {
    _placeEntity = nil;
    
    [[NSNotificationCenter defaultCenter] postNotificationName:Notify_UpdateOfExportFile object:nil];
}

@end
