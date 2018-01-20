/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Group ModelGroupid response object
*/

@interface CSRRestGroupModelGroupid : CSRRestBaseObject




/*!
    Model number
*/
@property(nonatomic) NSNumber* model;
  
/*!
    Index of the GroupID in this model
*/
@property(nonatomic) NSNumber* groupIndex;
  
/*!
    Instance of the group
*/
@property(nonatomic) NSNumber* instance;
  
/*!
    Group identifier
*/
@property(nonatomic) NSNumber* groupId;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestGroupModelGroupid

  @param model - (NSNumber*) Model number
  @param groupIndex - (NSNumber*) Index of the GroupID in this model
  @param instance - (NSNumber*) Instance of the group
  @param groupId - (NSNumber*) Group identifier
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestGroupModelGroupid
*/
- (id) initWithmodel: (NSNumber*) model     
       groupIndex: (NSNumber*) groupIndex     
       instance: (NSNumber*) instance     
       groupId: (NSNumber*) groupId     
       deviceId: (NSNumber*) deviceId;
       

@end
