/*!
    Copyright [2015] Qualcomm Technologies International, Ltd.
*/
/* Note: this is an auto-generated file. */


#import <Foundation/Foundation.h>
#import "CSRRestBaseObject.h"


/*!
    Request Object for WriteValue API for the Sensor model
*/

@interface CSRRestSensorWriteValueRequest : CSRRestBaseObject


/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type of the value.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorWriteValueRequestTypeEnum) {
  CSRRestSensorWriteValueRequestTypeEnumunknown,
  CSRRestSensorWriteValueRequestTypeEnuminternal_air_temperature,
  CSRRestSensorWriteValueRequestTypeEnumexternal_air_temperature,
  CSRRestSensorWriteValueRequestTypeEnumdesired_air_temperature,
  CSRRestSensorWriteValueRequestTypeEnuminternal_humidity,
  CSRRestSensorWriteValueRequestTypeEnumexternal_humidity,
  CSRRestSensorWriteValueRequestTypeEnumexternal_dewpoint,
  CSRRestSensorWriteValueRequestTypeEnuminternal_door,
  CSRRestSensorWriteValueRequestTypeEnumexternal_door,
  CSRRestSensorWriteValueRequestTypeEnuminternal_window,
  CSRRestSensorWriteValueRequestTypeEnumexternal_window,
  CSRRestSensorWriteValueRequestTypeEnumsolar_energy,
  CSRRestSensorWriteValueRequestTypeEnumnumber_of_activations,
  CSRRestSensorWriteValueRequestTypeEnumfridge_temperature,
  CSRRestSensorWriteValueRequestTypeEnumdesired_fridge_temperature,
  CSRRestSensorWriteValueRequestTypeEnumfreezer_temperature,
  CSRRestSensorWriteValueRequestTypeEnumdesired_freezer_temperature,
  CSRRestSensorWriteValueRequestTypeEnumoven_temperature,
  CSRRestSensorWriteValueRequestTypeEnumdesired_oven_temperature,
  CSRRestSensorWriteValueRequestTypeEnumseat_occupied,
  CSRRestSensorWriteValueRequestTypeEnumwashing_machine_state,
  CSRRestSensorWriteValueRequestTypeEnumdish_washer_state,
  CSRRestSensorWriteValueRequestTypeEnumclothes_dryer_state,
  CSRRestSensorWriteValueRequestTypeEnumtoaster_state,
  CSRRestSensorWriteValueRequestTypeEnumcarbon_dioxide,
  CSRRestSensorWriteValueRequestTypeEnumcarbon_monoxide,
  CSRRestSensorWriteValueRequestTypeEnumsmoke,
  CSRRestSensorWriteValueRequestTypeEnumwater_level,
  CSRRestSensorWriteValueRequestTypeEnumhot_water_temperature,
  CSRRestSensorWriteValueRequestTypeEnumcold_water_temperature,
  CSRRestSensorWriteValueRequestTypeEnumdesired_water_temperature,
  CSRRestSensorWriteValueRequestTypeEnumcooker_hob_back_left_state,
  CSRRestSensorWriteValueRequestTypeEnumdesired_cooker_hob_back_left_state,
  CSRRestSensorWriteValueRequestTypeEnumcooker_hob_front_left_state,
  CSRRestSensorWriteValueRequestTypeEnumdesired_cooker_hob_front_left_state,
  CSRRestSensorWriteValueRequestTypeEnumcooker_hob_back_middle_state,
  CSRRestSensorWriteValueRequestTypeEnumdesired_cooker_hob_back_middle_state,
  CSRRestSensorWriteValueRequestTypeEnumcooker_hob_front_middle_state,
  CSRRestSensorWriteValueRequestTypeEnumdesired_cooker_hob_front_middle_state,
  CSRRestSensorWriteValueRequestTypeEnumcooker_hob_back_right_state,
  CSRRestSensorWriteValueRequestTypeEnumdesired_cooker_hob_back_right_state,
  CSRRestSensorWriteValueRequestTypeEnumcooker_hob_front_right_state,
  CSRRestSensorWriteValueRequestTypeEnumdesired_cooker_hob_front_right_state,
  CSRRestSensorWriteValueRequestTypeEnumdesired_wakeup_alarm_time,
  CSRRestSensorWriteValueRequestTypeEnumdesired_second_wakeup_alarm_time,
  CSRRestSensorWriteValueRequestTypeEnumpassive_infrared_state,
  CSRRestSensorWriteValueRequestTypeEnumwater_flowing,
  CSRRestSensorWriteValueRequestTypeEnumdesired_water_flow,
  CSRRestSensorWriteValueRequestTypeEnumaudio_level,
  CSRRestSensorWriteValueRequestTypeEnumdesired_audio_level,
  CSRRestSensorWriteValueRequestTypeEnumfan_speed,
  CSRRestSensorWriteValueRequestTypeEnumdesired_fan_speed,
  CSRRestSensorWriteValueRequestTypeEnumwind_speed,
  CSRRestSensorWriteValueRequestTypeEnumwind_speed_gust,
  CSRRestSensorWriteValueRequestTypeEnumwind_direction,
  CSRRestSensorWriteValueRequestTypeEnumwind_direction_gust,
  CSRRestSensorWriteValueRequestTypeEnumrain_fall_last_hour,
  CSRRestSensorWriteValueRequestTypeEnumrain_fall_today,
  CSRRestSensorWriteValueRequestTypeEnumbarometric_pressure,
  CSRRestSensorWriteValueRequestTypeEnumsoil_temperature,
  CSRRestSensorWriteValueRequestTypeEnumsoil_moisure,
  CSRRestSensorWriteValueRequestTypeEnumwindow_cover_position,
  CSRRestSensorWriteValueRequestTypeEnumdesired_window_cover_position,
  CSRRestSensorWriteValueRequestTypeEnumgeneric_1_byte,
  CSRRestSensorWriteValueRequestTypeEnumgeneric_2_byte,
  CSRRestSensorWriteValueRequestTypeEnumgeneric_1_byte_typed,
  CSRRestSensorWriteValueRequestTypeEnumgeneric_2_byte_typed,
  CSRRestSensorWriteValueRequestTypeEnumgeneric_3_byte_typed,

};

