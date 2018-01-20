//
//  ViewController.m
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

#import "OTAUViewController.h"
#import "AppDelegate.h"
#import "DataBaseSimple.h"
#import "ThingModel.h"
#import "GroupedLightTableViewCell.h"

#import "FilesView.h"
#import "Masonry.h"

#define SCREEN_WIDTH  [UIScreen mainScreen].bounds.size.width
#define SCREEN_HEIGHT [UIScreen mainScreen].bounds.size.height

#define NEW_VERSION @"1.3"

@interface OTAUViewController ()<UITableViewDelegate,UITableViewDataSource> {
    UIView * chageGroupName;
    UITextField * filedName;
    dispatch_queue_t queue;
    
    NSMutableArray *_deviceOtaInfos;    //所有设备的OTA必须信息封装成dic，存入数组中
}
@property BOOL isUpdateRunning;
@property BOOL isInitRunning;
@property BOOL isAbortButton;
@property BOOL peripheralConnected;
@property uint8_t expectedCsKey;

@property (strong, nonatomic) NSMutableArray *ungroupedLights;
@property (strong, nonatomic) NSMutableArray *groupedLights;
@property (strong, nonatomic) NSMutableArray *thisGroupLights;
@property (strong, nonatomic) NSMutableArray *upToDataLights;
@property (strong, nonatomic) NSMutableArray *selectedLights;
@property (strong, nonatomic) NSMutableArray *delecateLights;
@property (strong, nonatomic)  UIView *bottomView;
@property (strong, nonatomic) UILabel *instructionsLabel;
@property (strong, nonatomic) UIButton *doTheGroupingButton;
@property (strong, nonatomic) UILabel *otherLabel;
@property (strong, nonatomic) UIView *chooseView;

@end

@implementation OTAUViewController

@synthesize dirArray;
@synthesize docInteractionController;

@synthesize firmwareName, targetName, updateButtonName;
@synthesize firmwareFilename, targetPeripheral;
@synthesize isAbortButton, isUpdateRunning, isInitRunning, peripheralConnected, expectedCsKey;

@synthesize deviceAddress, connectionState, crystalTrim, fwVersion;
@synthesize statusLog;
@synthesize startButton, abortButton, progressBar, percentLabel;
@synthesize modeLabel, challengeLabel, appVersionLabel, appVersion;

