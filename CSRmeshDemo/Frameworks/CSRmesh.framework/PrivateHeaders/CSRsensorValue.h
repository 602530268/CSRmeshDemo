//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

// This file is generated and should not be modified.

@import Foundation;

/**
 * @enum  SensorType
 *        Pass as an uint16_t in a NSNumber object
 */
typedef NS_ENUM (uint16_t, CSRsensorType) {
    /** Desired Cooker Hob Back Middle State */
    CSRsensorType_Desired_Cooker_Hob_Back_Middle_State = 36,
    /** Freezer Temperature */
    CSRsensorType_Freezer_Temperature = 15,
    /** Desired Air Temperature */
    CSRsensorType_Desired_Air_Temperature = 3,
    /** Desired Second Wakeup Alarm Time */
    CSRsensorType_Desired_Second_Wakeup_Alarm_Time = 44,
    /** Wind Speed */
    CSRsensorType_Wind_Speed = 52,
    /** External Dewpoint */
    CSRsensorType_External_Dewpoint = 6,
    /** Desired Window Cover Position */
    CSRsensorType_Desired_Window_Cover_Position = 62,
    /** Internal Humidity */
    CSRsensorType_Internal_Humidity = 4,
    /** Toaster State */
    CSRsensorType_Toaster_State = 23,
    /** Carbon Monoxide */
    CSRsensorType_Carbon_Monoxide = 25,
    /** Desired Fan Speed */
    CSRsensorType_Desired_Fan_Speed = 51,
    /** Water Flowing */
    CSRsensorType_Water_Flowing = 46,
    /** Clothes Dryer State */
    CSRsensorType_Clothes_Dryer_State = 22,
    /** Carbon Dioxide */
    CSRsensorType_Carbon_Dioxide = 24,
    /** Generic 2 Byte */
    CSRsensorType_Generic_2_Byte = 64,
    /** Generic 1 Byte Typed */
    CSRsensorType_Generic_1_Byte_Typed = 250,
    /** Soil Moisure */
    CSRsensorType_Soil_Moisure = 60,
    /** Generic 3 Byte Typed */
    CSRsensorType_Generic_3_Byte_Typed = 252,
    /** Water Level */
    CSRsensorType_Water_Level = 27,
    /** Barometric Pressure */
    CSRsensorType_Barometric_Pressure = 58,
    /** Oven Temperature */
    CSRsensorType_Oven_Temperature = 17,
    /** External Door */
    CSRsensorType_External_Door = 8,
    /** Washing Machine State */
    CSRsensorType_Washing_Machine_State = 20,
    /** Rain Fall Last Hour */
    CSRsensorType_Rain_Fall_Last_Hour = 56,
    /** Cooker Hob Front Middle State */
    CSRsensorType_Cooker_Hob_Front_Middle_State = 37,
    /** Internal Door */
    CSRsensorType_Internal_Door = 7,
    /** Audio Level */
    CSRsensorType_Audio_Level = 48,
    /** Desired Cooker Hob Front Left State */
    CSRsensorType_Desired_Cooker_Hob_Front_Left_State = 34,
    /** Generic 1 Byte */
    CSRsensorType_Generic_1_Byte = 63,
    /** Desired Freezer Temperature */
    CSRsensorType_Desired_Freezer_Temperature = 16,
    /** Soil Temperature */
    CSRsensorType_Soil_Temperature = 59,
    /** Desired Cooker Hob Front Right State */
    CSRsensorType_Desired_Cooker_Hob_Front_Right_State = 42,
    /** Desired Audio Level */
    CSRsensorType_Desired_Audio_Level = 49,
    /** Window Cover Position */
    CSRsensorType_Window_Cover_Position = 61,
    /** Desired Water Flow */
    CSRsensorType_Desired_Water_Flow = 47,
    /** Wind Direction */
    CSRsensorType_Wind_Direction = 54,
    /** Cooker Hob Back Middle State */
    CSRsensorType_Cooker_Hob_Back_Middle_State = 35,
    /** Internal Window */
    CSRsensorType_Internal_Window = 9,
    /** Cooker Hob Back Left State */
    CSRsensorType_Cooker_Hob_Back_Left_State = 31,
    /** External Humidity */
    CSRsensorType_External_Humidity = 5,
    /** Desired Water Temperature */
    CSRsensorType_Desired_Water_Temperature = 30,
    /** External Air Temperature */
    CSRsensorType_External_Air_Temperature = 2,
    /** Desired Fridge Temperature */
    CSRsensorType_Desired_Fridge_Temperature = 14,
    /** Number Of Activations */
    CSRsensorType_Number_Of_Activations = 12,
    /** Cooker Hob Back Right State */
    CSRsensorType_Cooker_Hob_Back_Right_State = 39,
    /** Cooker Hob Front Right State */
    CSRsensorType_Cooker_Hob_Front_Right_State = 41,
    /** Internal Air Temperature */
    CSRsensorType_Internal_Air_Temperature = 1,
    /** Fan Speed */
    CSRsensorType_Fan_Speed = 50,
    /** Wind Speed Gust */
    CSRsensorType_Wind_Speed_Gust = 53,
    /** Hot Water Temperature */
    CSRsensorType_Hot_Water_Temperature = 28,
    /** Desired Oven Temperature */
    CSRsensorType_Desired_Oven_Temperature = 18,
    /** Cooker Hob Front Left State */
    CSRsensorType_Cooker_Hob_Front_Left_State = 33,
    /** Desired Wakeup Alarm Time */
    CSRsensorType_Desired_Wakeup_Alarm_Time = 43,
    /** Passive Infrared State */
    CSRsensorType_Passive_Infrared_State = 45,
    /** Smoke */
    CSRsensorType_Smoke = 26,
    /** Desired Cooker Hob Front Middle State */
    CSRsensorType_Desired_Cooker_Hob_Front_Middle_State = 38,
    /** Generic 2 Byte Typed */
    CSRsensorType_Generic_2_Byte_Typed = 251,
    /** Cold Water Temperature */
    CSRsensorType_Cold_Water_Temperature = 29,
    /** Desired Cooker Hob Back Left State */
    CSRsensorType_Desired_Cooker_Hob_Back_Left_State = 32,
    /** External Window */
    CSRsensorType_External_Window = 10,
    /** Seat Occupied */
    CSRsensorType_Seat_Occupied = 19,
    /** Desired Cooker Hob Back Right State */
    CSRsensorType_Desired_Cooker_Hob_Back_Right_State = 40,
    /** Solar_Energy */
    CSRsensorType_Solar_Energy = 11,
    /** Wind Direction Gust */
    CSRsensorType_Wind_Direction_Gust = 55,
    /** Fridge Temperature */
    CSRsensorType_Fridge_Temperature = 13,
    /** Unknown */
    CSRsensorType_Unknown = 0,
    /** Dish Washer State */
    CSRsensorType_Dish_Washer_State = 21,
    /** Rain Fall Today */
    CSRsensorType_Rain_Fall_Today = 57,
    /** LastSensorType */
    CSRLastSensorType = 253
};

