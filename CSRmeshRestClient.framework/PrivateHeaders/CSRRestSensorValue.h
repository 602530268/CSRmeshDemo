/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    The actual Sensor Value response object
*/

@interface CSRRestSensorValue : CSRRestBaseObject


/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type of the value.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorValueTypeEnum) {
  CSRRestSensorValueTypeEnumunknown,
  CSRRestSensorValueTypeEnuminternal_air_temperature,
  CSRRestSensorValueTypeEnumexternal_air_temperature,
  CSRRestSensorValueTypeEnumdesired_air_temperature,
  CSRRestSensorValueTypeEnuminternal_humidity,
  CSRRestSensorValueTypeEnumexternal_humidity,
  CSRRestSensorValueTypeEnumexternal_dewpoint,
  CSRRestSensorValueTypeEnuminternal_door,
  CSRRestSensorValueTypeEnumexternal_door,
  CSRRestSensorValueTypeEnuminternal_window,
  CSRRestSensorValueTypeEnumexternal_window,
  CSRRestSensorValueTypeEnumsolar_energy,
  CSRRestSensorValueTypeEnumnumber_of_activations,
  CSRRestSensorValueTypeEnumfridge_temperature,
  CSRRestSensorValueTypeEnumdesired_fridge_temperature,
  CSRRestSensorValueTypeEnumfreezer_temperature,
  CSRRestSensorValueTypeEnumdesired_freezer_temperature,
  CSRRestSensorValueTypeEnumoven_temperature,
  CSRRestSensorValueTypeEnumdesired_oven_temperature,
  CSRRestSensorValueTypeEnumseat_occupied,
  CSRRestSensorValueTypeEnumwashing_machine_state,
  CSRRestSensorValueTypeEnumdish_washer_state,
  CSRRestSensorValueTypeEnumclothes_dryer_state,
  CSRRestSensorValueTypeEnumtoaster_state,
  CSRRestSensorValueTypeEnumcarbon_dioxide,
  CSRRestSensorValueTypeEnumcarbon_monoxide,
  CSRRestSensorValueTypeEnumsmoke,
  CSRRestSensorValueTypeEnumwater_level,
  CSRRestSensorValueTypeEnumhot_water_temperature,
  CSRRestSensorValueTypeEnumcold_water_temperature,
  CSRRestSensorValueTypeEnumdesired_water_temperature,
  CSRRestSensorValueTypeEnumcooker_hob_back_left_state,
  CSRRestSensorValueTypeEnumdesired_cooker_hob_back_left_state,
  CSRRestSensorValueTypeEnumcooker_hob_front_left_state,
  CSRRestSensorValueTypeEnumdesired_cooker_hob_front_left_state,
  CSRRestSensorValueTypeEnumcooker_hob_back_middle_state,
  CSRRestSensorValueTypeEnumdesired_cooker_hob_back_middle_state,
  CSRRestSensorValueTypeEnumcooker_hob_front_middle_state,
  CSRRestSensorValueTypeEnumdesired_cooker_hob_front_middle_state,
  CSRRestSensorValueTypeEnumcooker_hob_back_right_state,
  CSRRestSensorValueTypeEnumdesired_cooker_hob_back_right_state,
  CSRRestSensorValueTypeEnumcooker_hob_front_right_state,
  CSRRestSensorValueTypeEnumdesired_cooker_hob_front_right_state,
  CSRRestSensorValueTypeEnumdesired_wakeup_alarm_time,
  CSRRestSensorValueTypeEnumdesired_second_wakeup_alarm_time,
  CSRRestSensorValueTypeEnumpassive_infrared_state,
  CSRRestSensorValueTypeEnumwater_flowing,
  CSRRestSensorValueTypeEnumdesired_water_flow,
  CSRRestSensorValueTypeEnumaudio_level,
  CSRRestSensorValueTypeEnumdesired_audio_level,
  CSRRestSensorValueTypeEnumfan_speed,
  CSRRestSensorValueTypeEnumdesired_fan_speed,
  CSRRestSensorValueTypeEnumwind_speed,
  CSRRestSensorValueTypeEnumwind_speed_gust,
  CSRRestSensorValueTypeEnumwind_direction,
  CSRRestSensorValueTypeEnumwind_direction_gust,
  CSRRestSensorValueTypeEnumrain_fall_last_hour,
  CSRRestSensorValueTypeEnumrain_fall_today,
  CSRRestSensorValueTypeEnumbarometric_pressure,
  CSRRestSensorValueTypeEnumsoil_temperature,
  CSRRestSensorValueTypeEnumsoil_moisure,
  CSRRestSensorValueTypeEnumwindow_cover_position,
  CSRRestSensorValueTypeEnumdesired_window_cover_position,
  CSRRestSensorValueTypeEnumgeneric_1_byte,
  CSRRestSensorValueTypeEnumgeneric_2_byte,
  CSRRestSensorValueTypeEnumgeneric_1_byte_typed,
  CSRRestSensorValueTypeEnumgeneric_2_byte_typed,
  CSRRestSensorValueTypeEnumgeneric_3_byte_typed,

};

