/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestSiteInfoResponse.h"


/*!
    Response Object for Get Sites Call.
*/

@interface CSRRestGetSitesResponse : CSRRestBaseObject




/*!
    Array of all sites.
*/
@property(nonatomic) NSArray* sites;
  
/*!
    The page number of the response.
*/
@property(nonatomic) NSNumber* page;
  
/*!
    The page size of the response.
*/
@property(nonatomic) NSNumber* pageSize;
  
/*!
    Maximum number of results in the response.
*/
@property(nonatomic) NSNumber* maximumResults;
  
/*!
  Constructs instance of CSRRestGetSitesResponse

  @param sites - (NSArray*) Array of all sites.
  @param page - (NSNumber*) The page number of the response.
  @param pageSize - (NSNumber*) The page size of the response.
  @param maximumResults - (NSNumber*) Maximum number of results in the response.
  
  @return instance of CSRRestGetSitesResponse
*/
- (id) initWithsites: (NSArray*) sites     
       page: (NSNumber*) page     
       pageSize: (NSNumber*) pageSize     
       maximumResults: (NSNumber*) maximumResults;
       

@end
