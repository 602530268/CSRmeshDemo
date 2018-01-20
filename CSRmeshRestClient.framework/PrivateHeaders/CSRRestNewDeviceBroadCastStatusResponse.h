/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestErrorInfo.h"


/*!
    Response Object new device broadcast
*/

@interface CSRRestNewDeviceBroadCastStatusResponse : CSRRestBaseObject


/*!
    MASP Association flow state.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestNewDeviceBroadCastStatusResponseAssocFlowStateEnum) {
  CSRRestNewDeviceBroadCastStatusResponseAssocFlowStateEnumnot_started,
  CSRRestNewDeviceBroadCastStatusResponseAssocFlowStateEnuminitiated,
  CSRRestNewDeviceBroadCastStatusResponseAssocFlowStateEnumin_progress,
  CSRRestNewDeviceBroadCastStatusResponseAssocFlowStateEnumcomplete,
  CSRRestNewDeviceBroadCastStatusResponseAssocFlowStateEnumfailed,

};



/*!
    MASP Association flow state.
*/
@property(nonatomic) CSRRestNewDeviceBroadCastStatusResponseAssocFlowStateEnum assocFlowState;

/*!
    If association state is failed, additional information in the form of errors (error codes with corresponding error messages) is provided.
*/
@property(nonatomic) NSArray* errorCodes;
  
/*!
    UTC timestamp of occurrence of state
*/
@property(nonatomic) NSNumber* timestamp;
  
/*!
  Constructs instance of CSRRestNewDeviceBroadCastStatusResponse

  @param assocFlowState - (CSRRestNewDeviceBroadCastStatusResponseAssocFlowStateEnum) MASP Association flow state.
  @param errorCodes - (NSArray*) If association state is failed, additional information in the form of errors (error codes with corresponding error messages) is provided.
  @param timestamp - (NSNumber*) UTC timestamp of occurrence of state
  
  @return instance of CSRRestNewDeviceBroadCastStatusResponse
*/
- (id) initWithassocFlowState: (CSRRestNewDeviceBroadCastStatusResponseAssocFlowStateEnum) assocFlowState     
       errorCodes: (NSArray*) errorCodes     
       timestamp: (NSNumber*) timestamp;
       

@end
