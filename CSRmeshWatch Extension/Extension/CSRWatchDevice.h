//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>

@interface CSRWatchDevice : NSObject

-(NSArray *)getViews;

@property   (nonatomic) NSString *name;
@property   (nonatomic) NSNumber *deviceId;
@property   (nonatomic) BOOL    isLight;
@property   (nonatomic) BOOL    isHeater;
@property   (nonatomic) BOOL    isLock;
@property   (nonatomic) BOOL    isActivity;
@property   (nonatomic) BOOL    isDevice;
@property   (nonatomic) BOOL    isArea;
@property   (nonatomic) NSNumber    *desiredTemp;
@property   (nonatomic) NSNumber    *actualTemp;

@end