/**
 * @enum  CSRcookerHobState
 *        uint16_t values for the Cooker hob state
 */
typedef NS_ENUM (uint16_t, CSRcookerHobState) {
    /** CookerHob State Level 5 */
    CSRcookerHobState_Level_5 = 5,
    /** CookerHob State Level 4 */
    CSRcookerHobState_Level_4 = 4,
    /** CookerHob State Level 3 */
    CSRcookerHobState_Level_3 = 3,
    /** CookerHob State Level 2 */
    CSRcookerHobState_Level_2 = 2,
    /** CookerHob State Off Cold */
    CSRcookerHobState_Off_Cold = 0,
    /** CookerHob State Level 1 */
    CSRcookerHobState_Level_1 = 1,
    /** CookerHob State Off Hot */
    CSRcookerHobState_Off_Hot = 10,
    /** CookerHob State Level 9 */
    CSRcookerHobState_Level_9 = 9,
    /** CookerHob State Level 8 */
    CSRcookerHobState_Level_8 = 8,
    /** CookerHob State Level 7 */
    CSRcookerHobState_Level_7 = 7,
    /** CookerHob State Level 6 */
    CSRcookerHobState_Level_6 = 6
};

/**
 * @enum  CSRwindowState
 *        uint16_t values for the Window state
 */

typedef NS_ENUM (uint16_t, CSRwindowState) {
    /** Window State Closed Insecure */
    CSRwindowState_Closed_Insecure = 1,
    /** Window State Closed Secure */
    CSRwindowState_Closed_Secure = 0,
    /** Window State Open Secure */
    CSRwindowState_Open_Secure = 2,
    /** Window State Open Insecure */
    CSRwindowState_Open_Insecure = 3
};

