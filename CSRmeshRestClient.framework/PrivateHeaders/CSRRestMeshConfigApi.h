/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBlacklistDeviceRequest.h"
#import "CSRRestGetTenantsResponse.h"
#import "CSRRestCreateTenantRequest.h"
#import "CSRRestCreateTenantResponse.h"
#import "CSRRestTenantInfoResponse.h"
#import "CSRRestUpdateTenantInfoRequest.h"
#import "CSRRestCreateFileResponse.h"
#import "CSRRestGetFileResponse.h"
#import "CSRRestCreateFileRequest.h"
#import "CSRRestGetSitesResponse.h"
#import "CSRRestCreateSiteRequest.h"
#import "CSRRestCreateSiteResponse.h"
#import "CSRRestSiteInfoResponse.h"
#import "CSRRestUpdateSiteInfoRequest.h"
#import "CSRRestBaseObject.h"
#import "CSRRestApiStatusCode.h"
#import "CSRRestErrorResponse.h"
#import "CSRRestBaseApi.h"


/*!
  CSRRestMeshConfigApi is a part of the CSR Mesh Api and provides a set of related methods.
*/
@interface CSRRestMeshConfigApi: CSRRestBaseApi


/*!
  Blacklist a device
 
  This API is used to black list specified device. Specified device will be sent a CONFIG_RESET as soon as it is detected in mesh network in future, to erase network keys and its association status.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param siteId - (NSString*)  Site ID.
  @param meshId - (NSString*)  Mesh ID.
  @param deviceId - (NSString*)  Device ID which needs to be blacklisted.
  @param action - (NSString*) [optional] This value can be either add or cancel. Add / cancel blacklisting request for this device. Default value is add.
  @param validity - (NSNumber*) [optional] Validity for the add action in minutes. If not specified, or value 0 is provided, black listing should be tried indefinitely.
  @param blacklistDeviceRequest - (CSRRestBlacklistDeviceRequest*) [optional] Request Object for taking action pertaining to blacklisting of a device.
  @param responseBlock An optional block which receives the results of the resource load.
          If success, error object will be nil. If failure a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) blacklistDevice : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     siteId : (NSString*) siteId 
     meshId : (NSString*) meshId 
     deviceId : (NSString*) deviceId 
     action : (NSString*) action 
     validity : (NSNumber*) validity 
     blacklistDeviceRequest : (CSRRestBlacklistDeviceRequest*) blacklistDeviceRequest 
     responseHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get Tenant List
 
  This API retrieves a list of tenants for a solution.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param queryType - (NSString*)  Type of Query.
  @param pattern - (NSString*) [optional] URL encoded regular expression for pattern matching, applicable only if query_type field value is query_by_name.
  @param state - (NSString*) [optional] State of Tenant.
  @param pageSize - (NSNumber*) [optional] Maximum number of results to be returned in a page.
  @param page - (NSNumber*) [optional] Page number (starting at 0) to return.
  @param maximum - (NSNumber*) [optional] Maximum number of results to return.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestGetTenantsResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestGetTenantsResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getTenants : (NSString*) csrmeshApplicationCode 
     queryType : (NSString*) queryType 
     pattern : (NSString*) pattern 
     state : (NSString*) state 
     pageSize : (NSNumber*) pageSize 
     page : (NSNumber*) page 
     maximum : (NSNumber*) maximum 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestGetTenantsResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Create Tenant
 
  This API creates a tenant for a solution.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param createTenantRequest - (CSRRestCreateTenantRequest*)  Request Object for creating tenant.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestCreateTenantResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestCreateTenantResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) createTenant : (NSString*) csrmeshApplicationCode 
     createTenantRequest : (CSRRestCreateTenantRequest*) createTenantRequest 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestCreateTenantResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get Tenant Information
 
  This API retrieves information for a tenant.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestTenantInfoResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestTenantInfoResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getTenantInfo : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestTenantInfoResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Create Tenant
 
  This API creates a tenant with a predefined Tenant ID.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param createTenantRequest - (CSRRestCreateTenantRequest*)  Request Object for creating tenant.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestCreateTenantResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestCreateTenantResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) createTenant : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     createTenantRequest : (CSRRestCreateTenantRequest*) createTenantRequest 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestCreateTenantResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Delete Tenant
 
  This API deletes a tenant.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param responseBlock An optional block which receives the results of the resource load.
          If success, error object will be nil. If failure a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) deleteTenant : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     responseHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Update Tenant Information
 
  This API updates information for a tenant.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param updateTenantInfoRequest - (CSRRestUpdateTenantInfoRequest*)  Request Object for updating tenant information.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestTenantInfoResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestTenantInfoResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) updateTenant : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     updateTenantInfoRequest : (CSRRestUpdateTenantInfoRequest*) updateTenantInfoRequest 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestTenantInfoResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get File Information
 
  This API retrieves information for a file.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param fileName - (NSString*)  File name.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestCreateFileResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestCreateFileResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getFileInfo : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     fileName : (NSString*) fileName 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestCreateFileResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get a File content
 
  This API retrieves content of a file.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param fileName - (NSString*)  File name.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestGetFileResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestGetFileResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getFile : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     fileName : (NSString*) fileName 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestGetFileResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Upload a file
 
  This API creates a file specific to tenant ID.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param contentLength - (NSString*)  HTTP Request header, Content - Length must be supplied and should be set to the size of uploaded file in byte.
  @param tenantId - (NSString*)  Tenant ID.
  @param fileName - (NSString*)  File name.
  @param overwrite - (NSNumber*) [optional] This value, either true (default) or false, determines whether an existing file will be overwritten by this upload.  If true, any existing file will be overwritten.If false, the other parameters determine whether a conflict occurs and how that conflict is resolved.
  @param parentRev - (NSString*) [optional] If present, this parameter specifies the revision of the file you're editing. If parent_rev matches (or is higher than) the latest version of the file on gateway,that file will be replaced. Otherwise, a conflict will occur.
  @param deletionPolicy - (NSString*) [optional] This parameter specifies how this file should be deleted from gateway, following are possible values - manual: (Default) file not to be deleted automatically, it should only be deleted on application's DELETE request. This should be used for DB file shared by mobile. - auto: file should be automatically deleted by gateway after a predefined time period. This should be used for files uploaded for device firmware update.
  @param createFileRequest - (CSRRestCreateFileRequest*)  Request Object for creating file.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestCreateFileResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestCreateFileResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) createFile : (NSString*) csrmeshApplicationCode 
     contentLength : (NSString*) contentLength 
     tenantId : (NSString*) tenantId 
     fileName : (NSString*) fileName 
     overwrite : (NSNumber*) overwrite 
     parentRev : (NSString*) parentRev 
     deletionPolicy : (NSString*) deletionPolicy 
     createFileRequest : (CSRRestCreateFileRequest*) createFileRequest 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestCreateFileResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Delete File
 
  This API deletes a file.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param fileName - (NSString*)  file name.
  @param responseBlock An optional block which receives the results of the resource load.
          If success, error object will be nil. If failure a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) deleteFile : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     fileName : (NSString*) fileName 
     responseHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get all Sites
 
  This API retrieves all sites for a tenant.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param queryType - (NSString*)  Type of Query.
  @param pattern - (NSString*) [optional] URL encoded regular expression for pattern matching. This parameter is only applicable if query_type field value is query_by_name.
  @param state - (NSString*) [optional] State of Site.
  @param pageSize - (NSNumber*) [optional] Maximum number of results to be returned in a page.
  @param page - (NSNumber*) [optional] Page number (starting at 0) to return.
  @param maximum - (NSNumber*) [optional] Maximum number of results to return.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestGetSitesResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestGetSitesResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getSites : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     queryType : (NSString*) queryType 
     pattern : (NSString*) pattern 
     state : (NSString*) state 
     pageSize : (NSNumber*) pageSize 
     page : (NSNumber*) page 
     maximum : (NSNumber*) maximum 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestGetSitesResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Create Site
 
  This API creates a site for a tenant.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param createSiteRequest - (CSRRestCreateSiteRequest*)  Request Object for creating tenant.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestCreateSiteResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestCreateSiteResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) createSite : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     createSiteRequest : (CSRRestCreateSiteRequest*) createSiteRequest 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestCreateSiteResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Get Site Information
 
  This API retrieves information for a site.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param siteId - (NSString*)  Site ID.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestSiteInfoResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestSiteInfoResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) getSiteInfo : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     siteId : (NSString*) siteId 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestSiteInfoResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Create Site
 
  This API creates a site with a predefined Site ID.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param siteId - (NSString*)  Site ID.
  @param createSiteRequest - (CSRRestCreateSiteRequest*)  Request Object for creating tenant.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestCreateSiteResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestCreateSiteResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) createSite : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     siteId : (NSString*) siteId 
     createSiteRequest : (CSRRestCreateSiteRequest*) createSiteRequest 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestCreateSiteResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Delete Site
 
  This API deletes a site.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param siteId - (NSString*)  Site ID.
  @param responseBlock An optional block which receives the results of the resource load.
          If success, error object will be nil. If failure a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) deleteSite : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     siteId : (NSString*) siteId 
     responseHandler :(void (^)(NSNumber* meshRequestId,NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



/*!
  Update Site Information
 
  This API updates information for a site.
 
  @param csrmeshApplicationCode - (NSString*)  Application Code of calling application.
  @param tenantId - (NSString*)  Tenant ID.
  @param siteId - (NSString*)  Site ID.
  @param updateSiteInfoRequest - (CSRRestUpdateSiteInfoRequest*)  Request Object for Updating Application Information.
  @param responseBlock An optional block which receives the results of the resource load.
         If success, a valid object of CSRRestSiteInfoResponse is returned with nil object of NSError and CSRRestErrorResponse.
         If failure, an error object of NSError is returned with nil object of CSRRestSiteInfoResponse and also  a detailed error object of CSRRestErrorResponse for specific error codes and messages may available. See CSRRestApiStatusCode and NSError+StatusCode for more information's on error code details.

  @return meshRequestId - (NSNumber*) The id of the request. Pair up with the id returned in callback handlers.
 */
- (NSNumber*) updateSite : (NSString*) csrmeshApplicationCode 
     tenantId : (NSString*) tenantId 
     siteId : (NSString*) siteId 
     updateSiteInfoRequest : (CSRRestUpdateSiteInfoRequest*) updateSiteInfoRequest 
     responseHandler :(void (^)(NSNumber* meshRequestId, CSRRestSiteInfoResponse* output, NSError* error, CSRRestErrorResponse* errorResponse))responseBlock;



@end
