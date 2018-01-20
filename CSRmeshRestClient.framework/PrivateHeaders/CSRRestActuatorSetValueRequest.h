/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetValue API for the Actuator model
*/

@interface CSRRestActuatorSetValueRequest : CSRRestBaseObject


/*!
    Actuator type. The Type field is the actuator type value being set.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActuatorSetValueRequestTypeEnum) {
  CSRRestActuatorSetValueRequestTypeEnumunknown,
  CSRRestActuatorSetValueRequestTypeEnuminternal_air_temperature,
  CSRRestActuatorSetValueRequestTypeEnumexternal_air_temperature,
  CSRRestActuatorSetValueRequestTypeEnumdesired_air_temperature,
  CSRRestActuatorSetValueRequestTypeEnuminternal_humidity,
  CSRRestActuatorSetValueRequestTypeEnumexternal_humidity,
  CSRRestActuatorSetValueRequestTypeEnumexternal_dewpoint,
  CSRRestActuatorSetValueRequestTypeEnuminternal_door,
  CSRRestActuatorSetValueRequestTypeEnumexternal_door,
  CSRRestActuatorSetValueRequestTypeEnuminternal_window,
  CSRRestActuatorSetValueRequestTypeEnumexternal_window,
  CSRRestActuatorSetValueRequestTypeEnumsolar_energy,
  CSRRestActuatorSetValueRequestTypeEnumnumber_of_activations,
  CSRRestActuatorSetValueRequestTypeEnumfridge_temperature,
  CSRRestActuatorSetValueRequestTypeEnumdesired_fridge_temperature,
  CSRRestActuatorSetValueRequestTypeEnumfreezer_temperature,
  CSRRestActuatorSetValueRequestTypeEnumdesired_freezer_temperature,
  CSRRestActuatorSetValueRequestTypeEnumoven_temperature,
  CSRRestActuatorSetValueRequestTypeEnumdesired_oven_temperature,
  CSRRestActuatorSetValueRequestTypeEnumseat_occupied,
  CSRRestActuatorSetValueRequestTypeEnumwashing_machine_state,
  CSRRestActuatorSetValueRequestTypeEnumdish_washer_state,
  CSRRestActuatorSetValueRequestTypeEnumclothes_dryer_state,
  CSRRestActuatorSetValueRequestTypeEnumtoaster_state,
  CSRRestActuatorSetValueRequestTypeEnumcarbon_dioxide,
  CSRRestActuatorSetValueRequestTypeEnumcarbon_monoxide,
  CSRRestActuatorSetValueRequestTypeEnumsmoke,
  CSRRestActuatorSetValueRequestTypeEnumwater_level,
  CSRRestActuatorSetValueRequestTypeEnumhot_water_temperature,
  CSRRestActuatorSetValueRequestTypeEnumcold_water_temperature,
  CSRRestActuatorSetValueRequestTypeEnumdesired_water_temperature,
  CSRRestActuatorSetValueRequestTypeEnumcooker_hob_back_left_state,
  CSRRestActuatorSetValueRequestTypeEnumdesired_cooker_hob_back_left_state,
  CSRRestActuatorSetValueRequestTypeEnumcooker_hob_front_left_state,
  CSRRestActuatorSetValueRequestTypeEnumdesired_cooker_hob_front_left_state,
  CSRRestActuatorSetValueRequestTypeEnumcooker_hob_back_middle_state,
  CSRRestActuatorSetValueRequestTypeEnumdesired_cooker_hob_back_middle_state,
  CSRRestActuatorSetValueRequestTypeEnumcooker_hob_front_middle_state,
  CSRRestActuatorSetValueRequestTypeEnumdesired_cooker_hob_front_middle_state,
  CSRRestActuatorSetValueRequestTypeEnumcooker_hob_back_right_state,
  CSRRestActuatorSetValueRequestTypeEnumdesired_cooker_hob_back_right_state,
  CSRRestActuatorSetValueRequestTypeEnumcooker_hob_front_right_state,
  CSRRestActuatorSetValueRequestTypeEnumdesired_cooker_hob_front_right_state,
  CSRRestActuatorSetValueRequestTypeEnumdesired_wakeup_alarm_time,
  CSRRestActuatorSetValueRequestTypeEnumdesired_second_wakeup_alarm_time,
  CSRRestActuatorSetValueRequestTypeEnumpassive_infrared_state,
  CSRRestActuatorSetValueRequestTypeEnumwater_flowing,
  CSRRestActuatorSetValueRequestTypeEnumdesired_water_flow,
  CSRRestActuatorSetValueRequestTypeEnumaudio_level,
  CSRRestActuatorSetValueRequestTypeEnumdesired_audio_level,
  CSRRestActuatorSetValueRequestTypeEnumfan_speed,
  CSRRestActuatorSetValueRequestTypeEnumdesired_fan_speed,
  CSRRestActuatorSetValueRequestTypeEnumwind_speed,
  CSRRestActuatorSetValueRequestTypeEnumwind_speed_gust,
  CSRRestActuatorSetValueRequestTypeEnumwind_direction,
  CSRRestActuatorSetValueRequestTypeEnumwind_direction_gust,
  CSRRestActuatorSetValueRequestTypeEnumrain_fall_last_hour,
  CSRRestActuatorSetValueRequestTypeEnumrain_fall_today,
  CSRRestActuatorSetValueRequestTypeEnumbarometric_pressure,
  CSRRestActuatorSetValueRequestTypeEnumsoil_temperature,
  CSRRestActuatorSetValueRequestTypeEnumsoil_moisure,
  CSRRestActuatorSetValueRequestTypeEnumwindow_cover_position,
  CSRRestActuatorSetValueRequestTypeEnumdesired_window_cover_position,
  CSRRestActuatorSetValueRequestTypeEnumgeneric_1_byte,
  CSRRestActuatorSetValueRequestTypeEnumgeneric_2_byte,
  CSRRestActuatorSetValueRequestTypeEnumgeneric_1_byte_typed,
  CSRRestActuatorSetValueRequestTypeEnumgeneric_2_byte_typed,
  CSRRestActuatorSetValueRequestTypeEnumgeneric_3_byte_typed,

};



/*!
    Actuator type. The Type field is the actuator type value being set.
*/
@property(nonatomic) CSRRestActuatorSetValueRequestTypeEnum type;

/*!
    Actuator value. The Value field is the value that the actuator type.
*/
@property(nonatomic) NSArray* value;
  
/*!
  Constructs instance of CSRRestActuatorSetValueRequest

  @param type - (CSRRestActuatorSetValueRequestTypeEnum) Actuator type. The Type field is the actuator type value being set.
  @param value - (NSArray*) Actuator value. The Value field is the value that the actuator type.
  
  @return instance of CSRRestActuatorSetValueRequest
*/
- (id) initWithtype: (CSRRestActuatorSetValueRequestTypeEnum) type     
       value: (NSArray*) value;
       

@end
