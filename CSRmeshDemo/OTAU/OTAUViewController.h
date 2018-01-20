//
//  ViewController.h
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
//  Main View
//

/*
 double add:
 固件升级有个源码项目，支持单个设备的升级，需求是要支持多个设备的升级，但是在重构完2.1框架项目后我已经不想在重构固件升级了，所以这里是从老项目中转移过来的OTA代码
 关于OTAU升级，这个mesh灯的升级速度比我以前做的手环升级要慢的多了，大概需要3分钟左右的时间，
 如果遇到升级失败，原因可能有这些，提供参考：
 1.芯片问题，搜不到CSRmesh的名字的话是无法搜索在或连接到的
 2.电源坏了
 3.执行代码问题，可参考复杂的源代码
 4.设备发出的蓝牙被关闭了，试试关灯重开
 5.手机坏了，删除app、重新开机
 */

#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "FirmwareSelector.h"
#import "DiscoverViewController.h"
#import "OTAU.h"
//step1. 导入QuickLook库和头文件
#import <QuickLook/QuickLook.h>

@interface OTAUViewController : UIViewController <FirmwareDelegate, DiscoveryViewDelegate, OTAUDelegate,QLPreviewControllerDataSource,QLPreviewControllerDelegate,UIDocumentInteractionControllerDelegate,DiscoveryDelegate>
{
    //step3. 声明显示列表  >
    IBOutlet UITableView *readTable;
    UITableView * DeviceTable;
}
//setp4. 声明变量
//UIDocumentInteractionController : 一个文件交互控制器,提供应用程序管理与本地系统中的文件的用户交互的支持
//dirArray : 存储沙盒子里面的所有文件
@property(nonatomic,retain) NSMutableArray *dirArray;
@property (nonatomic, strong) UIDocumentInteractionController *docInteractionController;

@property (weak, nonatomic) IBOutlet UIView *BackView;
@property (weak, nonatomic) IBOutlet UIButton *firmwareName;
@property (weak, nonatomic) IBOutlet UIButton *targetName;
@property (weak, nonatomic) IBOutlet UIButton *updateButtonName;

@property (weak, nonatomic) IBOutlet UIView *tabbarView;
@property (strong, nonatomic) NSString *firmwareFilename;
@property (strong, nonatomic) CBPeripheral *targetPeripheral;

@property (weak, nonatomic) IBOutlet UITextView *statusLog;//

-(void) handleOpenURL:(NSURL *)url;
- (IBAction)startUpdate:(id)sender;
- (IBAction)abortUpdate:(id)sender;

@property (weak, nonatomic) IBOutlet UIButton *startButton;
@property (weak, nonatomic) IBOutlet UILabel *percentLabel;
@property (weak, nonatomic) IBOutlet UIButton *abortButton;
@property (weak, nonatomic) IBOutlet UIProgressView *progressBar;
@property (strong, nonatomic) UIProgressView *progressBar_new;
@property (weak, nonatomic) IBOutlet UILabel *deviceAddress;//
@property (weak, nonatomic) IBOutlet UILabel *connectionState;//
@property (weak, nonatomic) IBOutlet UILabel *crystalTrim;//
@property (weak, nonatomic) IBOutlet UILabel *fwVersion;//
@property (weak, nonatomic) IBOutlet UILabel *modeLabel;//
@property (weak, nonatomic) IBOutlet UILabel *challengeLabel;//
@property (weak, nonatomic) IBOutlet UILabel *appVersion;//
@property (weak, nonatomic) IBOutlet UILabel *appVersionLabel;//
- (IBAction)backButtton:(id)sender;



@end
