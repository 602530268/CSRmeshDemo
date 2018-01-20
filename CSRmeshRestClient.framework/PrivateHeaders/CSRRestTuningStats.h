/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Tuning Stats response object
*/

@interface CSRRestTuningStats : CSRRestBaseObject




/*!
    Part number (0..31). Bit 7 means more to come
*/
@property(nonatomic) NSNumber* partNumber;
  
/*!
    ID of first neighbour in this message
*/
@property(nonatomic) NSNumber* neighbourId1;
  
/*!
    Average rate neighbour 1 is seen, 6.2 fixed point format, 0..63.75
*/
@property(nonatomic) NSNumber* neighbourRate1;
  
/*!
    Average RSSI of neighbour 1
*/
@property(nonatomic) NSNumber* neighbourRssi1;
  
/*!
    ID of second neighbour in this message
*/
@property(nonatomic) NSNumber* neighbourId2;
  
/*!
    Average rate neighbour 2 is seen, 6.2 fixed point format, 0..63.75
*/
@property(nonatomic) NSNumber* neighbourRate2;
  
/*!
    Average RSSI of neighbour 2
*/
@property(nonatomic) NSNumber* neighbourRssi2;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestTuningStats

  @param partNumber - (NSNumber*) Part number (0..31). Bit 7 means more to come
  @param neighbourId1 - (NSNumber*) ID of first neighbour in this message
  @param neighbourRate1 - (NSNumber*) Average rate neighbour 1 is seen, 6.2 fixed point format, 0..63.75
  @param neighbourRssi1 - (NSNumber*) Average RSSI of neighbour 1
  @param neighbourId2 - (NSNumber*) ID of second neighbour in this message
  @param neighbourRate2 - (NSNumber*) Average rate neighbour 2 is seen, 6.2 fixed point format, 0..63.75
  @param neighbourRssi2 - (NSNumber*) Average RSSI of neighbour 2
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestTuningStats
*/
- (id) initWithpartNumber: (NSNumber*) partNumber     
       neighbourId1: (NSNumber*) neighbourId1     
       neighbourRate1: (NSNumber*) neighbourRate1     
       neighbourRssi1: (NSNumber*) neighbourRssi1     
       neighbourId2: (NSNumber*) neighbourId2     
       neighbourRate2: (NSNumber*) neighbourRate2     
       neighbourRssi2: (NSNumber*) neighbourRssi2     
       deviceId: (NSNumber*) deviceId;
       

@end