/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the second sensor type of the value. This field is optional, and can be zero octets in length.
*/
 typedef NS_OPTIONS(NSInteger, CSRRestSensorWriteValueRequestType2Enum) {
  CSRRestSensorWriteValueRequestType2Enumunknown,
  CSRRestSensorWriteValueRequestType2Enuminternal_air_temperature,
  CSRRestSensorWriteValueRequestType2Enumexternal_air_temperature,
  CSRRestSensorWriteValueRequestType2Enumdesired_air_temperature,
  CSRRestSensorWriteValueRequestType2Enuminternal_humidity,
  CSRRestSensorWriteValueRequestType2Enumexternal_humidity,
  CSRRestSensorWriteValueRequestType2Enumexternal_dewpoint,
  CSRRestSensorWriteValueRequestType2Enuminternal_door,
  CSRRestSensorWriteValueRequestType2Enumexternal_door,
  CSRRestSensorWriteValueRequestType2Enuminternal_window,
  CSRRestSensorWriteValueRequestType2Enumexternal_window,
  CSRRestSensorWriteValueRequestType2Enumsolar_energy,
  CSRRestSensorWriteValueRequestType2Enumnumber_of_activations,
  CSRRestSensorWriteValueRequestType2Enumfridge_temperature,
  CSRRestSensorWriteValueRequestType2Enumdesired_fridge_temperature,
  CSRRestSensorWriteValueRequestType2Enumfreezer_temperature,
  CSRRestSensorWriteValueRequestType2Enumdesired_freezer_temperature,
  CSRRestSensorWriteValueRequestType2Enumoven_temperature,
  CSRRestSensorWriteValueRequestType2Enumdesired_oven_temperature,
  CSRRestSensorWriteValueRequestType2Enumseat_occupied,
  CSRRestSensorWriteValueRequestType2Enumwashing_machine_state,
  CSRRestSensorWriteValueRequestType2Enumdish_washer_state,
  CSRRestSensorWriteValueRequestType2Enumclothes_dryer_state,
  CSRRestSensorWriteValueRequestType2Enumtoaster_state,
  CSRRestSensorWriteValueRequestType2Enumcarbon_dioxide,
  CSRRestSensorWriteValueRequestType2Enumcarbon_monoxide,
  CSRRestSensorWriteValueRequestType2Enumsmoke,
  CSRRestSensorWriteValueRequestType2Enumwater_level,
  CSRRestSensorWriteValueRequestType2Enumhot_water_temperature,
  CSRRestSensorWriteValueRequestType2Enumcold_water_temperature,
  CSRRestSensorWriteValueRequestType2Enumdesired_water_temperature,
  CSRRestSensorWriteValueRequestType2Enumcooker_hob_back_left_state,
  CSRRestSensorWriteValueRequestType2Enumdesired_cooker_hob_back_left_state,
  CSRRestSensorWriteValueRequestType2Enumcooker_hob_front_left_state,
  CSRRestSensorWriteValueRequestType2Enumdesired_cooker_hob_front_left_state,
  CSRRestSensorWriteValueRequestType2Enumcooker_hob_back_middle_state,
  CSRRestSensorWriteValueRequestType2Enumdesired_cooker_hob_back_middle_state,
  CSRRestSensorWriteValueRequestType2Enumcooker_hob_front_middle_state,
  CSRRestSensorWriteValueRequestType2Enumdesired_cooker_hob_front_middle_state,
  CSRRestSensorWriteValueRequestType2Enumcooker_hob_back_right_state,
  CSRRestSensorWriteValueRequestType2Enumdesired_cooker_hob_back_right_state,
  CSRRestSensorWriteValueRequestType2Enumcooker_hob_front_right_state,
  CSRRestSensorWriteValueRequestType2Enumdesired_cooker_hob_front_right_state,
  CSRRestSensorWriteValueRequestType2Enumdesired_wakeup_alarm_time,
  CSRRestSensorWriteValueRequestType2Enumdesired_second_wakeup_alarm_time,
  CSRRestSensorWriteValueRequestType2Enumpassive_infrared_state,
  CSRRestSensorWriteValueRequestType2Enumwater_flowing,
  CSRRestSensorWriteValueRequestType2Enumdesired_water_flow,
  CSRRestSensorWriteValueRequestType2Enumaudio_level,
  CSRRestSensorWriteValueRequestType2Enumdesired_audio_level,
  CSRRestSensorWriteValueRequestType2Enumfan_speed,
  CSRRestSensorWriteValueRequestType2Enumdesired_fan_speed,
  CSRRestSensorWriteValueRequestType2Enumwind_speed,
  CSRRestSensorWriteValueRequestType2Enumwind_speed_gust,
  CSRRestSensorWriteValueRequestType2Enumwind_direction,
  CSRRestSensorWriteValueRequestType2Enumwind_direction_gust,
  CSRRestSensorWriteValueRequestType2Enumrain_fall_last_hour,
  CSRRestSensorWriteValueRequestType2Enumrain_fall_today,
  CSRRestSensorWriteValueRequestType2Enumbarometric_pressure,
  CSRRestSensorWriteValueRequestType2Enumsoil_temperature,
  CSRRestSensorWriteValueRequestType2Enumsoil_moisure,
  CSRRestSensorWriteValueRequestType2Enumwindow_cover_position,
  CSRRestSensorWriteValueRequestType2Enumdesired_window_cover_position,
  CSRRestSensorWriteValueRequestType2Enumgeneric_1_byte,
  CSRRestSensorWriteValueRequestType2Enumgeneric_2_byte,
  CSRRestSensorWriteValueRequestType2Enumgeneric_1_byte_typed,
  CSRRestSensorWriteValueRequestType2Enumgeneric_2_byte_typed,
  CSRRestSensorWriteValueRequestType2Enumgeneric_3_byte_typed,

};



