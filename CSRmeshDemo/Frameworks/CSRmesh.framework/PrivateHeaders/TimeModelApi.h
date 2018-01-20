//
// Copyright 2014 - 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Time Model is used to report the current time in order to synchronize the time among mesh network.
 */

@protocol TimeModelApiDelegate <NSObject>
@optional

/*!
 * @brief didGetTimeState. An acknowledgement to the request to (time)getState.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short wrapped up in an NSNumber.
 * @param timeInterval - (NSNumber *) The interval in seconds between time broadcasts as an unsigned short wrapped up in an NSNumber.
 * @param meshRequestId - (NSNumber *) The ID assigned to the Api call that triggered this callback.
 */
- (void)didGetTimeState:(NSNumber * _Nonnull)deviceId
           timeInterval:(NSNumber * _Nonnull)timeInterval
          meshRequestId:(NSNumber * _Nullable)meshRequestId;

@end

@interface TimeModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/**
 * @brief Set the desired number of seconds between time broadcasts.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @param timeInterval (NSNumber *) Interval in seconds between time broadcasts.
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable)setState:(NSNumber *)deviceId
                    timeInterval:(NSNumber *)timeInterval
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSNumber * _Nullable timeInterval))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/**
 * @brief Get the number of seconds between time broadcasts.
 * @param deviceId - (NSNumber *) The CSRMesh Network ID of this device as an unsigned short
 * @return Unique id to identify the request. Included in the response or timeout message.
 */
- (NSNumber * _Nullable)getState:(NSNumber *)deviceId
                         success:(void (^ _Nullable)(NSNumber * _Nullable deviceId,
                                                     NSNumber * _Nullable timeInterval))success
                         failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/**
 * @brief Broadcast the desired time to the mesh network.
 * @param currentTime - (NSNumber *) The current UTC time in milliseconds from 1970-01-01 00:00
 * @param timeZone - (NSNumber *) The time zone is the number of 15-minute increments from UTC. This is an 8-bit signed integer.
 * @param masterFlag - (NSNumber *) 1 if this message is from the clock master, 0 if it is not
 */
- (void)broadcastTimeWithCurrentTime:(NSNumber * _Nonnull)currentTime
                            timeZone:(NSNumber * _Nonnull)timeZone
                          masterFlag:(NSNumber * _Nonnull)masterFlag;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<TimeModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<TimeModelApiDelegate>)delegate;

@end

NS_ASSUME_NONNULL_END
