/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestTrackerFound.h"


/*!
    Response Object of Found API for model Tracker
*/

@interface CSRRestTrackerFoundResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestTrackerFoundResponseStatusEnum) {
  CSRRestTrackerFoundResponseStatusEnumPending,
  CSRRestTrackerFoundResponseStatusEnumCompleted,
  CSRRestTrackerFoundResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestTrackerFoundResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Tracker Found response object
*/
@property(nonatomic) NSArray* found;
  
/*!
  Constructs instance of CSRRestTrackerFoundResponse

  @param status - (CSRRestTrackerFoundResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param found - (NSArray*) The actual Tracker Found response object
  
  @return instance of CSRRestTrackerFoundResponse
*/
- (id) initWithstatus: (CSRRestTrackerFoundResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       found: (NSArray*) found;
       

@end
