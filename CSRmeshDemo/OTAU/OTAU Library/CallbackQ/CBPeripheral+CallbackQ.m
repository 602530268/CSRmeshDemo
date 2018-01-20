//
//  CBPeripheral+CallbackQ.m
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

#import "CBPeripheral+CallbackQ.h"
#import "NSMutableArray+Queue.h"
#import <objc/runtime.h>

static void * queuePropertyKey;

@implementation CBPeripheral (CallbackQ)

@dynamic queue;

//=========================================================================
// Getter and Setter for queue property
- (NSMutableArray *)queue {
    return objc_getAssociatedObject(self, queuePropertyKey);
}

- (void)setQueue:(NSMutableArray *)queue {
    objc_setAssociatedObject(self, queuePropertyKey, queue, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}



//=========================================================================
// Save the callback object, PCM, in the Queue for this peripheral
-(void) saveCallback :(id) pcm {
    @synchronized(self) {
        if (self.queue==nil) {
            self.queue = [[NSMutableArray alloc]init];
        }
        
        [self.queue enqueue:pcm];
    }
}

-(id) getCallback {
    @synchronized(self) {
        id pcm = [self.queue dequeue];
        return (pcm);
    }
}


-(void) deleteQueue {
    @synchronized(self) {
        self.queue = nil;
    }
}

@end