/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type of the value.
*/
@property(nonatomic) CSRRestSensorWriteValueRequestTypeEnum type;

/*!
    Sensor Value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type field.
*/
@property(nonatomic) NSArray* value;
  
/*!
    Sensor type. The Type field is a 16-bit unsigned integer that determines the second sensor type of the value. This field is optional, and can be zero octets in length.
*/
@property(nonatomic) CSRRestSensorWriteValueRequestType2Enum type2;

/*!
    Sensor Value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type2 field. This field is optional, and can be zero octets in length.
*/
@property(nonatomic) NSArray* value2;
  
/*!
  Constructs instance of CSRRestSensorWriteValueRequest

  @param type - (CSRRestSensorWriteValueRequestTypeEnum) Sensor type. The Type field is a 16-bit unsigned integer that determines the sensor type of the value.
  @param value - (NSArray*) Sensor Value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type field.
  @param type2 - (CSRRestSensorWriteValueRequestType2Enum) Sensor type. The Type field is a 16-bit unsigned integer that determines the second sensor type of the value. This field is optional, and can be zero octets in length.
  @param value2 - (NSArray*) Sensor Value. The Value field is from 1 to 4 octets in length; the format of this field is determined by the Type2 field. This field is optional, and can be zero octets in length.
  
  @return instance of CSRRestSensorWriteValueRequest
*/
- (id) initWithtype: (CSRRestSensorWriteValueRequestTypeEnum) type     
       value: (NSArray*) value     
       type2: (CSRRestSensorWriteValueRequestType2Enum) type2     
       value2: (NSArray*) value2;
       

@end
