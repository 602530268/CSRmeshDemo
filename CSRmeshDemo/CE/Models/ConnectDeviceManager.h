//
//  ConnectDeviceManager.h
//  CSRmeshDemo
//
//  Created by double on 2017/7/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

/*
 连接管理器
 */

#import <Foundation/Foundation.h>

@interface ConnectDeviceManager : NSObject

@property(nonatomic,assign) BOOL connecting;    //正在连接

+ (ConnectDeviceManager *)shareInstance;

//Mesh框架默认不支持同时添加设备，新增方法处理
- (void)connectDevices:(NSMutableArray *)devices
               success:(void(^)(NSString *deviceName))success
              progress:(void(^)(NSString *deviceName, CGFloat progress))progress
                  fail:(void(^)(NSString *deviceName))fail
                finish:(void(^)())finish;

//除了当前正在连接的设备外，后续的连接取消
- (void)cancelConnect;

@end
