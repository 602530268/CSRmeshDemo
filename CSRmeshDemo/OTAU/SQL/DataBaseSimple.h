//
//  DataBaseSimple.h
//  PPRevealSilderDemo
//
//  Created by 毛志 on 14-8-27.
//  Copyright (c) 2014年 maozhi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FMDatabase.h"
#import "ThingModel.h"

@interface DataBaseSimple : NSObject

+ (DataBaseSimple *)shareInstance;
- (BOOL)insertIntoDB:(ThingModel *)model;
- (NSMutableArray *)selectFromDBWithLightUUID:(NSString *)LightUUID;
- (BOOL)updataInfoDB:(ThingModel *)model;
- (BOOL)updataInfoDB1:(ThingModel *)model;
- (BOOL)updataInfoOtaUUIDandVersion:(ThingModel *)model;
- (BOOL)updataInfoVersion:(ThingModel *)model;
- (NSMutableArray *)selectFromDBWithLightOtaUUID:(NSString *)OtaUUID;
- (NSMutableArray *)selectFromDBWithLightDeviceID:(NSString *)DeviceID;
@end