/**
 * @enum  CSRdoorState
 *        uint16_t values for the Door state
 */

typedef NS_ENUM (uint16_t, CSRdoorState) {
    /** Door State Closed Locked */
    CSRdoorState_Closed_Locked = 0,
    /** Door State Closed Unlocked */
    CSRdoorState_Closed_Unlocked = 1,
    /** Door State Open Unlocked */
    CSRdoorState_Open_Unlocked = 2
};


/**
 * @enum  CSRapplianceState
 *        uint16_t values for the Appliance state
 */

typedef NS_ENUM (uint16_t, CSRapplianceState) {
    /** Appliance State Washing */
    CSRapplianceState_Washing = 4,
    /** Appliance State Post Wash*/
    CSRapplianceState_Post_Wash = 5,
    /** Appliance State Cooling Down*/
    CSRapplianceState_Cooling_Down = 2,
    /** Appliance State Heating Up*/
    CSRapplianceState_Heating_Up = 1,
    /** Appliance State Idle*/
    CSRapplianceState_Idle = 0,
    /** Appliance State Pre Wash*/
    CSRapplianceState_Pre_Wash = 3
};

/**
 * @enum  CSRseatState
 *        uint16_t values for the Seat state
 */

typedef NS_ENUM (uint16_t, CSRseatState) {
    /** Seat State Empty */
    CSRseatState_Empty = 0,
    /** Seat State Occupied */
    CSRseatState_Occupied = 1,
    /** Seat State Continuously Occupied */
    CSRseatState_Continuously_Occupied = 2
};

/**
 * @enum  CSRdirection
 *        uint16_t values for the Direction
 */

typedef NS_ENUM (uint16_t, CSRdirection) {
    /** Direction North Of North East */
    CSRdirection_North_Of_North_East = 16,
    /** Direction East */
    CSRdirection_East = 64,
    /** Direction South Of South East */
    CSRdirection_South_Of_South_East = 112,
    /** Direction East Of North East */
    CSRdirection_East_Of_North_East = 48,
    /** Direction East Of South East */
    CSRdirection_East_Of_South_East = 80,
    /** Direction South */
    CSRdirection_South = 128,
    /** Direction North East */
    CSRdirection_North_East = 32,
    /** Direction South East */
    CSRdirection_South_East = 96,
    /** Direction North Of North West */
    CSRdirection_North_Of_North_West = 240,
    /** Direction South Of South West */
    CSRdirection_South_Of_South_West = 144,
    /** Direction West Of South West */
    CSRdirection_West_Of_South_West = 176,
    /** Direction West Of North West */
    CSRdirection_West_Of_North_West = 208,
    /** Direction South West */
    CSRdirection_South_West = 160,
    /** Direction West */
    CSRdirection_West = 192,
    /** Direction North West */
    CSRdirection_North_West = 224,
    /** Direction North */
    CSRdirection_North = 0
};

/**
 * @enum  CSRmovementState
 *        uint16_t values for the Movement state
 */

typedef NS_ENUM (uint16_t, CSRmovementState) {
    /** Movement State Movement Detected */
    CSRmovementState_Movement_Detected = 1,
    /** Movement State No Movement */
    CSRmovementState_No_Movement = 0
};

/**
 * @enum  CSRforwardBackward
 *        uint16_t values for the Forward/Backward state
 */

typedef NS_ENUM (uint16_t, CSRforwardBackward) {
    /** ForwardBackward Forward */
    CSRforwardBackward_Forward = 1,
    /** ForwardBackward Backwards */
    CSRforwardBackward_Backwards = 2
};


/**
 * @interface CSRsensorValue
 */
@interface CSRsensorValue:NSObject

