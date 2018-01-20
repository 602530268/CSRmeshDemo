//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>

/*!
 @header CSRCallbacks
 Internal typedefs for managing callbacks
 */

/// @typedef CSRGetStringCompletion handler for returning strings
typedef void (^CSRGetStringCompletion)(NSString *);

/// @typedef CSRGetBoolCompletion handler for returning booleans
typedef void (^CSRGetBoolCompletion)(BOOL);

/// @typedef CSRGetIntCompletion handler for returning integers
typedef void (^CSRGetIntCompletion)(NSInteger);

/// @typedef CSRGetIntCompletion handler for returning doubles
typedef void (^CSRGetDoubleCompletion)(double);

/// @typedef CSRErrorCompletion handler for returning NSError objects
typedef void (^CSRErrorCompletion)(NSError *);

/// @typedef CSRSetValueCompletion handler for setting values
typedef void (^CSRSetValueCompletion)(void);

typedef enum {
    CSRCallbackType_Bool,
    CSRCallbackType_Int,
    CSRCallbackType_Double,
    CSRCallbackType_String,
    CSRCallbackType_SetBool,
    CSRCallbackType_SetInt,
    CSRCallbackType_SetString,
    CSRCallbackType_SetData,
} CSRCallbackType;

/*!
 @class CSRCallbacks
 @abstract Manage callbacks to CBPeripheralDelegate methods
 */
@interface CSRCallbacks : NSObject

/// @brief The callback type
@property (nonatomic) CSRCallbackType callbackType;

/// @brief the success callback reference
@property (nonatomic) id successCallback;

/// @brief the failure callback reference
@property (nonatomic) id failureCallback;

/*!
 @brief Initialise the callback
 @param success The success callback
 @param failure The failure callback
 @param type The callback type
 */
- (id)initWith:(id)success failure:(id)failure type:(CSRCallbackType)type;

@end
