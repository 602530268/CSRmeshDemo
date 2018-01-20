//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class CSRPlaceEntity;

@interface CSRSettingsEntity : NSManagedObject

@property (nonatomic, retain) NSString * cloudMeshID;
@property (nonatomic, retain) NSString * cloudTenancyID;
@property (nonatomic, retain) NSNumber * concurrentConnections;
@property (nonatomic, retain) NSNumber * listeningMode;
@property (nonatomic, retain) NSNumber * retryCount;
@property (nonatomic, retain) NSNumber * retryInterval;
@property (nonatomic, retain) NSString * siteID;
@property (nonatomic, retain) NSString * userID;
@property (nonatomic, retain) CSRPlaceEntity *place;

@end
