typedef NS_ENUM(uint8_t, QTIRemoteCode) {
    QTIRemoteCode_Number0		= 0,
    QTIRemoteCode_Number1		= 1,
    QTIRemoteCode_Number2		= 2,
    QTIRemoteCode_Number3		= 3,
    QTIRemoteCode_Number4		= 4,
    QTIRemoteCode_Number5		= 5,
    QTIRemoteCode_Number6		= 6,
    QTIRemoteCode_Number7		= 7,
    QTIRemoteCode_Number8		= 8,
    QTIRemoteCode_Number9		= 9,
    QTIRemoteCode_DirectionN		= 16,
    QTIRemoteCode_DirectionE		= 17,
    QTIRemoteCode_DirectionS		= 18,
    QTIRemoteCode_DirectionW		= 19,
    QTIRemoteCode_DirectionNe		= 20,
    QTIRemoteCode_DirectionSe		= 21,
    QTIRemoteCode_DirectionSw		= 22,
    QTIRemoteCode_DirectionNw		= 23,
    QTIRemoteCode_DirectionNne		= 24,
    QTIRemoteCode_DirectionEne		= 25,
    QTIRemoteCode_DirectionEse		= 26,
    QTIRemoteCode_DirectionSse		= 27,
    QTIRemoteCode_DirectionSsw		= 28,
    QTIRemoteCode_DirectionWsw		= 29,
    QTIRemoteCode_DirectionWnw		= 30,
    QTIRemoteCode_DirectionNnw		= 31,
    QTIRemoteCode_Select		= 32,
    QTIRemoteCode_ChannelUp		= 33,
    QTIRemoteCode_ChannelDown		= 34,
    QTIRemoteCode_VolumeUp		= 35,
    QTIRemoteCode_VolumeDown		= 36,
    QTIRemoteCode_VolumeMute		= 37,
    QTIRemoteCode_Menu		= 38,
    QTIRemoteCode_Back		= 39,
    QTIRemoteCode_Guide		= 40,
    QTIRemoteCode_Play		= 41,
    QTIRemoteCode_Pause		= 42,
    QTIRemoteCode_Stop		= 43,
    QTIRemoteCode_FastForward		= 44,
    QTIRemoteCode_FastRewind		= 45,
    QTIRemoteCode_SkipForward		= 46,
    QTIRemoteCode_SkipBackward		= 47
};

typedef NS_ENUM(uint8_t, QTIBeaconType) {
    QTIBeaconType_Csr		= 0,
    QTIBeaconType_Ibeacon		= 1,
    QTIBeaconType_EddystoneUrl		= 2,
    QTIBeaconType_EddystoneUid		= 3,
    QTIBeaconType_LteDirect		= 4,
    QTIBeaconType_Lumicast		= 5
};

typedef NS_ENUM(uint8_t, QTIMinuteOfHour) {
    QTIMinuteOfHour_Unknown		= 0
};

typedef NS_ENUM(uint8_t, QTISecondOfMinute) {
    QTISecondOfMinute_Unknown		= 0
};

typedef NS_ENUM(uint8_t, QTIDeviceInformation) {
    QTIDeviceInformation_UuidLow		= 0,
    QTIDeviceInformation_UuidHigh		= 1,
    QTIDeviceInformation_ModelLow		= 2,
    QTIDeviceInformation_ModelHigh		= 3,
    QTIDeviceInformation_VidPidVersion		= 4,
    QTIDeviceInformation_Appearance		= 5,
    QTIDeviceInformation_Lastetag		= 6
};

typedef NS_ENUM(int16_t, QTIMinuteOfWeek) {
    QTIMinuteOfWeek_Unknown		= 0
};

typedef NS_ENUM(int16_t, QTIKeyProperties) {
    QTIKeyProperties_Administrator		= 0,
    QTIKeyProperties_User		= 1,
    QTIKeyProperties_Guest		= 2,
    QTIKeyProperties_Relayonly		= 3
};

typedef NS_ENUM(uint8_t, QTIBoolean) {
    QTIBoolean_False		= 0,
    QTIBoolean_True		= 1
};

typedef NS_ENUM(uint8_t, QTIPowerState) {
    QTIPowerState_Off		= 0,
    QTIPowerState_On		= 1,
    QTIPowerState_Standby		= 2,
    QTIPowerState_Onfromstandby		= 3
};

typedef NS_ENUM(uint8_t, QTIMonthOfYear) {
    QTIMonthOfYear_Unknown		= 0,
    QTIMonthOfYear_January		= 1,
    QTIMonthOfYear_February		= 2,
    QTIMonthOfYear_March		= 3,
    QTIMonthOfYear_April		= 4,
    QTIMonthOfYear_May		= 5,
    QTIMonthOfYear_June		= 6,
    QTIMonthOfYear_July		= 7,
    QTIMonthOfYear_August		= 8,
    QTIMonthOfYear_September		= 9,
    QTIMonthOfYear_October		= 10,
    QTIMonthOfYear_November		= 11,
    QTIMonthOfYear_December		= 12
};

