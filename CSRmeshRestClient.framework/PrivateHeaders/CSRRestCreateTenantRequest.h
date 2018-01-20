/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for Creating Tenant.
*/

@interface CSRRestCreateTenantRequest : CSRRestBaseObject


/*!
    State of Tenant.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestCreateTenantRequestStateEnum) {
  CSRRestCreateTenantRequestStateEnumactive,
  CSRRestCreateTenantRequestStateEnuminactive,

};



/*!
    Unique Name of Tenant
*/
@property(nonatomic) NSString* name;
  
/*!
    State of Tenant.
*/
@property(nonatomic) CSRRestCreateTenantRequestStateEnum state;

/*!
  Constructs instance of CSRRestCreateTenantRequest

  @param name - (NSString*) Unique Name of Tenant
  @param state - (CSRRestCreateTenantRequestStateEnum) State of Tenant.
  
  @return instance of CSRRestCreateTenantRequest
*/
- (id) initWithname: (NSString*) name     
       state: (CSRRestCreateTenantRequestStateEnum) state;
       

@end
