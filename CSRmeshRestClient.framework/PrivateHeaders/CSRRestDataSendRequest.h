/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object of send data API for model Data
*/

@interface CSRRestDataSendRequest : CSRRestBaseObject




/*!
    Arbitrary stream of data.
*/
@property(nonatomic) NSArray* dataOctets;
  
/*!
  Constructs instance of CSRRestDataSendRequest

  @param dataOctets - (NSArray*) Arbitrary stream of data.
  
  @return instance of CSRRestDataSendRequest
*/
- (id) initWithdataOctets: (NSArray*) dataOctets;
       

@end
