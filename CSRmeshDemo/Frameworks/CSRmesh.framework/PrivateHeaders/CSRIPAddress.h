//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;

/**
 @enum CSRNetworkAddressType - The address family
 */
typedef NS_ENUM(NSInteger, CSRNetworkAddressType) {
    /** IPv4 */
    NetworkAddressTypeIPV4,
    /** IPv6 */
    NetworkAddressTypeIPV6,
    /** A MAC address */
    NetworkAddressTypeMac
};

/*!
 @class CSRIPAddress
 @abstract Wrapper for the system address
 @discussion The port number will be zero if unset
 */
@interface CSRIPAddress : NSObject

/// @brief The address string
@property (nonatomic) NSString *ipAddress;
/// @brief The port number
@property (nonatomic) NSInteger portNumber;
/// @brief The address type
@property (nonatomic) CSRNetworkAddressType type;

/*!
 @brief Create an address
 @param addressData The NSData containing address information for this interface
 */
- (id)initWithData:(NSData *)data;

@end
