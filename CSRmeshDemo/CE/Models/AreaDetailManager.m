//
//  AreaDetailManager.m
//  CSRmeshDemo
//
//  Created by double on 2017/10/23.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

#import "AreaDetailManager.h"

@implementation AreaDetailManager
{
    void(^_finish)();
}

#pragma mark - APIs (public)
+ (AreaDetailManager *)shareInstance {
    static AreaDetailManager *manager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[AreaDetailManager alloc] init];
    });
    
    return manager;
}

//编辑组网
- (void)editAreaWith:(CSRAreaEntity *)areaEntity
         theAddArray:(NSMutableArray *)theAddArray
      theDeleteArray:(NSMutableArray *)theDeleteArray
              finish:(void(^)())finish {
    
    _finish = finish;
    
    if ([theAddArray count] != 0 && areaEntity != nil) {
        
        NSLog(@"正在组网...");
        
        [theAddArray enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
            NSNumber *localDeviceId = (NSNumber*)obj;
            
            CSRDeviceEntity *deviceEntity = [[CSRDatabaseManager sharedInstance] getDeviceEntityWithId:localDeviceId];
            
            NSNumber *groupIndex = [self getValueByIndex:deviceEntity areaEntity:areaEntity];
            if (![groupIndex  isEqual:@(-1)]) {
                [[GroupModelApi sharedInstance] setModelGroupId:deviceEntity.deviceId
                                                        modelNo:@(0xff)
                                                     groupIndex:groupIndex // index of the array where there is first 0 or -1
                                                       instance:@(0)
                                                        groupId:areaEntity.areaID //id of area
                                                        success:^(NSNumber *deviceId,
                                                                  NSNumber *modelNo,
                                                                  NSNumber *groupIndex,
                                                                  NSNumber *instance,
                                                                  NSNumber *desired) {
                                                            
                                                            NSMutableData *myData = (NSMutableData*)deviceEntity.groups;
                                                            uint16_t desiredValue = [desired unsignedShortValue];
                                                            int groupIndexInt = [groupIndex intValue];
                                                            if (groupIndexInt>-1) {
                                                                uint16_t *groups = (uint16_t *) myData.mutableBytes;
                                                                *(groups + groupIndexInt) = desiredValue;
                                                            }
                                                            
                                                            deviceEntity.groups = (NSData*)myData;
                                                            NSLog(@"deviceEntity.groups :%@", myData);
                                                            CSRAreaEntity *getAreaEntity = [[CSRDatabaseManager sharedInstance] getAreaEntityWithId: desired];
                                                            
                                                            if (getAreaEntity) {
                                                                //NSLog(@"deviceEntity2 :%@", deviceEntity);
                                                                [areaEntity addDevicesObject:deviceEntity];
                                                            }
                                                            [[CSRDatabaseManager sharedInstance] saveContext];
                                                            
                                                            
                                                        } failure:^(NSError *error) {
                                                            NSLog(@"mesh timeout");
                                                            
                                                        }];
            } else {
                NSLog(@"Device has 4 areas or something went wrong");
            }
            [NSThread sleepForTimeInterval:0.3];
            
        }];
        
    }
    if ([theDeleteArray count] != 0) {
        
        NSLog(@"正在移除组网...");
        
        [theDeleteArray enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
            NSNumber *localDeviceId = (NSNumber*)obj;
            
            CSRDeviceEntity *deviceEntity = [[CSRDatabaseManager sharedInstance] getDeviceEntityWithId:localDeviceId];
            NSNumber *groupIndex = [self getValueByIndex:deviceEntity areaEntity:areaEntity];
            
            [[GroupModelApi sharedInstance] setModelGroupId:deviceEntity.deviceId
                                                    modelNo:@(0xff)
                                                 groupIndex:groupIndex // index of the array where that value was located
                                                   instance:@(0)
                                                    groupId:@(0) //0 for deleting
                                                    success:^(NSNumber *deviceId,
                                                              NSNumber *modelNo,
                                                              NSNumber *groupIndex,
                                                              NSNumber *instance,
                                                              NSNumber *desired) {
                                                        
                                                        uint16_t *dataToModify = (uint16_t*)deviceEntity.groups.bytes;
                                                        NSMutableArray *desiredGroups = [NSMutableArray new];
                                                        for (int count=0; count < deviceEntity.groups.length/2; count++, dataToModify++) {
                                                            NSNumber *groupValue = @(*dataToModify);
                                                            [desiredGroups addObject:groupValue];
                                                        }
                                                        
                                                        NSNumber *areaValue = [desiredGroups objectAtIndex:[groupIndex integerValue]];
                                                        
                                                        [areaEntity removeDevicesObject:deviceEntity];
                                                        
                                                        NSLog(@"areaValue: %@",areaValue);
                                                        NSLog(@"此时areaEntity: %@",areaEntity);
                                                        
                                                        NSMutableData *myData = (NSMutableData*)deviceEntity.groups;
                                                        uint16_t desiredValue = [desired unsignedShortValue];
                                                        int groupIndexInt = [groupIndex intValue];
                                                        if (groupIndexInt>-1) {
                                                            uint16_t *groups = (uint16_t *) myData.mutableBytes;
                                                            *(groups + groupIndexInt) = desiredValue;
                                                        }
                                                        
                                                        deviceEntity.groups = (NSData*)myData;
                                                        NSLog(@"myData: %@",myData);
                                                        
                                                        [[CSRDatabaseManager sharedInstance] saveContext];
                                                        
                                                        
                                                    } failure:^(NSError *error) {
                                                        NSLog(@"mesh timeout");
                                                        
                                                    }];
            [NSThread sleepForTimeInterval:0.3];
            
        }];
    }

    [self performSelector:@selector(complete) withObject:nil afterDelay:4.0f];
}

