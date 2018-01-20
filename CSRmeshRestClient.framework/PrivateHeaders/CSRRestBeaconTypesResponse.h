/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestBeaconTypes.h"


/*!
    Response Object of Types API for model Beacon
*/

@interface CSRRestBeaconTypesResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconTypesResponseStatusEnum) {
  CSRRestBeaconTypesResponseStatusEnumPending,
  CSRRestBeaconTypesResponseStatusEnumCompleted,
  CSRRestBeaconTypesResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestBeaconTypesResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Beacon Types response object
*/
@property(nonatomic) NSArray* types;
  
/*!
  Constructs instance of CSRRestBeaconTypesResponse

  @param status - (CSRRestBeaconTypesResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param types - (NSArray*) The actual Beacon Types response object
  
  @return instance of CSRRestBeaconTypesResponse
*/
- (id) initWithstatus: (CSRRestBeaconTypesResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       types: (NSArray*) types;
       

@end