- (void)viewDidLoad
{
    [super viewDidLoad];

    self.navigationItem.title = @"software update";
    self.navigationController.navigationBar.tintColor = [UIColor lightGrayColor];   //item颜色
    self.navigationController.navigationBar.barTintColor = BaseNavColor;
    

    UIView * Nav = [[UIView alloc] initWithFrame:CGRectMake(0, 25, 80, 40)];
    //    [self.view addSubview:view];
    
    UIImageView * image1 = [[UIImageView alloc] initWithFrame:CGRectMake(0, 10, 19, 19)];
    image1.image = [UIImage imageNamed:@"nav_back"];
    [Nav addSubview:image1];
    
    UILabel * label = [[UILabel alloc] initWithFrame:CGRectMake(20, 10, 60, 20)];
    label.text = @"Back";
    label.font = [UIFont fontWithName:@"MontSerrat-Regular" size:16];
    [label setTextColor:[UIColor lightGrayColor]];
    [Nav addSubview:label];
    
    UIButton * but = [UIButton buttonWithType:UIButtonTypeCustom];
    [but addTarget:self action:@selector(backButtton:) forControlEvents:UIControlEventTouchUpInside];
    but.frame = CGRectMake(0, 0, 80, 40);
    [Nav addSubview:but];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:Nav];
    
    [[Discovery sharedInstance] setDiscoveryDelegate:self];
    [[Discovery sharedInstance] startScanForPeripheralsWithServices];
    
    queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    
    // Do any additional setup after loading the view, typically from a nib.
    [[OTAU sharedInstance] setOTAUDelegate:self];
    
    [self statusMessage: @"Start: Load CS key JSON\n"];
    if ([[OTAU sharedInstance] parseCsKeyJson:@"cskey_db"]) {
        [self statusMessage: @"Success: Load CS key JSON\n"];
    }
    else {
        [self statusMessage: @"Fail: Load CS key JSON\n"];
    }
    
    peripheralConnected = NO;
    [connectionState setText:@"DISCONNECTED"];
    
    progressBar.progress = 0.0;
    
    isInitRunning = NO;
    
    // Did we open App with email or dropbox attachment?
    AppDelegate *appDelegate= (AppDelegate *)[[UIApplication sharedApplication] delegate];
    if (appDelegate.urlImageFile)
        [self handleOpenURL:appDelegate.urlImageFile];
    
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
    
    
    UIView * AnoutherBackGroundView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)];
    AnoutherBackGroundView.backgroundColor = [UIColor colorWithRed:33/255. green:39/255. blue:57/255. alpha:1.0];
    [self.view addSubview:AnoutherBackGroundView];

    DeviceTable = [[UITableView alloc] init];
    if (SCREEN_HEIGHT==480 &&  SCREEN_WIDTH==320) {
        DeviceTable.frame = CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 100 - 64);
    } else if (SCREEN_HEIGHT==568 &&  SCREEN_WIDTH==320) {
        DeviceTable.frame = CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 150 - 64);
    } else if (SCREEN_HEIGHT==667 &&  SCREEN_WIDTH==375) {
        DeviceTable.frame = CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 180 - 64);
    }else{
        DeviceTable.frame = CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 200 - 64);
    }
    DeviceTable.delegate = self;
    DeviceTable.dataSource = self;
    DeviceTable.bounces = NO;
    [DeviceTable setSeparatorStyle:UITableViewCellSeparatorStyleNone];
    DeviceTable.backgroundColor = [UIColor colorWithRed:33/255. green:39/255. blue:57/255. alpha:1.0];
    [AnoutherBackGroundView addSubview:DeviceTable];
    // Do any additional setup after loading the view.
    
    if (SCREEN_HEIGHT==480 &&  SCREEN_WIDTH==320) {
        self.bottomView = [[UIView alloc] initWithFrame:CGRectMake(0, SCREEN_HEIGHT - 100 - 64, SCREEN_WIDTH, 100)];
    } else if (SCREEN_HEIGHT==568 &&  SCREEN_WIDTH==320) {
        self.bottomView = [[UIView alloc] initWithFrame:CGRectMake(0, SCREEN_HEIGHT - 150 - 64, SCREEN_WIDTH, 150)];
    } else if (SCREEN_HEIGHT==667 &&  SCREEN_WIDTH==375) {
        self.bottomView = [[UIView alloc] initWithFrame:CGRectMake(0, SCREEN_HEIGHT - 180 - 64, SCREEN_WIDTH, 180)];
    }else{
        self.bottomView = [[UIView alloc] initWithFrame:CGRectMake(0, SCREEN_HEIGHT - 200 - 64, SCREEN_WIDTH, 200)];
    }
    self.bottomView.backgroundColor = [UIColor colorWithRed:63/255. green:69/255. blue:83/255. alpha:1];
    [AnoutherBackGroundView addSubview:self.bottomView];
    #pragma 11111
    _chooseView = [[UIView alloc] initWithFrame:CGRectMake(self.view.center.x - 100, SCREEN_HEIGHT /2. - 120 - 64, 200, 240)];
    _chooseView.backgroundColor = [UIColor whiteColor];
    _chooseView.layer.cornerRadius = 10.0f;
    _chooseView.layer.masksToBounds = YES;

    [AnoutherBackGroundView addSubview:_chooseView];
    
    [_chooseView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.view);
        make.width.equalTo(self.view).multipliedBy(0.75);
        make.height.equalTo(self.view).multipliedBy(0.4);
    }];
    
    FilesView *filesView = [[FilesView alloc] init];
    [_chooseView addSubview:filesView];
    [filesView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.size.equalTo(_chooseView);
        make.center.equalTo(_chooseView);
    }];
    
    __weak typeof(self) weakSelf = self;
    filesView.fileCallback = ^(NSString *path) {
        weakSelf.firmwareFilename = path;
        weakSelf.chooseView.hidden = YES;
    };

    //在OTA页面中显示设备信息
    _deviceOtaInfos = @[].mutableCopy;
    
    NSMutableArray *devices = [[[CSRAppStateManager sharedInstance].selectedPlace.devices allObjects] mutableCopy];
    for (CSRDeviceEntity *deviceEntity in devices) {
        NSNumber *deviceId = deviceEntity.deviceId;
        NSString *uuid = [UDManager getDeviceUUIDString:deviceEntity.deviceId];
        NSString *name = deviceEntity.name;
        
        if (deviceId && name && uuid) {
            NSDictionary *dic = @{@"deviceId":deviceEntity.deviceId,
                                  @"uuid":uuid,
                                  @"name":name
                                  };
            [_deviceOtaInfos addObject:dic];
        }
    }
    
    CCLog(@"%@",_deviceOtaInfos);
    
}

-(void)viewDidDisappear:(BOOL)animated
{
    [[Discovery sharedInstance] setDiscoveryDelegate:nil];
    [[Discovery sharedInstance] stopScanning];
    
    [[OTAU sharedInstance] setOTAUDelegate:nil];
}

