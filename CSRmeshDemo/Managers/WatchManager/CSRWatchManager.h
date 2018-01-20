//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
@import WatchConnectivity;

@interface CSRWatchManager : NSObject <WCSessionDelegate>

+ (id) sharedInstance;

-(void) clearAllWatchData;
-(void) updateDesiredTemperature:(NSNumber *)deviceId desiredTemperature:(NSNumber *)temperature;
-(void) updateActualTemperature:(NSNumber *)deviceId actualTemperature:(NSNumber *)temperature;
-(void) updateFavourite:(id)item;
-(void) deleteFavourite:(NSNumber *)deviceId;

@property (nonatomic)   WCSession* wcSession;


@end
