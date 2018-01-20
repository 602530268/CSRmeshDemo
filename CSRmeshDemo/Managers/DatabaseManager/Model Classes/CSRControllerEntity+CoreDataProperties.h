//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//


#import "CSRControllerEntity.h"

NS_ASSUME_NONNULL_BEGIN

@interface CSRControllerEntity (CoreDataProperties)

@property (nullable, nonatomic, retain) NSData *authCode;
@property (nullable, nonatomic, retain) NSString *controllerName;
@property (nullable, nonatomic, retain) NSData *deviceHash;
@property (nullable, nonatomic, retain) NSNumber *deviceId;
@property (nullable, nonatomic, retain) NSData *dmKey;
@property (nullable, nonatomic, retain) NSNumber *isAssociated;
@property (nullable, nonatomic, retain) NSDate *updateDate;
@property (nullable, nonatomic, retain) NSData *uuid;
@property (nullable, nonatomic, retain) NSSet<CSRPlaceEntity *> *place;

@end

NS_ASSUME_NONNULL_END
