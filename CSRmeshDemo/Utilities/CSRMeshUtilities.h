//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>

@interface CSRMeshUtilities : NSObject

typedef NS_ENUM(NSInteger, CSRMeshModelNumber) {
    CSRMeshModelWATCHDOG = 0,
    CSRMeshModelCONFIG = 1,
    CSRMeshModelGROUP = 2,
    CSRMeshModelSENSOR = 4,
    CSRMeshModelACTUATOR = 5,
    CSRMeshModelASSET = 6,
    CSRMeshModelTRACKER = 7,
    CSRMeshModelDATA = 8,
    CSRMeshModelFIRMWARE = 9,
    CSRMeshModelDIAGNOSTIC = 10,
    CSRMeshModelBEARER = 11,
    CSRMeshModelPING = 12,
    CSRMeshModelBATTERY = 13,
    CSRMeshModelATTENTION = 14,
    
    CSRMeshModelTIME = 16,
    
    CSRMeshModelPOWER = 19,
    CSRMeshModelLIGHT = 20,
    CSRMeshModelSWITCH = 21,
    
    CSRMeshModelTUNING = 28,
    CSRMeshModelEXTENSION = 29,
    CSRMeshModelLARGE_OBJECT_TRANSFER = 30,
    CSRMeshModelBEACON = 32,
    CSRMeshModelBEACON_PROXY = 33,
    CSRMeshModelACTION = 34
};


typedef NS_ENUM(NSInteger, CSRMeshModelName) {
    CSRMeshModelName_WATCHDOG = 0,
    CSRMeshModelName_CONFIG = 1,
    CSRMeshModelName_GROUP = 2,
    CSRMeshModelName_KEY = 3,
    CSRMeshModelName_SENSOR = 4,
    CSRMeshModelName_ACTUATOR = 5,
    CSRMeshModelName_ASSET = 6,
    CSRMeshModelName_LOCATION = 7,
    CSRMeshModelName_DATA = 8,
    CSRMeshModelName_FIRMWARE = 9,
    CSRMeshModelName_DIAGNOSTIC = 10,
    CSRMeshModelName_BEARER = 11,
    CSRMeshModelName_PING = 12,
    CSRMeshModelName_BATTERY = 13,
    CSRMeshModelName_ATTENTION = 14,
    CSRMeshModelName_IDENTIFIER = 15,
    CSRMeshModelName_WALLCLOCK = 16,
    CSRMeshModelName_SEMANTIC = 17,
    CSRMeshModelName_EFFECT = 18,
    CSRMeshModelName_POWER = 19,
    CSRMeshModelName_LIGHT = 20,
    CSRMeshModelName_SWITCH = 21,
    CSRMeshModelName_EVENT = 22,
    CSRMeshModelName_VOLUME = 23,
    CSRMeshModelName_IV = 24,
    CSRMeshModelName_REMOTE = 25,
    CSRMeshModelName_USER = 26,
    CSRMeshModelName_TIMER = 27
};

typedef NS_ENUM(NSInteger, UUIDTreatmentMode)  {
    UUIDTreatmentMode_Trim = 0,
    UUIDTreatmentMode_Expand = 1
};

#pragma mark - Device constants utility methods
+ (NSString *)modelNameForModelNumber:(CSRMeshModelName)modelName;

#pragma mark - Short code utility methods
+ (uint8_t)shortcodeLookup:(char)code;
+ (NSString *)shortCodeFromString:(NSString *)string;

#pragma mark - UUID utility methods
+ (CBUUID *)scanUUIDString:(NSString *)string;
+ (NSString *)treatUUID:(NSString*)uuid withMode:(UUIDTreatmentMode)mode;
+ (CBUUID *)CBUUIDWithFlatUUIDString:(NSString *)uuidString;
+ (NSString *)reverseUUID:(NSString *)string;
+ (BOOL)isStringValidUUIDString:(NSString *)string;


@end
