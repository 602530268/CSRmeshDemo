/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual ObjectTransfer response object
*/

@interface CSRRestObjectTransfer : CSRRestBaseObject


/*!
    The current status of device for which object transfer was sent.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestObjectTransferStatusEnum) {
  CSRRestObjectTransferStatusEnumsuccess,
  CSRRestObjectTransferStatusEnumin_progress,
  CSRRestObjectTransferStatusEnumfailure,

};



/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
    The current status of device for which object transfer was sent.
*/
@property(nonatomic) CSRRestObjectTransferStatusEnum status;

/*!
  Constructs instance of CSRRestObjectTransfer

  @param deviceId - (NSNumber*) Id of the responding device
  @param status - (CSRRestObjectTransferStatusEnum) The current status of device for which object transfer was sent.
  
  @return instance of CSRRestObjectTransfer
*/
- (id) initWithdeviceId: (NSNumber*) deviceId     
       status: (CSRRestObjectTransferStatusEnum) status;
       

@end
