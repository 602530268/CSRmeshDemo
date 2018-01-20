//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface CSRmeshDevice : NSObject

@property (strong, atomic) CBUUID *uuid;
@property (strong, atomic) NSData *authCode;
@property (strong, atomic) NSNumber *rssi;


@property (strong, atomic) NSNumber *deviceId;
@property (strong, atomic) NSData *deviceHash;
@property (strong, atomic) NSString *networkKey;
@property (strong, atomic) NSString *name;

@property (strong, atomic) NSNumber *appearanceValue;
@property (strong, atomic) NSData *appearanceShortname;
@property (nonatomic, assign) BOOL isAssociated;

@property (strong, atomic) NSNumber *associationStepsCompleted;
@property (strong, atomic) NSNumber *associationStepsTotal;
@property (strong, atomic) NSNumber *failedToAssociate;

@property (strong, atomic) NSData *dhmKey;

//timer Methods
-(BOOL) timedMethods;

//retry device
@property (atomic) int resetRetriesRemaining;
@property (atomic) NSTimer *resetTimer;
@property (atomic) BOOL pendingRemoval;

@property (strong, atomic) NSValue *colorPosition;
//State value of the device (eg, red for a light, unlocked for lock...)
@property (nonatomic, strong) id stateValue;

@property (atomic) NSMutableData *incomingStream;

- (id)init;
- (id)initDatabaseDevice:(NSDictionary *)deviceProperties;
- (id)initForArea:(NSNumber *)number;

//Association
- (BOOL)isAssociated;
- (BOOL)isAssociating;
- (BOOL)isPendingAssociation;
- (BOOL)startAssociation;
- (NSString *) getAssociationStatus;
- (void)updateAssociationStatusWithNumberofStepsCompleted:(NSNumber *)stepsCompleted ofTotalSteps:(NSNumber *)totalSteps;
- (void)didAssociateDevice :(NSNumber *) deviceIdNumber;

//Operators
- (CGFloat)getLevel;
- (void)setLevel:(CGFloat)level;
- (UIColor *)getColor;
- (void)setColorWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue;
- (BOOL)getPower;
- (void)setPower:(BOOL)state;

//Models
- (void)createModelsWithModelNumber:(NSData *)modelNumbers withInfoType:(NSNumber *)infoType;
// NSMutableSet to find what models does the device support
@property (strong, atomic) NSMutableArray *modelsSet;


//Reset
- (void)didResetDevice;

@end
