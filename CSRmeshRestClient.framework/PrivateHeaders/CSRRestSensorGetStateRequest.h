/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for GetState API for the Sensor model
*/

@interface CSRRestSensorGetStateRequest : CSRRestBaseObject


/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor types being configured.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorGetStateRequestTypeEnum) {
  CSRRestSensorGetStateRequestTypeEnumunknown,
  CSRRestSensorGetStateRequestTypeEnuminternal_air_temperature,
  CSRRestSensorGetStateRequestTypeEnumexternal_air_temperature,
  CSRRestSensorGetStateRequestTypeEnumdesired_air_temperature,
  CSRRestSensorGetStateRequestTypeEnuminternal_humidity,
  CSRRestSensorGetStateRequestTypeEnumexternal_humidity,
  CSRRestSensorGetStateRequestTypeEnumexternal_dewpoint,
  CSRRestSensorGetStateRequestTypeEnuminternal_door,
  CSRRestSensorGetStateRequestTypeEnumexternal_door,
  CSRRestSensorGetStateRequestTypeEnuminternal_window,
  CSRRestSensorGetStateRequestTypeEnumexternal_window,
  CSRRestSensorGetStateRequestTypeEnumsolar_energy,
  CSRRestSensorGetStateRequestTypeEnumnumber_of_activations,
  CSRRestSensorGetStateRequestTypeEnumfridge_temperature,
  CSRRestSensorGetStateRequestTypeEnumdesired_fridge_temperature,
  CSRRestSensorGetStateRequestTypeEnumfreezer_temperature,
  CSRRestSensorGetStateRequestTypeEnumdesired_freezer_temperature,
  CSRRestSensorGetStateRequestTypeEnumoven_temperature,
  CSRRestSensorGetStateRequestTypeEnumdesired_oven_temperature,
  CSRRestSensorGetStateRequestTypeEnumseat_occupied,
  CSRRestSensorGetStateRequestTypeEnumwashing_machine_state,
  CSRRestSensorGetStateRequestTypeEnumdish_washer_state,
  CSRRestSensorGetStateRequestTypeEnumclothes_dryer_state,
  CSRRestSensorGetStateRequestTypeEnumtoaster_state,
  CSRRestSensorGetStateRequestTypeEnumcarbon_dioxide,
  CSRRestSensorGetStateRequestTypeEnumcarbon_monoxide,
  CSRRestSensorGetStateRequestTypeEnumsmoke,
  CSRRestSensorGetStateRequestTypeEnumwater_level,
  CSRRestSensorGetStateRequestTypeEnumhot_water_temperature,
  CSRRestSensorGetStateRequestTypeEnumcold_water_temperature,
  CSRRestSensorGetStateRequestTypeEnumdesired_water_temperature,
  CSRRestSensorGetStateRequestTypeEnumcooker_hob_back_left_state,
  CSRRestSensorGetStateRequestTypeEnumdesired_cooker_hob_back_left_state,
  CSRRestSensorGetStateRequestTypeEnumcooker_hob_front_left_state,
  CSRRestSensorGetStateRequestTypeEnumdesired_cooker_hob_front_left_state,
  CSRRestSensorGetStateRequestTypeEnumcooker_hob_back_middle_state,
  CSRRestSensorGetStateRequestTypeEnumdesired_cooker_hob_back_middle_state,
  CSRRestSensorGetStateRequestTypeEnumcooker_hob_front_middle_state,
  CSRRestSensorGetStateRequestTypeEnumdesired_cooker_hob_front_middle_state,
  CSRRestSensorGetStateRequestTypeEnumcooker_hob_back_right_state,
  CSRRestSensorGetStateRequestTypeEnumdesired_cooker_hob_back_right_state,
  CSRRestSensorGetStateRequestTypeEnumcooker_hob_front_right_state,
  CSRRestSensorGetStateRequestTypeEnumdesired_cooker_hob_front_right_state,
  CSRRestSensorGetStateRequestTypeEnumdesired_wakeup_alarm_time,
  CSRRestSensorGetStateRequestTypeEnumdesired_second_wakeup_alarm_time,
  CSRRestSensorGetStateRequestTypeEnumpassive_infrared_state,
  CSRRestSensorGetStateRequestTypeEnumwater_flowing,
  CSRRestSensorGetStateRequestTypeEnumdesired_water_flow,
  CSRRestSensorGetStateRequestTypeEnumaudio_level,
  CSRRestSensorGetStateRequestTypeEnumdesired_audio_level,
  CSRRestSensorGetStateRequestTypeEnumfan_speed,
  CSRRestSensorGetStateRequestTypeEnumdesired_fan_speed,
  CSRRestSensorGetStateRequestTypeEnumwind_speed,
  CSRRestSensorGetStateRequestTypeEnumwind_speed_gust,
  CSRRestSensorGetStateRequestTypeEnumwind_direction,
  CSRRestSensorGetStateRequestTypeEnumwind_direction_gust,
  CSRRestSensorGetStateRequestTypeEnumrain_fall_last_hour,
  CSRRestSensorGetStateRequestTypeEnumrain_fall_today,
  CSRRestSensorGetStateRequestTypeEnumbarometric_pressure,
  CSRRestSensorGetStateRequestTypeEnumsoil_temperature,
  CSRRestSensorGetStateRequestTypeEnumsoil_moisure,
  CSRRestSensorGetStateRequestTypeEnumwindow_cover_position,
  CSRRestSensorGetStateRequestTypeEnumdesired_window_cover_position,
  CSRRestSensorGetStateRequestTypeEnumgeneric_1_byte,
  CSRRestSensorGetStateRequestTypeEnumgeneric_2_byte,
  CSRRestSensorGetStateRequestTypeEnumgeneric_1_byte_typed,
  CSRRestSensorGetStateRequestTypeEnumgeneric_2_byte_typed,
  CSRRestSensorGetStateRequestTypeEnumgeneric_3_byte_typed,

};



/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor types being configured.
*/
@property(nonatomic) CSRRestSensorGetStateRequestTypeEnum type;

/*!
  Constructs instance of CSRRestSensorGetStateRequest

  @param type - (CSRRestSensorGetStateRequestTypeEnum) Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor types being configured.
  
  @return instance of CSRRestSensorGetStateRequest
*/
- (id) initWithtype: (CSRRestSensorGetStateRequestTypeEnum) type;
       

@end
