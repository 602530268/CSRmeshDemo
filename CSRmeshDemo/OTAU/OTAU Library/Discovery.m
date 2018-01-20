//
//  Discovery.m
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
// Peripheral and service discovery
// 1. A scan is automatically started when the Central Manager is powered ON
// 2. Scanning stops upon exiting the Discover Devices View
//____________________________________________________________________________


#import "Discovery.h"
#import "OTAU.h"
#import "AppDelegate.h"
#import "DataBaseSimple.h"
#import "ThingModel.h"

/****************************************************************************/
/*			Private variables and methods									*/
/****************************************************************************/

@interface Discovery () <CBCentralManagerDelegate, CBPeripheralDelegate> {
	CBCentralManager    *centralManager;
	BOOL				pendingInit;
}
@end


@implementation Discovery

@synthesize foundPeripherals;
@synthesize discoveryDelegate;
@synthesize connectedPeripheral;


#pragma mark -
#pragma mark Init
/****************************************************************************/
/*									Init									*/
/****************************************************************************/
// Use singleton pattern as we only need one instance of this class.
// First call will instantiate the one object & initialise it.
// Returns a pointer to the self object
+ (id) sharedInstance {
	static Discovery	*this	= nil;
    
	if (!this)
		this = [[Discovery alloc] init];
    
	return this;
}


//============================================================================
// One time initialisation, called after instatiation of this singleton class
//
- (id) init {
    self = [super init];
    if (self) {
		pendingInit = YES;
		foundPeripherals = [[NSMutableArray alloc] init];
		centralManager = [[CBCentralManager alloc] initWithDelegate:self
                                                              queue:nil
                                                            options:@{CBCentralManagerOptionRestoreIdentifierKey:@"OTAU"}];
	}
    return self;
}


#pragma mark -
#pragma mark Discovery
/****************************************************************************/
/*								Discovery                                   */
/****************************************************************************/
// Scan for peripherals that advertise the services given in servicesUUIDs
// if servicesUUID is nil then scan for all peripherals
- (void) startScanForPeripheralsWithServices {
    if (centralManager && centralManager.state==CBCentralManagerStatePoweredOn) {
        [foundPeripherals removeAllObjects];
        connectedPeripheral=nil;
        [centralManager scanForPeripheralsWithServices:nil options:nil];
        [self statusMessage:[NSString stringWithFormat:@"Scanning...\n"]];
    }
}


- (void) stopScanning {
	[centralManager stopScan];
}

