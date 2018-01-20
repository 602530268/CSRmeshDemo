//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>

@interface CSRParseAndLoad : NSObject

- (void) deleteEntitiesInSelectedPlace;

- (void) parseIncomingDictionary:(NSDictionary*)parsingDictionary;
- (NSData *) composeDatabase;


@end