/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the second sensor type of the value. This field is optional, and can be zero octets in length.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorValueType2Enum) {
  CSRRestSensorValueType2Enumunknown,
  CSRRestSensorValueType2Enuminternal_air_temperature,
  CSRRestSensorValueType2Enumexternal_air_temperature,
  CSRRestSensorValueType2Enumdesired_air_temperature,
  CSRRestSensorValueType2Enuminternal_humidity,
  CSRRestSensorValueType2Enumexternal_humidity,
  CSRRestSensorValueType2Enumexternal_dewpoint,
  CSRRestSensorValueType2Enuminternal_door,
  CSRRestSensorValueType2Enumexternal_door,
  CSRRestSensorValueType2Enuminternal_window,
  CSRRestSensorValueType2Enumexternal_window,
  CSRRestSensorValueType2Enumsolar_energy,
  CSRRestSensorValueType2Enumnumber_of_activations,
  CSRRestSensorValueType2Enumfridge_temperature,
  CSRRestSensorValueType2Enumdesired_fridge_temperature,
  CSRRestSensorValueType2Enumfreezer_temperature,
  CSRRestSensorValueType2Enumdesired_freezer_temperature,
  CSRRestSensorValueType2Enumoven_temperature,
  CSRRestSensorValueType2Enumdesired_oven_temperature,
  CSRRestSensorValueType2Enumseat_occupied,
  CSRRestSensorValueType2Enumwashing_machine_state,
  CSRRestSensorValueType2Enumdish_washer_state,
  CSRRestSensorValueType2Enumclothes_dryer_state,
  CSRRestSensorValueType2Enumtoaster_state,
  CSRRestSensorValueType2Enumcarbon_dioxide,
  CSRRestSensorValueType2Enumcarbon_monoxide,
  CSRRestSensorValueType2Enumsmoke,
  CSRRestSensorValueType2Enumwater_level,
  CSRRestSensorValueType2Enumhot_water_temperature,
  CSRRestSensorValueType2Enumcold_water_temperature,
  CSRRestSensorValueType2Enumdesired_water_temperature,
  CSRRestSensorValueType2Enumcooker_hob_back_left_state,
  CSRRestSensorValueType2Enumdesired_cooker_hob_back_left_state,
  CSRRestSensorValueType2Enumcooker_hob_front_left_state,
  CSRRestSensorValueType2Enumdesired_cooker_hob_front_left_state,
  CSRRestSensorValueType2Enumcooker_hob_back_middle_state,
  CSRRestSensorValueType2Enumdesired_cooker_hob_back_middle_state,
  CSRRestSensorValueType2Enumcooker_hob_front_middle_state,
  CSRRestSensorValueType2Enumdesired_cooker_hob_front_middle_state,
  CSRRestSensorValueType2Enumcooker_hob_back_right_state,
  CSRRestSensorValueType2Enumdesired_cooker_hob_back_right_state,
  CSRRestSensorValueType2Enumcooker_hob_front_right_state,
  CSRRestSensorValueType2Enumdesired_cooker_hob_front_right_state,
  CSRRestSensorValueType2Enumdesired_wakeup_alarm_time,
  CSRRestSensorValueType2Enumdesired_second_wakeup_alarm_time,
  CSRRestSensorValueType2Enumpassive_infrared_state,
  CSRRestSensorValueType2Enumwater_flowing,
  CSRRestSensorValueType2Enumdesired_water_flow,
  CSRRestSensorValueType2Enumaudio_level,
  CSRRestSensorValueType2Enumdesired_audio_level,
  CSRRestSensorValueType2Enumfan_speed,
  CSRRestSensorValueType2Enumdesired_fan_speed,
  CSRRestSensorValueType2Enumwind_speed,
  CSRRestSensorValueType2Enumwind_speed_gust,
  CSRRestSensorValueType2Enumwind_direction,
  CSRRestSensorValueType2Enumwind_direction_gust,
  CSRRestSensorValueType2Enumrain_fall_last_hour,
  CSRRestSensorValueType2Enumrain_fall_today,
  CSRRestSensorValueType2Enumbarometric_pressure,
  CSRRestSensorValueType2Enumsoil_temperature,
  CSRRestSensorValueType2Enumsoil_moisure,
  CSRRestSensorValueType2Enumwindow_cover_position,
  CSRRestSensorValueType2Enumdesired_window_cover_position,
  CSRRestSensorValueType2Enumgeneric_1_byte,
  CSRRestSensorValueType2Enumgeneric_2_byte,
  CSRRestSensorValueType2Enumgeneric_1_byte_typed,
  CSRRestSensorValueType2Enumgeneric_2_byte_typed,
  CSRRestSensorValueType2Enumgeneric_3_byte_typed,

};



/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type of the value.
*/
@property(nonatomic) CSRRestSensorValueTypeEnum type;

/*!
    Sensor value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type field.
*/
@property(nonatomic) NSArray* value;
  
/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the second sensor type of the value. This field is optional, and can be zero octets in length.
*/
@property(nonatomic) CSRRestSensorValueType2Enum type2;

/*!
    Sensor value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type2 field. This field shall only be included if the Type2 field exists.
*/
@property(nonatomic) NSArray* value2;
  
/*!
    Id of the responding device
*/
@property(nonatomic) NSNumber* deviceId;
  
/*!
  Constructs instance of CSRRestSensorValue

  @param type - (CSRRestSensorValueTypeEnum) Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type of the value.
  @param value - (NSArray*) Sensor value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type field.
  @param type2 - (CSRRestSensorValueType2Enum) Sensor type. The Type field is a 16-bit unsigned integer that determines the second sensor type of the value. This field is optional, and can be zero octets in length.
  @param value2 - (NSArray*) Sensor value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type2 field. This field shall only be included if the Type2 field exists.
  @param deviceId - (NSNumber*) Id of the responding device
  
  @return instance of CSRRestSensorValue
*/
- (id) initWithtype: (CSRRestSensorValueTypeEnum) type     
       value: (NSArray*) value     
       type2: (CSRRestSensorValueType2Enum) type2     
       value2: (NSArray*) value2     
       deviceId: (NSNumber*) deviceId;
       

@end
