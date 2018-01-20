//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import <CSRmesh/MeshServiceApi.h>
#import <CSRmesh/AttentionModelApi.h>
#import <CSRmesh/BearerModelApi.h>
#import <CSRmesh/ConfigModelApi.h>
#import <CSRmesh/MeshServiceApi.h>
#import <CSRmesh/FirmwareModelApi.h>
#import <CSRmesh/GroupModelApi.h>
#import <CSRmesh/LightModelApi.h>
#import <CSRmesh/PowerModelApi.h>
#import <CSRmesh/DataModelApi.h>
#import <CSRmesh/PingModelApi.h>
#import <CSRmesh/BatteryModelApi.h>
#import <CSRmesh/SensorModelApi.h>
#import <CSRmesh/ActuatorModelApi.h>


@interface CSRmeshManager : NSObject <MeshServiceApiDelegate, AttentionModelApiDelegate, BearerModelApiDelegate, ConfigModelApiDelegate, MeshServiceApiDelegate, FirmwareModelApiDelegate, GroupModelApiDelegate, LightModelApiDelegate, PowerModelApiDelegate, DataModelApiDelegate, PingModelApiDelegate, BatteryModelApiDelegate, SensorModelApiDelegate, ActuatorModelApiDelegate>

+ (id) sharedInstance;
- (void)setUpDelegates;

@end
