//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#pragma mark - define Color Palette

#define kColorBlueCSR @"#3A75C4"
#define kColorDarkBlueCSR @"#2B5791"
#define kColorLightBlueCSR @"#538BCA"
#define kColorOrangeCSR @"#FFE55D"
#define kColorLightGreen500 @"#8BC34A"
#define kColorLightGreen700 @"#689F38"
#define kColorAmber600 @"#FFB300"
#define kColorAmber800 @"#FF8F00"
#define kColorRed600 @"#E53935"
#define kColorRed800 @"#C62828"
#define kColorRed900 @"#B71C1C"
#define kColorCyan500 @"#00BCD4"
#define kColorCyan700 @"#0097A7"
#define kColorDeepPurple400 @"#7E57C2"
#define kColorDeepPurple600 @"#5E35B1"
#define kColorDeepOrange50 @"#FBE9E7"
#define kColorTeal100 @"#B2DFDB"
#define kColorTeal500 @"#009688"

#define kColorNames @[@{@"colorName" : @"Black", @"hexValue" : @"000000"}, @{@"colorName" : @"Navy", @"hexValue" : @"000080"}, @{@"colorName" : @"DarkBlue", @"hexValue" : @"00008B"}, @{@"colorName" : @"MediumBlue", @"hexValue" : @"0000CD"}, @{@"colorName" : @"Blue", @"hexValue" : @"0000FF"}, @{@"colorName" : @"DarkGreen", @"hexValue" : @"006400"}, @{@"colorName" : @"Green", @"hexValue" : @"008000"}, @{@"colorName" : @"Teal", @"hexValue" : @"008080"}, @{@"colorName" : @"DarkCyan", @"hexValue" : @"008B8B"}, @{@"colorName" : @"DeepSkyBlue", @"hexValue" : @"00BFFF"}, @{@"colorName" : @"DarkTurquoise", @"hexValue" : @"00CED1"}, @{@"colorName" : @"MediumSpringGreen", @"hexValue" : @"00FA9A"}, @{@"colorName" : @"Lime", @"hexValue" : @"00FF00"}, @{@"colorName" : @"SpringGreen", @"hexValue" : @"00FF7F"}, @{@"colorName" : @"Aqua", @"hexValue" : @"00FFFF"}, @{@"colorName" : @"Cyan", @"hexValue" : @"00FFFF"}, @{@"colorName" : @"MidnightBlue", @"hexValue" : @"191970"}, @{@"colorName" : @"DodgerBlue", @"hexValue" : @"1E90FF"}, @{@"colorName" : @"LightSeaGreen", @"hexValue" : @"20B2AA"}, @{@"colorName" : @"ForestGreen", @"hexValue" : @"228B22"}, @{@"colorName" : @"SeaGreen", @"hexValue" : @"2E8B57"}, @{@"colorName" : @"DarkSlateGray", @"hexValue" : @"2F4F4F"}, @{@"colorName" : @"LimeGreen", @"hexValue" : @"32CD32"}, @{@"colorName" : @"MediumSeaGreen", @"hexValue" : @"3CB371"}, @{@"colorName" : @"Turquoise", @"hexValue" : @"40E0D0"}, @{@"colorName" : @"RoyalBlue", @"hexValue" : @"4169E1"}, @{@"colorName" : @"SteelBlue", @"hexValue" : @"4682B4"}, @{@"colorName" : @"DarkSlateBlue", @"hexValue" : @"483D8B"}, @{@"colorName" : @"MediumTurquoise", @"hexValue" : @"48D1CC"}, @{@"colorName" : @"Indigo ", @"hexValue" : @"4B0082"}, @{@"colorName" : @"DarkOliveGreen", @"hexValue" : @"556B2F"}, @{@"colorName" : @"CadetBlue", @"hexValue" : @"5F9EA0"}, @{@"colorName" : @"CornflowerBlue", @"hexValue" : @"6495ED"}, @{@"colorName" : @"RebeccaPurple", @"hexValue" : @"663399"}, @{@"colorName" : @"MediumAquaMarine", @"hexValue" : @"66CDAA"}, @{@"colorName" : @"DimGray", @"hexValue" : @"696969"}, @{@"colorName" : @"SlateBlue", @"hexValue" : @"6A5ACD"}, @{@"colorName" : @"OliveDrab", @"hexValue" : @"6B8E23"}, @{@"colorName" : @"SlateGray", @"hexValue" : @"708090"}, @{@"colorName" : @"LightSlateGray", @"hexValue" : @"778899"}, @{@"colorName" : @"MediumSlateBlue", @"hexValue" : @"7B68EE"}, @{@"colorName" : @"LawnGreen", @"hexValue" : @"7CFC00"}, @{@"colorName" : @"Chartreuse", @"hexValue" : @"7FFF00"}, @{@"colorName" : @"Aquamarine", @"hexValue" : @"7FFFD4"}, @{@"colorName" : @"Maroon", @"hexValue" : @"800000"}, @{@"colorName" : @"Purple", @"hexValue" : @"800080"}, @{@"colorName" : @"Olive", @"hexValue" : @"808000"}, @{@"colorName" : @"Gray", @"hexValue" : @"808080"}, @{@"colorName" : @"SkyBlue", @"hexValue" : @"87CEEB"}, @{@"colorName" : @"LightSkyBlue", @"hexValue" : @"87CEFA"}, @{@"colorName" : @"BlueViolet", @"hexValue" : @"8A2BE2"}, @{@"colorName" : @"DarkRed", @"hexValue" : @"8B0000"}, @{@"colorName" : @"DarkMagenta", @"hexValue" : @"8B008B"}, @{@"colorName" : @"SaddleBrown", @"hexValue" : @"8B4513"}, @{@"colorName" : @"DarkSeaGreen", @"hexValue" : @"8FBC8F"}, @{@"colorName" : @"LightGreen", @"hexValue" : @"90EE90"}, @{@"colorName" : @"MediumPurple", @"hexValue" : @"9370DB"}, @{@"colorName" : @"DarkViolet", @"hexValue" : @"9400D3"}, @{@"colorName" : @"PaleGreen", @"hexValue" : @"98FB98"}, @{@"colorName" : @"DarkOrchid", @"hexValue" : @"9932CC"}, @{@"colorName" : @"YellowGreen", @"hexValue" : @"9ACD32"}, @{@"colorName" : @"Sienna", @"hexValue" : @"A0522D"}, @{@"colorName" : @"Brown", @"hexValue" : @"A52A2A"}, @{@"colorName" : @"DarkGray", @"hexValue" : @"A9A9A9"}, @{@"colorName" : @"LightBlue", @"hexValue" : @"ADD8E6"}, @{@"colorName" : @"GreenYellow", @"hexValue" : @"ADFF2F"}, @{@"colorName" : @"PaleTurquoise", @"hexValue" : @"AFEEEE"}, @{@"colorName" : @"LightSteelBlue", @"hexValue" : @"B0C4DE"}, @{@"colorName" : @"PowderBlue", @"hexValue" : @"B0E0E6"}, @{@"colorName" : @"FireBrick", @"hexValue" : @"B22222"}, @{@"colorName" : @"DarkGoldenRod", @"hexValue" : @"B8860B"}, @{@"colorName" : @"MediumOrchid", @"hexValue" : @"BA55D3"}, @{@"colorName" : @"RosyBrown", @"hexValue" : @"BC8F8F"}, @{@"colorName" : @"DarkKhaki", @"hexValue" : @"BDB76B"}, @{@"colorName" : @"Silver", @"hexValue" : @"C0C0C0"}, @{@"colorName" : @"MediumVioletRed", @"hexValue" : @"C71585"}, @{@"colorName" : @"IndianRed ", @"hexValue" : @"CD5C5C"}, @{@"colorName" : @"Peru", @"hexValue" : @"CD853F"}, @{@"colorName" : @"Chocolate", @"hexValue" : @"D2691E"}, @{@"colorName" : @"Tan", @"hexValue" : @"D2B48C"}, @{@"colorName" : @"LightGray", @"hexValue" : @"D3D3D3"}, @{@"colorName" : @"Thistle", @"hexValue" : @"D8BFD8"}, @{@"colorName" : @"Orchid", @"hexValue" : @"DA70D6"}, @{@"colorName" : @"GoldenRod", @"hexValue" : @"DAA520"}, @{@"colorName" : @"PaleVioletRed", @"hexValue" : @"DB7093"}, @{@"colorName" : @"Crimson", @"hexValue" : @"DC143C"}, @{@"colorName" : @"Gainsboro", @"hexValue" : @"DCDCDC"}, @{@"colorName" : @"Plum", @"hexValue" : @"DDA0DD"}, @{@"colorName" : @"BurlyWood", @"hexValue" : @"DEB887"}, @{@"colorName" : @"LightCyan", @"hexValue" : @"E0FFFF"}, @{@"colorName" : @"Lavender", @"hexValue" : @"E6E6FA"}, @{@"colorName" : @"DarkSalmon", @"hexValue" : @"E9967A"}, @{@"colorName" : @"Violet", @"hexValue" : @"EE82EE"}, @{@"colorName" : @"PaleGoldenRod", @"hexValue" : @"EEE8AA"}, @{@"colorName" : @"LightCoral", @"hexValue" : @"F08080"}, @{@"colorName" : @"Khaki", @"hexValue" : @"F0E68C"}, @{@"colorName" : @"AliceBlue", @"hexValue" : @"F0F8FF"}, @{@"colorName" : @"HoneyDew", @"hexValue" : @"F0FFF0"}, @{@"colorName" : @"Azure", @"hexValue" : @"F0FFFF"}, @{@"colorName" : @"SandyBrown", @"hexValue" : @"F4A460"}, @{@"colorName" : @"Wheat", @"hexValue" : @"F5DEB3"}, @{@"colorName" : @"Beige", @"hexValue" : @"F5F5DC"}, @{@"colorName" : @"WhiteSmoke", @"hexValue" : @"F5F5F5"}, @{@"colorName" : @"MintCream", @"hexValue" : @"F5FFFA"}, @{@"colorName" : @"GhostWhite", @"hexValue" : @"F8F8FF"}, @{@"colorName" : @"Salmon", @"hexValue" : @"FA8072"}, @{@"colorName" : @"AntiqueWhite", @"hexValue" : @"FAEBD7"}, @{@"colorName" : @"Linen", @"hexValue" : @"FAF0E6"}, @{@"colorName" : @"LightGoldenRodYellow", @"hexValue" : @"FAFAD2"}, @{@"colorName" : @"OldLace", @"hexValue" : @"FDF5E6"}, @{@"colorName" : @"Red", @"hexValue" : @"FF0000"}, @{@"colorName" : @"Fuchsia", @"hexValue" : @"FF00FF"}, @{@"colorName" : @"Magenta", @"hexValue" : @"FF00FF"}, @{@"colorName" : @"DeepPink", @"hexValue" : @"FF1493"}, @{@"colorName" : @"OrangeRed", @"hexValue" : @"FF4500"}, @{@"colorName" : @"Tomato", @"hexValue" : @"FF6347"}, @{@"colorName" : @"HotPink", @"hexValue" : @"FF69B4"}, @{@"colorName" : @"Coral", @"hexValue" : @"FF7F50"}, @{@"colorName" : @"DarkOrange", @"hexValue" : @"FF8C00"}, @{@"colorName" : @"LightSalmon", @"hexValue" : @"FFA07A"}, @{@"colorName" : @"Orange", @"hexValue" : @"FFA500"}, @{@"colorName" : @"LightPink", @"hexValue" : @"FFB6C1"}, @{@"colorName" : @"Pink", @"hexValue" : @"FFC0CB"}, @{@"colorName" : @"Gold", @"hexValue" : @"FFD700"}, @{@"colorName" : @"PeachPuff", @"hexValue" : @"FFDAB9"}, @{@"colorName" : @"NavajoWhite", @"hexValue" : @"FFDEAD"}, @{@"colorName" : @"Moccasin", @"hexValue" : @"FFE4B5"}, @{@"colorName" : @"Bisque", @"hexValue" : @"FFE4C4"}, @{@"colorName" : @"MistyRose", @"hexValue" : @"FFE4E1"}, @{@"colorName" : @"BlanchedAlmond", @"hexValue" : @"FFEBCD"}, @{@"colorName" : @"PapayaWhip", @"hexValue" : @"FFEFD5"}, @{@"colorName" : @"LavenderBlush", @"hexValue" : @"FFF0F5"}, @{@"colorName" : @"SeaShell", @"hexValue" : @"FFF5EE"}, @{@"colorName" : @"Cornsilk", @"hexValue" : @"FFF8DC"}, @{@"colorName" : @"LemonChiffon", @"hexValue" : @"FFFACD"}, @{@"colorName" : @"FloralWhite", @"hexValue" : @"FFFAF0"}, @{@"colorName" : @"Snow", @"hexValue" : @"FFFAFA"}, @{@"colorName" : @"Yellow", @"hexValue" : @"FFFF00"}, @{@"colorName" : @"LightYellow", @"hexValue" : @"FFFFE0"}, @{@"colorName" : @"Ivory", @"hexValue" : @"FFFFF0"}, @{@"colorName" : @"White", @"hexValue" : @"FFFFFF"}]