typedef NS_ENUM(uint8_t, QTIHourOfDay) {
    QTIHourOfDay_Unknown		= 0
};

typedef NS_ENUM(uint8_t, QTIDayOfMonth) {
    QTIDayOfMonth_Unknown		= 0
};

typedef NS_ENUM(uint8_t, QTITimerMode) {
    QTITimerMode_Programming		= 0,
    QTITimerMode_Active		= 1,
    QTITimerMode_PartlyRandom		= 2,
    QTITimerMode_CompletelyRandom		= 3
};

typedef NS_ENUM(int16_t, QTISensorType) {
    QTISensorType_Unknown		= 0,
    QTISensorType_InternalAirTemperature		= 1,
    QTISensorType_ExternalAirTemperature		= 2,
    QTISensorType_DesiredAirTemperature		= 3,
    QTISensorType_InternalHumidity		= 4,
    QTISensorType_ExternalHumidity		= 5,
    QTISensorType_ExternalDewpoint		= 6,
    QTISensorType_InternalDoor		= 7,
    QTISensorType_ExternalDoor		= 8,
    QTISensorType_InternalWindow		= 9,
    QTISensorType_ExternalWindow		= 10,
    QTISensorType_SolarEnergy		= 11,
    QTISensorType_NumberOfActivations		= 12,
    QTISensorType_FridgeTemperature		= 13,
    QTISensorType_DesiredFridgeTemperature		= 14,
    QTISensorType_FreezerTemperature		= 15,
    QTISensorType_DesiredFreezerTemperature		= 16,
    QTISensorType_OvenTemperature		= 17,
    QTISensorType_DesiredOvenTemperature		= 18,
    QTISensorType_SeatOccupied		= 19,
    QTISensorType_WashingMachineState		= 20,
    QTISensorType_DishWasherState		= 21,
    QTISensorType_ClothesDryerState		= 22,
    QTISensorType_ToasterState		= 23,
    QTISensorType_CarbonDioxide		= 24,
    QTISensorType_CarbonMonoxide		= 25,
    QTISensorType_Smoke		= 26,
    QTISensorType_WaterLevel		= 27,
    QTISensorType_HotWaterTemperature		= 28,
    QTISensorType_ColdWaterTemperature		= 29,
    QTISensorType_DesiredWaterTemperature		= 30,
    QTISensorType_CookerHobBackLeftState		= 31,
    QTISensorType_DesiredCookerHobBackLeftState		= 32,
    QTISensorType_CookerHobFrontLeftState		= 33,
    QTISensorType_DesiredCookerHobFrontLeftState		= 34,
    QTISensorType_CookerHobBackMiddleState		= 35,
    QTISensorType_DesiredCookerHobBackMiddleState		= 36,
    QTISensorType_CookerHobFrontMiddleState		= 37,
    QTISensorType_DesiredCookerHobFrontMiddleState		= 38,
    QTISensorType_CookerHobBackRightState		= 39,
    QTISensorType_DesiredCookerHobBackRightState		= 40,
    QTISensorType_CookerHobFrontRightState		= 41,
    QTISensorType_DesiredCookerHobFrontRightState		= 42,
    QTISensorType_DesiredWakeupAlarmTime		= 43,
    QTISensorType_DesiredSecondWakeupAlarmTime		= 44,
    QTISensorType_PassiveInfraredState		= 45,
    QTISensorType_WaterFlowing		= 46,
    QTISensorType_DesiredWaterFlow		= 47,
    QTISensorType_AudioLevel		= 48,
    QTISensorType_DesiredAudioLevel		= 49,
    QTISensorType_FanSpeed		= 50,
    QTISensorType_DesiredFanSpeed		= 51,
    QTISensorType_WindSpeed		= 52,
    QTISensorType_WindSpeedGust		= 53,
    QTISensorType_WindDirection		= 54,
    QTISensorType_WindDirectionGust		= 55,
    QTISensorType_RainFallLastHour		= 56,
    QTISensorType_RainFallToday		= 57,
    QTISensorType_BarometricPressure		= 58,
    QTISensorType_SoilTemperature		= 59,
    QTISensorType_SoilMoisure		= 60,
    QTISensorType_WindowCoverPosition		= 61,
    QTISensorType_DesiredWindowCoverPosition		= 62,
    QTISensorType_Generic1Byte		= 63,
    QTISensorType_Generic2Byte		= 64,
    QTISensorType_Generic1ByteTyped		= 250,
    QTISensorType_Generic2ByteTyped		= 251,
    QTISensorType_Generic3ByteTyped		= 252
};