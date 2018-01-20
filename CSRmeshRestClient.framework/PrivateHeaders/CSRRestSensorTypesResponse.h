/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestSensorTypes.h"


/*!
    Response Object of Types API for model Sensor
*/

@interface CSRRestSensorTypesResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorTypesResponseStatusEnum) {
  CSRRestSensorTypesResponseStatusEnumPending,
  CSRRestSensorTypesResponseStatusEnumCompleted,
  CSRRestSensorTypesResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestSensorTypesResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Sensor Types response object
*/
@property(nonatomic) NSArray* types;
  
/*!
  Constructs instance of CSRRestSensorTypesResponse

  @param status - (CSRRestSensorTypesResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param types - (NSArray*) The actual Sensor Types response object
  
  @return instance of CSRRestSensorTypesResponse
*/
- (id) initWithstatus: (CSRRestSensorTypesResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       types: (NSArray*) types;
       

@end
