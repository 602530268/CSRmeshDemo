//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>
#import "CSRConstants.h"
#import <CSRmesh/MeshServiceApi.h>


@interface CSRmeshSettings : NSObject

+ (id) sharedInstance;

- (BleAutoConnectMode)getBleConnectMode;
- (void)setBleConnectMode:(BleAutoConnectMode)mode;
- (CSRBleListenMode)getBleListenMode;
- (void)setBleListenMode:(CSRBleListenMode)status;
- (void)setRetryInterval:(NSNumber *)interval;
- (void)setRetryCount:(NSNumber *)count;
- (void)setHostID:(NSNumber *)hostID;

- (void)setCloudTenancyID:(NSNumber*)tenancyId;
- (void)setCloudMeshID:(NSNumber*)meshId;


@end