#define kPlaceColors @[@"#f44336", @"#e91e63", @"#9c27b0", @"#3f51b5", @"#2196f3", @"#00bcd4", @"#009688", @"#4caf50", @"#8bc34a", @"#cddc39", @"#ffba00", @"#ff9800", @"#795548", @"#9e9e9e", @"#607d8b"]

#define kPlaceIcons @[@{@"id":@(0), @"iconImage":@"imageOfIconNewCar"}, @{@"id":@(1), @"iconImage":@"imageOfIconNewBuilding"}, @{@"id":@(2), @"iconImage":@"imageOfIconNewCoffee"}, @{@"id":@(3), @"iconImage":@"imageOfIconNewWorld"}, @{@"id":@(4), @"iconImage":@"imageOfIconNewFactory"}, @{@"id":@(5), @"iconImage":@"imageOfIconNewFoot"}, @{@"id":@(6), @"iconImage":@"imageOfIconNewGame"}, @{@"id":@(7), @"iconImage":@"imageOfIconNewHealth"}, @{@"id":@(8), @"iconImage":@"imageOfIconNewHome"}, @{@"id":@(9), @"iconImage":@"imageOfIconNewMovie"}, @{@"id":@(10), @"iconImage":@"imageOfIconNewSchool"}, @{@"id":@(11), @"iconImage":@"imageOfIconNewStadium"}, @{@"id":@(12), @"iconImage":@"imageOfIconNewSuitcase"}, @{@"id":@(13), @"iconImage":@"imageOfIconNewView"}, @{@"id":@(14), @"iconImage":@"imageOfIconNewIndustry"}];


