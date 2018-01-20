/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Watchdog Message response object
*/

@interface CSRRestWatchdogMessage : CSRRestBaseObject




/*!
    Size of any expected response
*/
@property(nonatomic) NSNumber* rspSize;
  
/*!
    Random data from a device: Because the RandomData field is encrypted, a passive eavesdropper will not be able to determine the contents of this message, compared with any other message. However, it is still good practice to use random contents in this field. Note: All messages are encrypted and the sequence number is unique even if the RandomData field is a constant value, so the transmitted data are different in each message. However, knowledge of this constant value will enable a possible known plain text attack, so the use of a constant value for the RandomData field is not recommended.
*/
@property(nonatomic) NSArray* randomData;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestWatchdogMessage

  @param rspSize - (NSNumber*) Size of any expected response
  @param randomData - (NSArray*) Random data from a device: Because the RandomData field is encrypted, a passive eavesdropper will not be able to determine the contents of this message, compared with any other message. However, it is still good practice to use random contents in this field. Note: All messages are encrypted and the sequence number is unique even if the RandomData field is a constant value, so the transmitted data are different in each message. However, knowledge of this constant value will enable a possible known plain text attack, so the use of a constant value for the RandomData field is not recommended.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestWatchdogMessage
*/
- (id) initWithrspSize: (NSNumber*) rspSize     
       randomData: (NSArray*) randomData     
       deviceId: (NSNumber*) deviceId;
       

@end
