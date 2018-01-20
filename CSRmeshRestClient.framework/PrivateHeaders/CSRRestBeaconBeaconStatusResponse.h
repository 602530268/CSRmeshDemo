/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestBeaconBeaconStatus.h"


/*!
    Response Object of BeaconStatus API for model Beacon
*/

@interface CSRRestBeaconBeaconStatusResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBeaconBeaconStatusResponseStatusEnum) {
  CSRRestBeaconBeaconStatusResponseStatusEnumPending,
  CSRRestBeaconBeaconStatusResponseStatusEnumCompleted,
  CSRRestBeaconBeaconStatusResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestBeaconBeaconStatusResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Beacon BeaconStatus response object
*/
@property(nonatomic) NSArray* beaconStatus;
  
/*!
  Constructs instance of CSRRestBeaconBeaconStatusResponse

  @param status - (CSRRestBeaconBeaconStatusResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param beaconStatus - (NSArray*) The actual Beacon BeaconStatus response object
  
  @return instance of CSRRestBeaconBeaconStatusResponse
*/
- (id) initWithstatus: (CSRRestBeaconBeaconStatusResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       beaconStatus: (NSArray*) beaconStatus;
       

@end
