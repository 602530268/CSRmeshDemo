//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//
#ifndef CSRMeshAreaDetailScreen_h
#define CSRMeshAreaDetailScreen_h


#endif /* CSRMeshAreaDetailScreen_h */
#import "CSRCommonToolbar.h"

@interface CSRMeshAreaDetailScreen : CSRCommonToolbar

- (void) setAreaTitle : (NSString *) areaTitle;

- (NSArray *) getDevices;

- (BOOL) isDevicePresent:(NSString *) deviceName;

- (void) addDevice:deviceName error:(NSString **)errorDescription;

- (void) deleteDevice:(NSString *) deviceName error:(NSString **)errorDescription;

@end

