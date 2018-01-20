/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestActuatorTypes.h"


/*!
    Response Object of Types API for model Actuator
*/

@interface CSRRestActuatorTypesResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActuatorTypesResponseStatusEnum) {
  CSRRestActuatorTypesResponseStatusEnumPending,
  CSRRestActuatorTypesResponseStatusEnumCompleted,
  CSRRestActuatorTypesResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestActuatorTypesResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Actuator Types response object
*/
@property(nonatomic) NSArray* types;
  
/*!
  Constructs instance of CSRRestActuatorTypesResponse

  @param status - (CSRRestActuatorTypesResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param types - (NSArray*) The actual Actuator Types response object
  
  @return instance of CSRRestActuatorTypesResponse
*/
- (id) initWithstatus: (CSRRestActuatorTypesResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       types: (NSArray*) types;
       

@end
