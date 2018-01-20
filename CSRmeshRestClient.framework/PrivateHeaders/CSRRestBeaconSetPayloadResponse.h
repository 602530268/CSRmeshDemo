/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestBeaconSetPayload.h"


/*!
    Response Object of SetPayload API for model Beacon
*/

@interface CSRRestBeaconSetPayloadResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconSetPayloadResponseStatusEnum) {
  CSRRestBeaconSetPayloadResponseStatusEnumPending,
  CSRRestBeaconSetPayloadResponseStatusEnumCompleted,
  CSRRestBeaconSetPayloadResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestBeaconSetPayloadResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Beacon SetPayload response object
*/
@property(nonatomic) NSArray* setPayload;
  
/*!
  Constructs instance of CSRRestBeaconSetPayloadResponse

  @param status - (CSRRestBeaconSetPayloadResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param setPayload - (NSArray*) The actual Beacon SetPayload response object
  
  @return instance of CSRRestBeaconSetPayloadResponse
*/
- (id) initWithstatus: (CSRRestBeaconSetPayloadResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       setPayload: (NSArray*) setPayload;
       

@end
