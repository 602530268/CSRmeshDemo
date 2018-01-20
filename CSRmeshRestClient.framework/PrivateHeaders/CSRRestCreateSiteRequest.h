/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestSiteInfoObject.h"


/*!
    Request Object for creating site.
*/

@interface CSRRestCreateSiteRequest : CSRRestBaseObject


/*!
    State of Site. Transactions are not permitted for inactive sites.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestCreateSiteRequestStateEnum) {
  CSRRestCreateSiteRequestStateEnumactive,
  CSRRestCreateSiteRequestStateEnuminactive,

};



/*!
    Name of Site
*/
@property(nonatomic) NSString* name;
  
/*!
    State of Site. Transactions are not permitted for inactive sites.
*/
@property(nonatomic) CSRRestCreateSiteRequestStateEnum state;

/*!
    Array of mesh and respective gateways associated with the site.
*/
@property(nonatomic) NSArray* meshes;
  
/*!
  Constructs instance of CSRRestCreateSiteRequest

  @param name - (NSString*) Name of Site
  @param state - (CSRRestCreateSiteRequestStateEnum) State of Site. Transactions are not permitted for inactive sites.
  @param meshes - (NSArray*) Array of mesh and respective gateways associated with the site.
  
  @return instance of CSRRestCreateSiteRequest
*/
- (id) initWithname: (NSString*) name     
       state: (CSRRestCreateSiteRequestStateEnum) state     
       meshes: (NSArray*) meshes;
       

@end