#pragma mark - Notifications

#pragma UI/menu
#define kCSRMenuShowedNotification @"CSRMenuShowedNotification"
#define kCSRMenuHiddenNotification @"CSRMenuHiddenNotification"

#pragma BLE
#define kCSRSetScannerEnabled @"CSRSetScannerEnabled"

#pragma mark - Mesh Model

#define CONFIG      @"CONFIG"
#define LIGHT       @"LIGHT"
#define POWER       @"POWER"
#define GROUP       @"GROUP"
#define SWITCH      @"SWITCH"
#define ATTENTION   @"ATTENTION"
#define FIRMWARE    @"FIRMWARE"
#define DATA        @"DATA"
#define BEARER      @"BEARER"
#define PING        @"PING"
#define BATTERY     @"BATTERY"
#define SENSOR      @"SENSOR"
#define ACTUATOR    @"ACTUATOR"

#pragma mark - REST parameters

#define kcNameParam           @"name"
#define kcStateParam          @"state"
#define kcMeshesParam         @"meshes"
#define kcMeshIdParam         @"mesh_id"
#define kcSiteIdParam         @"site_id"

#pragma mark - Database Constants

#define kDEVICE_UUID @"DEVICE_UUID"
#define kDEVICE_HASH @"DEVICE_HASH"
#define kDEVICE_AUTH_CODE @"DEVICE_AUTH_CODE"
#define kDEVICE_NUMBER @"DEVICE_NUMBER"
#define kAREA_NUMBER @"AREA_NUMBER"
#define kAREA_NAME @"AREA_NAME"
#define kDEVICE_NAME @"DEVICE_NAME"
#define kDEVICE_NETWORK_KEY @"DEVICE_NETWORK_KEY"
#define kDEVICE_MODELS_LOW @"CSR_MODEL_LOW"
#define kDEVICE_MODELS_HIGH @"CSR_MODEL_HIGH"
#define kDEVICE_APPEARANCE @"CSR_APPEARANCE"
#define kDEVICE_ISASSOCIATED @"DEVICE_ISASSOCIATED"
#define kDEVICE_DHM @"DEVICE_DHM"

