//
// Copyright 2015 Qualcomm Technologies International, Ltd.
//


#import "CSROTAUGattCommand.h"

#define OTAU_GATT_COMMAND_ACK_MASK               0x8000
#define OTAU_GATT_COMMAND_MASK                   0x7FFF

@implementation CSROTAUGattCommand

- (NSUInteger)length {
    return [self.command length];
}

- (NSData *)getPacket {
    return self.command;
}

- (NSInteger)getPayloadLength {
    return [self.command length] - OTAU_GATT_HEADER_SIZE;
}

- (void)setCommandId:(OTAUCommandType)type {
    if (self.command) {
        unsigned char *header = (unsigned char *)[self.command bytes];
        
        header[OTAU_GATT_HEADER_OFFSET_COMMAND_ID] = (type >> 8) & 0xFF;
        header[OTAU_GATT_HEADER_OFFSET_COMMAND_ID + 1] = type & 0xFF;
        self.command_id = type;
    }
}

- (OTAUCommandType)getCommandId {
    // take off potential ACK bit (0x8000)
    return self.command_id & OTAU_GATT_COMMAND_MASK;
}

- (void)setVendorId:(uint16_t)vendor {
    if (self.command) {
        unsigned char *header = (unsigned char *)[self.command bytes];
        
        header[OTAU_GATT_HEADER_OFFSET_VENDOR_ID] = (vendor >> 8) & 0xFF;
        header[OTAU_GATT_HEADER_OFFSET_VENDOR_ID + 1] = vendor & 0xFF;
        self.vendor_id = vendor;
    }
}

- (uint16_t)getVendorId {
    return self.vendor_id;
}

- (void)addPayload:(NSData *)payload {
    [self.command appendData:payload];
}

- (NSData *)getPayload {
    NSInteger payload_length = [self getPayloadLength];
    
    if (!payload_length) {
        return nil;
    }
    
    NSRange payload_range = {OTAU_GATT_HEADER_OFFSET_PAYLOAD, payload_length};
    
    return [self.command subdataWithRange:payload_range];
}

- (BOOL)isAcknowledgement {
    return (self.command_id & OTAU_GATT_COMMAND_ACK_MASK) != 0;
}

- (BOOL)isControl {
    OTAUCommandType cmd = [self getCommandId];
    
    if (cmd >= OTAUCommand_Volume && cmd < OTAUCommand_GetAPIVersion) {
        return YES;
    }
    
    return NO;
}

- (BOOL)isConfiguration {
    OTAUCommandType cmd = [self getCommandId];
    
    if (cmd >= OTAUCommand_SetLEDConfiguration && cmd < OTAUCommand_Volume) {
        return YES;
    }
    
    return NO;
}

- (OTAUCommandStatus)status {
    if (self.command && ([self getPayloadLength] >= 1)) {
        unsigned char *header = (unsigned char *)[self.command bytes];
        
        return (OTAUCommandStatus)header[OTAU_GATT_HEADER_OFFSET_PAYLOAD];
    }
    
    return OTAUStatus_NoStatusAvailable;
}

- (OTAUCommandUpdate)updateStatus {
    if (self.command && ([self getPayloadLength] >= 1)) {
        unsigned char *header = (unsigned char *)[self.command bytes];
        
        return (OTAUCommandUpdate)header[OTAU_GATT_HEADER_OFFSET_PAYLOAD + 1];
    }
    
    return OTAUUpdate_Unknown;
}

- (OTAUCommandUpdateResponse)updateResponse {
    if (self.command && ([self getPayloadLength] >= 1)) {
        unsigned char *header = (unsigned char *)[self.command bytes];
        
        return (OTAUCommandUpdateResponse)header[OTAU_GATT_HEADER_OFFSET_PAYLOAD];
    }
    
    return OTAUUpdateResponse_Success;
}

// get event type from notification
- (OTAUEvent)event {
    // if we have a command, it is an event notification and there is a payload
    // to look at
    if (   self.command
        && ([self getCommandId] == OTAUCommand_EventNotification)
        && ([self getPayloadLength] >= 1)) {
        unsigned char *header = (unsigned char *)[self.command bytes];
        
        return (OTAUEvent)header[OTAU_GATT_HEADER_OFFSET_PAYLOAD];
    }
    
    return OTAUEvent_UnknownEvent;
}

- (id)init {
    return [self initWithNSData:nil];
}

- (id)initWithNSData:(NSData *)data {
    if ([data length] < OTAU_GATT_HEADER_SIZE)
        return nil;
    
    if (self = [super init]) {
        // copy the data into this object instance
        self.command = [data copy];
        
        unsigned char *header = (unsigned char *)[self.command bytes];
        
        self.command_id |= (header[OTAU_GATT_HEADER_OFFSET_COMMAND_ID] << 8);
        self.command_id |= header[OTAU_GATT_HEADER_OFFSET_COMMAND_ID + 1];
        self.vendor_id |= (header[OTAU_GATT_HEADER_OFFSET_VENDOR_ID] << 8);
        self.vendor_id |= header[OTAU_GATT_HEADER_OFFSET_VENDOR_ID + 1];
    }
    
    return self;
}

- (id)initWithLength:(NSInteger)length {
    if (length < OTAU_GATT_HEADER_SIZE)
        return nil;
    
    if (self = [super init]) {
        self.command = [[NSMutableData alloc] initWithLength:length];
        
        if (!self.command) {
            return nil;
        }
    }
    
    return self;
}

@end
