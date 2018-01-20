/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Config Info response object
*/

@interface CSRRestConfigInfo : CSRRestBaseObject


/*!
    The type of information. The Info field is an 8-bit unsigned integer that enumerates the information being requested. The following values are defined:0x00 = UUID Low, 0x01 = UUID High, 0x02 = Model Low, 0x03 = Model High.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestConfigInfoInfoEnum) {
  CSRRestConfigInfoInfoEnumUUID_low,
  CSRRestConfigInfoInfoEnumUUID_high,
  CSRRestConfigInfoInfoEnumModel_low,
  CSRRestConfigInfoInfoEnumModel_high,
  CSRRestConfigInfoInfoEnumVID_PID_Version,
  CSRRestConfigInfoInfoEnumAppearance,
  CSRRestConfigInfoInfoEnumLastETag,

};



/*!
    The type of information. The Info field is an 8-bit unsigned integer that enumerates the information being requested. The following values are defined:0x00 = UUID Low, 0x01 = UUID High, 0x02 = Model Low, 0x03 = Model High.
*/
@property(nonatomic) CSRRestConfigInfoInfoEnum info;

/*!
    Information requested. The Information field is a 64-bit value that contains information determined by the Info field. If the Info field is 0x00, the Information field contains the least significant 64-bits of the DeviceUUID. If the Info field is 0x01, the Information field contains the most significant 64-bits of the DeviceUUID. If the Info field is 0x02, the Information field contains the least significant 64-bits of the ModelsSupported bit-field. If the Info field is 0x03, the Information field contains the most significant 64-bits of the ModelsSupported bit-field.
*/
@property(nonatomic) NSArray* information;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestConfigInfo

  @param info - (CSRRestConfigInfoInfoEnum) The type of information. The Info field is an 8-bit unsigned integer that enumerates the information being requested. The following values are defined:0x00 = UUID Low, 0x01 = UUID High, 0x02 = Model Low, 0x03 = Model High.
  @param information - (NSArray*) Information requested. The Information field is a 64-bit value that contains information determined by the Info field. If the Info field is 0x00, the Information field contains the least significant 64-bits of the DeviceUUID. If the Info field is 0x01, the Information field contains the most significant 64-bits of the DeviceUUID. If the Info field is 0x02, the Information field contains the least significant 64-bits of the ModelsSupported bit-field. If the Info field is 0x03, the Information field contains the most significant 64-bits of the ModelsSupported bit-field.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestConfigInfo
*/
- (id) initWithinfo: (CSRRestConfigInfoInfoEnum) info     
       information: (NSArray*) information     
       deviceId: (NSNumber*) deviceId;
       

@end
