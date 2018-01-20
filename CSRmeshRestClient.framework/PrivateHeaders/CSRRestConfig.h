/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 
 REVISION:      $Revision: #1 $
 */

#import <Foundation/Foundation.h>

#import "CSRRestFileLogger.h"

/**
 * List of supported server components
*/
typedef NS_OPTIONS(NSInteger, CSRRestServerComponent){
    /*!
     Command and control server
     */
    CSRRestServerComponent_CNC,
    
    /*!
     Configuration server
     */
    CSRRestServerComponent_CONFIG,
    
    /*!
     Authentication server
     */
    CSRRestServerComponent_AUTH
};

/**
 * List of supported connection channel
 */
typedef NS_OPTIONS(NSInteger, CSRRestConnectionChannel){
    /*!
     connect over cloud
     */
    CSRRestConnectionChannel_CLOUD,
    
    /*!
     connect over gateway
     */
    CSRRestConnectionChannel_GATEWAY
};

/*!
 Manages global configurations like CNC Server url, port, http request retry interval etc..
 */
@interface CSRRestConfig : NSObject


/*!
 This method must be called upon the first use of the CSRRestConfig as it creates and initialises a singleton object and returns a handle to it so that the same can be used to invoke instance methods and properties.
 
 @return id - The id of the singleton object.
 */
+(id)sharedInstance;

/*!
 Connection channel for rest lib.
 Default value is CSRRestConnectionChannel_GATEWAY
 */
@property (nonatomic, assign, readonly) CSRRestConnectionChannel connectionChannel;

/*!
 Command and control server URL.
 Default value is http://nil/csrmesh/cnc
 */
@property (nonatomic, strong, readonly) NSString *serverUrlCNC;

/*!
 Command and control server URI scheme.
 Default value is http
 */
@property (nonatomic, strong, readonly) NSString *uriSchemeCNC;

/*!
 Command and control server host.
 Default value is nil
 */
@property (nonatomic, strong, readonly) NSString *hostCNC;

/*!
 Command and control server port.
 Default value is 80
 */
@property (nonatomic, strong, readonly) NSString *portCNC;

/*!
 Command and control server base path.
 Default value is /csrmesh/cnc
 */
@property (nonatomic, strong, readonly) NSString *basePathCNC;

/*!
 Config server URL.
 Default value is http://nil/csrmesh/config
 */
@property (nonatomic, strong, readonly) NSString *serverUrlConfig;

/*!
 Config server URI scheme.
 Default value is http
 */
@property (nonatomic, strong, readonly) NSString *uriSchemeConfig;

/*!
 Config server host.
 Default value is nil
 */
@property (nonatomic, strong, readonly) NSString *hostConfig;

/*!
 Config server port.
 Default value is 80
 */
@property (nonatomic, strong, readonly) NSString *portConfig;

/*!
 Config server base path.
 Default value is /csrmesh/cnc
 */
@property (nonatomic, strong, readonly) NSString *basePathConfig;

/*!
 Auth server URL.
 Default value is http://nil/csrmesh/security
 */
@property (nonatomic, strong, readonly) NSString *serverUrlAuth;

/*!
 Config server URI scheme.
 Default value is http
 */
@property (nonatomic, strong, readonly) NSString *uriSchemeAuth;

/*!
 Auth server host.
 Default value is nil
 */
@property (nonatomic, strong, readonly) NSString *hostAuth;

/*!
 Auth server port.
 Default value is 80
 */
@property (nonatomic, strong, readonly) NSString *portAuth;

/*!
 Auth server base path.
 Default value is /csrmesh/security
 */
@property (nonatomic, strong, readonly) NSString *basePathAuth;

/*!
 Minimum interval between post and respective first get state call, in seconds.
 Default value is 2 seconds.
 */
@property (nonatomic, assign, readwrite) NSInteger minWaitingTimeAckResponse;

/*!
 Maximum retry attempts required for failed requests.
 Default value is 5.
 */
@property (nonatomic, assign, readwrite) NSInteger maxRetryAttempts;


/*!
 Retry interval between two requests, value is in milli seconds.
 Default value is 12 seconds.
 */
@property (nonatomic, assign, readwrite) NSInteger retryInterval;

/*!
 Config server ssl certificates.
 */
@property (nonatomic, strong, readonly) NSMutableDictionary *certInfo;



/*!
 Set the server base URL of services like Command and Control, config etc.
 
 @param  serverComponent the enum for the requested component's url
 @param  uriScheme  the uri scheme, default is http
 @param  host  the server DNS, default is null
 @param  port the server port, default is 80
 @param  basePath the base scheme
 */
- (void)  setServerUrl:(CSRRestServerComponent)serverComponent uriScheme:(NSString*)uriScheme host:(NSString*) host port:(NSString*) port basePath:(NSString*) basePath connectionChannel:(CSRRestConnectionChannel) connectionChannel;


/*!
 Add own http headers if required
 
 @param value - (NSString*) The new value for the header field. Any existing value for the field is replaced by the new value
 @param key - (NSString*) The name of the header field to set. In keeping with the HTTP RFC, HTTP header field names are case-insensitive
 */
- (void) addExtraHeader:(NSString*)value forKey:(NSString*)key;


/*!
 Add the public certificate of Root CA, in case Cloud or Gateway is using self-signed certificate for https.
 Passed certificate will be used to trust SSL challenge raised from server/gateway.
 This API can be called multiple times to add multiple certificates for different server, e.g. different certificates for gateway and cloud etc.
 
 @param  path of the client certificate file located in bundel.
 */
-(BOOL)addRootCACertificate:(NSString *)certPath;

/*!
 Remove the public certificate of Root CA, in case Cloud or Gateway is using self-signed certificate for https.
 This API can be called multiple times to remove multiple certificates for different server, e.g. different certificates for gateway and cloud etc.
 
 @param  path of the client certificate file located in bundel.
 */
-(BOOL)removeRootCACertificate:(NSString *)certPath;


@end
