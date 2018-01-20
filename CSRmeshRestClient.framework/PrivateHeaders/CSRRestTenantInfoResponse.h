/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Info Object of tenant returned as part of Get Tenant call
*/

@interface CSRRestTenantInfoResponse : CSRRestBaseObject




/*!
    Tenant ID
*/
@property(nonatomic) NSString* tenantId;
  
/*!
    Name of Tenant
*/
@property(nonatomic) NSString* name;
  
/*!
    State of Tenant.
*/
@property(nonatomic) NSString* state;
  
/*!
  Constructs instance of CSRRestTenantInfoResponse

  @param tenantId - (NSString*) Tenant ID
  @param name - (NSString*) Name of Tenant
  @param state - (NSString*) State of Tenant.
  
  @return instance of CSRRestTenantInfoResponse
*/
- (id) initWithtenantId: (NSString*) tenantId     
       name: (NSString*) name     
       state: (NSString*) state;
       

@end
