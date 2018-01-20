//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import "CSRGatewayEntity.h"

NS_ASSUME_NONNULL_BEGIN

@interface CSRGatewayEntity (CoreDataProperties)

@property (nullable, nonatomic, retain) NSString *basePath;
@property (nullable, nonatomic, retain) NSData *deviceHash;
@property (nullable, nonatomic, retain) NSNumber *deviceId;
@property (nullable, nonatomic, retain) NSString *host;
@property (nullable, nonatomic, retain) NSString *name;
@property (nullable, nonatomic, retain) NSNumber *port;
@property (nullable, nonatomic, retain) NSNumber *state;
@property (nullable, nonatomic, retain) NSString *uuid;
@property (nullable, nonatomic, retain) NSData *dhmKey;
@property (nullable, nonatomic, retain) CSRPlaceEntity *place;

@end

NS_ASSUME_NONNULL_END