/****************************************************************************/
/*								Discovery  Delegates                        */
/****************************************************************************/
// centralManager:scanForPeripheralsWithServices initiated callback
// In turn call the didDidcoverPeripheral delegate
- (void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI {
    NSLog(@"did discover peripheral %@",peripheral.name);
    
 	if (![foundPeripherals containsObject:peripheral]) {
		[foundPeripherals addObject:peripheral];
        
        if ([peripheral.name isEqualToString:@"otau_mesh"]) {
            [self discoveryDidRefresh];
        }else if ([peripheral.name isEqualToString:@"CSRmesh"]) {
            [self discoveryDidRefresh];
        }
	}
    NSArray *keyArray=[advertisementData[@"kCBAdvDataServiceData"] allKeys];//LightUUID
    NSArray *valueArray=[advertisementData[@"kCBAdvDataServiceData"] allValues];//version  格式0103 1.3版本
    NSString * str = [NSString stringWithFormat:@"%@",keyArray[0]];
    NSString * str1 = [[NSString alloc] initWithData:valueArray[0] encoding:NSASCIIStringEncoding];
    if ([str1 intValue] == 14) {
        
    }
    DataBaseSimple * db = [DataBaseSimple shareInstance];
    ThingModel * M = [[ThingModel alloc] init];
        if ([db selectFromDBWithLightUUID:str].count != 0) {
            NSString *string = [NSString stringWithFormat:@"%@",peripheral.identifier];
            string = [self handleStringWithString:string];
            M.OtaUUID = string;
            M.Version = str1;
            M.LightUUID = str;
            [db updataInfoOtaUUIDandVersion:M];
        }
    [self didDiscoverPeripheral:peripheral];
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

//============================================================================
// Connected to Peripheral, now initiate discover services
- (void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral {
    NSLog(@"Established connection to Peripheral %@\n",peripheral.name);
    [self statusMessage:[NSString stringWithFormat:@"Established Connection To Peripheral %@\n",peripheral.name]];
    
    peripheral.delegate=self;
 
    AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
    appDelegate.discoveredChars = [NSNumber numberWithBool: NO];
    if (peripheral.services.count==0) {
        NSLog(@" -Discovering Services");
        [peripheral discoverServices:nil];
    }
    else {
        NSLog(@" -skipped discover services");
        for (CBService *service in peripheral.services) {
            NSLog (@" - Service=%@",service.UUID);
            [self statusMessage:[NSString stringWithFormat:@" - Service=%@",service.UUID]];
        }
    }
    
    
    [self didConnectPeripheral:peripheral];

}

//============================================================================
// Services discovered, now look for OTAU service to determine OTAU capability.
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error {
    bool isOtau=NO;
    NSLog(@"did discover services for peripheral %@",peripheral.name);
    if (error == nil) {
        if (peripheral.state==CBPeripheralStateConnected) {
            [self didDiscoverServices:peripheral];
            [self statusMessage:[NSString stringWithFormat:@"Found Services\n"]];
            CBUUID *uuid = [CBUUID UUIDWithString:serviceApplicationOtauUuid];
            CBUUID *bl_uuid = [CBUUID UUIDWithString:serviceBootOtauUuid];
            CBUUID *devInfoUuid = [CBUUID UUIDWithString:serviceDeviceInfoUuid];
            AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
            appDelegate.devInfoService = nil;
            for (CBService *service in peripheral.services) {
                NSLog(@" -Found service %@",service.UUID);
                [self statusMessage:[NSString stringWithFormat:@"%@\n",service.UUID]];
                if ([service.UUID isEqual:uuid]) {
                    isOtau=YES;
                    appDelegate.peripheralInBoot = [NSNumber numberWithBool: NO];
                    [self didChangeMode];
                    [peripheral discoverCharacteristics:nil forService:service];
                    appDelegate.targetService = service;
                    if (appDelegate.devInfoService != nil) {
                        break;
                    }
                }
                else if ([service.UUID isEqual:bl_uuid]) {
                    isOtau = YES;
                    appDelegate.peripheralInBoot = [NSNumber numberWithBool: YES];
                    [self didChangeMode];
                    [peripheral discoverCharacteristics:nil forService:service];
                    appDelegate.targetService = service;
                    if (appDelegate.devInfoService != nil) {
                        break;
                    }
                }
                else if ([service.UUID isEqual:devInfoUuid]) {
                    [peripheral discoverCharacteristics:nil forService:service];
                    appDelegate.devInfoService = service;
                    if (isOtau) {
                        // Already found the OTAU service so we are done now.
                        break;
                    }
                }
            }
            [self discoveryDidRefresh];
            
        }
    }
    else {
        NSLog(@"%@ Error = %@", peripheral.name, [error userInfo]);
    }

}


//============================================================================
// Discover Characteristics for either Application or Boot OTAU service.
- (void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error {
    NSLog(@"did discover chars for peripheral %@ and Service %@",peripheral.name, service.UUID);
    
    if (error == nil) {
        CBUUID *uuid = [CBUUID UUIDWithString:serviceApplicationOtauUuid];
        CBUUID *bl_uuid = [CBUUID UUIDWithString:serviceBootOtauUuid];

        if ([service.UUID isEqual:uuid] || [service.UUID isEqual:bl_uuid]) {
            AppDelegate *appDelegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
            appDelegate.discoveredChars = [NSNumber numberWithBool: YES];
            [self otauPeripheralTest:peripheral :YES];
        }
        
        for (CBCharacteristic *characteristic in service.characteristics) {
            NSLog(@"Discovered characteristic %@", characteristic.UUID);
        }
    }
}



//============================================================================
// Reconnect a peripheral that has been switched from Application to Boot mode.
- (void) centralManager:(CBCentralManager *)central didRetrieveConnectedPeripherals:(NSArray *)peripherals {
	CBPeripheral	*peripheral;
	
    NSLog(@"did retrieve connected peripherals");

	for (peripheral in peripherals) {
		[central connectPeripheral:peripheral options:nil];
	}
	[self discoveryDidRefresh];
}


//============================================================================
- (void) centralManager:(CBCentralManager *)central didRetrievePeripheral:(CBPeripheral *)peripheral {
    NSLog(@"did retrieve peripheral %@",peripheral.name);
	[central connectPeripheral:peripheral options:nil];
	[self discoveryDidRefresh];
}

#pragma mark -
#pragma mark Connection/Disconnection
/****************************************************************************/
/*						Connection/Disconnection                            */
/****************************************************************************/
- (void) connectPeripheral:(CBPeripheral*)peripheral {
    NSLog(@"attempt connect to Peripheral %@",peripheral.name);
	if ([peripheral state]!=CBPeripheralStateConnected) {
		[centralManager connectPeripheral:peripheral options:nil];
	}
}


- (void) disconnectPeripheral:(CBPeripheral*)peripheral {
    NSLog(@"attempt disconnect Peripheral %@",peripheral.name);
    if (peripheral) {
        [centralManager cancelPeripheralConnection:peripheral];
    }
}



- (void) centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    NSLog(@"Attempted connection to peripheral %@ failed: %@", [peripheral name], [error localizedDescription]);
}


- (void) centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    NSLog(@"did disconnect Peripheral %@\n",peripheral.name);
    [self statusMessage:[NSString stringWithFormat:@"Removed Connection To Peripheral %@\n",peripheral.name]];
    [self didDisconnect:peripheral error:error];
}


- (void) clearDevices {
    NSLog(@"remove objects in foundPeripherals");
    [foundPeripherals removeAllObjects];
}



//============================================================================
// Load previously connected device, by its Service UUID
-(void) retrieveConnectedPeripheral:(NSArray *) services {
    NSLog(@"Retrieve Connected Peripherals %@", services);
    NSArray *peripherals = [centralManager retrieveConnectedPeripheralsWithServices:services];
    if (peripherals) {
        for (CBPeripheral *peripheral in peripherals) {
            [foundPeripherals addObject:peripheral];
        }
        [self discoveryDidRefresh];
    }
}


/****************************************************************************/
/*								CB Central Delegates						*/
/****************************************************************************/

-(void) centralManager:(CBCentralManager *)central willRestoreState:(NSDictionary *)state {
}


// Bluetooth Module change of state
// Mainly used to check the Bluetooth is powered up and to a;ert the user if it is not.
//
- (void) centralManagerDidUpdateState:(CBCentralManager *)central
{
    static CBCentralManagerState previousState = -1;
    
	switch ([centralManager state]) {
		case CBCentralManagerStatePoweredOff: {
            [self statusMessage:[NSString stringWithFormat:@"Bluetooth Powered Off\n"]];
            NSLog(@"Central Powered OFF");
            [foundPeripherals removeAllObjects];
            [self discoveryDidRefresh];
            
			/* Tell user to power up bluetooth, but not on first run - the Framework will alert in that instance. */
            [self discoveryStatePoweredOff];
			break;
		}
            
		case CBCentralManagerStateUnauthorized: {
			/* Tell user the app is not allowed. */
			break;
		}
            
		case CBCentralManagerStateUnknown: {
			/* Bad news, let's wait for another event. */
			break;
		}
            
		case CBCentralManagerStatePoweredOn: {
            [self statusMessage:[NSString stringWithFormat:@"Bluetooth Powered On\n"]];
            NSLog(@"Central powered ON");
            [foundPeripherals removeAllObjects];
            connectedPeripheral=nil;
			pendingInit = NO;
            [central scanForPeripheralsWithServices:nil options:nil];
            [self statusMessage:[NSString stringWithFormat:@"Scanning...\n"]];
            break;
		}
            
		case CBCentralManagerStateResetting: {
            NSLog(@"Central Resetting");
            [self discoveryDidRefresh];
            
			pendingInit = YES;
			break;
		}
            
        case CBCentralManagerStateUnsupported:
            break;

	}
    
    previousState = [centralManager state];
}

/****************************************************************************/
/*								Utility Functions                           */
/****************************************************************************/
// Gets an array of the saved peripherals
// It is quicker and takes less power than scanning for new devices
-(void) retrieveCachedPeripherals {
    NSArray *services = [[NSArray alloc] initWithObjects:
                         [CBUUID UUIDWithString:serviceApplicationOtauUuid], nil];
    
    [self retrieveConnectedPeripheral:services];
}


//============================================================================
// Before OTAU can be used on a device, it must first be checked for this capability.
// The existence of service kOtaUpgradeApplicationServiceUuid is an indicator of this.
// Service discovery is by way of a call back and therefore this test is split across two methods.
//
// This method connects to the device and reads its services in preperation for a call to
// isOTAUPeripheral which actually carries out the check.
//
-(void) startOTAUTest:(CBPeripheral *) peripheral {
    [self statusMessage:[NSString stringWithFormat:@"\nStart: OTAU Test\n"]];

    if (peripheral.state!=CBPeripheralStateConnected)
    {
        [self connectPeripheral:peripheral];
    }
    else {
        if (peripheral.services.count<1)
        {
            [peripheral discoverServices:nil];
        }
    }
}

//============================================================================
// Test for OTAU capability.
//  - This is indicated by the presence of serviceApplicationOtauUuid
-(BOOL) isOTAUPeripheral:(CBPeripheral *) peripheral {
    NSLog(@"Is this OTAU peripheral: %@",peripheral.name);
    CBUUID *uuid = [CBUUID UUIDWithString:serviceApplicationOtauUuid];
    for (CBService *service in peripheral.services) {
        NSLog(@" -Service = %@",service.UUID);
        if ([service.UUID isEqual:uuid]){
            return (YES);
        }
    }
    return (NO);
}

//============================================================================
// Retrieve a previously connected to device by reference to its UUID
// Use the UUID to reconnect when switching device from Application to Boot.
-(NSArray *) retrievePeripheralsWithIdentifier:(NSUUID *) uuid {
    NSLog(@"Retrieve peripherals with UUID=%@",[uuid UUIDString]);
    NSArray *peripheralIdentifiers = [[NSArray alloc]initWithObjects:uuid, nil];
    
    return([centralManager retrievePeripheralsWithIdentifiers:peripheralIdentifiers]);

}


//============================================================================
// Called when the user deletes a cached peripheral from the table of peripherals.
-(void) removeCachedPeripheral:(NSUUID *) uuid {
}


//============================================================================
// Delegate calls grouped here for convenience. Observe following precautions before calling delegate
// 1. Run the call on the Main thread
// 2. Check the delegated object is valid
// 3. Check the delegated methid is implemented

-(void) discoveryDidRefresh {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(discoveryDidRefresh)])
            [discoveryDelegate discoveryDidRefresh];
    }];    
}

