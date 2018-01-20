/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestGroupNumberOfModelGroupids.h"


/*!
    Response Object of NumberOfModelGroupids API for model Group
*/

@interface CSRRestGroupNumberOfModelGroupidsResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestGroupNumberOfModelGroupidsResponseStatusEnum) {
  CSRRestGroupNumberOfModelGroupidsResponseStatusEnumPending,
  CSRRestGroupNumberOfModelGroupidsResponseStatusEnumCompleted,
  CSRRestGroupNumberOfModelGroupidsResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestGroupNumberOfModelGroupidsResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Group NumberOfModelGroupids response object
*/
@property(nonatomic) NSArray* numberOfModelGroupids;
  
/*!
  Constructs instance of CSRRestGroupNumberOfModelGroupidsResponse

  @param status - (CSRRestGroupNumberOfModelGroupidsResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param numberOfModelGroupids - (NSArray*) The actual Group NumberOfModelGroupids response object
  
  @return instance of CSRRestGroupNumberOfModelGroupidsResponse
*/
- (id) initWithstatus: (CSRRestGroupNumberOfModelGroupidsResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       numberOfModelGroupids: (NSArray*) numberOfModelGroupids;
       

@end
