//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class CSRPlaceEntity;

@interface CSRUserEntity : NSManagedObject

@property (nonatomic, retain) NSString * email;
@property (nonatomic, retain) NSString * name;
@property (nonatomic, retain) NSString * token;
@property (nonatomic, retain) NSString * userId;
@property (nonatomic, retain) NSSet *places;
@end

@interface CSRUserEntity (CoreDataGeneratedAccessors)

- (void)addPlacesObject:(CSRPlaceEntity *)value;
- (void)removePlacesObject:(CSRPlaceEntity *)value;
- (void)addPlaces:(NSSet *)values;
- (void)removePlaces:(NSSet *)values;

@end
