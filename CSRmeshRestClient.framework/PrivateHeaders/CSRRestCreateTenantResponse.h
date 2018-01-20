/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Response Object post Tenant Creation
*/

@interface CSRRestCreateTenantResponse : CSRRestBaseObject




/*!
    Created Tenant ID
*/
@property(nonatomic) NSString* tenantId;
  
/*!
  Constructs instance of CSRRestCreateTenantResponse

  @param tenantId - (NSString*) Created Tenant ID
  
  @return instance of CSRRestCreateTenantResponse
*/
- (id) initWithtenantId: (NSString*) tenantId;
       

@end
