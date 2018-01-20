//
//  DataBaseSimple.m
//  PPRevealSilderDemo
//
//  Created by 毛志 on 14-8-27.
//  Copyright (c) 2014年 maozhi. All rights reserved.
//

#import "DataBaseSimple.h"

@implementation DataBaseSimple
{
    FMDatabase * _dataBase;
}

+ (DataBaseSimple *)shareInstance
{
    static DataBaseSimple * simple = nil;
    if (simple == nil) {
        simple = [[DataBaseSimple alloc] init];
    }
    return simple;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        NSString *path = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
        path = [path stringByAppendingPathComponent:@"TaoBao.db"];
        NSLog(@"path is %@",path);
        _dataBase = [FMDatabase databaseWithPath:path];
        if (![_dataBase open]) {
            NSLog(@"open error!");
            return nil;
        }
        
        if(![_dataBase executeUpdate:@"create table if not exists TaoBao (ID integer primary key autoincrement,LightUUID text,Name text,DevicedID text,OtaUUID text,Version text)"]){
            NSLog(@"create table error!");
        }
    }
    return self;
}

- (BOOL)insertIntoDB:(ThingModel *)model
{
    return [_dataBase executeUpdate:@"insert into TaoBao (ID,LightUUID,Name,DevicedID,OtaUUID,Version) values (?,?,?,?,?,?)",[NSNumber numberWithInt:model.ID.intValue],model.LightUUID,model.Name,model.DevicedID,model.OtaUUID,model.Version];
}

- (BOOL)updataInfoDB:(ThingModel *)model
{
    return [_dataBase executeUpdate:@"update TaoBao set LightUUID =?,Name =?,DevicedID =?  where ID = ?",model.LightUUID,model.Name,model.DevicedID,[NSNumber numberWithInt:model.ID.intValue]];
}
- (BOOL)updataInfoDB1:(ThingModel *)model
{
    return [_dataBase executeUpdate:@"update TaoBao set Name =?  where ID = ?",model.Name,[NSNumber numberWithInt:model.ID.intValue]];
}

- (BOOL)updataInfoOtaUUIDandVersion:(ThingModel *)model
{
    return [_dataBase executeUpdate:@"update TaoBao set OtaUUID =?,Version =?  where LightUUID = ?",model.OtaUUID,model.Version,model.LightUUID];
}

- (BOOL)updataInfoVersion:(ThingModel *)model
{
    return [_dataBase executeUpdate:@"update TaoBao set Version =?  where OtaUUID = ?",model.Version,model.OtaUUID];
}

- (NSMutableArray *)selectFromDBWithLightUUID:(NSString *)LightUUID
{
    NSMutableArray * arr = [NSMutableArray array];
    FMResultSet * set = [_dataBase executeQuery:@"select * from TaoBao where LightUUID=?",LightUUID];
    while ([set next]) {
        ThingModel * m = [[ThingModel alloc] init];
        m.ID = [NSString stringWithFormat:@"%d",[set intForColumn:@"ID"]];
        m.LightUUID = [set stringForColumn:@"LightUUID"];
        m.Name = [set stringForColumn:@"Name"];
        m.DevicedID = [set stringForColumn:@"DevicedID"];
        m.OtaUUID = [set stringForColumn:@"OtaUUID"];
        m.Version = [set stringForColumn:@"Version"];
        [arr addObject:m];
    }
        
    return arr;
}

- (NSMutableArray *)selectFromDBWithLightOtaUUID:(NSString *)OtaUUID
{
    NSMutableArray * arr = [NSMutableArray array];
    FMResultSet * set = [_dataBase executeQuery:@"select * from TaoBao where OtaUUID=?",OtaUUID];
    while ([set next]) {
        ThingModel * m = [[ThingModel alloc] init];
        m.ID = [NSString stringWithFormat:@"%d",[set intForColumn:@"ID"]];
        m.LightUUID = [set stringForColumn:@"LightUUID"];
        m.Name = [set stringForColumn:@"Name"];
        m.DevicedID = [set stringForColumn:@"DevicedID"];
        m.OtaUUID = [set stringForColumn:@"OtaUUID"];
        m.Version = [set stringForColumn:@"Version"];
        [arr addObject:m];
    }
    
    return arr;
}

- (NSMutableArray *)selectFromDBWithLightDeviceID:(NSString *)DeviceID
{
    NSMutableArray * arr = [NSMutableArray array];
    FMResultSet * set = [_dataBase executeQuery:@"select * from TaoBao where ID=?",[NSNumber numberWithInt:DeviceID.intValue]];
    while ([set next]) {
        ThingModel * m = [[ThingModel alloc] init];
        m.ID = [NSString stringWithFormat:@"%d",[set intForColumn:@"ID"]];
        m.LightUUID = [set stringForColumn:@"LightUUID"];
        m.Name = [set stringForColumn:@"Name"];
        m.DevicedID = [set stringForColumn:@"DevicedID"];
        m.OtaUUID = [set stringForColumn:@"OtaUUID"];
        m.Version = [set stringForColumn:@"Version"];
        [arr addObject:m];
    }
    
    return arr;
}

@end
