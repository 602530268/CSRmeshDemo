/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Sensor State response object
*/

@interface CSRRestSensorState : CSRRestBaseObject


/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type for the associated state.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorStateTypeEnum) {
  CSRRestSensorStateTypeEnumunknown,
  CSRRestSensorStateTypeEnuminternal_air_temperature,
  CSRRestSensorStateTypeEnumexternal_air_temperature,
  CSRRestSensorStateTypeEnumdesired_air_temperature,
  CSRRestSensorStateTypeEnuminternal_humidity,
  CSRRestSensorStateTypeEnumexternal_humidity,
  CSRRestSensorStateTypeEnumexternal_dewpoint,
  CSRRestSensorStateTypeEnuminternal_door,
  CSRRestSensorStateTypeEnumexternal_door,
  CSRRestSensorStateTypeEnuminternal_window,
  CSRRestSensorStateTypeEnumexternal_window,
  CSRRestSensorStateTypeEnumsolar_energy,
  CSRRestSensorStateTypeEnumnumber_of_activations,
  CSRRestSensorStateTypeEnumfridge_temperature,
  CSRRestSensorStateTypeEnumdesired_fridge_temperature,
  CSRRestSensorStateTypeEnumfreezer_temperature,
  CSRRestSensorStateTypeEnumdesired_freezer_temperature,
  CSRRestSensorStateTypeEnumoven_temperature,
  CSRRestSensorStateTypeEnumdesired_oven_temperature,
  CSRRestSensorStateTypeEnumseat_occupied,
  CSRRestSensorStateTypeEnumwashing_machine_state,
  CSRRestSensorStateTypeEnumdish_washer_state,
  CSRRestSensorStateTypeEnumclothes_dryer_state,
  CSRRestSensorStateTypeEnumtoaster_state,
  CSRRestSensorStateTypeEnumcarbon_dioxide,
  CSRRestSensorStateTypeEnumcarbon_monoxide,
  CSRRestSensorStateTypeEnumsmoke,
  CSRRestSensorStateTypeEnumwater_level,
  CSRRestSensorStateTypeEnumhot_water_temperature,
  CSRRestSensorStateTypeEnumcold_water_temperature,
  CSRRestSensorStateTypeEnumdesired_water_temperature,
  CSRRestSensorStateTypeEnumcooker_hob_back_left_state,
  CSRRestSensorStateTypeEnumdesired_cooker_hob_back_left_state,
  CSRRestSensorStateTypeEnumcooker_hob_front_left_state,
  CSRRestSensorStateTypeEnumdesired_cooker_hob_front_left_state,
  CSRRestSensorStateTypeEnumcooker_hob_back_middle_state,
  CSRRestSensorStateTypeEnumdesired_cooker_hob_back_middle_state,
  CSRRestSensorStateTypeEnumcooker_hob_front_middle_state,
  CSRRestSensorStateTypeEnumdesired_cooker_hob_front_middle_state,
  CSRRestSensorStateTypeEnumcooker_hob_back_right_state,
  CSRRestSensorStateTypeEnumdesired_cooker_hob_back_right_state,
  CSRRestSensorStateTypeEnumcooker_hob_front_right_state,
  CSRRestSensorStateTypeEnumdesired_cooker_hob_front_right_state,
  CSRRestSensorStateTypeEnumdesired_wakeup_alarm_time,
  CSRRestSensorStateTypeEnumdesired_second_wakeup_alarm_time,
  CSRRestSensorStateTypeEnumpassive_infrared_state,
  CSRRestSensorStateTypeEnumwater_flowing,
  CSRRestSensorStateTypeEnumdesired_water_flow,
  CSRRestSensorStateTypeEnumaudio_level,
  CSRRestSensorStateTypeEnumdesired_audio_level,
  CSRRestSensorStateTypeEnumfan_speed,
  CSRRestSensorStateTypeEnumdesired_fan_speed,
  CSRRestSensorStateTypeEnumwind_speed,
  CSRRestSensorStateTypeEnumwind_speed_gust,
  CSRRestSensorStateTypeEnumwind_direction,
  CSRRestSensorStateTypeEnumwind_direction_gust,
  CSRRestSensorStateTypeEnumrain_fall_last_hour,
  CSRRestSensorStateTypeEnumrain_fall_today,
  CSRRestSensorStateTypeEnumbarometric_pressure,
  CSRRestSensorStateTypeEnumsoil_temperature,
  CSRRestSensorStateTypeEnumsoil_moisure,
  CSRRestSensorStateTypeEnumwindow_cover_position,
  CSRRestSensorStateTypeEnumdesired_window_cover_position,
  CSRRestSensorStateTypeEnumgeneric_1_byte,
  CSRRestSensorStateTypeEnumgeneric_2_byte,
  CSRRestSensorStateTypeEnumgeneric_1_byte_typed,
  CSRRestSensorStateTypeEnumgeneric_2_byte_typed,
  CSRRestSensorStateTypeEnumgeneric_3_byte_typed,

};



/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type for the associated state.
*/
@property(nonatomic) CSRRestSensorStateTypeEnum type;

/*!
    How often the sensor value is repeated.
*/
@property(nonatomic) NSNumber* repeatInterval;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestSensorState

  @param type - (CSRRestSensorStateTypeEnum) Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type for the associated state.
  @param repeatInterval - (NSNumber*) How often the sensor value is repeated.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestSensorState
*/
- (id) initWithtype: (CSRRestSensorStateTypeEnum) type     
       repeatInterval: (NSNumber*) repeatInterval     
       deviceId: (NSNumber*) deviceId;
       

@end
