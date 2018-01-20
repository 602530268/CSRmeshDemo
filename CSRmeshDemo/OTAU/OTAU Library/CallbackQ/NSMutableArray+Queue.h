//
//  NSMutableArray+Queue.h
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
//  This category Class provides Queue functionality. This is built on NSMutableArray by way of
//  the following methods.
//
//  dequeue - Removes an object from the head of the Q and returns it.
//            Returns nil if the Q is empty or the stored object is nil.
//
//  enqueue - Adds given object to the Tail of the Queue.
//
//  To use, simply create an NSMutableArray object and call these methods to ADD and REMOVE objects from the Q.
//

#import <Foundation/Foundation.h>

@interface NSMutableArray (Queue)

- (id) dequeue;
- (void) enqueue:(id)obj;


@end
