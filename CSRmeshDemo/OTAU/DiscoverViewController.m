//
//  DiscoverViewController.m
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

#import "DiscoverViewController.h"

@interface DiscoverViewController ()
@property (strong, nonatomic) NSIndexPath *selectedCell;
@end

@implementation DiscoverViewController

@synthesize viewName, peripheralsList;
@synthesize discoveryViewDelegate;
@synthesize  selectedCell;
@synthesize statusLog;



- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    
    [[Discovery sharedInstance] setDiscoveryDelegate:self];
    [[Discovery sharedInstance] startScanForPeripheralsWithServices];
}

-(void)viewDidDisappear:(BOOL)animated
{
    [[Discovery sharedInstance] setDiscoveryDelegate:nil];
}


- (void)viewDidAppear:(BOOL)animated
{
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/****************************************************************************/
/*							TableView Delegates								*/
/****************************************************************************/
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    NSInteger   res;
    res = [[[Discovery sharedInstance] foundPeripherals] count];
    NSMutableArray * arr = [[NSMutableArray alloc] init];
    for (int i = 0; i < res; i++) {
        CBPeripheral *peripheral = (CBPeripheral*)[[Discovery sharedInstance] foundPeripherals][i];
        if ([[peripheral name] length]) {
            [arr addObject:peripheral];
        }
    }
    return (arr.count);
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell	*cell;
    CBPeripheral	*peripheral;
    NSArray			*devices;
    NSInteger		row	= [indexPath row];
    static NSString *cellID = @"Cell";
    
    cell = [tableView dequeueReusableCellWithIdentifier:cellID];
    if (!cell)
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:cellID];
    
    devices = [[Discovery sharedInstance] foundPeripherals];
    peripheral = (CBPeripheral*)[devices objectAtIndex:row];

    cell.textLabel.text = peripheral.name;
    
    return cell;
}

-(NSString *)handleStringWithString:(NSString *)str{
    
    NSMutableString * muStr = [NSMutableString stringWithString:str];
    while (1) {
        NSRange range = [muStr rangeOfString:@"<"];
        NSRange range1 = [muStr rangeOfString:@">"];
        if (range.location != NSNotFound) {
            NSInteger loc = range.location;
            NSInteger len = range1.location - range.location;
            [muStr deleteCharactersInRange:NSMakeRange(loc, len + 1)];
        }else{
            break;
        }
    }
    
    return muStr;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    CBPeripheral	*peripheral;
    NSArray			*devices;
    NSInteger		row	= [indexPath row];
    
    devices = [[Discovery sharedInstance] foundPeripherals];
    peripheral = (CBPeripheral*)[devices objectAtIndex:row];
    
    if ([peripheral state]!=CBPeripheralStateConnected) {
        [[Discovery sharedInstance] connectPeripheral:peripheral];
        // is this an OTAU peripheral?
        // Display "checking" in the cell view
        selectedCell = indexPath;
        [tableView reloadData];
        
        // check for OTAU service
        [[Discovery sharedInstance] startOTAUTest:peripheral];
        
        //[discoveryViewDelegate setTarget:peripheral];
        [self statusMessage:[NSString stringWithFormat:@"Connecting %@\n",peripheral.name]];
        
    }
    else if([[Discovery sharedInstance]isOTAUPeripheral:peripheral]){
        [discoveryViewDelegate setTarget:peripheral];
        
    }
    
}




// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}



// Override to support editing the table view.


/*
 // Override to support rearranging the table view.
 - (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
 {
 }
 */

/*
 // Override to support conditional rearranging of the table view.
 - (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
 {
 // Return NO if you do not want the item to be re-orderable.
 return YES;
 }
 */

/*
 #pragma mark - Navigation
 
 // In a story board-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
 {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 
 */

/****************************************************************************/
/*                       BleDiscoveryDelegate Methods                       */
/****************************************************************************/
- (void) discoveryDidRefresh
{
    [peripheralsList reloadData];
}


//============================================================================
- (void) discoveryStatePoweredOff
{
    NSString *title     = NSLocalizedString(@"Bluetooth Power", nil);
    NSString *message   = NSLocalizedString(@"message", nil);
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:NSLocalizedString(@"OK", nil) otherButtonTitles:nil];
    [alertView show];
}

//============================================================================
// callback: is this an otau capable peripheral
-(void) otauPeripheralTest:(CBPeripheral *) peripheral :(BOOL) isOtau {
    if (isOtau) {
        [self statusMessage:[NSString stringWithFormat:@"Success: OTAU Test\n"]];
        [discoveryViewDelegate setTarget:peripheral];
        [[Discovery sharedInstance] stopScanning];
    }
    else {
        [self statusMessage:[NSString stringWithFormat:@"Failed: OTAU Test\nDisconnecting...\n"]];
        [[Discovery sharedInstance] disconnectPeripheral:peripheral];
    }
}


//============================================================================
// The central is successfuly powered on
-(void) centralPoweredOn
{
    [[Discovery sharedInstance] retrieveCachedPeripherals ];
}


//============================================================================
-(void) statusMessage:(NSString *)message
{
    [statusLog setScrollEnabled:NO];
    [statusLog setText:[statusLog.text stringByAppendingString:message]];
    [statusLog setScrollEnabled:YES];
    NSRange range = NSMakeRange(statusLog.text.length - 1, 1);
    [statusLog scrollRangeToVisible:range];
}


/****************************************************************************/
/*				IB controls                                                 */
/****************************************************************************/

- (IBAction)backButton:(id)sender {
    [discoveryViewDelegate setTarget:nil];
    [[Discovery sharedInstance] stopScanning];
}


@end
