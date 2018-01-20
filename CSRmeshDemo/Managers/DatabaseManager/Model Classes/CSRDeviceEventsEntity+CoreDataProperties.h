//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRDeviceEventsEntity.h"

NS_ASSUME_NONNULL_BEGIN

@interface CSRDeviceEventsEntity (CoreDataProperties)

@property (nullable, nonatomic, retain) NSNumber *actionID;
@property (nullable, nonatomic, retain) NSNumber *deviceEventID;
@property (nullable, nonatomic, retain) NSNumber *deviceID;
@property (nullable, nonatomic, retain) NSNumber *eventRepeatMills;
@property (nullable, nonatomic, retain) NSNumber *eventTime;
@property (nullable, nonatomic, retain) CSREventEntity *events;

@end

NS_ASSUME_NONNULL_END
