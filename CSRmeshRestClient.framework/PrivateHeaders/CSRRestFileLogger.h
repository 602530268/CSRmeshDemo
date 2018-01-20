/*!
 Copyright [2015] Qualcomm Technologies International, Ltd.
 
 REVISION:      $Revision: #2 $
 */

#import <Foundation/Foundation.h>

@interface CSRRestFileLogger : NSObject

@property (nonatomic,readwrite) unsigned int logLevel;

+ (CSRRestFileLogger *)sharedInstance;

- (void)log:(NSString*)file level:(unsigned int)level function:(const char*)function line:(int)line format:(NSString *)format, ...;
- (void)log:(NSString*)file  level:(unsigned int)level function:(const char*)function line:(int)line format:(NSString *)format arguments:(va_list)list;

@end
