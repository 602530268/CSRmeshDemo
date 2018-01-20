/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestFirmwareVersion.h"


/*!
    Response Object of Version API for model Firmware
*/

@interface CSRRestFirmwareVersionResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestFirmwareVersionResponseStatusEnum) {
  CSRRestFirmwareVersionResponseStatusEnumPending,
  CSRRestFirmwareVersionResponseStatusEnumCompleted,
  CSRRestFirmwareVersionResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestFirmwareVersionResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Firmware Version response object
*/
@property(nonatomic) NSArray* version;
  
/*!
  Constructs instance of CSRRestFirmwareVersionResponse

  @param status - (CSRRestFirmwareVersionResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param version - (NSArray*) The actual Firmware Version response object
  
  @return instance of CSRRestFirmwareVersionResponse
*/
- (id) initWithstatus: (CSRRestFirmwareVersionResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       version: (NSArray*) version;
       

@end