- (void)viewDidAppear:(BOOL)animated {
    AppDelegate *appDelegate= (AppDelegate *)[[UIApplication sharedApplication] delegate];
    if (!peripheralConnected) {
        [modeLabel setText:@"-"];
    }
    else if ([appDelegate.peripheralInBoot boolValue]==YES) {
        [modeLabel setText:@"BOOT"];
    }
    else {
        [modeLabel setText:@"APP"];
    }
    
}

#pragma 22222
- (void)chooseFile :(UIButton * )sender {
    int ROW = (int)sender.tag;
    //获取当前的文件
    NSArray *files = [[NSBundle mainBundle] pathsForResourcesOfType:@".xuv" inDirectory:@"./"];
    NSString *filepath = (NSString *) [files objectAtIndex:ROW];
    firmwareFilename = filepath;
    
    _chooseView.hidden = YES;
}

- (void) viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.bottomView.backgroundColor = [UIColor colorWithRed:63/255. green:69/255. blue:83/255. alpha:1];
    self.instructionsLabel = [[UILabel alloc] init];
    self.instructionsLabel.textAlignment = NSTextAlignmentCenter;
    self.instructionsLabel.textColor = [UIColor lightGrayColor];
//    self.instructionsLabel.font = [UIFont MED_FONT];
    [self.instructionsLabel setText: @"select multiple lights to update"];
    [self.instructionsLabel sizeToFit];
    self.instructionsLabel.numberOfLines = 2;
    float textHeight = self.instructionsLabel.frame.size.height;
    float textWidth = self.instructionsLabel.frame.size.width;
    
    float width = textWidth * 5/9;
    float spacing = (self.bottomView.frame.size.width - width)/2;
    
    self.instructionsLabel.frame = CGRectMake(spacing - 15, self.bottomView.frame.size.height/2. - textHeight, width + 30, textHeight   *2);
    [self.bottomView addSubview:self.instructionsLabel];
    NSLog(@"%f,%f",self.bottomView.frame.size.height,self.instructionsLabel.frame.origin.y);
    
    self.otherLabel = [[UILabel alloc] init];
    self.otherLabel.textColor = [UIColor lightGrayColor];
//    self.otherLabel.font = [UIFont MED_FONT];
    self.otherLabel.numberOfLines = 2;
    self.otherLabel.textAlignment = NSTextAlignmentCenter;
    //    [self.otherLabel setText:@"selected lights \n should be blinking"];
    [self.otherLabel sizeToFit];
    //    float width2 = self.otherLabel.frame.size.width;
    //    float spacing2 = (self.bottomView.frame.size.width - width2)/2;
