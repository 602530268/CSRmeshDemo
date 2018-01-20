/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 
 REVISION:      $Revision: #2 $
 */


#import <Foundation/Foundation.h>


/*! CSRRestApiStatusCode is a part of the CSR Mesh Api and provides status code returned by Model Api. */
typedef NS_OPTIONS(NSInteger, CSRRestApiStatusCode){
    /*!
     Request completed successfully
     */
    STATUS_OK = 0,
    
    /*!
     Malformed syntax of the request
     */
    STATUS_BAD_REQUEST = 400,
    
    /*!
     Request requires user authentication
     */
    STATUS_UNAUTHORIZED_REQUEST = 401,
    
    /*!
     Forbidden access
     */
    STATUS_FORBIDDEN_REQUEST = 403,
    
    /*!
     The requested resource could not be found
     */
    STATUS_NOT_FOUND = 404,
    
    /*!
     The method specified in the Request-Line is not allowed for the resource identified by the Request-URI
     */
    STATUS_METHOD_NOT_ALLOWED = 405,
    
    /*!
     Request timed out
     */
    STATUS_REQUEST_TIMEOUT = 408,
    
    /*!
     Server encountered an unexpected condition
     */
    STATUS_INTERNAL_SERVER_ERROR = 500,
    
    /*!
     Server does not support this functionality
     */
    STATUS_NOT_IMPLEMENTED = 501,
    
    /*!
     Server(acting as gateway) received invalid response from the upstream server
     */
    STATUS_BAD_GATEWAY = 502,
    
    /*!
     The server is currently unavailable
     */
    STATUS_SERVICE_UNAVAILABLE = 503,
    
    /*!
     The server is currently unavailable
     */
    STATUS_GATEWAY_TIMEOUT = 504,
    
    /*!
     The server does not support, or refuses to support, the HTTP protocol version that was used in the request message
     */
    STATUS_HTTP_VERSION_NOT_SUPPORTED = 505,
    
    /*!
     A server with the specified hostname could not be found
     */
    STATUS_INVALID_HOST = -1003,
    
    /*!
     A server with the specified hostname can't be connected
     */
    STATUS_CAN_NOT_CONNECT_TO_HOST = -1004,
    
    /*!
     Network connection lost
     */
    STATUS_NETWORK_CONNECTION_LOST = -1005,
    
    /*!
     No Internet connectivity
     */
    STATUS_NOT_CONNECTED_TO_INTERNET = -1009,
    
};
