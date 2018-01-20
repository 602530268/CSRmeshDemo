//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRMeshTenant.h"

@interface CSRMeshSite : NSObject

/// @brief tenant Link to parent object
@property CSRMeshTenant *tenant;

/// @brief siteId The site id
@property NSString *siteId;

/// @brief name The readable site name
@property NSString *name;


/// @brief meshes A list of meshes available at the site
@property NSMutableArray *meshes;

/*!
 @brief Initialise a site with some data
 @param tenantObject Parent object
 @param site The site id
 @param siteName The readable site name
 @param state The site state
 */
- (id)initWith:(CSRMeshTenant *)tenantObject
          site:(NSString *)site
      siteName:(NSString *)siteName
         state:(NSString *)state;

/*!
 @brief Update the site on the cloud. Note that the meshes will be updated too
 @param applicationCode A string that identifies the calling application
 @param siteName The new site name
 @param success The success block
 @param failure The failure block
 */
- (void)updateSite:(NSString *)applicationCode
          siteName:(NSString *)siteName
           success:(void (^)(NSNumber *meshRequestId))success
           failure:(void (^)(NSError *error))failure;

/*!
 @brief Delete the site on the cloud
 @param success The success block
 @param failure The failure block
 */
- (void)deleteSite:(void (^)(NSNumber *meshRequestId))success
           failure:(void (^)(NSError *error))failure;

@end
