/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Response Object get gateway uuid response
*/

@interface CSRRestGetGatewayProfileResponse : CSRRestBaseObject




/*!
    Gateway UUID
*/
@property(nonatomic) NSString* gwUuid;
  
/*!
    Base path url for CGI.
*/
@property(nonatomic) NSString* gwCgiBasepath;
  
/*!
  Constructs instance of CSRRestGetGatewayProfileResponse

  @param gwUuid - (NSString*) Gateway UUID
  @param gwCgiBasepath - (NSString*) Base path url for CGI.
  
  @return instance of CSRRestGetGatewayProfileResponse
*/
- (id) initWithgwUuid: (NSString*) gwUuid     
       gwCgiBasepath: (NSString*) gwCgiBasepath;
       

@end
