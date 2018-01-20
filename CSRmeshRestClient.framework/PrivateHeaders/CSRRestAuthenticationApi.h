/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 
 REVISION:      $Revision: #1 $
 */

#import <Foundation/Foundation.h>
#import "CSRRestBaseApi.h"
#import "CSRRestAuthSeedResponse.h"
#import "CSRRestAuthenticateGatewayRequest.h"
#import "CSRRestAuthenticateGatewayResponse.h"
#import "CSRRestExchangeSecretRequest.h"
#import "CSRRestExchangeSecretResponse.h"
#import "CSRRestErrorResponse.h"

typedef NS_OPTIONS(NSInteger, CSRRestAuthenticationState) {
    
    CSRRestNotAuthenticated,
    CSRRestAuthenticated,
    CSRRestAuthenticationInProgress,
    CSRRestAuthenticationExpired
    
};

@protocol CSRRestAuthenticationDelegate <NSObject>
@required
/*-(void) authenticationCompletedWithStatus:(BOOL) status;
-(void) sessionExpired;
-(void) authenticationExpired;*/
-(void) notifyAuthenticationState:(CSRRestAuthenticationState) status;

@end

@interface CSRRestAuthenticationApi : CSRRestBaseApi


@property (nonatomic,weak) id <CSRRestAuthenticationDelegate> delegate;


- (BOOL) startAuthentication:(NSString *)deviceUuid
                      meshId:(NSString *)meshId
                      dhmKey:(NSData *)dhmKey
                  networkKey:(NSData *)networkKey;

-(CSRRestAuthenticationState) getAuthenticationState;




@end
