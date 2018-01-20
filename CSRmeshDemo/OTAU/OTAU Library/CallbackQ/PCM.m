//
//  PCM.m
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
// Objects of this class are stored in the PCMQ.
//

#import "PCM.h"


@implementation PCM

@synthesize PCMPeripheral, PCMService, PCMCharacteristic, PCMError, PCMName;

-(id) init:(CBPeripheral *)peripheral :(CBService *)service :(CBCharacteristic *)characteristic :(NSError *)error :(NSString *)name {
    
    PCMPeripheral = peripheral;
    PCMService = service;
    PCMCharacteristic = characteristic;
    PCMError = error;
    PCMName = name;
    
    return (self);
}



@end
