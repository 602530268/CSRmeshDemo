//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>

@interface NSData (Encryption)

- (NSData *)AES256EncryptWithKey:(NSString *)key iv:(NSData*)iv;
- (NSData *)AES256DecryptWithKey:(NSString *)key iv:(NSData*)iv;

@end
