/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for GetInfo API for the Config model
*/

@interface CSRRestConfigGetInfoRequest : CSRRestBaseObject


/*!
    The type of information being requested. The Info field is an 8-bit unsigned integer that enumerates the information being requested. The following values are defined: 0x00 = UUID Low, 0x01 UUID High, 0x02 = Model Low, 0x03 = Model High, 0x04 = VID_PID_Version, 0x05 = Appearance, 0x06 = LastETag, 0x07 = Conformance, 0x08 = Stack Version.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestConfigGetInfoRequestInfoEnum) {
  CSRRestConfigGetInfoRequestInfoEnumUUID_low,
  CSRRestConfigGetInfoRequestInfoEnumUUID_high,
  CSRRestConfigGetInfoRequestInfoEnumModel_low,
  CSRRestConfigGetInfoRequestInfoEnumModel_high,
  CSRRestConfigGetInfoRequestInfoEnumVID_PID_Version,
  CSRRestConfigGetInfoRequestInfoEnumAppearance,
  CSRRestConfigGetInfoRequestInfoEnumLastETag,

};



/*!
    The type of information being requested. The Info field is an 8-bit unsigned integer that enumerates the information being requested. The following values are defined: 0x00 = UUID Low, 0x01 UUID High, 0x02 = Model Low, 0x03 = Model High, 0x04 = VID_PID_Version, 0x05 = Appearance, 0x06 = LastETag, 0x07 = Conformance, 0x08 = Stack Version.
*/
@property(nonatomic) CSRRestConfigGetInfoRequestInfoEnum info;

/*!
  Constructs instance of CSRRestConfigGetInfoRequest

  @param info - (CSRRestConfigGetInfoRequestInfoEnum) The type of information being requested. The Info field is an 8-bit unsigned integer that enumerates the information being requested. The following values are defined: 0x00 = UUID Low, 0x01 UUID High, 0x02 = Model Low, 0x03 = Model High, 0x04 = VID_PID_Version, 0x05 = Appearance, 0x06 = LastETag, 0x07 = Conformance, 0x08 = Stack Version.
  
  @return instance of CSRRestConfigGetInfoRequest
*/
- (id) initWithinfo: (CSRRestConfigGetInfoRequestInfoEnum) info;
       

@end
