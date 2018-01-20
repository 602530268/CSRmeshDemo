/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
*/

@interface CSRRestRegisterRespOpcodesResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestRegisterRespOpcodesResponseStatusEnum) {
  CSRRestRegisterRespOpcodesResponseStatusEnumPending,
  CSRRestRegisterRespOpcodesResponseStatusEnumCompleted,
  CSRRestRegisterRespOpcodesResponseStatusEnumTimeOut,
  CSRRestRegisterRespOpcodesResponseStatusEnumFailure,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestRegisterRespOpcodesResponseStatusEnum status;

/*!
  Constructs instance of CSRRestRegisterRespOpcodesResponse

  @param status - (CSRRestRegisterRespOpcodesResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  
  @return instance of CSRRestRegisterRespOpcodesResponse
*/
- (id) initWithstatus: (CSRRestRegisterRespOpcodesResponseStatusEnum) status;
       

@end
