//
//  DiscoverViewController.h
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
//  Discover Devices and allow user to choose one for OTAU
//

#import <UIKit/UIKit.h>
#import "Discovery.h"

@protocol DiscoveryViewDelegate <NSObject>
-(void) setTarget:(id)peripheral;

@end


@interface DiscoverViewController : UIViewController <DiscoveryDelegate, UITableViewDelegate>



@property (weak, nonatomic) IBOutlet UINavigationItem *viewName;
@property (strong, nonatomic) IBOutlet UITableView *peripheralsList;

@property (strong, nonatomic) id<DiscoveryViewDelegate> discoveryViewDelegate;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *activityIndicator;
- (IBAction)backButton:(id)sender;

@property (weak, nonatomic) IBOutlet UITextView *statusLog;
@end
