//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#ifndef CSRMeshAreaListPage_h
#define CSRMeshAreaListPage_h
#import "CSRCommonToolbar.h"


#endif /* CSRMeshAreaListPage_h */

@interface CSRMeshAreaListPage : CSRCommonToolbar

-(NSString *) getTitle;

-(BOOL) isAreaScreenDisplayed;

- (void) addArea : (NSDictionary *) areaDetails;

- (void) deleteArea : (NSString *) areaName;

- (void) openConfigurationOf : (NSString *) areaName;

- (NSInteger) getNoOfDevicesFromArea:(NSString *)areaName;

- (BOOL) isAreaPresent : (NSString *) areaName;

- (void) addDeviceToArea:(NSString*)areaName deviceName:(NSString*)deviceName error:(NSString **)errorDescription;

@end