//Models and Groups
#define kDEVICE_MODEL_NUMBER_STRING @"modelNoString"
#define kDEVICE_NUMBER_OF_MODEL_GROUP_ID_STRING @"numberOfModelGroupIdsString"
#define kDEVICE_MESH_REQUEST_ID_STRING @"meshRequestIdString"



#pragma mark - CSR mesh Notification and Parameter Keys
//To be filled in
#define kCSRmeshManagerTransactionNotification @"kCSRmeshManagerTransactionNotification"
#define kDeviceHashString @"deviceHashString"
#define kAppearanceValueString @"appearanceValueString"
#define kShortNameString @"shortNameString"
#define kDeviceUuidString @"deviceUuidString"
#define kDeviceRssiString @"deviceRssiString"
#define kScannerEnabledString @"scannerEnabledString"
#define kDeviceIdString @"kDeviceIdString"
#define kMeshRequestIdString @"kMeshRequestIdString"
#define kTotalStepsString @"kTotalStepsString"
#define kStepsCompletedString @"kStepsCompletedString"
#define kInfoTypeString @"kInfoTypeString"
#define kDeviceDHMString @"kDeviceDHMString"

//Temp Control Constants
#define SENSOR_VALUE_CHANGED @"SNSOR_VALUE_CHANGED"
#define kSensorsString @"SensorsString"
#define kActuatorTypeString @"ActuatorTypeString"