-(void) discoveryStatePoweredOff {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(discoveryStatePoweredOff)])
            [discoveryDelegate discoveryStatePoweredOff];
    }];
}

-(void) otauPeripheralTest:(CBPeripheral *) peripheral :(BOOL) isOtau {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(otauPeripheralTest::)])
            [discoveryDelegate otauPeripheralTest:peripheral:isOtau];
    }];
}

-(void) didConnectPeripheral:(CBPeripheral *) peripheral {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(didConnectPeripheral:)])
            [discoveryDelegate didConnectPeripheral:peripheral];
    }];
}

-(void) didDiscoverPeripheral:(CBPeripheral *) peripheral {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(didDiscoverPeripheral:)])
            [discoveryDelegate didDiscoverPeripheral:peripheral];
    }];
}

-(void) didDiscoverServices:(CBPeripheral *) peripheral {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(didDiscoverServices:)])
            [discoveryDelegate didDiscoverServices:peripheral];
    }];
}

-(void) centralPoweredOn {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(centralPoweredOn)])
            [discoveryDelegate centralPoweredOn];
    }];
}

-(void) didDisconnect:(CBPeripheral *)peripheral error:(NSError *)error {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(didDisconnect: error:)])
            [discoveryDelegate didDisconnect:peripheral error:error];
    }];
}

-(void) statusMessage:(NSString *)message {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(statusMessage:)])
            [discoveryDelegate statusMessage:message];
    }];
}

-(void) didChangeMode {
    [[NSOperationQueue mainQueue] addOperationWithBlock:^ {
        if(discoveryDelegate && [discoveryDelegate respondsToSelector:@selector(didChangeMode)])
            [discoveryDelegate didChangeMode];
    }];
}


@end
