//
//  SharePlaceManager.h
//  CSRmeshDemo
//
//  Created by double on 2017/10/30.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

/*
 共享设备管理器
 */

#import <Foundation/Foundation.h>

@interface SharePlaceManager : NSObject

@property (nonatomic) CSRPlaceEntity *placeEntity;
@property(nonatomic,strong) NSURL *importedURL;

+ (SharePlaceManager *)shareInstance;

//导出包
- (void)exportPlaceTo:(UIViewController *)vc;

//保存包
- (void)saveImportPlace;

@end
