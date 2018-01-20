/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestExtensionConflict.h"


/*!
    Response Object of Conflict API for model Extension
*/

@interface CSRRestExtensionConflictResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestExtensionConflictResponseStatusEnum) {
  CSRRestExtensionConflictResponseStatusEnumPending,
  CSRRestExtensionConflictResponseStatusEnumCompleted,
  CSRRestExtensionConflictResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestExtensionConflictResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Extension Conflict response object
*/
@property(nonatomic) NSArray* conflict;
  
/*!
  Constructs instance of CSRRestExtensionConflictResponse

  @param status - (CSRRestExtensionConflictResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param conflict - (NSArray*) The actual Extension Conflict response object
  
  @return instance of CSRRestExtensionConflictResponse
*/
- (id) initWithstatus: (CSRRestExtensionConflictResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       conflict: (NSArray*) conflict;
       

@end