/*!
* @brief Create a CSRsensorValue object initialised with desired cooker hob back middle state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredCookerHobBackMiddleState:(CSRcookerHobState)cookerHobState;

/**
* @brief Create a CSRsensorValue object initialised with freezer temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithFreezerTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with desired air temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredAirTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with desired second wakeup alarm time.
* @param minutesOfTheDay Range is 0 to 1439. Number of minutes in to the day - e.g. 900 minutes of the day = 15:00
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredSecondWakeupAlarmTime:(NSNumber* _Nonnull)minutesOfTheDay;

/*!
* @brief Create a CSRsensorValue object initialised with wind speed.
* @param centimetresPerSecond Measurement of speed - typically used for wind speeds - actually measured in centimetres per second
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithWindSpeed:(NSNumber* _Nonnull)centimetresPerSecond;

/*!
* @brief Create a CSRsensorValue object initialised with external dewpoint.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithExternalDewpoint:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with desired window cover position.
* @param percentage Range is 0 to 100. Percentage from 0% to 100%
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredWindowCoverPosition:(NSNumber* _Nonnull)percentage;

/*!
* @brief Create a CSRsensorValue object initialised with internal humidity.
* @param percentage Range is 0 to 100. Percentage from 0% to 100%
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithInternalHumidity:(NSNumber* _Nonnull)percentage;

/*!
* @brief Create a CSRsensorValue object initialised with toaster state.
* @param applianceState Enumeration of CSRapplianceState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithToasterState:(CSRapplianceState)applianceState;
;

/*!
* @brief Create a CSRsensorValue object initialised with carbon monoxide.
* @param partsPerMillion Parts per million
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithCarbonMonoxide:(NSNumber* _Nonnull)partsPerMillion;

/*!
* @brief Create a CSRsensorValue object initialised with desired fan speed.
* @param forwardBackward Enumeration of CSRforwardBackward.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredFanSpeed:(CSRforwardBackward)forwardBackward;
;

/*!
* @brief Create a CSRsensorValue object initialised with water flowing.
* @param waterFlowRate Range is 0 to 65534. Measured in millilitres per second
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithWaterFlowing:(NSNumber* _Nonnull)waterFlowRate;

/*!
* @brief Create a CSRsensorValue object initialised with clothes dryer state.
* @param applianceState Enumeration of CSRapplianceState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithClothesDryerState:(CSRapplianceState)applianceState;
;

/*!
* @brief Create a CSRsensorValue object initialised with carbon dioxide.
* @param partsPerMillion Parts per million
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithCarbonDioxide:(NSNumber* _Nonnull)partsPerMillion;

/*!
* @brief Create a CSRsensorValue object initialised with generic 2 byte.
* @param generic_2Byte Generic sensor type of 2 byte
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithGeneric_2Byte:(NSNumber* _Nonnull)generic_2Byte;

/*!
* @brief Create a CSRsensorValue object initialised with generic 1 byte typed.
* @param generic_1ByteTyped Byte 0: Type (OEM defined) Byte 1: Data type
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithGeneric_1ByteTyped:(NSNumber* _Nonnull)generic_1ByteTyped;

/*!
* @brief Create a CSRsensorValue object initialised with soil moisure.
* @param percentage Range is 0 to 100. Percentage from 0% to 100%
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithSoilMoisure:(NSNumber* _Nonnull)percentage;

/*!
* @brief Create a CSRsensorValue object initialised with generic 3 byte typed.
* @param generic_3ByteTyped Byte 0: Type (OEM defined) Byte 1: Data type. Byte 2: Data Type. Byte 3: Data Type
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithGeneric_3ByteTyped:(NSNumber* _Nonnull)generic_3ByteTyped;

/*!
* @brief Create a CSRsensorValue object initialised with water level.
* @param percentage Range is 0 to 100. Percentage from 0% to 100%
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithWaterLevel:(NSNumber* _Nonnull)percentage;

/*!
* @brief Create a CSRsensorValue object initialised with barometric pressure.
* @param airPressure Air Pressure in hectopascals
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithBarometricPressure:(NSNumber* _Nonnull)airPressure;

/*!
* @brief Create a CSRsensorValue object initialised with oven temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithOvenTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with external door.
* @param doorState Enumeration of CSRdoorState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithExternalDoor:(CSRdoorState)doorState;
;

/*!
* @brief Create a CSRsensorValue object initialised with washing machine state.
* @param applianceState Enumeration of CSRapplianceState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithWashingMachineState:(CSRapplianceState)applianceState;
;

/*!
* @brief Create a CSRsensorValue object initialised with rain fall last hour.
* @param millimetres Measurement of distance - typically used for rainfall - see http://en.wikipedia.org/wiki/List_of_weather_records#Rain
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithRainFallLastHour:(NSNumber* _Nonnull)millimetres;

/*!
* @brief Create a CSRsensorValue object initialised with cooker hob front middle state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithCookerHobFrontMiddleState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with internal door.
* @param doorState Enumeration of CSRdoorState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithInternalDoor:(CSRdoorState)doorState;
;

/*!
* @brief Create a CSRsensorValue object initialised with audio level.
* @param decibel typically used for audio volume levels
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithAudioLevel:(NSNumber* _Nonnull)decibel;

/*!
* @brief Create a CSRsensorValue object initialised with desired cooker hob front left state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredCookerHobFrontLeftState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with generic 1 byte.
* @param generic_1Byte Generic sensor type of 1 byte
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithGeneric_1Byte:(NSNumber* _Nonnull)generic_1Byte;

/*!
* @brief Create a CSRsensorValue object initialised with desired freezer temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredFreezerTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with soil temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithSoilTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with desired cooker hob front right state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredCookerHobFrontRightState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with desired audio level.
* @param decibel typically used for audio volume levels
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredAudioLevel:(NSNumber* _Nonnull)decibel;

/*!
* @brief Create a CSRsensorValue object initialised with window cover position.
* @param percentage Range is 0 to 100. Percentage from 0% to 100%
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithWindowCoverPosition:(NSNumber* _Nonnull)percentage;

/*!
* @brief Create a CSRsensorValue object initialised with desired water flow.
* @param waterFlowRate Range is 0 to 65534. Measured in millilitres per second
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredWaterFlow:(NSNumber* _Nonnull)waterFlowRate;

/*!
* @brief Create a CSRsensorValue object initialised with wind direction.
* @param direction Enumeration of CSRdirection.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithWindDirection:(CSRdirection)direction;
;

/*!
* @brief Create a CSRsensorValue object initialised with cooker hob back middle state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithCookerHobBackMiddleState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with internal window.
* @param windowState Enumeration of CSRwindowState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithInternalWindow:(CSRwindowState)windowState;
;

/*!
* @brief Create a CSRsensorValue object initialised with cooker hob back left state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithCookerHobBackLeftState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with external humidity.
* @param percentage Range is 0 to 100. Percentage from 0% to 100%
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithExternalHumidity:(NSNumber* _Nonnull)percentage;

/*!
* @brief Create a CSRsensorValue object initialised with desired water temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredWaterTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with external air temperature.
* @param lowerTemperatureKelvin Lower Temperature Kelvin
* @param upperTemperatureKelvin Upper Temperature Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithExternalAirTemperature:(NSNumber* _Nonnull)lowerTemperatureKelvin upperTemperatureKelvin:(NSNumber* _Nonnull)upperTemperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with desired fridge temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredFridgeTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with number of activations.
* @param _16BitCounter Range is 0 to 65534. used to count things
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithNumberOfActivations:(NSNumber* _Nonnull)_16BitCounter;

/*!
* @brief Create a CSRsensorValue object initialised with cooker hob back right state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithCookerHobBackRightState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with cooker hob front right state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithCookerHobFrontRightState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with internal air temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithInternalAirTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with fan speed.
* @param percentage Range is 0 to 100. Percentage from 0% to 100%
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithFanSpeed:(NSNumber* _Nonnull)percentage;

/*!
* @brief Create a CSRsensorValue object initialised with wind speed gust.
* @param centimetresPerSecond Measurement of speed - typically used for wind speeds - actually measured in centimetres per second
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithWindSpeedGust:(NSNumber* _Nonnull)centimetresPerSecond;

/*!
* @brief Create a CSRsensorValue object initialised with hot water temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithHotWaterTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with desired oven temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredOvenTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with cooker hob front left state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithCookerHobFrontLeftState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with desired wakeup alarm time.
* @param minutesOfTheDay Range is 0 to 1439. Number of minutes in to the day - e.g. 900 minutes of the day = 15:00
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredWakeupAlarmTime:(NSNumber* _Nonnull)minutesOfTheDay;

/*!
* @brief Create a CSRsensorValue object initialised with passive infrared state.
* @param movementState Enumeration of CSRmovementState. PIR Sensor of similar states
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithPassiveInfraredState:(CSRmovementState)movementState;
;

/*!
* @brief Create a CSRsensorValue object initialised with smoke.
* @param microgramsPerCubicMetre Concentration of typically pollution in micrograms per cubic metre
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithSmoke:(NSNumber* _Nonnull)microgramsPerCubicMetre;

/*!
* @brief Create a CSRsensorValue object initialised with desired cooker hob front middle state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredCookerHobFrontMiddleState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with generic 2 byte typed.
* @param generic_2ByteTyped Byte 0: Type (OEM defined) Byte 1: Data type. Byte 2: Data Type
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithGeneric_2ByteTyped:(NSNumber* _Nonnull)generic_2ByteTyped;

/*!
* @brief Create a CSRsensorValue object initialised with cold water temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithColdWaterTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with desired cooker hob back left state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredCookerHobBackLeftState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with external window.
* @param windowState Enumeration of CSRwindowState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithExternalWindow:(CSRwindowState)windowState;
;

/*!
* @brief Create a CSRsensorValue object initialised with seat occupied.
* @param seatState Enumeration of CSRseatState. Did something sit on this seat - or has something been on this seat for more than 24 hours and therefore is continuously occupied
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithSeatOccupied:(CSRseatState)seatState;
;

/*!
* @brief Create a CSRsensorValue object initialised with desired cooker hob back right state.
* @param cookerHobState Enumeration of CSRcookerHobState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDesiredCookerHobBackRightState:(CSRcookerHobState)cookerHobState;
;

/*!
* @brief Create a CSRsensorValue object initialised with solar energy.
* @param wattsPerSquareMetre Typically used to measure solar energy landing in a location
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithSolarEnergy:(NSNumber* _Nonnull)wattsPerSquareMetre;

/*!
* @brief Create a CSRsensorValue object initialised with wind direction gust.
* @param direction Enumeration of CSRdirection.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithWindDirectionGust:(CSRdirection)direction;
;

/*!
* @brief Create a CSRsensorValue object initialised with fridge temperature.
* @param temperatureKelvin 1/32th of a Kelvin
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithFridgeTemperature:(NSNumber* _Nonnull)temperatureKelvin;

/*!
* @brief Create a CSRsensorValue object initialised with dish washer state.
* @param applianceState Enumeration of CSRapplianceState.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithDishWasherState:(CSRapplianceState)applianceState;
;

/*!
* @brief Create a CSRsensorValue object initialised with rain fall today.
* @param millimetres Measurement of distance - typically used for rainfall - see http://en.wikipedia.org/wiki/List_of_weather_records#Rain
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithRainFallToday:(NSNumber* _Nonnull)millimetres;

// Additional methods
/*!
* @brief Initialise the object with the value received in a CSRmesh packet.
* @param sensorType The sensor type, which should be in the range of the CSRsensorType enum.
* @param value The sensor value bytes as received. May contain multiple values for compound types.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithEncodedValue:(CSRsensorType)sensorType encodedValue:(NSData *_Nonnull)value;

/*!
* @brief Initialise the object with the given Value and Type.
* @param sensorType The sensor type, which should be in the range of the CSRsensorType enum.
* @param value The sensor value encoded into NSNumber. The number of Bytes for this Type will be encoded.
* @return CSRSensorValue instance.
*/
+ (id _Nullable)initWithTypeAndValue:(CSRsensorType)sensorType value:(NSNumber *_Nonnull)value;

