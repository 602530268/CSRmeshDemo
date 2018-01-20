//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//



#import "CSRLoadDatabaseManager.h"
#import "CSRSettingsEntity.h"
#import "CSRDeviceEntity.h"
#import "CSRAreaEntity.h"
#import "CSRmeshDevice.h"
#import "NSManagedObject+DeleteEntities.h"
#import "CSRParseAndLoad.h"
#import "CSRDatabaseManager.h"

@interface CSRLoadDatabaseManager()  {
    
    NSManagedObjectContext *managedObjectContext;
}
@end

@implementation CSRLoadDatabaseManager


+ (id) sharedInstance
{
    static dispatch_once_t token;
    static CSRLoadDatabaseManager *shared = nil;
    
    dispatch_once(&token, ^{
        shared = [[CSRLoadDatabaseManager alloc] init];
    });
    
    return shared;

}
- (id) init {
    self = [super init];
    if (self) {
        
        managedObjectContext = [CSRDatabaseManager sharedInstance].managedObjectContext;
        
        [NSManagedObject deleteAllObjects:@"CSRDeviceEntity"];
        //[NSManagedObject deleteAllObjects:@"CSRModelEntity"];
        [NSManagedObject deleteAllObjects:@"CSRAreaEntity"];

    }
    return self;
}

- (void) handleOpenURL:(NSURL *)url {
    
    NSData *jsonDataImported = [NSData dataWithContentsOfURL:url];
    NSError *error;
    NSDictionary *jsonDictionary = [NSJSONSerialization JSONObjectWithData:jsonDataImported options:NSJSONReadingMutableLeaves error:&error];
    
    CSRParseAndLoad *parseLoad = [[CSRParseAndLoad alloc] init];
    
    NSArray *groupsArray = jsonDictionary[@"areas_list"];
    [parseLoad parseAndLoadGroups:groupsArray];

    [NSThread sleepForTimeInterval:0.5];
    
    NSArray *devicesArray = jsonDictionary[@"devices_list"];
    [parseLoad parseAndLoadDevices:devicesArray];
    
    
    
    
}


@end

