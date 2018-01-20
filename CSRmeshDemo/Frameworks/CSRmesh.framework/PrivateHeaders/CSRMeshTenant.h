//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;

@interface CSRMeshTenant : NSObject

/// @brief The current tenant id
@property NSString *tenantId;

/// @brief The current user name
@property NSString *name;

/// @brief The sites associated with this tenant
@property NSMutableArray *sites;

/*!
 @brief Initialise an instance of site
 @param name The site or place name
 @param state The state of the site.
 */
- (id)initWith:(NSString *)tenant
          name:(NSString *)name
         state:(NSString *)state;

/*!
 @brief Create a site using the current tenant.
 @param applicationCode A string that identifies the calling application
 @param siteName The site or place name
 @param meshId This will be an hmac of the network key and secret key
 @param gatewayUUIDs An array of gateway UUIDs (From Bonjour @see CSRGatewayNetService)
 */
- (void)createSite:(NSString *)applicationCode
          siteName:(NSString *)siteName
            meshId:(NSString *)meshId
      gatewayUUIDs:(NSArray *)gatewayUUIDs
           success:(void (^)(NSString *siteId))success
           failure:(void (^)(NSError *error))failure;

- (void)setSite:(NSString *)applicationCode
         siteId:(NSString *)siteId
         meshId:(NSString *)meshId
   gatewayUUIDs:(NSArray *)gatewayUUIDs
        success:(void (^)(NSString *siteId))success
        failure:(void (^)(NSError *error))failure;

/*!
 @brief Create a site for the current user.
 @param applicationCode A string that identifies the calling application
 @param siteName The site or place name
 @param success callback block
 @param failure callback block
 */
- (void)createSite:(NSString *)applicationCode
          siteName:(NSString *)siteName
           success:(void (^)(NSString *siteId))success
           failure:(void (^)(NSError *error))failure;

- (void)setSite:(NSString *)applicationCode
         siteId:(NSString *)siteId
        success:(void (^)(NSString *siteId))success
        failure:(void (^)(NSError *error))failure;


/*!
 @brief Populate the list of sites for the currant tenant from the cloud.
 @param applicationCode A string that identifies the calling application
 @param success callback block
 @param failure callback block
 */
- (void)getSites:(NSString *)applicationCode
        siteName:(NSString *)siteName
         success:(void (^)(NSNumber *meshRequestId))success
         failure:(void (^)(NSError *error))failure;

/*!
 @brief Delete the current tenant.
 @param success callback block
 @param failure callback block
 */
- (void)deleteTenant:(void (^)(NSNumber *meshRequestId))success
             failure:(void (^)(NSError *error))failure;

@end
