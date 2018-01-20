/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for updating firmware of devices in mesh network.
*/

@interface CSRRestObjectTransferRequest : CSRRestBaseObject


/*!
    String representing the type of firmware image.Possible values are partial_image, full_image and others. Default value is full_image
*/
 typedef NS_OPTIONS(NSInteger, CSRRestObjectTransferRequestFileTypeEnum) {
  CSRRestObjectTransferRequestFileTypeEnumpartial_image,
  CSRRestObjectTransferRequestFileTypeEnumfull_image,
  CSRRestObjectTransferRequestFileTypeEnumothers,

};



/*!
    List of device-ids. Device-id can either be device-id or group-id or '0' for all devices.
*/
@property(nonatomic) NSArray* devices;
  
/*!
    String representing the type of firmware image.Possible values are partial_image, full_image and others. Default value is full_image
*/
@property(nonatomic) CSRRestObjectTransferRequestFileTypeEnum fileType;

/*!
    Bluetooth Company Code to be used for LOT_Annouce by the mesh.
*/
@property(nonatomic) NSNumber* companyCode;
  
/*!
    Timeout in seconds.
*/
@property(nonatomic) NSNumber* timeout;
  
/*!
    Firmware file name, which has been previously uploaded using generic file upload API.
*/
@property(nonatomic) NSString* fileName;
  
/*!
    Firmware major version.
*/
@property(nonatomic) NSNumber* majorVersion;
  
/*!
    Firmware minor version.
*/
@property(nonatomic) NSNumber* minorVersion;
  
/*!
  Constructs instance of CSRRestObjectTransferRequest

  @param devices - (NSArray*) List of device-ids. Device-id can either be device-id or group-id or '0' for all devices.
  @param fileType - (CSRRestObjectTransferRequestFileTypeEnum) String representing the type of firmware image.Possible values are partial_image, full_image and others. Default value is full_image
  @param companyCode - (NSNumber*) Bluetooth Company Code to be used for LOT_Annouce by the mesh.
  @param timeout - (NSNumber*) Timeout in seconds.
  @param fileName - (NSString*) Firmware file name, which has been previously uploaded using generic file upload API.
  @param majorVersion - (NSNumber*) Firmware major version.
  @param minorVersion - (NSNumber*) Firmware minor version.
  
  @return instance of CSRRestObjectTransferRequest
*/
- (id) initWithdevices: (NSArray*) devices     
       fileType: (CSRRestObjectTransferRequestFileTypeEnum) fileType     
       companyCode: (NSNumber*) companyCode     
       timeout: (NSNumber*) timeout     
       fileName: (NSString*) fileName     
       majorVersion: (NSNumber*) majorVersion     
       minorVersion: (NSNumber*) minorVersion;
       

@end
