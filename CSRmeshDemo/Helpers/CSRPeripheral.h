//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <CoreBluetooth/CoreBluetooth.h>

/*!
 @header CSRPeripheral
 A wrapper class to hold extra information about a CBPeripheral
 */

/*!
 @class CSRPeripheral
 @abstract A CBPeripheral wrapper
 @discussion A wrapper class to hold extra information about a CBPeripheral
 */
@interface CSRPeripheral : NSObject

/// @brief The CBPeripheral
@property (nonatomic) CBPeripheral *peripheral;

/// @brief The advertisement data dictionary
@property (nonatomic) NSDictionary *advertisementData;

/// @brief The signal strength upon discovery
@property (nonatomic) NSNumber *signalStrength;

/*!
 @brief create a new instance of the wrapper class
 @param cbPeripheral The CBPeripheral
 @param dict A dictionary containing extra advertising data
 @param rssi The signal strength value
 @return CSRPeripheral
 */
- (id)initWithCBPeripheral:(CBPeripheral *)cbPeripheral
         advertisementData:(NSDictionary *)dict
                      rssi:(NSNumber *)rssi;

/*!
 @brief The current connection status of the peripheral
 @return BOOL true if the peripheral is currently connected
 */
- (BOOL)isConnected;

@end
