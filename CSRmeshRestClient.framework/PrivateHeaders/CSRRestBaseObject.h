/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
 
    REVISION:      $Revision: #14 $
 */

#import <Foundation/Foundation.h>

/*!
 Base class for request and response model classes
 */
@interface CSRRestBaseObject : NSObject

/*!
 Constructs instance of CSRRestBaseObject, derived class must override and call this method.
 It may return a nil object on giving inappropiate values for key, e.g. wrong enum value.
 
 @param dict - (NSDictionary*) A dictionary conatains the key value pair for all the required properties for derived class
 
 @return instance of CSRRestBaseObject
 */
- (id) initWithValues:(NSDictionary*)dict;

/*!
 Convert the instance into dictionary represention, derived class must override and call this method
 
 @return dictionary - (NSDictionary*) The hashmap representation for derived class instance
 All the properties are stored in dictionary in key value pair.
 */
- (NSDictionary*) asDictionary;
@end