//删除组网
- (void)deleteAreaWith:(CSRAreaEntity *)areaEntity finish:(void(^)())finish {
    
    _finish = finish;
    
    [UDManager removeInfoWith:areaEntity.areaID];
    
    NSMutableArray *deviceArr = @[].mutableCopy;
    if (areaEntity) {
        NSSet *deviceSet = areaEntity.devices;
        
        for (CSRDeviceEntity *device in deviceSet) {
            [deviceArr addObject:device];
        }
        
    }
    
    if ([deviceArr count] != 0) {
        
        [deviceArr enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
            CSRDeviceEntity *localDeviceEntity = (CSRDeviceEntity*)obj;
            
            NSNumber *groupIndex = [self getValueByIndex:localDeviceEntity areaEntity:areaEntity];
            //            NSLog(@"groupIndex :%@", groupIndex);
            
            [[GroupModelApi sharedInstance] setModelGroupId:localDeviceEntity.deviceId
                                                    modelNo:@(0xff)
                                                 groupIndex:groupIndex // index of the array where that value was located
                                                   instance:@(0)
                                                    groupId:@(0) //0 for deleting
                                                    success:^(NSNumber *deviceId,
                                                              NSNumber *modelNo,
                                                              NSNumber *groupIndex,
                                                              NSNumber *instance,
                                                              NSNumber *desired) {
                                                        
                                                        uint16_t *dataToModify = (uint16_t*)localDeviceEntity.groups.bytes;
                                                        NSMutableArray *desiredGroups = [NSMutableArray new];
                                                        for (int count=0; count < localDeviceEntity.groups.length/2; count++, dataToModify++) {
                                                            NSNumber *groupValue = @(*dataToModify);
                                                            [desiredGroups addObject:groupValue];
                                                        }
                                                        
                                                        if (groupIndex && [groupIndex integerValue]<desiredGroups.count) {
                                                            
                                                            NSNumber *areaValue = [desiredGroups objectAtIndex:[groupIndex integerValue]];
                                                            
                                                            CSRAreaEntity *getAreaEntity = [[[CSRDatabaseManager sharedInstance] fetchObjectsWithEntityName:@"CSRAreaEntity" withPredicate:@"areaID == %@", areaValue] firstObject];
                                                            
                                                            if (getAreaEntity) {
                                                                
                                                                [areaEntity removeDevicesObject:localDeviceEntity];
                                                            }
                                                            
                                                            
                                                            NSMutableData *myData = (NSMutableData*)localDeviceEntity.groups;
                                                            uint16_t desiredValue = [desired unsignedShortValue];
                                                            int groupIndexInt = [groupIndex intValue];
                                                            if (groupIndexInt>-1) {
                                                                uint16_t *groups = (uint16_t *) myData.mutableBytes;
                                                                *(groups + groupIndexInt) = desiredValue;
                                                            }
                                                            localDeviceEntity.groups = (NSData*)myData;
                                                            
                                                            [[CSRDatabaseManager sharedInstance] saveContext];
                                                        }
                                                        
                                                        
                                                    } failure:^(NSError *error) {
                                                        NSLog(@"mesh timeout");
                                                        
                                                    }];
            
            [NSThread sleepForTimeInterval:0.3];
            
        }];
    }
    if(areaEntity) {
        [[CSRDevicesManager sharedInstance] removeAreaWithAreaId:areaEntity.areaID];
        [[CSRAppStateManager sharedInstance].selectedPlace removeAreasObject:areaEntity];
        [[CSRDatabaseManager sharedInstance].managedObjectContext deleteObject:areaEntity];
        
        [self complete];
    }
    
}

