//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "CSRPlaceEntity.h"
#import "CSRUserEntity.h"
#import "CSRGatewayEntity.h"
#import "CSRConstants.h"
#import <CSRmesh/MeshServiceApi.h>
#import <CSRmesh/CSRNetServiceBrowser.h>

typedef NS_ENUM(NSUInteger, CSRMeshRestEndpoint) {
    CSRMeshRestEndpoint_Cloud = 0,
    CSRMeshRestEndpoint_Gateway
};

typedef NS_ENUM(NSUInteger, CSRMeshRestMode) {
    CSRMeshRestMode_Config = 0,
    CSRMeshRestMode_CNC,
    CSRMeshRestMode_AUTH
};

typedef NS_ENUM(NSInteger, CSRSelectedBearerType) {
    CSRSelectedBearerType_Bluetooth,
    CSRSelectedBearerType_Gateway,
    CSRSelectedBearerType_Cloud
};



@interface CSRAppStateManager : NSObject <CSRNetServiceBrowserDelegate>

@property (nonatomic) UIColor *globalTintColor;
@property (nonatomic) CSRPlaceEntity *selectedPlace;
@property (nonatomic) CSRUserEntity *currentUser;
@property (nonatomic) CSRGatewayEntity *currentGateway;
@property (nonatomic) CSRSelectedBearerType bearerType;
@property (nonatomic) BOOL isBearerModeAutomatic;
@property (nonatomic) NSString *globalCloudHost;


//for importing datbase to place
//@property (nonatomic) BOOL isImportMode;

+ (CSRAppStateManager*)sharedInstance;

- (void)switchConnectionForSelectedBearerType:(CSRSelectedBearerType)bearerType;
- (void)setupCloudWithEndpoint:(CSRMeshRestEndpoint)endpoint withMode:(CSRMeshRestMode)mode;
- (void)createDefaultPlace;
- (void)setupPlace;
- (void)selectGatewayCommunicationChannel;
- (CSRUserEntity *)createUserForCurrentlyLoggedInUser;
- (NSArray *)getAvaialableBearersList;
- (void)connectivityCheck;

//SJ
- (void)callBonjour;

@end
