//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRNetService.h"

/*!
 @header CSRNetServiceBrowser
 Search for Bonjour services
 */

@protocol CSRNetServiceBrowserDelegate;

/*!
 @class CSRNetServiceBrowser
 @abstract Singleton class that manages searching for Bonjour services
 @discussion The network service browser implements the CSRNetServiceBrowserDelegate
 */
@interface CSRNetServiceBrowser : NSObject

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet *delegates;

/// @brief The list of services
@property (nonatomic, strong) NSMutableArray *services;

/*!
 @brief The singleton instance
 @return sharedInstance - The id of the singleton object.
 */
+ (CSRNetServiceBrowser *)sharedInstance;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<CSRNetServiceBrowserDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<CSRNetServiceBrowserDelegate>)delegate;

/*!
 @brief Start looking for Bonjour services with this pattern. The service will call
 delegates every time a new service is found.
 @param serviceType Typically _[a service]._tcp e.g. _mesh._tcp
 @param domain If blank use a blank string rather than nil
 */
- (void)startBrowsing:(NSString *)serviceType domain:(NSString *)domain;

/*!
 @brief Stop looking for Bonjour services.
 */
- (void)stopBrowsing;

@end

/*!
 @protocol CSRNetServiceBrowserDelegate
 @discussion Callbacks for service discovery
 */
@protocol CSRNetServiceBrowserDelegate <NSObject>

@optional

/*!
 @brief Called when a service is found and it's IP Address resolved.
 @param service The CSRNetService found
 */
- (void)didFindService:(CSRNetService *)service;

@end
