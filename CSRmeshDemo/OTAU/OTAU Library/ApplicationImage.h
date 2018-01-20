//
//  Firmware.h
//  OTAU
//
/******************************************************************************
 *  Copyright (C) Cambridge Silicon Radio Limited 2014
 *
 *  This software is provided to the customer for evaluation
 *  purposes only and, as such early feedback on performance and operation
 *  is anticipated. The software source code is subject to change and
 *  not intended for production. Use of developmental release software is
 *  at the user's own risk. This software is provided "as is," and CSR
 *  cautions users to determine for themselves the suitability of using the
 *  beta release version of this software. CSR makes no warranty or
 *  representation whatsoever of merchantability or fitness of the product
 *  for any particular purpose or use. In no event shall CSR be liable for
 *  any consequential, incidental or special damages whatsoever arising out
 *  of the use of or inability to use this software, even if the user has
 *  advised CSR of the possibility of such damages.
 *
 ******************************************************************************/
//
// Prepare an Application file for upload to a device.



#import <Foundation/Foundation.h>


@interface ApplicationImage : NSObject

+ (id) sharedInstance;

-(NSData *) prepareFirmwareWith:(NSData *)crystalTrim
                            and:(NSData *) bluetoothMacAddress
                            and:(NSData*) iRoot
                            and:(NSData*) eRoot
                        forFile:(NSString *) filepath;
/*!
 @method prepareFirmware
 @discussion Take the Aplication image file that is included in the Main Bundle and merge in the given Bluetooth MAC Address and the Crystal trim. Then compute the CRC for the Data Block and the CRC for the Header Block. The image file is now ready for upload to the target.
 @updated 2013-11-27
*/


@end


