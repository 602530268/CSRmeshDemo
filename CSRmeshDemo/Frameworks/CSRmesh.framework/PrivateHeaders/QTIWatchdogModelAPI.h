@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

@protocol QTIWatchdogModelAPIDelegate <NSObject>

@optional

- (NSNumber *)didGetMessage:(NSNumber *)deviceId
                    rspSize:(uint8_t)rspSize
                 randomData:(NSData *)randomData;
- (NSNumber *)didGetInterval:(NSNumber *)deviceId
                    interval:(uint16_t)interval
             activeAfterTime:(uint16_t)activeAfterTime
               meshRequestId:(NSNumber *)meshRequestId;

@end

@interface QTIWatchdogModelAPI : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/*!
 * Upon receiving a WATCHDOG_MESSAGE message, if the RspSize field is set to a non-zero value, then the device shall respond with a WATCHDOG_MESSAGE with the RspSize field set to zero, and RspSize -1 octets of additional RandomData.
 * @param rspSize - (uint8_t) Size of any expected response
 * @param randomData - (NSData *) Random data from a device: Because the RandomData field is encrypted, a passive eavesdropper will not be able to determine the contents of this message, compared with any other message. However, it is still good practice to use random contents in this field. Note: All messages are encrypted and the sequence number is unique even if the RandomData field is a constant value, so the transmitted data are different in each message. However, knowledge of this constant value will enable a possible known plain text attack, so the use of a constant value for the RandomData field is not recommended.
 */
- (NSNumber * _Nullable)setMessage:(NSNumber *)deviceId
                           rspSize:(uint8_t)rspSize
                        randomData:(NSData *)randomData;

/*!
 * @breif setInterval - Upon receiving a WATCHDOG_SET_INTERVAL message, the device shall save the Interval and ActiveAfterTime fields into the Interval and ActiveAfterTime variables and respond with a WATCHDOG_INTERVAL message with the current variable values.
 * @param interval - (uint16_t) The watchdog Interval being set in seconds and indicates the maximum interval that watchdog messages should be sent.
 * @param activeAfterTime - (uint16_t) The watchdog ActiveAfterTime being set in seconds that indicates the period of time that a device will listen for responses after sending a watchdog message.
 * @return BOOL - YES if the command needs a TID/
 */
- (NSNumber * _Nullable)setInterval:(NSNumber *)deviceId
                           interval:(uint16_t)interval
                    activeAfterTime:(uint16_t)activeAfterTime
                            success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                        uint16_t interval,
                                                        uint16_t activeAfterTime))success
                            failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<QTIWatchdogModelAPIDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<QTIWatchdogModelAPIDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END

