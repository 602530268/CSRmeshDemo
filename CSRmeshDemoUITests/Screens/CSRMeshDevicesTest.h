//
//  CSRMeshDevices.h
//  CSRmeshDemo
//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#ifndef CSRMeshDevices_h
#define CSRMeshDevices_h


#endif /* CSRMeshDevices_h */
#import "CSRCommonToolbar.h"

@interface CSRMeshDevicesTest : CSRCommonToolbar

+ (CSRMeshDevicesTest *) sharedInstance;

- (instancetype) init;

- (void) openMenu;

- (BOOL) addDeviceFromDetectedList:(NSString *)appearanceName authCode:(NSString *)authCode testInstance:(XCTestCase *)tc error:(NSString **)errorDescription;

- (BOOL) addDeviceFromDetectedList:(NSString *)uuid appearanceName:(NSString *)appearanceName authCode:(NSString *)authCode testInstance:(XCTestCase *)tc error:(NSString **)errorDescription;

- (BOOL) disassociateDeviceWithName : deviceNameOnListPage error: (NSString **)errorDescription;

- (BOOL) isDeviceDisplayedOnDevicesListScreen : (NSString *)appearanceName;

-(void) openConfigOfDeviceWithName : (NSString *) deviceNameOnListPage error : (NSString **) errorDescription;

- (void) openDeviceWithName: deviceAppearanceName error:(NSString **)errorDescription;

- (BOOL) isDevicesListScreenDisplayed;


@end
