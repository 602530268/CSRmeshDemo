//
//  BridgeStateManager.h
//  CSRmeshDemo
//
//  Created by double on 2017/11/9.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

/*
 桥连接状态管理器
 */

#import <Foundation/Foundation.h>

@interface BridgeStateManager : NSObject

@property(nonatomic,assign) BOOL bridgeConnnected;  //桥连接状态

+ (BridgeStateManager *)shareInstance;

//搜索周围桥并连接
- (void)scanBridgeAndConnect;

@end
