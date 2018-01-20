//
//  FirmwareSelector.m
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

#import "FirmwareSelector.h"

@interface FirmwareSelector ()

@end

@implementation FirmwareSelector
@synthesize firmwareDelegate;
@synthesize dirArray;
@synthesize docInteractionController;


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    //step6. 获取沙盒里所有文件
    NSFileManager *fileManager = [NSFileManager defaultManager];
    //在这里获取应用程序Documents文件夹里的文件及文件夹列表
    NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDir = [documentPaths objectAtIndex:0];
    NSError *error = nil;
    NSArray *fileList = [[NSArray alloc] init];
    //fileList便是包含有该文件夹下所有文件的文件名及文件夹名的数组
    fileList = [fileManager contentsOfDirectoryAtPath:documentDir error:&error];
    
    self.dirArray = [[NSMutableArray alloc] init];
    for (NSString *file in fileList)
    {
        [self.dirArray addObject:file];
    }
    
    //step6. 刷新列表, 显示数据
    [readTable reloadData];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
        NSArray *files = [[NSBundle mainBundle] pathsForResourcesOfType:@".xuv" inDirectory:@"./"];
        return (files.count);
//    return [self.dirArray count];
}
//step7. 利用url路径打开UIDocumentInteractionController
- (void)setupDocumentControllerWithURL:(NSURL *)url
{
    if (self.docInteractionController == nil)
    {
        self.docInteractionController = [UIDocumentInteractionController interactionControllerWithURL:url];
        self.docInteractionController.delegate = self;
    }
    else
    {
        self.docInteractionController.URL = url;
    }
}
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    	UITableViewCell	*cell;
        static NSString *cellID = @"Cell";
    
    	cell = [tableView dequeueReusableCellWithIdentifier:cellID];
    	if (!cell)
    		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:cellID];
    
        NSArray *files = [[NSBundle mainBundle] pathsForResourcesOfType:@".xuv" inDirectory:@"./"];
    
        NSString *filepath = (NSString *) [files objectAtIndex:[indexPath row]];
        NSString *filename = [[filepath lastPathComponent] stringByDeletingPathExtension];
    
        [[cell textLabel] setText:filename];
    
    	return cell;
//    static NSString *CellName = @"CellName";
//    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellName];
//    if (cell == nil)
//    {
//        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellName];
//        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
//    }
//    
//    NSURL *fileURL= nil;
//    NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString *documentDir = [documentPaths objectAtIndex:0];
//    NSString *path = [documentDir stringByAppendingPathComponent:[self.dirArray objectAtIndex:indexPath.row]];
//    fileURL = [NSURL fileURLWithPath:path];
//    
//    [self setupDocumentControllerWithURL:fileURL];
//    cell.textLabel.text = [self.dirArray objectAtIndex:indexPath.row];
//    NSInteger iconCount = [self.docInteractionController.icons count];
//    if (iconCount > 0)
//    {
//        cell.imageView.image = [self.docInteractionController.icons objectAtIndex:iconCount - 1];
//    }
//    
//    return cell;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
        NSArray *files = [[NSBundle mainBundle] pathsForResourcesOfType:@".xuv" inDirectory:@"./"];
    
        NSString *filepath = (NSString *) [files objectAtIndex:[indexPath row]];
    
//    NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
//    NSString *documentDir = [documentPaths objectAtIndex:0];
//    NSString *path = [documentDir stringByAppendingPathComponent:[self.dirArray objectAtIndex:indexPath.row]];
//    
//    QLPreviewController *previewController = [[QLPreviewController alloc] init];
//    previewController.dataSource = self;
//    previewController.delegate = self;
//    
//    // start previewing the document at the current section index
//    previewController.currentPreviewItemIndex = indexPath.row;
//    [[self navigationController] pushViewController:previewController animated:YES];
//    //  [self presentViewController:previewController animated:YES completion:nil];
    
    [firmwareDelegate firmwareSelector:filepath];
}



/*
 // Override to support conditional editing of the table view.
 - (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
 {
 // Return NO if you do not want the specified item to be editable.
 return YES;
 }
 */

/*
 // Override to support editing the table view.
 - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
 {
 if (editingStyle == UITableViewCellEditingStyleDelete) {
 // Delete the row from the data source
 [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
 }
 else if (editingStyle == UITableViewCellEditingStyleInsert) {
 // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
 }
 }
 */

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
#pragma mark - UIDocumentInteractionControllerDelegate

- (NSString *)applicationDocumentsDirectory
{
    return [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
}

- (UIViewController *)documentInteractionControllerViewControllerForPreview:(UIDocumentInteractionController *)interactionController
{
    return self;
}


#pragma mark - QLPreviewControllerDataSource

// Returns the number of items that the preview controller should preview
- (NSInteger)numberOfPreviewItemsInPreviewController:(QLPreviewController *)previewController
{
    return 1;
}

- (void)previewControllerDidDismiss:(QLPreviewController *)controller
{
    // if the preview dismissed (done button touched), use this method to post-process previews
}

// returns the item that the preview controller should preview
- (id)previewController:(QLPreviewController *)previewController previewItemAtIndex:(NSInteger)idx
{
    NSURL *fileURL = nil;
    NSIndexPath *selectedIndexPath = [readTable indexPathForSelectedRow];
    NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDir = [documentPaths objectAtIndex:0];
    NSString *path = [documentDir stringByAppendingPathComponent:[self.dirArray objectAtIndex:selectedIndexPath.row]];
    fileURL = [NSURL fileURLWithPath:path];
    return fileURL;
}

- (IBAction)backButton:(id)sender {
    [firmwareDelegate firmwareSelector:@""];
}
@end
