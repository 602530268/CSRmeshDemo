//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "NSManagedObject+DeleteEntities.h"
#import "CSRDatabaseManager.h"

@implementation NSManagedObject (DeleteEntities)

+ (void) deleteAllObjects: (NSString *) entityDescription  {
    
    
    NSManagedObjectContext *managedObjectContext = [CSRDatabaseManager sharedInstance].managedObjectContext;

    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] initWithEntityName:entityDescription];
    [fetchRequest setIncludesPropertyValues:NO];
    
    NSError *error = nil;
    NSArray *items = [managedObjectContext executeFetchRequest:fetchRequest error:&error];
    
    for (NSManagedObject *managedObject in items) {
        [managedObjectContext deleteObject:managedObject];
        //NSLog(@"%@ object deleted",entityDescription);
    }
    if (![managedObjectContext save:&error]) {
        //NSLog(@"Error deleting %@ - error:%@",entityDescription,error);
    }
    
}


@end
