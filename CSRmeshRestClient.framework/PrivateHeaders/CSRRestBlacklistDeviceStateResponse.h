/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Response Object depicting Blacklisted Device State.
*/

@interface CSRRestBlacklistDeviceStateResponse : CSRRestBaseObject


/*!
    State of requested Blacklisted Device
*/
 typedef NS_OPTIONS(NSInteger, CSRRestBlacklistDeviceStateResponseStateEnum) {
  CSRRestBlacklistDeviceStateResponseStateEnumNot_Listed,
  CSRRestBlacklistDeviceStateResponseStateEnumReset_Not_Sent,
  CSRRestBlacklistDeviceStateResponseStateEnumReset_Sent,
  CSRRestBlacklistDeviceStateResponseStateEnumReset_Timedout,

};



/*!
    State of requested Blacklisted Device
*/
@property(nonatomic) CSRRestBlacklistDeviceStateResponseStateEnum state;


@property(nonatomic) NSNumber* timestamp;
  
/*!
  Constructs instance of CSRRestBlacklistDeviceStateResponse

  @param state - (CSRRestBlacklistDeviceStateResponseStateEnum) State of requested Blacklisted Device
  @param timestamp - (NSNumber*)
  
  @return instance of CSRRestBlacklistDeviceStateResponse
*/
- (id) initWithstate: (CSRRestBlacklistDeviceStateResponseStateEnum) state     
       timestamp: (NSNumber*) timestamp;
       

@end
