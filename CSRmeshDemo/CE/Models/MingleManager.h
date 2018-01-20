//
//  MingleManager.h
//  CSRmeshDemo
//
//  Created by chencheng on 2017/11/24.
//  Copyright © 2017年 Cambridge Silicon Radio Ltd. All rights reserved.
//

/*
 多款灯型兼容管理器
 */

#import <Foundation/Foundation.h>

@interface MingleManager : NSObject

//所有灯型都是 Ecosmart 厂商的
+ (BOOL)allLightsIsEcosmart;

//是否是RGB类型的灯
+ (BOOL)isRGBLight:(NSNumber *)deviceId;

//该灯组是否拥有RGB灯
+ (BOOL)containRGBLightWithArea:(CSRAreaEntity *)areaEntity;

//属于老三款灯
+ (BOOL)isOldLights:(NSNumber *)deviceId;

@end
