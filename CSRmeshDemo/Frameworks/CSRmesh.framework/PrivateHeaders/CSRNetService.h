//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;

/*!
 @class CSRNetService
 @abstract Store the address information for the service
 @discussion The device may have one or more addresses.
 */
@interface CSRNetService : NSObject

/// @brief name The name of the object on the network
@property (nonatomic, strong) NSString *name;

/// @brief addresses The list of ip addresses for this network service
@property (nonatomic, strong) NSMutableArray *addresses;

/// @brief extra data about the bonjour service
@property (nonatomic, strong) NSMutableDictionary *txtRecordData;

/*!
 @brief Create a net service
 @param serviceName The service name
 @param addressData The array of NSData containing address information for this device
 @param recordData Extra text information about the service
 */
- (id)initWithName:(NSString *)serviceName
         ipAddress:(NSArray *)addressData
     txtRecordData:(NSDictionary *)recordData;

@end
