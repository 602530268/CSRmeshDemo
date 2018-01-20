/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestConfigDeviceIdentifier.h"


/*!
    Response Object of DeviceIdentifier API for model Config
*/

@interface CSRRestConfigDeviceIdentifierResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestConfigDeviceIdentifierResponseStatusEnum) {
  CSRRestConfigDeviceIdentifierResponseStatusEnumPending,
  CSRRestConfigDeviceIdentifierResponseStatusEnumCompleted,
  CSRRestConfigDeviceIdentifierResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestConfigDeviceIdentifierResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Config DeviceIdentifier response object
*/
@property(nonatomic) NSArray* deviceIdentifier;
  
/*!
  Constructs instance of CSRRestConfigDeviceIdentifierResponse

  @param status - (CSRRestConfigDeviceIdentifierResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param deviceIdentifier - (NSArray*) The actual Config DeviceIdentifier response object
  
  @return instance of CSRRestConfigDeviceIdentifierResponse
*/
- (id) initWithstatus: (CSRRestConfigDeviceIdentifierResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       deviceIdentifier: (NSArray*) deviceIdentifier;
       

@end
