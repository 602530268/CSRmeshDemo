//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import "CSRNetService.h"

/*!
 @class CSRGatewayNetService
 @abstract A CSR gateway with mesh connectivity
 @discussion Allow communications between local mesh network and the cloud
 */
@interface CSRGatewayNetService : CSRNetService

/// @brief The base path to use for REST commands
@property (nonatomic) NSString *basePath;

/// @brief The gateways UUID
@property (nonatomic) NSString *gatewayUUID;

@end