//    self.otherLabel.frame = CGRectMake(self.instructionsLabel.frame.origin.x, 50, self.instructionsLabel.frame.size.width, 40);
    self.otherLabel.frame = CGRectMake(0, 50, self.bottomView.frame.size.width, 40);
    self.otherLabel.hidden = YES;
    [self.bottomView addSubview:self.otherLabel];
    
    float buttonWidth = 250;
    UIButton *button = [[UIButton alloc] initWithFrame:CGRectMake((self.bottomView.frame.size.width - buttonWidth)/2, self.bottomView.frame.size.height/3*2, buttonWidth, 40)];
    button.backgroundColor = [UIColor colorWithRed:229/255. green:143/255. blue:0/255. alpha:1.0];
    button.layer.cornerRadius = 20;
    [self.bottomView addSubview:button];
    button.hidden = YES;
    [button addTarget:self action:@selector(selectedBLEUpdate) forControlEvents:UIControlEventTouchUpInside];
    self.doTheGroupingButton = button;
    
    _progressBar_new = [[UIProgressView alloc] initWithFrame:CGRectMake(30, 40, self.bottomView.frame.size.width - 60, 60)];
    _progressBar_new.progress = 0;
    _progressBar_new.hidden = YES;
    [self.bottomView addSubview:_progressBar_new];
}
static int UpDataFiger = 0;
- (void) selectedBLEUpdate {
    
    CBPeripheral	*peripheral;
    peripheral = (CBPeripheral*)[_selectedLights objectAtIndex:UpDataFiger];
    _progressBar_new.hidden = NO;
    if ([peripheral state]!=CBPeripheralStateConnected) {
        [[Discovery sharedInstance] connectPeripheral:peripheral];
        // is this an OTAU peripheral?
        // Display "checking" in the cell view
        //        selectedCell = indexPath;
        [DeviceTable reloadData];
        
        // check for OTAU service
        [[Discovery sharedInstance] startOTAUTest:peripheral];
        
        //[discoveryViewDelegate setTarget:peripheral];
        [self statusMessage:[NSString stringWithFormat:@"Connecting %@\n",peripheral.name]];
        _otherLabel.hidden = NO;
        [_otherLabel setText:[NSString stringWithFormat:@"Connecting %@\n",peripheral.name]];
    }
    else if([[Discovery sharedInstance]isOTAUPeripheral:peripheral]){
        targetPeripheral = peripheral;
                [self setTarget:peripheral];
        
    }
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([[segue identifier] isEqualToString:@"chooseFirmware"]) {
        FirmwareSelector *fs = (FirmwareSelector *)[segue destinationViewController];
        fs.firmwareDelegate = self;
    }
    
    if ([[segue identifier] isEqualToString:@"chooseTarget"]) {
        DiscoverViewController *dvc = (DiscoverViewController *)[segue destinationViewController];
        dvc.discoveryViewDelegate = self;
    }
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

// Delegates
-(void) firmwareSelector:(NSString *) filepath {
    if ([filepath isEqualToString:@""]) {
    }
    else {
        NSString *filename = [[filepath lastPathComponent] stringByDeletingPathExtension];
        [firmwareName setTitle:filename forState:UIControlStateNormal];
        [firmwareName setAlpha:1.0];
        firmwareFilename = filepath;

    }
    [self dismissViewControllerAnimated:YES completion:nil];
    [self setStartAndAbortButtonLook];
}

-(void) setTarget:(id)peripheral
{
    if (peripheral != nil)
    {
        [targetName setTitle:[peripheral name] forState:UIControlStateNormal];
        [targetName setAlpha:1.0];
        targetPeripheral = peripheral;
        _otherLabel.text = @"CONNECTED";
        [connectionState setText:@"CONNECTED"];
        isInitRunning = YES;
        [self setStartAndAbortButtonLook];
        [[OTAU sharedInstance] initOTAU:peripheral];
    }
    
    // Dismiss Discovery View and any nulify all delegates set up for it.
    [[Discovery sharedInstance] setDiscoveryDelegate:nil];
//    [self dismissViewControllerAnimated:YES completion:nil];
    [[Discovery sharedInstance] stopScanning];
    [self setStartAndAbortButtonLook];
    
    //异步函数
    dispatch_async(queue, ^{
        while (1) {
            
            if (startButton.enabled) {
                
                [self startUpdate:nil];
                return ;
            }
        }
        
        
    });
}

- (IBAction)cancelFirmware:(id)sender
{
    [firmwareName setTitle:@"Set Firmware" forState:UIControlStateNormal];
    [firmwareName setAlpha:0.4];
    firmwareFilename=nil;
    [self setStartAndAbortButtonLook];
}

- (IBAction)cancelTarget:(id)sender
{
    [self clearTarget];
}

//============================================================================
// Called when the Start button is pressed
//
- (IBAction)startUpdate:(id)sender
{
//    if (isAbortButton==NO)
//    {
        if (firmwareFilename!=nil && targetPeripheral!=nil)
        {
            isAbortButton=YES;
            isUpdateRunning=YES;
            [self statusMessage:@"------[ Update Started ]------\n"];
            
            [[OTAU sharedInstance] startOTAU:firmwareFilename];//选择版本的路径  选择方法在firmwareSelector中tableview上的的选中事件上
            self.progressBar_new.progress = 0.0;
            [percentLabel setText: @"0%"];
            [self.otherLabel setText:@"0%"];
            [self setStartAndAbortButtonLook];
        }
//    }
}

//============================================================================
// Called when the Abort button is pressed
//
- (IBAction)abortUpdate:(id)sender
{
    if (isAbortButton==YES)
    {
        isAbortButton=NO;
        [self statusMessage:@"Update Aborted\n"];
        [[OTAU sharedInstance]  abortOTAU:targetPeripheral];
        isUpdateRunning=NO;
        [self setStartAndAbortButtonLook];
    }
}

-(void) clearTarget {
    [targetName setTitle:@"set target" forState:UIControlStateNormal];
    [targetName setAlpha:1.0];
//    targetPeripheral=nil;
    [self setStartAndAbortButtonLook];
}

//============================================================================
// Set the look of the Start and Abort Buttons to reflect whether or not the button is available.
//
// Call this method after...
//  - Setting the App File
//  - Choosing the target
//  - After Start Button is Pressed
//  - After Abort button is pressed
//  - At the end of an Update
//  - Update error received.
//
// To Disable button: set Alpha to 0.2 and Enabled to NO
// To Enable Button:  set Alpha to 1.0 and Enabled to YES
//
// Enable Start Button if App File and Target are both valid and update not running.
// Enable Abort Button if Update is running.
-(void) setStartAndAbortButtonLook
{
    if (isInitRunning || isUpdateRunning) {
        [startButton setEnabled:NO];
        [firmwareName setEnabled:NO];
        [targetName setEnabled:NO];
    }
    else {
        [firmwareName setEnabled:YES];
        [targetName setEnabled:YES];
        if (targetPeripheral!=nil && firmwareFilename!=nil)
        {
            [startButton setEnabled:YES];
        }
        else
        {
            [startButton setEnabled:NO];
        }
    }
    
    if (isUpdateRunning)
    {
        [abortButton setHidden:NO];
        [progressBar setHidden:NO];
//        [self.progressBar_new setHidden:NO];
        [percentLabel setHidden: NO];
        [abortButton setEnabled:YES];
        [startButton setHidden:YES];
    }
    else
    {
        [abortButton setHidden:YES];
        [abortButton setEnabled:NO];
        [progressBar setHidden:YES];
//         [self.progressBar_new setHidden:YES];
        [percentLabel setHidden: YES];
        [startButton setHidden:NO];
    }
}


/****************************************************************************/
/*								Open With.....                              */
/****************************************************************************/
-(void) handleOpenURL:(NSURL *)url {
    //NSError *outError;
    //NSString *fileString = [NSString stringWithContentsOfURL:url
    //                                               encoding:NSUTF8StringEncoding
    //                                                error:&outError];
    NSString *filename = [[url lastPathComponent] stringByDeletingPathExtension];
    [firmwareName setTitle:filename forState:UIControlStateNormal];
    [firmwareName setAlpha:1.0];
    firmwareFilename = url.path;
    [self statusMessage:[NSString stringWithFormat:@"Imported File %@\n",firmwareFilename]];
}



/****************************************************************************/
/*								Delegates                                   */
/****************************************************************************/
//============================================================================
// Update the progress bar when a progress percentage update is received during OTAU update.
-(void) didUpdateProgress: (uint8_t) percent {
    self.progressBar_new.hidden = NO;
    self.progressBar_new.progress = percent / 100.0f;
    [percentLabel setText: [NSString stringWithFormat:@"%d%%", percent]];
    [self.otherLabel setText: [NSString stringWithFormat:@"%d%%", percent]];
    if (percent == 100) {
        // Transfer is complete so update controls to hide abort and progress bar,
        // but show a disabled start button as init is running again to query versions
        // and cs keys. We will receive the "complete" delegate when that is done.
        isUpdateRunning = NO;
        isInitRunning = YES;
        [self setStartAndAbortButtonLook];
    }
}

//============================================================================
//
-(void) didUpdateBtaAndTrim:(NSData *)btMacAddress :(NSData *)crystalTrimValue {
    [self.deviceAddress setText: @"-"];
    [self.crystalTrim setText: @"-"];
    
    if (btMacAddress != nil && crystalTrimValue != nil) {
        // Display bluetooth address.
        const uint8_t *octets = (uint8_t*)[btMacAddress bytes];
        NSString *display = [NSString stringWithFormat:@"%02X:%02X:%02X:%02X:%02X:%02X",
                             octets[0], octets[1], octets[2], octets[3], octets[4], octets[5]];
        
        [deviceAddress setText:display];
        
        // Display crystal trim.
        const uint16_t *trim = (uint16_t*)[crystalTrimValue bytes];
        display = [NSString stringWithFormat:@"0x%X", *trim];
        [crystalTrim setText:display];
        [self statusMessage: @"Success: Read CS keys.\n"];
    }
    else {
        [self statusMessage: @"Failed to read CS keys.\n"];
    }
    
    if (isInitRunning) {
        isInitRunning = NO;
        [self setStartAndAbortButtonLook];
    }
}

//============================================================================
// This delegate is called after we have called initOTAU and the library has finished
// querying the peripheral.
-(void) didUpdateVersion:(uint8_t)otauVersion {
    [self.fwVersion setText: @"-"];
    
    if (otauVersion > 3) {
        [fwVersion setText: [NSString stringWithFormat:@"%d", otauVersion]];
        [self statusMessage: @"Success: Get version.\n"];
    }
    else {
        [self statusMessage: @"Failed to read OTAU version.\n"];
    }
}

//============================================================================
//
-(void) didUpdateAppVersion:(NSString*)appVersionString {
    [self statusMessage: [NSString stringWithFormat:@"Success: Got app version:%@\n", appVersionString]];
    if (appVersionString != nil) {
        [appVersion setText: appVersionString];
        [appVersionLabel setHidden: NO];
        [appVersion setHidden: NO];
    }
    else {
        [appVersionLabel setHidden: YES];
        [appVersion setHidden: YES];
    }
}

//============================================================================
// This delegate is called when the selected peripheral connection state changes.
-(void) didChangeConnectionState:(bool)isConnected {
    [deviceAddress setText: @"-"];
    [crystalTrim setText: @"-"];
    [fwVersion setText: @"-"];
    [modeLabel setText: @"-"];
    [challengeLabel setText: @"-"];
    [appVersion setText: @"-"];
    if (isConnected) {
        peripheralConnected = YES;
        [connectionState setText:@"CONNECTED"];
    }
    else {
        peripheralConnected = NO;
        [connectionState setText:@"DISCONNECTED"];
    }
}

//============================================================================
//
-(void) didChangeMode: (bool) isBootMode {
    if (isBootMode) {
        [modeLabel setText: @"BOOT"];
    }
    else {
        [modeLabel setText: @"APP"];
    }
}

//============================================================================
//
-(void) didUpdateChallengeResponse:(bool)challengeEnabled {
    if (challengeEnabled) {
        [challengeLabel setText: @"ENABLED"];
    }
    else {
        [challengeLabel setText: @"DISABLED"];
    }
}

//============================================================================
// Display an Alert upon successful completion
//成功回调
-(void) completed:(NSString *) message {
    isAbortButton=NO;
    isUpdateRunning=NO;
//    _progressBar_new.hidden = YES;
//    _otherLabel.hidden = YES;
    [self setStartAndAbortButtonLook];
    
    [[Discovery sharedInstance] setDiscoveryDelegate:self];
//    [[Discovery sharedInstance] startScanForPeripheralsWithServices];
    
    [[Discovery sharedInstance] disconnectPeripheral:targetPeripheral];
    if (!_upToDataLights) {
        _upToDataLights = [[NSMutableArray alloc] init];
    }
    [_upToDataLights addObject:targetPeripheral];
    [_groupedLights addObject:targetPeripheral];
    [_ungroupedLights removeObject:targetPeripheral];
    [_selectedLights removeObject:targetPeripheral];
    [DeviceTable reloadData];
    if (_selectedLights.count != 0) {
        _otherLabel.text = message;
        _otherLabel.text = [NSString stringWithFormat:@"%ld",_selectedLights.count];
        [self selectedBLEUpdate];
    }
    if (_selectedLights.count == 0) {
        _progressBar_new.hidden = YES;
        _otherLabel.hidden = YES;
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        NSString *title;
        
        title = @"OTAU";
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                        message:@"update successful"
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
    });

//    [self backButtton:nil];
}

