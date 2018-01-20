/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Sensor Types response object
*/

@interface CSRRestSensorTypes : CSRRestBaseObject


/*!
    Array of sensor types supported (16 bits per type). The Types field is a variable length sequence of sensor types that the device sending this message supports. The sensor types included in this message shall be ordered by sensor type number and shall always be higher than the FirstType in the corresponding SENSOR_GET_TYPES message. Note: This field can be zero octets in length if a device does not support any sensor types greater than or equal to the FirstType in the corresponding SENSOR_GET_TYPES message.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorTypesTypesEnum) {
  CSRRestSensorTypesTypesEnumunknown,
  CSRRestSensorTypesTypesEnuminternal_air_temperature,
  CSRRestSensorTypesTypesEnumexternal_air_temperature,
  CSRRestSensorTypesTypesEnumdesired_air_temperature,
  CSRRestSensorTypesTypesEnuminternal_humidity,
  CSRRestSensorTypesTypesEnumexternal_humidity,
  CSRRestSensorTypesTypesEnumexternal_dewpoint,
  CSRRestSensorTypesTypesEnuminternal_door,
  CSRRestSensorTypesTypesEnumexternal_door,
  CSRRestSensorTypesTypesEnuminternal_window,
  CSRRestSensorTypesTypesEnumexternal_window,
  CSRRestSensorTypesTypesEnumsolar_energy,
  CSRRestSensorTypesTypesEnumnumber_of_activations,
  CSRRestSensorTypesTypesEnumfridge_temperature,
  CSRRestSensorTypesTypesEnumdesired_fridge_temperature,
  CSRRestSensorTypesTypesEnumfreezer_temperature,
  CSRRestSensorTypesTypesEnumdesired_freezer_temperature,
  CSRRestSensorTypesTypesEnumoven_temperature,
  CSRRestSensorTypesTypesEnumdesired_oven_temperature,
  CSRRestSensorTypesTypesEnumseat_occupied,
  CSRRestSensorTypesTypesEnumwashing_machine_state,
  CSRRestSensorTypesTypesEnumdish_washer_state,
  CSRRestSensorTypesTypesEnumclothes_dryer_state,
  CSRRestSensorTypesTypesEnumtoaster_state,
  CSRRestSensorTypesTypesEnumcarbon_dioxide,
  CSRRestSensorTypesTypesEnumcarbon_monoxide,
  CSRRestSensorTypesTypesEnumsmoke,
  CSRRestSensorTypesTypesEnumwater_level,
  CSRRestSensorTypesTypesEnumhot_water_temperature,
  CSRRestSensorTypesTypesEnumcold_water_temperature,
  CSRRestSensorTypesTypesEnumdesired_water_temperature,
  CSRRestSensorTypesTypesEnumcooker_hob_back_left_state,
  CSRRestSensorTypesTypesEnumdesired_cooker_hob_back_left_state,
  CSRRestSensorTypesTypesEnumcooker_hob_front_left_state,
  CSRRestSensorTypesTypesEnumdesired_cooker_hob_front_left_state,
  CSRRestSensorTypesTypesEnumcooker_hob_back_middle_state,
  CSRRestSensorTypesTypesEnumdesired_cooker_hob_back_middle_state,
  CSRRestSensorTypesTypesEnumcooker_hob_front_middle_state,
  CSRRestSensorTypesTypesEnumdesired_cooker_hob_front_middle_state,
  CSRRestSensorTypesTypesEnumcooker_hob_back_right_state,
  CSRRestSensorTypesTypesEnumdesired_cooker_hob_back_right_state,
  CSRRestSensorTypesTypesEnumcooker_hob_front_right_state,
  CSRRestSensorTypesTypesEnumdesired_cooker_hob_front_right_state,
  CSRRestSensorTypesTypesEnumdesired_wakeup_alarm_time,
  CSRRestSensorTypesTypesEnumdesired_second_wakeup_alarm_time,
  CSRRestSensorTypesTypesEnumpassive_infrared_state,
  CSRRestSensorTypesTypesEnumwater_flowing,
  CSRRestSensorTypesTypesEnumdesired_water_flow,
  CSRRestSensorTypesTypesEnumaudio_level,
  CSRRestSensorTypesTypesEnumdesired_audio_level,
  CSRRestSensorTypesTypesEnumfan_speed,
  CSRRestSensorTypesTypesEnumdesired_fan_speed,
  CSRRestSensorTypesTypesEnumwind_speed,
  CSRRestSensorTypesTypesEnumwind_speed_gust,
  CSRRestSensorTypesTypesEnumwind_direction,
  CSRRestSensorTypesTypesEnumwind_direction_gust,
  CSRRestSensorTypesTypesEnumrain_fall_last_hour,
  CSRRestSensorTypesTypesEnumrain_fall_today,
  CSRRestSensorTypesTypesEnumbarometric_pressure,
  CSRRestSensorTypesTypesEnumsoil_temperature,
  CSRRestSensorTypesTypesEnumsoil_moisure,
  CSRRestSensorTypesTypesEnumwindow_cover_position,
  CSRRestSensorTypesTypesEnumdesired_window_cover_position,
  CSRRestSensorTypesTypesEnumgeneric_1_byte,
  CSRRestSensorTypesTypesEnumgeneric_2_byte,
  CSRRestSensorTypesTypesEnumgeneric_1_byte_typed,
  CSRRestSensorTypesTypesEnumgeneric_2_byte_typed,
  CSRRestSensorTypesTypesEnumgeneric_3_byte_typed,

};



/*!
Array of sensor types supported (16 bits per type). The Types field is a variable length sequence of sensor types that the device sending this message supports. The sensor types included in this message shall be ordered by sensor type number and shall always be higher than the FirstType in the corresponding SENSOR_GET_TYPES message. Note: This field can be zero octets in length if a device does not support any sensor types greater than or equal to the FirstType in the corresponding SENSOR_GET_TYPES message.
*/
@property(nonatomic) NSArray* types;

/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestSensorTypes

  @param types - (CSRRestSensorTypesTypesEnum) Array of sensor types supported (16 bits per type). The Types field is a variable length sequence of sensor types that the device sending this message supports. The sensor types included in this message shall be ordered by sensor type number and shall always be higher than the FirstType in the corresponding SENSOR_GET_TYPES message. Note: This field can be zero octets in length if a device does not support any sensor types greater than or equal to the FirstType in the corresponding SENSOR_GET_TYPES message.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestSensorTypes
*/
- (id) initWithtypes: (NSArray*) types     
       deviceId: (NSNumber*) deviceId;
       

@end
