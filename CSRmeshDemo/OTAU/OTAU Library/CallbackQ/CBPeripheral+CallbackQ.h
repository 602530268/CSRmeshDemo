//
//  CBPeripheral+CallbackQ.h
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
//  This category Class adds a callback Queue to CBPeripheral. It is used to Queue
//  Asynchronous callbacks for background processing.
//
//  To use, simply create an NSMutableArray and call these methods to add and remove objects from Q.
//  saveCallback : Add the given PCM object to the Q.
//  getCallback : Remove and return the PCM object at the head of the Queue.
//  deleteQueue : Clear the Queue.
//
//  PCM = Peripheral Callback Management
//

#import <CoreBluetooth/CoreBluetooth.h>


@interface CBPeripheral (CallbackQ)

@property (strong, atomic)   NSMutableArray  *queue;


-(void) saveCallback :(id) pcm;
-(id) getCallback;
-(void) deleteQueue;


@end
