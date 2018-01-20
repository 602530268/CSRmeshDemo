/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 
 REVISION:      $Revision: #1 $
 */

#import <Foundation/Foundation.h>

@interface CSRRestAuthConfig : NSObject


/*!
 This method must be called upon the first use of the CSRRestAuthConfig as it creates and initialises a singleton object and returns a handle to it so that the same can be used to invoke instance methods and properties.
 
 @return id - The id of the singleton object.
 */
+(id)sharedInstance;

/*!
 Session key of CE.
 */
@property (nonatomic, strong) NSString *deviceUUID;

/*!
 Mesh id key of network.
 */
@property (nonatomic, strong) NSString *meshID;

/*!
 Auth seed of CE.
 */
@property (nonatomic, strong) NSString *authSeed;

/*!
 Session key of CE.
 */
@property (nonatomic, strong) NSData *sessionKeyCE;

/*!
 Session key of gateway.
 */
@property (nonatomic, strong) NSData *sessionKeyGateway;

/*!
 Diversifier of CE.
 */
@property (nonatomic, strong) NSData *diversifierCE;

/*!
 Diversifier of gateway.
 */
@property (nonatomic, strong) NSData *diversifierGateway;

/*!
 Initial Vector of CE.
 */
@property (nonatomic, strong) NSData *initialVectorCE;

/*!
 initial Vector of gateway.
 */
@property (nonatomic, strong) NSData *initialVectorGateway;

/*!
 Sequence number of CE.
 */
@property (nonatomic, assign, readonly) NSInteger sequenceNumberCE;

/*!
 Sequence number of gateway.
 */
@property (nonatomic, assign, readwrite) NSInteger sequenceNumberGateway;

/*!
Indicates that rest api is authenticated or not. Default value is false.
*/
@property (nonatomic, assign, readwrite) Boolean authenticated;

/*
 This method will return the next sequence number to be send in request.
 */
-(NSNumber *)nextSequenceNumber;

/*
 This method will reset the sequence number to 0.
 */
-(void)resetSequenceNumber;


#define CSR_REST_EXPIRY_NOTIFICATION @"csr_rest_expiry_notification"
#define CSR_REST_EXPIRY_STATUS @"csr_rest_expiry_status"

@end
