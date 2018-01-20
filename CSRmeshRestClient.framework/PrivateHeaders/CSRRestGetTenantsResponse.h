/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestTenantInfoResponse.h"


/*!
    Response Object for Get Tenants Call
*/

@interface CSRRestGetTenantsResponse : CSRRestBaseObject




/*!
    Array of Tenants retrieved as per the query parameters.
*/
@property(nonatomic) NSArray* tenants;
  
/*!
    Page number of the response.
*/
@property(nonatomic) NSNumber* page;
  
/*!
    Page size of the response.
*/
@property(nonatomic) NSNumber* pageSize;
  
/*!
    Maximum number of results in the response.
*/
@property(nonatomic) NSNumber* maximumResults;
  
/*!
  Constructs instance of CSRRestGetTenantsResponse

  @param tenants - (NSArray*) Array of Tenants retrieved as per the query parameters.
  @param page - (NSNumber*) Page number of the response.
  @param pageSize - (NSNumber*) Page size of the response.
  @param maximumResults - (NSNumber*) Maximum number of results in the response.
  
  @return instance of CSRRestGetTenantsResponse
*/
- (id) initWithtenants: (NSArray*) tenants     
       page: (NSNumber*) page     
       pageSize: (NSNumber*) pageSize     
       maximumResults: (NSNumber*) maximumResults;
       

@end