/*!
* @brief Get the size in bytes of the encoded value for a particular sensor type.
* @param sensorType The sensor type, which should be in the range of the CSRsensorType enum.
* @return Size of the encoded value in bytes or nil if the type is out of range.
*/
+ (NSNumber * _Nullable) getValueSizeByType:(CSRsensorType)sensorType;

/*!
* @brief Get the value. The interpretation of the value depends on it's type.
*
* @return Sensor value.
*/
- (NSDictionary * _Nullable)getValue;

/*!
* @brief Get the payload. The payload is the type:value portion of the Sensor setValue message
*
* @return MCP payload.
*/
-(NSData * _Nullable) getPayload;

/*!
* @brief return the Type
*
* @return CSRsensortype.
*/
-(CSRsensorType) getType;

/*!
* @brief decode payload and return up to 2 CSRsensorValue objects
* @param payload : the type and value MCP payload
* @param sensor1Ptr : pointer to a CSRsensorValue object, first decoded sensor will be assigned to this
* @param sensor2Ptr : pointer to a CSRsensorValue object, second decoded sensor will be assigned to this
*/

+ (void)initWithPayload:(NSData * _Nonnull)payload sensor1Ptr:(CSRsensorValue *_Nonnull *_Nullable)sensor1Ptr sensor2Ptr:(CSRsensorValue *_Nonnull * _Nullable)sensor2Ptr;

@end