//[Name of associated class] + [Did | Will] + [UniquePartOfName] + Notification
#define kCSRmeshManagerDidDiscoverDeviceNotification @"CSRmeshManagerDidDiscoverDeviceNotification"
#define kCSRmeshManagerDidUpdateAppearanceNotification @"CSRmeshManagerDidUpdateAppearanceNotification"
#define kCSRmeshManagerWillSetScannerEnabledNotification @"CSRmeshManagerWillSetScannerEnabledNotification"
#define kCSRmeshManagerDidAssociateDeviceNotification @"CSRmeshManagerDidAssociateDeviceNotification"
#define kCSRmeshManagerIsAssociatingDeviceNotification @"CSRmeshManagerIsAssociatingDeviceNotification"
#define kCSRmeshManagerDidTimeoutMessageNotification @"CSRmeshManagerDidTimeoutMessageNotification"
#define kCSRmeshManagerDidGetDeviceInfoNotification @"CSRmeshManagerDidGetDeviceInfoNotification"
#define kCSRBridgeDiscoveryViewControllerWillRefreshUINotification @"CSRBridgeDiscoveryViewControllerWillRefreshUINotification"
#define kCSRDevicesManagerDidRemoveUnassociatedDevicesNotification @"CSRDevicesManagerDidRemoveUnassociatedDevicesNotification"
#define kCSRmeshManagerDeviceAssociationSuccessNotification @"CSRmeshManagerDeviceAssociationSuccessNotification"
#define kCSRmeshManagerDeviceAssociationProgressNotification @"CSRmeshManagerDeviceAssociationProgressNotification"
#define kCSRmeshManagerDeviceAssociationFailedNotification @"CSRmeshManagerDeviceAssociationFailedNotification"
#define kCSRmeshManagerDidGetNumberOfModelGroupIdsNotification @"CSRmeshManagerDidGetNumberOfModelGroupIdsNotification"
#define kCSRmeshManagerDidSetModelGroupIdNotification @"CSRmeshManagerDidSetModelGroupIdNotification"
#define kCSRDevicesSearchListControlDisplayNotification @"CSRDevicesSearchListControlDisplayNotification"
#define kCSRGatewayConnectionStatusChangedNotification @"CSRGatewayConnectionStatusChangedNotification"
#define kCSRImportPlaceDataNotification @"CSRImportPlaceDataNotification"
#define kCSRRefreshNotification @"CSRRefreshNotification"
#define kCSRDeviceManagerDeviceFoundForReset @"CSRDeviceManagerDeviceFoundForReset"

#pragma mark - Login notifications

#define kCSRAppStateManagerDidFinishLoginProcessNotification @"CSRAppStateManagerDidFinishLoginProcessNotification"



#pragma mark - Bridge settings constants

// Local defines - useful if these are used more than once or if change neccessitated
#define BACKGROUND_HIGHLIGHT    colorWithRed:227.0/255.0 green:80.0/255.0 blue:28.0/255.0 alpha:1.0
#define BLUE_TICK               @"blueTick"

// User setting Notifications
#define CSR_BLE_CONNECTION_MODE     @"CSR_BRIDGE_CONNECTION_MODE"
#define CSR_BLE_LISTEN_MODE         @"CSR_BRIDGE_LISTEN_MODE"