//移除设备所在的指定的组网
- (void)editDeviceWith:(CSRDeviceEntity *)deviceEntity areaEntity:(CSRAreaEntity *)areaEntity finish:(void(^)())finish {
    
    [self deleteAreaForDevice:deviceEntity withAreaID:areaEntity.areaID];
    
    NSMutableData *actualData = (NSMutableData *)deviceEntity.groups;
    NSMutableArray *allGroupsData = [NSMutableArray new];
    allGroupsData = [self fillTheActualData:actualData];
    
    
    deviceEntity.areas = nil;
    __block uint16_t groupIndex = 0;
    
    [allGroupsData enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        NSNumber *desired = (NSNumber*)obj;
        
        [[GroupModelApi sharedInstance] setModelGroupId:deviceEntity.deviceId
                                                modelNo:@(0xff)
                                             groupIndex:@(groupIndex)
                                               instance:@(0)
                                                groupId:desired
                                                success:^(NSNumber * _Nullable deviceId,
                                                          NSNumber * _Nullable modelNo,
                                                          NSNumber * _Nullable groupIndex,
                                                          NSNumber * _Nullable instance,
                                                          NSNumber * _Nullable groupId) {
                                                    
                                                    NSMutableData *groups = [NSMutableData dataWithData:deviceEntity.groups];
                                                    
                                                    // Add received group to array of groups for this device and save
                                                    int offset = (int) [groupIndex integerValue];
                                                    uint16_t *group = groups.mutableBytes;
                                                    group += offset;
                                                    uint16_t groupToBeReplaced = *group;
                                                    *group = [groupId unsignedShortValue];
                                                    
                                                    
                                                    // Add or remove area to device
                                                    if ([groupId unsignedShortValue] == 0) {
                                                        groupId = @(groupToBeReplaced);
                                                    }
                                                    
                                                    CSRAreaEntity *areaEntity = [[CSRDatabaseManager sharedInstance] getAreaEntityWithId:desired];
                                                    
                                                    if (areaEntity) {
                                                        
                                                        if ([desired unsignedShortValue] == 0) {
                                                            
                                                            [deviceEntity removeAreasObject:areaEntity];
                                                            
                                                        } else {
                                                            
                                                            [deviceEntity addAreasObject:areaEntity];
                                                            
                                                        }
                                                    }
                                                    deviceEntity.groups = groups;
                                                    [[CSRDatabaseManager sharedInstance] saveContext];
                                                    
                                                } failure:^(NSError * _Nullable error) {
                                                    
                                                    NSLog(@"mesh timeout");
                                                }];
        
        [NSThread sleepForTimeInterval:0.3f];
    }];
    
    
}

#pragma mark - APIs(private)
//method to getIndexByValue
- (NSNumber *) getValueByIndex:(CSRDeviceEntity*)deviceEntity areaEntity:(CSRAreaEntity *)areaEntity
{
    
    uint16_t *dataToModify = (uint16_t*)deviceEntity.groups.bytes;
    
    for (int count=0; count < deviceEntity.groups.length/2; count++, dataToModify++) {
        if (*dataToModify == [areaEntity.areaID unsignedShortValue]) {
            return @(count);
            
        } else if (*dataToModify == 0){
            return @(count);
        }
    }
    
    return @(-1);
}

- (void)complete {
    if (_finish) {
        _finish();
    }
}

- (BOOL) writeAreaForDevice:(CSRDeviceEntity *)deviceEntity withAreaID:(NSNumber *)areaID
{
    NSMutableData *areasData = (NSMutableData*)deviceEntity.groups;
    uint16_t *rover = (uint16_t*)areasData.mutableBytes;
    int count;
    for (count =0; count < areasData.length/2; count++, rover++) {
        if (*rover == 0) {
            *rover = [areaID unsignedShortValue];
            return YES;
        }
    }
    return NO;
}

- (void) deleteAreaForDevice:(CSRDeviceEntity *)deviceEntity withAreaID:(NSNumber *)areaID
{
    NSMutableData *areasData = (NSMutableData*)deviceEntity.groups;
    uint16_t *rover = (uint16_t*)areasData.mutableBytes;
    uint16_t areaIDValue = [areaID intValue];
    int count;
    for (count =0; count < areasData.length/2; count++, rover++) {
        if (*rover == areaIDValue) {
            *rover = 0;
            return;
        }
    }
    
}

//fill the _actualData
- (NSMutableArray*) fillTheActualData:(NSMutableData *)actualData
{
    NSMutableArray *desiredGroups = [NSMutableArray array];
    uint16_t *actual = (uint16_t*)actualData.bytes;
    
    for (int count=0; count < actualData.length/2; count++, actual++) {
        NSNumber *desired = @(*actual);
        [desiredGroups addObject:desired];
    }
    return desiredGroups;
}

@end
