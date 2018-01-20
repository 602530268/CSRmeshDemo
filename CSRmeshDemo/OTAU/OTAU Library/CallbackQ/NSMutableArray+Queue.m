//
//  NSMutableArray+Queue.m
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
//
//

#import "NSMutableArray+Queue.h"

@implementation NSMutableArray (Queue)

// Remove the object at the head of the Q and return it.
// return nil if the Q is empty

- (id) dequeue {
    if ([self count] == 0)
        // Q is empty so return nil
        return nil;
    
    id headOfQ = [self objectAtIndex:0];
    [self removeObjectAtIndex:0];
    
    return headOfQ;
}


// Add to the tail of the queue (no one likes it when people cut in line!)
- (void) enqueue:(id)obj {
    [self addObject:obj];
}


@end
