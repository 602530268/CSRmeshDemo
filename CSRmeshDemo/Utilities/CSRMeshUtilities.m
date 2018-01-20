//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import "CSRMeshUtilities.h"

@implementation CSRMeshUtilities

#pragma mark - Device constants methods

+ (NSString*)modelNameForModelNumber:(CSRMeshModelName)modelName
{
    
    switch (modelName) {
        case CSRMeshModelName_WATCHDOG:
            return @"WATCHDOG";
            break;
        case CSRMeshModelName_CONFIG:
            return @"CONFIG";
            break;
        case CSRMeshModelName_GROUP:
            return @"GROUP";
            break;
        case CSRMeshModelName_KEY:
            return @"KEY";
            break;
        case CSRMeshModelName_SENSOR:
            return @"SENSOR";
            break;
        case CSRMeshModelName_ACTUATOR:
            return @"ACTUATOR";
            break;
        case CSRMeshModelName_LOCATION:
            return @"LOCATION";
            break;
        case CSRMeshModelName_DATA:
            return @"DATA";
            break;
        case CSRMeshModelName_FIRMWARE:
            return @"FIRMWARE";
            break;
        case CSRMeshModelName_DIAGNOSTIC:
            return @"DIAGNOSTIC";
            break;
        case CSRMeshModelName_BEARER:
            return @"BEARER";
            break;
        case CSRMeshModelName_PING:
            return @"PING";
            break;
        case CSRMeshModelName_BATTERY:
            return @"BATTERY";
            break;
        case CSRMeshModelName_ATTENTION:
            return @"ATTENTION";
            break;
        case CSRMeshModelName_IDENTIFIER:
            return @"IDENTIFIER";
            break;
        case CSRMeshModelName_WALLCLOCK:
            return @"WALLCLOCK";
            break;
        case CSRMeshModelName_SEMANTIC:
            return @"SEMANTIC";
            break;
        case CSRMeshModelName_EFFECT:
            return @"EFFECT";
            break;
        case CSRMeshModelName_POWER:
            return @"POWER";
            break;
        case CSRMeshModelName_LIGHT:
            return @"LIGHT";
            break;
        case CSRMeshModelName_SWITCH:
            return @"SWITCH";
            break;
        case CSRMeshModelName_EVENT:
            return @"EVENT";
            break;
        case CSRMeshModelName_VOLUME:
            return @"VOLUME";
            break;
        case CSRMeshModelName_IV:
            return @"IV";
            break;
        case CSRMeshModelName_REMOTE:
            return @"REMOTE";
            break;
        case CSRMeshModelName_USER:
            return @"USER";
            break;
        case CSRMeshModelName_TIMER:
            return @"TIMER";
            break;
        default:
            break;
    }
    
    return @"N/A";
    
}

#pragma mark - Short code utility methods

const uint8_t shortcodeslookup[] ={'B','b','C','D','d','F','f','G','g','H','h','K','L','M','m','N','n','P','p','R','r','T','t','U','V','W','X','4','5','6','8','9',0};

+ (uint8_t)shortcodeLookup:(char)code
{
    // Cache last value to improve performance
    static uint8_t lastValue=0;
    static char    lastChar=0;
    
    if (lastChar == code) {
        return(lastValue);
    }
    
    uint8_t *rover = (uint8_t *) &shortcodeslookup[0];
    while (*rover) {
        if (*rover==code) {
            // cache last value
            lastValue = rover-shortcodeslookup;
            lastChar = code;
            return (lastValue);
        }
        rover ++;
    }
    
    return (0xff);
}

+ (NSString *)shortCodeFromString:(NSString *)string
{
    string = [string stringByReplacingOccurrencesOfString:@"-" withString:@""];
    
    return [NSString stringWithFormat:@"%@-%@-%@-%@-%@", [string substringToIndex:4], [[string substringFromIndex:4] substringToIndex:4], [[string substringFromIndex:8] substringToIndex:4], [[string substringFromIndex:12] substringToIndex:4], [[string substringFromIndex:16] substringToIndex:4]];
}

#pragma mark - UUID utility methods

+ (CBUUID *)scanUUIDString:(NSString *)string
{
    return (CBUUID *)[CBUUID UUIDWithString:string];
}

+ (NSString*)treatUUID:(NSString*)uuid withMode:(UUIDTreatmentMode)mode
{
    if (mode == UUIDTreatmentMode_Trim) {
        
        return (NSString*)[uuid substringWithRange:NSMakeRange(2, [uuid length]-2)];
        
    } else if (mode == UUIDTreatmentMode_Expand) {
        
        return [NSString stringWithFormat:@"0x%@",uuid];
        
    }
    
    return nil;
}

+ (CBUUID *)CBUUIDWithFlatUUIDString:(NSString *)uuidString
{
    uuidString = [uuidString stringByReplacingOccurrencesOfString:@"-" withString:@""];
    
    return [CBUUID UUIDWithString:[NSString stringWithFormat:@"%@-%@-%@-%@-%@", [uuidString substringToIndex:8], [[uuidString substringFromIndex:8] substringToIndex:4], [[uuidString substringFromIndex:12] substringToIndex:4], [[uuidString substringFromIndex:16] substringToIndex:4], [uuidString substringFromIndex:20]]];
}

+ (NSString *)reverseUUID:(NSString *)string
{
    
    NSString *UUIDString = string;
    
    UUIDString = [UUIDString stringByReplacingOccurrencesOfString:@"-" withString:@""];
    
    NSMutableString *reversedUUID = [[NSMutableString alloc] initWithString:@""];
    
    while ([UUIDString length] > 0) {
        
        [reversedUUID appendString:[UUIDString substringWithRange:NSMakeRange([UUIDString length] - 4, 4)]];
        UUIDString = [UUIDString substringToIndex:[UUIDString length] - 4];
    }
    
    NSLog(@"reversedUUID: %@", reversedUUID);
    
    return reversedUUID;
    
}

+ (BOOL)isStringValidUUIDString:(NSString *)string
{
    
    NSString *UUIDString = string;
    
    UUIDString = [UUIDString stringByReplacingOccurrencesOfString:@"-" withString:@""];
    
    if ([UUIDString length] < 32) {
        
        return NO;
    }
    
    UUIDString = [NSString stringWithFormat:@"%@-%@-%@-%@-%@", [UUIDString substringToIndex:8], [[UUIDString substringFromIndex:8] substringToIndex:4], [[UUIDString substringFromIndex:12] substringToIndex:4], [[UUIDString substringFromIndex:16] substringToIndex:4], [UUIDString substringFromIndex:20]];
    
    return (BOOL)[[NSUUID alloc] initWithUUIDString:UUIDString];
}


@end
