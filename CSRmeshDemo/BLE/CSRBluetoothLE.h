//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "CBPeripheral+Info.h"


/****************************************************************************/
/*							UI protocols									*/
/****************************************************************************/
@protocol CSRBluetoothLEDelegate <NSObject>
@optional
- (void) CBPowerIsOff;
- (void) CBPoweredOn;
- (void) discoveredBridge;
- (void) didConnectBridge :(CBPeripheral *) bridge;
- (void) didDiscoverBridgeService :(CBPeripheral *) bridge;
@end



/****************************************************************************/
/*						Public Interface                                    */
/****************************************************************************/
@interface CSRBluetoothLE : NSObject

    
+ (id) sharedInstance;
-(void) connectPeripheral:(CBPeripheral *) peripheral;
-(void) disconnectPeripheral:(CBPeripheral *) peripheral;
-(void)cc_disconnectPeripheral:(CBPeripheral *) peripheral;

-(void) connectPeripheralNoCheck:(CBPeripheral *) peripheral;
-(void) removeDiscoveredPeripheralsExceptConnected;
-(void) startScan;
-(void) stopScan;
- (void)powerOnCentralManager;
- (void)powerOffCentralManager;

-(void) setScanner :(BOOL) stateRequired source:(id) source;

@property (nonatomic, strong) NSMutableArray *discoveredBridges;
@property (nonatomic, weak) id<CSRBluetoothLEDelegate>  bleDelegate;
@property (nonatomic) CBCentralManagerState cbCentralManagerState;


@end
