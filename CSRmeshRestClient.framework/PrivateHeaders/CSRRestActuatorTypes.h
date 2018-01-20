/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Actuator Types response object
*/

@interface CSRRestActuatorTypes : CSRRestBaseObject


/*!
    Array of sensor types supported (16 bits per type). The Types field is a variable length sequence of sensor types that the device sending this message supports. The sensor types included in this message is ordered by sensor type number and is always higher than the FirstType in the corresponding ACTUATOR_GET_TYPES message. Note: This field can be zero octets in length if a device does not support any sensor types greater than or equal to the FirstType in the corresponding ACTUATOR_GET_TYPES message.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestActuatorTypesTypesEnum) {
  CSRRestActuatorTypesTypesEnumunknown,
  CSRRestActuatorTypesTypesEnuminternal_air_temperature,
  CSRRestActuatorTypesTypesEnumexternal_air_temperature,
  CSRRestActuatorTypesTypesEnumdesired_air_temperature,
  CSRRestActuatorTypesTypesEnuminternal_humidity,
  CSRRestActuatorTypesTypesEnumexternal_humidity,
  CSRRestActuatorTypesTypesEnumexternal_dewpoint,
  CSRRestActuatorTypesTypesEnuminternal_door,
  CSRRestActuatorTypesTypesEnumexternal_door,
  CSRRestActuatorTypesTypesEnuminternal_window,
  CSRRestActuatorTypesTypesEnumexternal_window,
  CSRRestActuatorTypesTypesEnumsolar_energy,
  CSRRestActuatorTypesTypesEnumnumber_of_activations,
  CSRRestActuatorTypesTypesEnumfridge_temperature,
  CSRRestActuatorTypesTypesEnumdesired_fridge_temperature,
  CSRRestActuatorTypesTypesEnumfreezer_temperature,
  CSRRestActuatorTypesTypesEnumdesired_freezer_temperature,
  CSRRestActuatorTypesTypesEnumoven_temperature,
  CSRRestActuatorTypesTypesEnumdesired_oven_temperature,
  CSRRestActuatorTypesTypesEnumseat_occupied,
  CSRRestActuatorTypesTypesEnumwashing_machine_state,
  CSRRestActuatorTypesTypesEnumdish_washer_state,
  CSRRestActuatorTypesTypesEnumclothes_dryer_state,
  CSRRestActuatorTypesTypesEnumtoaster_state,
  CSRRestActuatorTypesTypesEnumcarbon_dioxide,
  CSRRestActuatorTypesTypesEnumcarbon_monoxide,
  CSRRestActuatorTypesTypesEnumsmoke,
  CSRRestActuatorTypesTypesEnumwater_level,
  CSRRestActuatorTypesTypesEnumhot_water_temperature,
  CSRRestActuatorTypesTypesEnumcold_water_temperature,
  CSRRestActuatorTypesTypesEnumdesired_water_temperature,
  CSRRestActuatorTypesTypesEnumcooker_hob_back_left_state,
  CSRRestActuatorTypesTypesEnumdesired_cooker_hob_back_left_state,
  CSRRestActuatorTypesTypesEnumcooker_hob_front_left_state,
  CSRRestActuatorTypesTypesEnumdesired_cooker_hob_front_left_state,
  CSRRestActuatorTypesTypesEnumcooker_hob_back_middle_state,
  CSRRestActuatorTypesTypesEnumdesired_cooker_hob_back_middle_state,
  CSRRestActuatorTypesTypesEnumcooker_hob_front_middle_state,
  CSRRestActuatorTypesTypesEnumdesired_cooker_hob_front_middle_state,
  CSRRestActuatorTypesTypesEnumcooker_hob_back_right_state,
  CSRRestActuatorTypesTypesEnumdesired_cooker_hob_back_right_state,
  CSRRestActuatorTypesTypesEnumcooker_hob_front_right_state,
  CSRRestActuatorTypesTypesEnumdesired_cooker_hob_front_right_state,
  CSRRestActuatorTypesTypesEnumdesired_wakeup_alarm_time,
  CSRRestActuatorTypesTypesEnumdesired_second_wakeup_alarm_time,
  CSRRestActuatorTypesTypesEnumpassive_infrared_state,
  CSRRestActuatorTypesTypesEnumwater_flowing,
  CSRRestActuatorTypesTypesEnumdesired_water_flow,
  CSRRestActuatorTypesTypesEnumaudio_level,
  CSRRestActuatorTypesTypesEnumdesired_audio_level,
  CSRRestActuatorTypesTypesEnumfan_speed,
  CSRRestActuatorTypesTypesEnumdesired_fan_speed,
  CSRRestActuatorTypesTypesEnumwind_speed,
  CSRRestActuatorTypesTypesEnumwind_speed_gust,
  CSRRestActuatorTypesTypesEnumwind_direction,
  CSRRestActuatorTypesTypesEnumwind_direction_gust,
  CSRRestActuatorTypesTypesEnumrain_fall_last_hour,
  CSRRestActuatorTypesTypesEnumrain_fall_today,
  CSRRestActuatorTypesTypesEnumbarometric_pressure,
  CSRRestActuatorTypesTypesEnumsoil_temperature,
  CSRRestActuatorTypesTypesEnumsoil_moisure,
  CSRRestActuatorTypesTypesEnumwindow_cover_position,
  CSRRestActuatorTypesTypesEnumdesired_window_cover_position,
  CSRRestActuatorTypesTypesEnumgeneric_1_byte,
  CSRRestActuatorTypesTypesEnumgeneric_2_byte,
  CSRRestActuatorTypesTypesEnumgeneric_1_byte_typed,
  CSRRestActuatorTypesTypesEnumgeneric_2_byte_typed,
  CSRRestActuatorTypesTypesEnumgeneric_3_byte_typed,

};



/*!
Array of sensor types supported (16 bits per type). The Types field is a variable length sequence of sensor types that the device sending this message supports. The sensor types included in this message is ordered by sensor type number and is always higher than the FirstType in the corresponding ACTUATOR_GET_TYPES message. Note: This field can be zero octets in length if a device does not support any sensor types greater than or equal to the FirstType in the corresponding ACTUATOR_GET_TYPES message.
*/
@property(nonatomic) NSArray* types;

/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestActuatorTypes

  @param types - (CSRRestActuatorTypesTypesEnum) Array of sensor types supported (16 bits per type). The Types field is a variable length sequence of sensor types that the device sending this message supports. The sensor types included in this message is ordered by sensor type number and is always higher than the FirstType in the corresponding ACTUATOR_GET_TYPES message. Note: This field can be zero octets in length if a device does not support any sensor types greater than or equal to the FirstType in the corresponding ACTUATOR_GET_TYPES message.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestActuatorTypes
*/
- (id) initWithtypes: (NSArray*) types     
       deviceId: (NSNumber*) deviceId;
       

@end
