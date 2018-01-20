/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for SetState API for the Sensor model
*/

@interface CSRRestSensorSetStateRequest : CSRRestBaseObject


/*!
    Sensor type.The Type field is a 16-bit unsigned integer that determines the sensor type for the associated state.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorSetStateRequestTypeEnum) {
  CSRRestSensorSetStateRequestTypeEnumunknown,
  CSRRestSensorSetStateRequestTypeEnuminternal_air_temperature,
  CSRRestSensorSetStateRequestTypeEnumexternal_air_temperature,
  CSRRestSensorSetStateRequestTypeEnumdesired_air_temperature,
  CSRRestSensorSetStateRequestTypeEnuminternal_humidity,
  CSRRestSensorSetStateRequestTypeEnumexternal_humidity,
  CSRRestSensorSetStateRequestTypeEnumexternal_dewpoint,
  CSRRestSensorSetStateRequestTypeEnuminternal_door,
  CSRRestSensorSetStateRequestTypeEnumexternal_door,
  CSRRestSensorSetStateRequestTypeEnuminternal_window,
  CSRRestSensorSetStateRequestTypeEnumexternal_window,
  CSRRestSensorSetStateRequestTypeEnumsolar_energy,
  CSRRestSensorSetStateRequestTypeEnumnumber_of_activations,
  CSRRestSensorSetStateRequestTypeEnumfridge_temperature,
  CSRRestSensorSetStateRequestTypeEnumdesired_fridge_temperature,
  CSRRestSensorSetStateRequestTypeEnumfreezer_temperature,
  CSRRestSensorSetStateRequestTypeEnumdesired_freezer_temperature,
  CSRRestSensorSetStateRequestTypeEnumoven_temperature,
  CSRRestSensorSetStateRequestTypeEnumdesired_oven_temperature,
  CSRRestSensorSetStateRequestTypeEnumseat_occupied,
  CSRRestSensorSetStateRequestTypeEnumwashing_machine_state,
  CSRRestSensorSetStateRequestTypeEnumdish_washer_state,
  CSRRestSensorSetStateRequestTypeEnumclothes_dryer_state,
  CSRRestSensorSetStateRequestTypeEnumtoaster_state,
  CSRRestSensorSetStateRequestTypeEnumcarbon_dioxide,
  CSRRestSensorSetStateRequestTypeEnumcarbon_monoxide,
  CSRRestSensorSetStateRequestTypeEnumsmoke,
  CSRRestSensorSetStateRequestTypeEnumwater_level,
  CSRRestSensorSetStateRequestTypeEnumhot_water_temperature,
  CSRRestSensorSetStateRequestTypeEnumcold_water_temperature,
  CSRRestSensorSetStateRequestTypeEnumdesired_water_temperature,
  CSRRestSensorSetStateRequestTypeEnumcooker_hob_back_left_state,
  CSRRestSensorSetStateRequestTypeEnumdesired_cooker_hob_back_left_state,
  CSRRestSensorSetStateRequestTypeEnumcooker_hob_front_left_state,
  CSRRestSensorSetStateRequestTypeEnumdesired_cooker_hob_front_left_state,
  CSRRestSensorSetStateRequestTypeEnumcooker_hob_back_middle_state,
  CSRRestSensorSetStateRequestTypeEnumdesired_cooker_hob_back_middle_state,
  CSRRestSensorSetStateRequestTypeEnumcooker_hob_front_middle_state,
  CSRRestSensorSetStateRequestTypeEnumdesired_cooker_hob_front_middle_state,
  CSRRestSensorSetStateRequestTypeEnumcooker_hob_back_right_state,
  CSRRestSensorSetStateRequestTypeEnumdesired_cooker_hob_back_right_state,
  CSRRestSensorSetStateRequestTypeEnumcooker_hob_front_right_state,
  CSRRestSensorSetStateRequestTypeEnumdesired_cooker_hob_front_right_state,
  CSRRestSensorSetStateRequestTypeEnumdesired_wakeup_alarm_time,
  CSRRestSensorSetStateRequestTypeEnumdesired_second_wakeup_alarm_time,
  CSRRestSensorSetStateRequestTypeEnumpassive_infrared_state,
  CSRRestSensorSetStateRequestTypeEnumwater_flowing,
  CSRRestSensorSetStateRequestTypeEnumdesired_water_flow,
  CSRRestSensorSetStateRequestTypeEnumaudio_level,
  CSRRestSensorSetStateRequestTypeEnumdesired_audio_level,
  CSRRestSensorSetStateRequestTypeEnumfan_speed,
  CSRRestSensorSetStateRequestTypeEnumdesired_fan_speed,
  CSRRestSensorSetStateRequestTypeEnumwind_speed,
  CSRRestSensorSetStateRequestTypeEnumwind_speed_gust,
  CSRRestSensorSetStateRequestTypeEnumwind_direction,
  CSRRestSensorSetStateRequestTypeEnumwind_direction_gust,
  CSRRestSensorSetStateRequestTypeEnumrain_fall_last_hour,
  CSRRestSensorSetStateRequestTypeEnumrain_fall_today,
  CSRRestSensorSetStateRequestTypeEnumbarometric_pressure,
  CSRRestSensorSetStateRequestTypeEnumsoil_temperature,
  CSRRestSensorSetStateRequestTypeEnumsoil_moisure,
  CSRRestSensorSetStateRequestTypeEnumwindow_cover_position,
  CSRRestSensorSetStateRequestTypeEnumdesired_window_cover_position,
  CSRRestSensorSetStateRequestTypeEnumgeneric_1_byte,
  CSRRestSensorSetStateRequestTypeEnumgeneric_2_byte,
  CSRRestSensorSetStateRequestTypeEnumgeneric_1_byte_typed,
  CSRRestSensorSetStateRequestTypeEnumgeneric_2_byte_typed,
  CSRRestSensorSetStateRequestTypeEnumgeneric_3_byte_typed,

};



/*!
    Sensor type.The Type field is a 16-bit unsigned integer that determines the sensor type for the associated state.
*/
@property(nonatomic) CSRRestSensorSetStateRequestTypeEnum type;

/*!
    How often the sensor value is repeated. The RepeatInterval is an 8-bit unsigned integer representing the interval in seconds between repeated transmissions of sensor values by this device.
*/
@property(nonatomic) NSNumber* repeatInterval;
  
/*!
  Constructs instance of CSRRestSensorSetStateRequest

  @param type - (CSRRestSensorSetStateRequestTypeEnum) Sensor type.The Type field is a 16-bit unsigned integer that determines the sensor type for the associated state.
  @param repeatInterval - (NSNumber*) How often the sensor value is repeated. The RepeatInterval is an 8-bit unsigned integer representing the interval in seconds between repeated transmissions of sensor values by this device.
  
  @return instance of CSRRestSensorSetStateRequest
*/
- (id) initWithtype: (CSRRestSensorSetStateRequestTypeEnum) type     
       repeatInterval: (NSNumber*) repeatInterval;
       

@end
