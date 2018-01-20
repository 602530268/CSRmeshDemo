/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
 
    REVISION:      $Revision: #14 $
 */

#import <Foundation/Foundation.h>
#import "CSRRestBaseObject_Private.h"

/*!
 Base class for Api
 */
@interface CSRRestBaseApi : NSObject

/*!
 This method must be called upon the first use of the Api as it creates and initialises a singleton object and returns a handle to it so that the same can be used to invoke instance methods.
 
 @return id - The id of the singleton object.
 */
+ (instancetype)sharedInstance;


/*!
 Constructs instance of CSRRestBaseApi, derived class must override and call this method
 
 @return instance of CSRRestBaseApi
 */
-(instancetype) init;


/*!
 Constructs dictionary/array representation for provided request data
 
 @return instance of NSDictionary or NSArray based on the request data type.
 */
-(id) bodyDictForRequest:(id)request;

@end
