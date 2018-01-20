//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "CSRDatabaseManager.h"
#import "CSRAreaEntity.h"
#import "CSRSettingsEntity.h"
#import "CSREventEntity.h"

@interface CSRDatabaseManager : NSObject {
    BOOL newDatabase;
}

@property (readonly, strong, nonatomic) NSManagedObjectContext *managedObjectContext;
@property (readonly, strong, nonatomic) NSManagedObjectModel *managedObjectModel;
@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator *persistentStoreCoordinator;

+ (CSRDatabaseManager*)sharedInstance;
- (void)saveContext;

//Fetch
- (NSArray *)fetchObjectsWithEntityName:(NSString *)entityName withPredicate:(id)stringOrPredicate, ...;

//DEVICE
- (NSNumber *)getNextFreeIDOfType:(NSString *)typeString;

#pragma mark - Gateway methods
- (NSNumber*)getNextFreeGatewayDeviceId;

//Groups
- (CSRAreaEntity*) saveNewArea :(NSNumber *) areaId areaName:(NSString *) areaName;

// Remove Device
-(void) removeDeviceFromDatabase :(NSNumber *) deviceId;

//Remove Area
- (void) removeAreaFromDatabaseWithAreaId:(NSNumber*)areaId;

//Database Local functions
-(void) loadDatabase;
//-(NSString *) fetchNetworkKey;
- (CSRAreaEntity *)getAreaEntityWithId:(NSNumber *)areaId;
- (CSRDeviceEntity *)getDeviceEntityWithId:(NSNumber *)deviceId;
- (CSRSettingsEntity *)fetchSettingsEntity;
- (CSRSettingsEntity *)settingsForCurrentlySelectedPlace;

- (void) saveDeviceModel :(NSNumber *) deviceNumber modelNumber:(NSData *) modelNumber infoType:(NSNumber *) infoType;

@end
