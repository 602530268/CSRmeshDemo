//
//  AreaDetailManager.h
//  CSRmeshDemo
//
//  Created by double on 2017/10/23.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

/*
 灯组管理器
 */

#import <Foundation/Foundation.h>

@interface AreaDetailManager : NSObject

+ (AreaDetailManager *)shareInstance;

//编辑组网
- (void)editAreaWith:(CSRAreaEntity *)areaEntity
         theAddArray:(NSMutableArray *)theAddArray
      theDeleteArray:(NSMutableArray *)theDeleteArray
              finish:(void(^)())finish;

//删除组网
- (void)deleteAreaWith:(CSRAreaEntity *)areaEntity
                finish:(void(^)())finish;

//移除设备所在的指定的组网
- (void)editDeviceWith:(CSRDeviceEntity *)deviceEntity
            areaEntity:(CSRAreaEntity *)areaEntity
                finish:(void(^)())finish;

@end