//============================================================================
// Display the status in the Text view
-(void) statusMessage:(NSString *)message
{
//    [statusLog setText:[statusLog.text stringByAppendingString:message]];
//    NSRange range = NSMakeRange(statusLog.text.length - 1, 1);
//    [statusLog scrollRangeToVisible:range];
//    NSLog( @"statusMessage=====%@",message);
}


//============================================================================
// Display error as an Alert
-(void) otauError:(NSError *) error {
    if (isInitRunning) {
        isInitRunning = NO;
        [self clearTarget];
    }
    else if (isUpdateRunning) {
        isAbortButton = NO;
        isUpdateRunning = NO;
    }
    
    // Convert error code to 4 character string, as error codes will be in the range 1000-9999
    NSString *errorCodeString = [NSString stringWithFormat:@"%4d",(int)error.code];
    
    // Lookup Error string from error code
    NSString *errorString = NSLocalizedStringFromTable (errorCodeString, @"ErrorCodes", nil);
//    _otherLabel.text = errorString;
    
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"OTAU Error"
                                                        message:@"update failed"
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
    });
    
    [self setStartAndAbortButtonLook];
    if (_selectedLights.count != 0) {
        [_selectedLights removeObjectAtIndex:0];
        if (_selectedLights.count != 0)
        [self selectedBLEUpdate];
    }
}

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
- (IBAction)backButtton:(id)sender {
    
//    [discoveryViewDelegate setTarget:nil];
    [[Discovery sharedInstance] stopScanning];
    
    [self dismissViewControllerAnimated:YES completion:nil];
    
    return;
    UIStoryboard *secondStroyBoard=[UIStoryboard storyboardWithName:@"Main" bundle:nil];
    
    UIViewController *LightGroupView=[secondStroyBoard instantiateViewControllerWithIdentifier:@"UIViewController-CTE-eT-0s3"];
    
    [self.navigationController pushViewController:LightGroupView animated:YES];
    
}

