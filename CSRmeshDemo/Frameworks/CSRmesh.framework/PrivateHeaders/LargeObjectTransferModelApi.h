//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

@import Foundation;
#import "CSRmeshApi.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 * @header Ability to exchange information between nodes such as to allow a peer-to-peer data transfer to be established after a negotiation phase.
 */

@protocol LargeObjectTransferModelApiDelegate <NSObject>
@optional

/**
 * @brief Received an announcement.
 * @param deviceId
 * @param companyCode - (uint16_t wrapped in NSNumber) Bluetooth Company Code
 * @param platformType - (uint8_t wrapped in NSNumber) Platform this object is intended for:
 * 0=CSR101x, 1=CSR102x,
 * other values up to 127 reserved for future Qualcomm products. 128 and up – user defined values
 * @param typeEncoding - (uint8_t wrapped in NSNumber) Type description of intended payload
 *0=firmware update.
 *other values up to 127 reserved for other Qualcomm products. 128 and up – user defined values
 * @param imageType - (uint8_t wrapped in NSNumber) What the image is
 *0= Light, 1=Switch, 2=Sensor, 3=Heater, 4=Gateway, 5=Beacon,
 *6=beacon Proxy, 7=Lumicast, 8=Bridge.
 *other values up to 127 reserved for future Qualcomm products. 128 and up – user defined values
 * @param size - (uint8_t wrapped in NSNumber) Number of kilobytes in the Large Object (0 = < 1K bytes, 1 = >=1K bytes, < 2K bytes, and so on)
 * @param objectVersion - (NSData) Object Version in byte order Major, Minor, Revision. A node can use this to decide if it already has this version of the object
 * @param targetDestination - (uint16_t wrapped in NSNumber) Destination of the Large Object
 * @param serviceID - NSDictionary - key=interest, value=ServiceID , used to compute the serviceUUID by calling computeServiceUUID (serviceID(value), serviceIDSignature), where serviceID signature is a const 8-byte array where bytes 1 to 6 are preagreed and are the same value in the phone and the device and bytes 7 & 8 is the deviceID in this case the deviceID of the phone. If calling interestRequest, then the serviceId value is bits 0 to 62 of the key.

 */
- (void)didGetAnnouncement:(NSNumber *)deviceId
               companyCode:(NSNumber * _Nullable)companyCode
              platformType:(NSNumber * _Nullable)platformType
              typeEncoding:(NSNumber * _Nullable)typeEncoding
                 imageType:(NSNumber * _Nullable)imageType
                      size:(NSNumber * _Nullable)size
             objectVersion:(NSData * _Nullable)objectVersion
         targetDestination:(NSNumber * _Nullable)targetDestination
                 serviceID:(NSDictionary * _Nullable)serviceID;

/**
 * @brief Received an interest
 * @param deviceId
 * @param interest - To be used to lookup the serviceID in the dictionary returned by annouceRequest. Call the Api computeServiceUUID to obtain the serviceUUID.
 */
- (void)didGetInterest:(NSNumber *)deviceId
             interest:(NSData * _Nullable)interest;

@end

@interface LargeObjectTransferModelApi : CSRmeshApi

/// @brief A list of delegates to callback
@property (atomic, strong, readwrite) NSMutableSet * delegates;

/**
 * @brief A node wanting to provide a large object to neighbouring Mesh Nodes issues an ANNOUNCE with the associated content type. This message will have TTL=0, thus will only be answered by its immediate neighbours. The ANNOUNCE has the total size of the packet to be issued. The format and encoding of the large object is subject to the provided type and is out of scope of this document. The destination ID can either be 0, a group or a specific Device ID. In case the destination ID is not zero, only members of the group (associated with the LOT model) or the device with the specified Device ID responds with the intent to download the object for their own consumption. Every other node either ignores or accepts the offer for the purpose of relaying the packet.
 * @param deviceId
 * @param companyCode - Bluetooth Company Code
 * @param typeEncoding - Type description of the intended payload
 * @param size - Number of kilobytes in the Large Object
 * @param objectVersion - The node software version as 3 bytes of major.minor.revision
 * @param targetDestination - Destination of the Large Object
 * @param failure - Block called upon error
 * @return NSDictionary - key=interest, value=ServiceID , used to compute the serviceUUID by calling computeServiceUUID (serviceID(value), serviceIDSignature), where serviceID signature is a const 8-byte array where bytes 1 to 6 are preagreed and are the same value in the phone and the device and bytes 7 & 8 is the deviceID in this case it is the desitnation deviceID.
 */
- (NSDictionary * _Nonnull)announceRequest:(NSNumber * _Nonnull)deviceId
            companyCode:(NSNumber * _Nonnull)companyCode
           platformType:(NSNumber * _Nonnull)platformType
           typeEncoding:(NSNumber * _Nonnull)typeEncoding
              imageType:(NSNumber * _Nonnull)imageType
                   size:(NSNumber * _Nonnull)size
          objectVersion:(NSData * _Nonnull)objectVersion
      targetDestination:(NSNumber *)targetDestination
                failure:(void (^ _Nullable)(NSError * _Nullable error))failure;

/**
 * @brief Compute the serviceUUID to be used to form a GATT connection to a device for the purpose of Over-the-air-update of device software.
 * @param serviceID - the value returned in the NSDictionary from announceRequest.
 * @param serviceIdSignature - A const 8-byte array, that is the same in the phone and the node.
 * @param failure - Block called if there is an error with the input values
 * @return NSData - The serviceUUID that is used to form a GATT connection to the device.
 */
-(NSData * _Nonnull) computeServiceUUID:(NSData * _Nonnull)serviceID
                     serviceIdSignature:(NSData * _Nonnull)serviceIdSignature
                                failure:(void (^ _Nullable)(NSError * _Nullable error))failure;


/**
 * @brief In case a node is ready to receive the proposed object, it responds with this message. The intended behaviour of the Large Object Transfer is to allow a Peer-to-Peer connection between the consumer and the producer. The consumer uses a ServiceID, part of which is randomly selected. The top 64 bits are 0x1122334455667788, the least significant 63 bits are randomly selected by the consumer node. The most significant bit of the least significant 64 bits is an encoding of the intent to relay the received data. Once this message has been issued, the consumer node starts advertising a connectable service with the 128-bits service composed through the concatenation of the fixed 64 bits and the randomly selected 63 bits. The duration of the advertisement is an implementation decision.
 * @param deviceId
 * @param serviceId - Least Significant 63 bits of Service ID to be used for transfer - Most Significant Bit set to 1 if the source intends to use the packet.
 */
- (void)interestRequest:(NSNumber * _Nonnull)deviceId
              serviceId:(NSNumber * _Nullable)serviceId;

/*!
 @brief Register a delegate object to callback. Duplicates will be ignored.
 @param delegate The delegate object specified to receive peripheral events.
 */
- (void)addDelegate:(id<LargeObjectTransferModelApiDelegate>)delegate;

/*!
 @brief Remove an object to callbacks. Objects that are not present will be ignored.
 @param delegate The delegate object specified to no longer receive peripheral events.
 */
- (void)removeDelegate:(id<LargeObjectTransferModelApiDelegate>)delegate;


@end

NS_ASSUME_NONNULL_END
