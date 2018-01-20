//
//  DeleteDeviceManager.h
//  CSRmeshDemo
//
//  Created by double on 2017/10/19.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

/*
 移除设备管理器
 */

#import <Foundation/Foundation.h>

@interface DeleteDeviceManager : NSObject

+ (DeleteDeviceManager *)shareInstance;
@property(nonatomic,assign) BOOL deleteArea;    //删除组网的灯，为true时将不会出现提示框，一往无前的删除下去，否则会有提示框，默认false

//移除设备
- (void)deleteDevice:(CSRDeviceEntity *)deviceEntity
             success:(void(^)())success
                fail:(void(^)())fail;

//删除多盏灯
- (void)deleteMoreLights:(NSMutableArray <CSRDeviceEntity *>*)lights
              areaEntity:(CSRAreaEntity *)areaEntity
                  finish:(void(^)())finish;

/*
 删除多盏灯的时候因为桥的关系，会出现删除不彻底，有些灯依旧没有复位的情况，现在开始优化删除逻辑

 步骤如下：
 1.展示提示框
 2.开始多盏灯的删除，离线状态的灯强制删除
 3.检测当前桥连接bool和当前剩余灯数量count。当桥连接为false时在3s后重新执行3步骤；当剩余灯数量不为0时执行2步骤；直到bool为true且count=0
 4.删除完成后隐藏提示框
 5.点击提示框可取消删除

 */

@end