/****************************************************************************/
#pragma mark - TableView Delegates					
/****************************************************************************/
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    NSInteger   res;
    res = [[[Discovery sharedInstance] foundPeripherals] count];
    _ungroupedLights = [[NSMutableArray alloc] init];
    _groupedLights = [[NSMutableArray alloc] init];
    for (int i = 0; i < res; i++) {
        CBPeripheral *peripheral = (CBPeripheral*)[[Discovery sharedInstance] foundPeripherals][i];
#pragma 读取当前UUID所对应的name 并显示出来
        NSString *string = [NSString stringWithFormat:@"%@",peripheral.identifier];
        string = [self handleStringWithString:string];
        DataBaseSimple * db = [DataBaseSimple shareInstance];
        ThingModel * M;
        int co = 0;
        if (_upToDataLights.count != 0) {
            for (int i = 0 ; i < _upToDataLights.count; i++) {
                 if ((CBPeripheral *)_upToDataLights[i] == peripheral) {
                     co = 1;
                     break;
                 }
            }
            if (co == 1) {
                 [_groupedLights addObject:peripheral];
            }else {
                if ([db selectFromDBWithLightOtaUUID:string].count ==0) {
                    if ([peripheral.name isEqualToString:@"otau_mesh"]) {
                        [_ungroupedLights addObject:peripheral];
                    }else if ([peripheral.name isEqualToString:@"CSRmesh"]) {
                        [_ungroupedLights addObject:peripheral];
                    }
                }else {
                    M = [db selectFromDBWithLightOtaUUID:string][0];
                    if ([M.Version isEqualToString:@"14"]) {
                        [_groupedLights addObject:peripheral];
                    }else
                        [_ungroupedLights addObject:peripheral];
                }
            }
        }else {
            if ([db selectFromDBWithLightOtaUUID:string].count ==0) {
                if ([peripheral.name isEqualToString:@"otau_mesh"]) {
                    [_ungroupedLights addObject:peripheral];
                }else if ([peripheral.name isEqualToString:@"CSRmesh"]) {
                    [_ungroupedLights addObject:peripheral];
                }
            }else {
                M = [db selectFromDBWithLightOtaUUID:string][0];
                if ([M.Version isEqualToString:@"14"]) {
                    [_groupedLights addObject:peripheral];
                }else
                    [_ungroupedLights addObject:peripheral];
            }
        }
        
        
        
        
        

    }
    if (section == 0) {
        return _ungroupedLights.count;
    }
    return (_groupedLights.count);
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    if (section == 0 && _ungroupedLights.count > 0) {
        return 60;
    }
    else if (section == 1 && _groupedLights.count > 0) {
        return 60;
    }
    return 0;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 60;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    GroupedLightTableViewCell *cell;
    CBPeripheral	*peripheral;
    
    cell = [tableView dequeueReusableCellWithIdentifier:@"lightCell"];
    if (!cell) {
        cell = [[GroupedLightTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"lightCell"];
    }
//    cell.textLabel.font = [UIFont MED_FONT];
    cell.isSelected = NO;
    
    if (indexPath.section == 0) {
        if (_ungroupedLights.count == 0) {
            
        }else
            peripheral = (CBPeripheral*)[_ungroupedLights objectAtIndex:indexPath.row];
    }
    
    if (indexPath.section == 1) {
        if (_groupedLights.count == 0) {
            
        }else
            peripheral = (CBPeripheral*)[_groupedLights objectAtIndex:indexPath.row];
    }
    
    if (_selectedLights) {
        for (int i = 0;  i < _selectedLights.count; i++) {
            if (_selectedLights[i] == peripheral) {
                cell.isSelected = YES;
            }
        }
    }
#pragma 读取当前UUID所对应的name 并显示出来
    NSString *string = [NSString stringWithFormat:@"%@",peripheral.identifier];
    string = [self handleStringWithString:string];
    DataBaseSimple * db = [DataBaseSimple shareInstance];
    ThingModel * M;
    if ([db selectFromDBWithLightOtaUUID:string].count ==0) {
        
    }else {
        M = [db selectFromDBWithLightOtaUUID:string][0];
    }
    
    if ([[peripheral name] length] > 0)
        [[cell textLabel] setText:[peripheral name]];
//    else
//        [[cell textLabel] setText:@"No-Name"];
    
    //[[cell detailTextLabel] setText:@"Mac Address"];
#pragma 显示当前UUID所对应的灯的名字
    if (M != nil) {
        
        [[cell textLabel] setText:M.Name];
        
    }
//    cell.isSelected = YES;
    if (indexPath.section == 0) {
        cell.textLabel.textColor = [UIColor whiteColor];
        cell.imageView.tintColor = [UIColor whiteColor];
    }else if (indexPath.section == 1) {
        cell.isSelected = NO;
        cell.textLabel.textColor = [UIColor lightGrayColor];
        cell.imageView.tintColor = [UIColor lightGrayColor];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.backgroundColor = [UIColor clearColor];
    
    CCLog(@"ota,peripheral: %@",peripheral.identifier)
    
    for (NSDictionary *dic in _deviceOtaInfos) {
        
        if ([dic[@"uuid"] isEqualToString:peripheral.identifier.UUIDString]) {
            cell.textLabel.text = dic[@"name"];
            break;
        }
    }
    
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

- (UIView *)tableView:(UITableView *)tableView
viewForHeaderInSection:(NSInteger)section {
    UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0, -3, tableView.frame.size.width, 60)];
    UILabel *headerLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 05, tableView.frame.size.width, 40)];
