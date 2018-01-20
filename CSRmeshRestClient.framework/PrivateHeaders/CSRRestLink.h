/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Hateoas Link Object.
*/

@interface CSRRestLink : CSRRestBaseObject


/*!
    HTTP Method
*/
 typedef NS_OPTIONS(NSInteger, CSRRestLinkMethodEnum) {
  CSRRestLinkMethodEnumGET,
  CSRRestLinkMethodEnumPOST,
  CSRRestLinkMethodEnumPUT,
  CSRRestLinkMethodEnumPATCH,
  CSRRestLinkMethodEnumDELETE,

};



/*!
    Relation to the resource.
*/
@property(nonatomic) NSString* rel;
  
/*!
    HTTP Method
*/
@property(nonatomic) CSRRestLinkMethodEnum method;

/*!
    Actual URI String.
*/
@property(nonatomic) NSString* href;
  
/*!
  Constructs instance of CSRRestLink

  @param rel - (NSString*) Relation to the resource.
  @param method - (CSRRestLinkMethodEnum) HTTP Method
  @param href - (NSString*) Actual URI String.
  
  @return instance of CSRRestLink
*/
- (id) initWithrel: (NSString*) rel     
       method: (CSRRestLinkMethodEnum) method     
       href: (NSString*) href;
       

@end
