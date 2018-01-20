//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSREventEntity.h"

NS_ASSUME_NONNULL_BEGIN

@interface CSREventEntity (CoreDataProperties)

@property (nullable, nonatomic, retain) NSNumber *eventActive;
@property (nullable, nonatomic, retain) NSNumber *eventid;
@property (nullable, nonatomic, retain) NSString *eventName;
@property (nullable, nonatomic, retain) NSNumber *eventRepeatType;
@property (nullable, nonatomic, retain) NSNumber *eventType;
@property (nullable, nonatomic, retain) NSData *eventValue;
@property (nullable, nonatomic, retain) NSSet<CSRDeviceEventsEntity *> *deviceEvents;
@property (nullable, nonatomic, retain) NSSet<CSRDeviceEntity *> *devices;

@end

@interface CSREventEntity (CoreDataGeneratedAccessors)

- (void)addDeviceEventsObject:(CSRDeviceEventsEntity *)value;
- (void)removeDeviceEventsObject:(CSRDeviceEventsEntity *)value;
- (void)addDeviceEvents:(NSSet<CSRDeviceEventsEntity *> *)values;
- (void)removeDeviceEvents:(NSSet<CSRDeviceEventsEntity *> *)values;

- (void)addDevicesObject:(CSRDeviceEntity *)value;
- (void)removeDevicesObject:(CSRDeviceEntity *)value;
- (void)addDevices:(NSSet<CSRDeviceEntity *> *)values;
- (void)removeDevices:(NSSet<CSRDeviceEntity *> *)values;

@end

NS_ASSUME_NONNULL_END