//    headerLabel.font = [UIFont MED_FONT];
    headerLabel.textAlignment = NSTextAlignmentCenter;
    if (section == 0) {
        headerLabel.backgroundColor = [UIColor colorWithRed:255/255. green:249/255. blue:240/255. alpha:1.0];
        headerLabel.textColor = [UIColor colorWithRed:72/255. green:79/255. blue:96/255. alpha:1.0];
        headerLabel.text = @"update available";
    }
    else if (section == 1) {
        headerLabel.backgroundColor = [UIColor colorWithRed:255/255. green:249/255. blue:240/255. alpha:1.0];
        headerLabel.textColor = [UIColor colorWithRed:72/255. green:79/255. blue:96/255. alpha:1.0];
        headerLabel.text = @"up to date";
    }
    
    [view addSubview:headerLabel];
    return view;
}

- (void) tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 1) {
        return ;
    }
    
    GroupedLightTableViewCell * cell = [tableView cellForRowAtIndexPath:indexPath];
    cell.isSelected = !cell.isSelected;
    
    if (!_selectedLights) {
        _selectedLights = [[NSMutableArray alloc] init];
    }
    if (cell.isSelected) {
        [_selectedLights addObject:_ungroupedLights[indexPath.row]];
    }else
        [_selectedLights removeObject:_ungroupedLights[indexPath.row]];
    [self updateBottomView];
}


