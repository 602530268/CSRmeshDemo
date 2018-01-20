//
//  FirmwareSelector.h
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
//  Present a list of inbuilt Application files and allow the user to choose one
//

#import <UIKit/UIKit.h>
//step1. 导入QuickLook库和头文件
#import <QuickLook/QuickLook.h>

@protocol FirmwareDelegate <NSObject>

-(void) firmwareSelector:(NSString *) filename;

@end



@interface FirmwareSelector : UIViewController <UITableViewDelegate,QLPreviewControllerDataSource,QLPreviewControllerDelegate,UIDocumentInteractionControllerDelegate>
{
    //step3. 声明显示列表  >
    UITableView *readTable;
}
//setp4. 声明变量
//UIDocumentInteractionController : 一个文件交互控制器,提供应用程序管理与本地系统中的文件的用户交互的支持
//dirArray : 存储沙盒子里面的所有文件
@property(nonatomic,retain) NSMutableArray *dirArray;
@property (nonatomic, strong) UIDocumentInteractionController *docInteractionController;
@property (strong, nonatomic) id<FirmwareDelegate> firmwareDelegate;
- (IBAction)backButton:(id)sender;

@end