#define CSR_RETRY_INTERVAL_NUMBER   @"RETRY_INTERVAL_NUMBER"
#define CSR_RETRY_COUNT_NUMBER      @"RETRY_COUNT_NUMBER"
#define CSR_HOST_ID_NUMBER          @"HOST_ID_NUMBER"
#define CSR_CLOUD_TENANCY_NUMBER @"CSR_CLOUD_TENANCY_NUMBER"
#define CSR_CLOUD_MESH_NUMBER @"CSR_CLOUD_MESH_NUMBER"

// Peripheral properties
#define CSR_PERIPHERAL_NAME         @"CSR_PERIPHERAL_NAME"
#define CSR_PERIPHERAL_RSSI         @"CSR_PERIPHERAL_RSSI"
#define CSR_PERIPHERAL_ID           @"CSR_PERIPHERAL_ID"


typedef enum {
    CSR_BLE_CONNECTIONS_MANUAL = 0,
    CSR__BLE_ONE_CONNECTION,
    CSR_BLE_TWO_CONNECTIONS,
} BleAutoConnectMode;
//
//typedef enum {
//    CSR_SCAN_LISTEN_MODE = 0,
//    CSR_SCAN_NOTIFICATION_LISTEN_MODE,
//    CSR_NOTIFICATION_LISTEN_MODE,
//} BleListenMode;

typedef NS_ENUM(NSUInteger, CSRMeshBridgeScanMode) {
    CSRMeshBridgeScanMode_Manual = 0,
    CSRMeshBridgeScanMode_Automatic
};

//typedef NS_ENUM(NSUInteger, CSRBearerType) {
//    CSRBearerType_Bluetooth = 0,
//    CSRBearerType_Cloud = 1
//};


typedef NS_ENUM(NSUInteger, CSRApperanceName) {
    CSRApperanceNameLight = 4192,
    CSRApperanceNameSensor = 4194,
    CSRApperanceNameHeater = 4195,
    CSRApperanceNameSwitch = 4193,
    CSRApperanceNameGateway = 4196,
    CSRApperanceNameController = 4191
};

typedef NS_ENUM(NSUInteger, CSRGatewayState) {
    CSRGateWayState_NotAssociated = 0,
    CSRGateWayState_Associated = 1,
    CSRGateWayState_Local = 2,
    CSRGateWayState_Cloud = 3
};

typedef NS_ENUM(NSUInteger, CSRGatewayConnectionMode) {
    CSRGatewayConnectionMode_All = 0,
    CSRGatewayConnectionMode_Local = 1,
    CSRGatewayConnectionMode_Cloud = 2,
    CSRGatewayConnectionMode_DeleteCloud = 3,
    CSRGatewayConnectionMode_DeleteGateway = 4,
    CSRGatewayConnectionMode_RemoveBluetooth = 5
};


#pragma mark - Mock server constants

#define kMockServerUriScheme    @"http"
#define kMockServerHost         @"10.101.10.103"
#define kMockServerPort         @"8082"
#define kCNCServerBasePath      @"/csrmesh/cnc"
#define kAAAServerBasePath      @"/csrmesh/aaa"
#define kConfigServerBasePath   @"/csrmesh/config"
#define kAuthServerBasePath     @"/csrmesh/security"

#pragma mark - Cloud Server constants

#define kCloudServerUriScheme @"https"
#define kGatewayServerUriScheme @"http"
#define kAppCode @"438e1398-ae04-43ab-857b-07dd28ea25e2"
//#define kCloudServerUrl @"csrmesh-test.csrlbs.com"

//// test2
//#define kAppCode @"64f82e4d-0337-4e85-ac9e-61b50c5f2c27"
#define kCloudServerUrl @"csrmesh-2-1.csrlbs.com"

#define kCloudServerPort @"443"
#define kCSRGlobalCloudHost @"kCSRGlobalCloudHost"

#pragma mark - Add device wizard validation messages

#define kAddWizardValidationMessage_Security @"Please enter authorisation code"
#define kAddWizardValidationMessage_ShortCode @"Please enter short code"
#define kAddWizardValidationMessage_ScanQR @"It seems that QR code scan was unsuccessful.\nPlease try again before going to another step or select different way to add new device."


#pragma mark - Air Temperature limits
#define kCSR_AirTemp_Default    20.0
#define kCSR_AirTemp_MAX        30.0
#define kCSR_AirTemp_MIN        14.0
#define kCSR_AirTemp_Increment  0.5


#define LOCALIZEDSTRING(string) NSLocalizedString(string, nil)

