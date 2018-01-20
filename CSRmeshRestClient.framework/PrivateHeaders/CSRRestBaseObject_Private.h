/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 
 REVISION:      $Revision: #1 $
 */

#ifndef CSRRestBaseObject_Private_h
#define CSRRestBaseObject_Private_h

#import "CSRRestBaseObject.h"

@interface CSRRestBaseObject ()

/*!
 Convert the instance into dictionary represention, derived class must override and call this method
 
 @return dictionary - (NSDictionary*) The hashmap representation for derived class instance
 All the properties are stored in dictionary in key value pair.
 */
- (NSDictionary*) asDictionary;

@end
#endif /* CSRRestBaseObject_h */
