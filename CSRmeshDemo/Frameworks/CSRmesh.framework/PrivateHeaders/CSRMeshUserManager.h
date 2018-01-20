//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRMeshTenant.h"
#import "CSRMeshSite.h"
#import <CSRmeshRestClient/CSRRestConfig.h>

@protocol CSRMeshUserManagerDelegate;

/**
 @enum CSRBearerType - Command routing
 */
typedef NS_ENUM(NSInteger, CSRBearerType) {
    /** Bluetooth bearer type */
    CSRBearerType_Bluetooth,
    /** Cloud/Gateway bearer type */
    CSRBearerType_Cloud
};

/*!
 @class CSRMeshUser
 @abstract Singleton class that manages the current user
 @discussion The mesh user class implements the CSRMeshUserDelegate
 */
@interface CSRMeshUserManager : NSObject

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet *delegates;

/// @brief The current tenant
@property (nonatomic) CSRMeshTenant *tenant;

/// @brief The current site
@property (nonatomic) CSRMeshSite *site;

/// @brief The current meshId.
@property (nonatomic) NSString *meshId;

/// @brief The current applicationId.
@property (nonatomic) NSString *applicationId;

/// @brief The current bearer type
@property (nonatomic) CSRBearerType bearerType;

/*!
 @brief The singleton instance
 @return sharedInstance - The id of the singleton object.
 */
+ (CSRMeshUserManager *)sharedInstance;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive user events.
 */
- (void)addDelegate:(id<CSRMeshUserManagerDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive user events.
 */
- (void)removeDelegate:(id<CSRMeshUserManagerDelegate>)delegate;


/*!
 @brief Create a tenant for a given user.
 @param applicationCode A string that identifies the calling application
 @param username A string containing the username
 @param success callback block
 @param failure callback block
 */
- (void)createTenant:(NSString *)applicationCode
            username:(NSString *)username
             success:(void (^)(CSRMeshTenant *tenant))success
             failure:(void (^)(NSError *error))failure;


- (void)setTenant:(NSString *)applicationCode
         tenantId:(NSString *)tenantId
          success:(void (^)(CSRMeshTenant *tenant))success
          failure:(void (^)(NSError *error))failure;


/*!
 @brief Set up the rest client
 @param component
 @param uriScheme
 @param host
 @param port
 @param basePath
 */
- (void)setupCloud:(NSString *)uriScheme
              host:(NSString *)host
              port:(NSString *)port
          basePath:(NSString *)basePath
         serverURL:(CSRRestServerComponent)serverURL
connectionChannel:(CSRRestConnectionChannel) connectionChannel;


@end
