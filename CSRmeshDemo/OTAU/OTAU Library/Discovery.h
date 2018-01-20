//
//  Discovery.h
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

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>



/****************************************************************************/
/*							UI protocols									*/
/****************************************************************************/
@protocol DiscoveryDelegate <NSObject>
@optional
- (void) discoveryDidRefresh;
- (void) discoveryStatePoweredOff;
- (void) otauPeripheralTest:(CBPeripheral *) peripheral :(BOOL) isOtau;
- (void) didConnectPeripheral:(CBPeripheral *) peripheral;
- (void) didDiscoverPeripheral:(CBPeripheral *) peripheral;
- (void) didDiscoverServices:(CBPeripheral *) peripheral;
- (void) centralPoweredOn;
- (void) didDisconnect:(CBPeripheral *)peripheral error:(NSError *)error;
- (void) statusMessage:(NSString *)message;
- (void) didChangeMode;

@end



/****************************************************************************/
/*							Discovery class									*/
/****************************************************************************/
@interface Discovery : NSObject

+ (id) sharedInstance;


/****************************************************************************/
/*								UI controls									*/
/****************************************************************************/
@property (nonatomic, assign) id<DiscoveryDelegate>  discoveryDelegate;


/****************************************************************************/
/*								Actions										*/
/****************************************************************************/
- (void) startScanForPeripheralsWithServices;
- (void) stopScanning;

- (void) connectPeripheral:(CBPeripheral*)peripheral;
- (void) disconnectPeripheral:(CBPeripheral*)peripheral;

/****************************************************************************/
/*								Utility Methods								*/
/****************************************************************************/
-(void) retrieveCachedPeripherals;
-(BOOL) isOTAUPeripheral:(CBPeripheral *) peripheral;
-(void) startOTAUTest:(CBPeripheral *) peripheral;
-(NSArray *) retrievePeripheralsWithIdentifier:(NSUUID *) uuid;
-(void) removeCachedPeripheral:(NSUUID *) uuid;

/****************************************************************************/
/*							Access to the devices							*/
/****************************************************************************/
@property (strong, nonatomic) NSMutableArray    *foundPeripherals;
@property (strong, nonatomic) CBPeripheral      *connectedPeripheral;
@end

