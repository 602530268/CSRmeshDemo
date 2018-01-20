//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface CSRUtilities : NSObject

#pragma mark - String utility methods
+ (BOOL)isStringEmpty:(NSString *)stringToCheck;
+ (BOOL)isString:(NSString *)stringToCheck containsCharacters:(NSString *)characters;
+ (BOOL)isStringContainsValidHexCharacters:(NSString *)stringToCheck;
+ (NSString *)stringFromData:(NSData *)data;

#pragma mark - Date time utility methods
+ (NSString *)createDateTimeString:(NSDate *)date skipMiliSeconds:(BOOL)skipMiliSeconds;
+ (NSString *)createUnixTimestampFromDate:(NSDate *)date;
+ (NSDate *)createDateFromUnixTimestamp:(NSNumber *)unixTimestamp;
+ (NSDate *)createDateFromString:(NSString *)dateString withFormat:(NSString *)dateFormat;
+ (NSString *)formatDate:(NSDate *)date withFormatString:(NSString *)formatString;
+ (NSString *)formatUnixTimestamp:(NSString *)unixTimestamp withFormatString:(NSString *)formatString;
+ (NSString *)getSecondsDigit;

#pragma mark - Data utility methods
+ (NSData *)dataFromHexString:(NSString *)string;
+ (NSData *)scanDataString:(NSString *)string;
+ (NSString *)hexStringFromData:(NSData *)data;
+ (NSData *)hexStringToUUID:(NSString *)string;
+ (NSData *)UUIDDataFromHexString:(NSString *)string;
+ (NSMutableData *)reverseData:(NSData *)data;
+ (uint64_t)NSDataToInt:(NSData *)data;
+ (NSData *)IntToNSData:(uint64_t)data;


#pragma mark - Number utility methods
+ (NSNumber *)scanHexString:(NSString *)string;
+ (NSNumber *)scanBoolString:(NSString *)string;
+ (NSNumber *)scanIntString:(NSString *)string;

#pragma mark - Label utility methods
+ (CGFloat)calculateLabelHeightForText:(NSString *)text usingFont:(UIFont *)font maxWidth:(CGFloat)width;
+ (CGFloat)calculateLabelWidthForText:(NSString *)text usingFont:(UIFont *)font maxWidth:(CGFloat)width;

#pragma mark - View utility methods
+ (BOOL)iterateSubviewsOfUIView:(UIView*)view toDepth:(NSInteger)depth toFindView:(NSString *)targetView;

#pragma mark - Documents directory utility methods
+ (NSString *)documentsDirectoryPath;
+ (NSURL *)documentsDirectoryPathURL;
+ (NSArray *)getFilesAtPath:(NSString *)path;

#pragma mark - Color utility methods
+ (UIColor *)colorFromRGB:(NSInteger)rgbValue;
+ (UIColor*)colorFromHex:(NSString *)colourString;
+ (UIColor *)colorFromActualRed:(float)red green:(float)green blue:(float)blue alpha:(float)alpha;
+ (NSString *)colorNameForRGB:(NSInteger)rgbValue;
+ (UIColor *)colorFromImageAtPoint:(CGPoint *)point frameWidth:(float)width frameHeight:(float)height;
+ (UIColor *)multiplyIntensityOfColor:(UIColor *)color withIntensityMultiplier:(CGFloat)intensityMultiplier;
+ (NSInteger)rgbFromColor:(UIColor *)color;
+ (NSString *)hexFromColor:(UIColor *)color;
+ (NSString *)rgbFromColorName:(NSString *)colorName;

#pragma mark - Image utility methods
+ (UIImage *)imageWithColor:(UIColor *)color;
+ (UIImage *)imageWithImage:(UIImage *)image scaledToSize:(CGSize)newSize;

#pragma mark - JSON utility methods
+ (NSString *)createJSONstringFromDictionary:(NSDictionary *)dictionary;

#pragma mark - NSUserDefaults utility methods
+ (id)getValueFromDefaultsForKey:(NSString *)key;
+ (BOOL)saveObject:(id)object toDefaultsWithKey:(NSString *)key;

#pragma mark - MD5 String
+ (NSString*)md5OutputString:(NSString*)input;

#pragma mark - Stack trace
+ (void)stackTrace;

#pragma mark - Data types Coversion
+ (BOOL)boolValue:(NSData *)data;
+ (NSInteger)intValue:(NSData *)data;
+ (double)doubleValue:(NSData *)data offset:(NSInteger)offset;
+ (NSString *)stringValue:(NSData *)data;

+ (NSData *)randomDataOfLength:(size_t)length;

+ (NSString *)createFile:(NSString *)directory;

+ (NSData *)authCodefromString:(NSString *)pinString;

//compression and decompression class methods
+ (NSData*) uncompressGZip:(NSData*) compressedData;

@end