-(void)updateBottomView {
    
    NSSet *selectedSet = [NSSet setWithArray:self.selectedLights];
    NSSet *thisGroupSet = [NSSet setWithArray:self.thisGroupLights];
    BOOL allMatchedUp = [selectedSet isEqualToSet:thisGroupSet];
    dispatch_async(dispatch_get_main_queue(), ^{
        if(allMatchedUp){
            self.instructionsLabel.hidden = NO;
            self.otherLabel.hidden = YES;
            self.doTheGroupingButton.hidden = YES;
//            _progressBar_new .hidden = YES;
        }
        else {
            self.instructionsLabel.hidden = YES;
            //            self.otherLabel.hidden = NO;
            //            AssocitedProgress.hidden = NO;
//            for (int i = 0; i < self.selectedLights.count; i++) {
//                MeshDevice *meshDevice = self.delecateLights[i];
//                NSString *str = [meshDevice getAssociationStatus];
//                if ([str isEqualToString:@"Associated"]) {
//                    [self.selectedLights removeObjectAtIndex:i];
//                    [self.delecateLights removeObjectAtIndex:i];
//                }else if ([str isEqualToString:@"Failed"]) {
//                    [self.selectedLights removeObjectAtIndex:i];
//                    [self.delecateLights removeObjectAtIndex:i];
//                    GroupedLightTableViewCell * cell = [DeviceTable cellForRowAtIndexPath:self.selectedLights[i]];
//                    cell.isSelected = NO;
//                }
//            }
            if (self.selectedLights.count == 1) {
                [self.doTheGroupingButton setTitle:[NSString stringWithFormat:@"update %ld light", (unsigned long)self.selectedLights.count] forState:UIControlStateNormal];
            }else
                [self.doTheGroupingButton setTitle:[NSString stringWithFormat:@"update %ld lights", (unsigned long)self.selectedLights.count] forState:UIControlStateNormal];
            self.doTheGroupingButton.hidden = NO;
        }
        
    });
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
    [DeviceTable reloadData];
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
        [self setTarget:peripheral];
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

#pragma mark - Other
- (void)dealloc {
    NSLog(@"dealloc: %@",self);
}

@end
