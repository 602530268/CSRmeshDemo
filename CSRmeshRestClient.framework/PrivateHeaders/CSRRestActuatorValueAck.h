/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Actuator ValueAck response object
*/

@interface CSRRestActuatorValueAck : CSRRestBaseObject


/*!
    Actuator type. The Type field is a 16-bit value that determines the actuator type.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActuatorValueAckTypeEnum) {
  CSRRestActuatorValueAckTypeEnumunknown,
  CSRRestActuatorValueAckTypeEnuminternal_air_temperature,
  CSRRestActuatorValueAckTypeEnumexternal_air_temperature,
  CSRRestActuatorValueAckTypeEnumdesired_air_temperature,
  CSRRestActuatorValueAckTypeEnuminternal_humidity,
  CSRRestActuatorValueAckTypeEnumexternal_humidity,
  CSRRestActuatorValueAckTypeEnumexternal_dewpoint,
  CSRRestActuatorValueAckTypeEnuminternal_door,
  CSRRestActuatorValueAckTypeEnumexternal_door,
  CSRRestActuatorValueAckTypeEnuminternal_window,
  CSRRestActuatorValueAckTypeEnumexternal_window,
  CSRRestActuatorValueAckTypeEnumsolar_energy,
  CSRRestActuatorValueAckTypeEnumnumber_of_activations,
  CSRRestActuatorValueAckTypeEnumfridge_temperature,
  CSRRestActuatorValueAckTypeEnumdesired_fridge_temperature,
  CSRRestActuatorValueAckTypeEnumfreezer_temperature,
  CSRRestActuatorValueAckTypeEnumdesired_freezer_temperature,
  CSRRestActuatorValueAckTypeEnumoven_temperature,
  CSRRestActuatorValueAckTypeEnumdesired_oven_temperature,
  CSRRestActuatorValueAckTypeEnumseat_occupied,
  CSRRestActuatorValueAckTypeEnumwashing_machine_state,
  CSRRestActuatorValueAckTypeEnumdish_washer_state,
  CSRRestActuatorValueAckTypeEnumclothes_dryer_state,
  CSRRestActuatorValueAckTypeEnumtoaster_state,
  CSRRestActuatorValueAckTypeEnumcarbon_dioxide,
  CSRRestActuatorValueAckTypeEnumcarbon_monoxide,
  CSRRestActuatorValueAckTypeEnumsmoke,
  CSRRestActuatorValueAckTypeEnumwater_level,
  CSRRestActuatorValueAckTypeEnumhot_water_temperature,
  CSRRestActuatorValueAckTypeEnumcold_water_temperature,
  CSRRestActuatorValueAckTypeEnumdesired_water_temperature,
  CSRRestActuatorValueAckTypeEnumcooker_hob_back_left_state,
  CSRRestActuatorValueAckTypeEnumdesired_cooker_hob_back_left_state,
  CSRRestActuatorValueAckTypeEnumcooker_hob_front_left_state,
  CSRRestActuatorValueAckTypeEnumdesired_cooker_hob_front_left_state,
  CSRRestActuatorValueAckTypeEnumcooker_hob_back_middle_state,
  CSRRestActuatorValueAckTypeEnumdesired_cooker_hob_back_middle_state,
  CSRRestActuatorValueAckTypeEnumcooker_hob_front_middle_state,
  CSRRestActuatorValueAckTypeEnumdesired_cooker_hob_front_middle_state,
  CSRRestActuatorValueAckTypeEnumcooker_hob_back_right_state,
  CSRRestActuatorValueAckTypeEnumdesired_cooker_hob_back_right_state,
  CSRRestActuatorValueAckTypeEnumcooker_hob_front_right_state,
  CSRRestActuatorValueAckTypeEnumdesired_cooker_hob_front_right_state,
  CSRRestActuatorValueAckTypeEnumdesired_wakeup_alarm_time,
  CSRRestActuatorValueAckTypeEnumdesired_second_wakeup_alarm_time,
  CSRRestActuatorValueAckTypeEnumpassive_infrared_state,
  CSRRestActuatorValueAckTypeEnumwater_flowing,
  CSRRestActuatorValueAckTypeEnumdesired_water_flow,
  CSRRestActuatorValueAckTypeEnumaudio_level,
  CSRRestActuatorValueAckTypeEnumdesired_audio_level,
  CSRRestActuatorValueAckTypeEnumfan_speed,
  CSRRestActuatorValueAckTypeEnumdesired_fan_speed,
  CSRRestActuatorValueAckTypeEnumwind_speed,
  CSRRestActuatorValueAckTypeEnumwind_speed_gust,
  CSRRestActuatorValueAckTypeEnumwind_direction,
  CSRRestActuatorValueAckTypeEnumwind_direction_gust,
  CSRRestActuatorValueAckTypeEnumrain_fall_last_hour,
  CSRRestActuatorValueAckTypeEnumrain_fall_today,
  CSRRestActuatorValueAckTypeEnumbarometric_pressure,
  CSRRestActuatorValueAckTypeEnumsoil_temperature,
  CSRRestActuatorValueAckTypeEnumsoil_moisure,
  CSRRestActuatorValueAckTypeEnumwindow_cover_position,
  CSRRestActuatorValueAckTypeEnumdesired_window_cover_position,
  CSRRestActuatorValueAckTypeEnumgeneric_1_byte,
  CSRRestActuatorValueAckTypeEnumgeneric_2_byte,
  CSRRestActuatorValueAckTypeEnumgeneric_1_byte_typed,
  CSRRestActuatorValueAckTypeEnumgeneric_2_byte_typed,
  CSRRestActuatorValueAckTypeEnumgeneric_3_byte_typed,

};



/*!
    Actuator type. The Type field is a 16-bit value that determines the actuator type.
*/
@property(nonatomic) CSRRestActuatorValueAckTypeEnum type;

/*!
    Actuator value associated to the provided type.
*/
@property(nonatomic) NSArray* value;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestActuatorValueAck

  @param type - (CSRRestActuatorValueAckTypeEnum) Actuator type. The Type field is a 16-bit value that determines the actuator type.
  @param value - (NSArray*) Actuator value associated to the provided type.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestActuatorValueAck
*/
- (id) initWithtype: (CSRRestActuatorValueAckTypeEnum) type     
       value: (NSArray*) value     
       deviceId: (NSNumber*) deviceId;
       

@end
