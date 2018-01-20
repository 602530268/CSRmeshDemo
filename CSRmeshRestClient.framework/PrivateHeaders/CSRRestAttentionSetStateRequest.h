/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetState API for the Attention model
*/

@interface CSRRestAttentionSetStateRequest : CSRRestBaseObject


/*!
    Attract attention
*/
 typedef NS_OPTIONS(NSInteger, CSRRestAttentionSetStateRequestAttractAttentionEnum) {
  CSRRestAttentionSetStateRequestAttractAttentionEnumFalse,
  CSRRestAttentionSetStateRequestAttractAttentionEnumTrue,

};



/*!
    Attract attention
*/
@property(nonatomic) CSRRestAttentionSetStateRequestAttractAttentionEnum attractAttention;

/*!
    Duration for attracting attention
*/
@property(nonatomic) NSNumber* duration;
  
/*!
  Constructs instance of CSRRestAttentionSetStateRequest

  @param attractAttention - (CSRRestAttentionSetStateRequestAttractAttentionEnum) Attract attention
  @param duration - (NSNumber*) Duration for attracting attention
  
  @return instance of CSRRestAttentionSetStateRequest
*/
- (id) initWithattractAttention: (CSRRestAttentionSetStateRequestAttractAttentionEnum) attractAttention     
       duration: (NSNumber*) duration;
       

@end
