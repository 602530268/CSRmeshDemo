//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "CSRmeshDevice.h"
#import "CSRmeshArea.h"
#import <CSRmesh/MeshServiceApi.h>
#import <CSRmesh/ConfigModelApi.h>
#import <CSRmesh/GroupModelApi.h>
#import <CSRmesh/SensorModelApi.h>
#import <CSRmesh/LightModelApi.h>
#import <CSRmesh/PowerModelApi.h>
#import "CSRAreaEntity.h"

@interface CSRDevicesManager : NSObject <SensorModelApiDelegate>

//old
@property (strong, atomic) NSNumber *areaId;
@property (strong, atomic) NSNumber *deviceIdNumber;
//new
@property (atomic, strong) NSString *siteId;
@property (atomic, strong) NSString *userId;

// Array of mesh devices & Groups
@property (nonatomic) NSMutableArray *unassociatedMeshDevices;
@property (nonatomic) NSMutableArray *scannedMeshDevices;
@property (nonatomic) NSMutableArray *meshDevices;
@property (nonatomic) NSMutableArray *meshAreas;

// Discovered devices, indexed by DeviceId, UUID, Shortcode
@property (strong, atomic) NSMutableDictionary *deviceDictionary;

// mesh objects
//@property (strong, atomic) CSRmeshArea *allDevicesArea;
@property (strong, atomic) CSRmeshDevice *selectedDevice;
@property (weak, nonatomic) CSRmeshArea *selectedArea;

@property (assign, nonatomic) BOOL isDeviceTypeGateway;

+ (CSRDevicesManager*)sharedInstance;
- (id) init;

//create device and group
-(void) createDeviceFromProperties : (NSDictionary *) deviceProperties;
-(void) createAreaFromProperties : (NSDictionary *) areaProperties;


-(CSRmeshDevice *) didAssociateDevice :(NSNumber *) deviceId deviceHash :(NSData *) deviceHash;

//get total number of groups and devices
- (NSInteger) getTotalAssociatedDevices;
- (NSInteger) getTotalAreas;
- (CSRmeshDevice*)getAllDevices;

- (void) deleteDevicesInArray;

- (CSRAreaEntity*) addMeshArea:(NSString*)name;

//Get mesh device and mesh group object
- (CSRmeshArea *) getArea :(NSInteger) offset;
- (CSRmeshDevice *) getDeviceFromAssociatedList :(NSInteger) offset;

- (CSRmeshArea *) getAreaFromId :(NSNumber *) groupIdNumber;

- (CSRmeshDevice *) addDeviceWithUUID:(CBUUID *)uuid andRSSI:(NSNumber *)rssi;
- (CSRmeshDevice *) addDeviceWithDeviceHash :(NSData *) deviceHash authCode:(NSData *) authCode;
- (CSRmeshDevice *) getDeviceFromDeviceId :(NSNumber *) deviceId;

- (NSArray*) getMeshDevicesArray;

-(void) setDeviceDiscoveryFilter:(id)obj mode:(BOOL) mode;

-(void) updateAppearance :(NSData *) deviceHash appearanceValue:(NSNumber *) appearanceValue shortName:(NSData *) shortName;
-(void) updateDeviceAssociationInfo :(NSData *) deviceHash withStepsCompleted:(NSNumber *) stepsCompleted ofTotalSteps:(NSNumber *) totalSteps;

- (CSRmeshDevice *)checkPreviouslyScannedDevicesWithDeviceHash:(NSData*)deviceHash;

- (CSRmeshDevice *)getDeviceWithDevicePredicate:(NSData*)value;
- (void)addScannedDevice:(CSRmeshDevice*)mDevice;

#pragma mark Remove Devices
-(void) initiateRemoveDevice :(CSRmeshDevice *) meshDevice;

#pragma mark Remove Areas
- (void) removeAreaWithAreaId:(NSNumber*)areaId;

#pragma mark Remove Events
- (void) removeEventWithEventId:(NSNumber*)eventId;

//--------------Temp Control--------------
-(void) setDesiredTemperatureForArea :(CSRmeshArea *) meshArea;

#pragma mark Library calls
- (void)associateDeviceFromCSRDeviceManager:(NSData *)deviceHash authorisationCode:(NSData *)authCode;
//double add,手动指定deviceID，所有设备同时连接，加快连接速度
- (void)new_associateDeviceFromCSRDeviceManager:(NSData *)deviceHash authorisationCode:(NSData *)authCode deviceId:(NSNumber *)deviceId;

- (void)getModelsAndGroupsCall:(NSNumber *)deviceId infoType:(NSNumber *)infoType;
- (void)setDeviceDiscoveryFilterEnabled:(BOOL)enabled;
- (void)setAttention:(NSData *)deviceHash attentionState:(NSNumber *)attentionState withDuration:(NSNumber *) duration;
- (void)getNumberOfModelGroupIds:(NSNumber *)deviceId modelNo:(NSNumber *)modelNo;
- (void)setSiteID:(NSString *) siteID;

- (void)setNetworkPassPhrase:(NSString *)passPhrase;
- (void)setNetworkKey:(NSData *)networkKey;

-(void) setAttentionPreAssociation:(NSData *)deviceHash attentionState:(NSNumber *)attentionState withDuration:(NSNumber *) duration;

//-(void) resetDevice:(NSNumber *)deviceId;
-(void) removeDevice :(CSRmeshDevice *) meshDevice;
-(void) didResetDevice :(NSNumber *) deviceId;
- (void) setNextDeviceID:(NSNumber *)deviceNo;

- (id)getStateForDeviceWithId:(NSNumber *)deviceId;

- (void) setColor:(NSNumber*)deviceId color:(UIColor*)actualColor duration:(NSNumber*)duration;
- (void) setWhite:(NSNumber *)deviceId level:(NSNumber *)level duration:(NSNumber *)duration;
- (void) setColorTemperature:(NSNumber *)deviceId temperature:(NSNumber *)temperature duration:(NSNumber *)duration;

- (void) setPowerState:(NSNumber *)deviceId state:(NSNumber *)state;


@end
