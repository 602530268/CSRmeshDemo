//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#ifndef CSRMeshGroups_h
#define CSRMeshGroups_h


#endif /* CSRMeshGroups_h */
#import "CSRCommonToolbar.h"

@interface CSRMeshGroups : CSRCommonToolbar

-(id) init;

-(NSString *) getTitle;

-(BOOL) isAreaPresent:(NSString *) areaName;

-(BOOL) isAreaSelected:(NSString *) areaName;

-(BOOL) isGroupsScreenDisplayed;

-(void) clickAreaWithName:(NSString *)areaName error:(NSString **)errorDescription;

-(void) selectArea:(NSString *)areaName error:(NSString **)errorDescription;

-(void) back;

-(void) save;

@end
