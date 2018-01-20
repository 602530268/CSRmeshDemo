/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"
#import "CSRRestTuningStats.h"


/*!
    Response Object of Stats API for model Tuning
*/

@interface CSRRestTuningStatsResponse : CSRRestBaseObject


/*!
    Status of the request - Pending,Completed or TimeOut
*/
 typedef NS_OPTIONS(NSInteger, CSRRestTuningStatsResponseStatusEnum) {
  CSRRestTuningStatsResponseStatusEnumPending,
  CSRRestTuningStatsResponseStatusEnumCompleted,
  CSRRestTuningStatsResponseStatusEnumTimeOut,

};



/*!
    Status of the request - Pending,Completed or TimeOut
*/
@property(nonatomic) CSRRestTuningStatsResponseStatusEnum status;

/*!
    Status check URL for pending responses.
*/
@property(nonatomic) NSString* statusUrl;
  
/*!
    The actual Tuning Stats response object
*/
@property(nonatomic) NSArray* stats;
  
/*!
  Constructs instance of CSRRestTuningStatsResponse

  @param status - (CSRRestTuningStatsResponseStatusEnum) Status of the request - Pending,Completed or TimeOut
  @param statusUrl - (NSString*) Status check URL for pending responses.
  @param stats - (NSArray*) The actual Tuning Stats response object
  
  @return instance of CSRRestTuningStatsResponse
*/
- (id) initWithstatus: (CSRRestTuningStatsResponseStatusEnum) status     
       statusUrl: (NSString*) statusUrl     
       stats: (NSArray*) stats;
       

@end
