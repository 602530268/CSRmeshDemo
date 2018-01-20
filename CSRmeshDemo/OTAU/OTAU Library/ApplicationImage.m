//
//  Firmware.m
//  OTAU
//
/******************************************************************************
 *  Copyright (C) Cambridge Silicon Radio Limited 2014
 *
 *  This software is provided to the customer for evaluation
 *  purposes only and, as such early feedback on performance and operation
 *  is anticipated. The software source code is subject to change and
 *  not intended for production. Use of developmental release software is
 *  at the user's own risk. This software is provided "as is," and CSR
 *  cautions users to determine for themselves the suitability of using the
 *  beta release version of this software. CSR makes no warranty or
 *  representation whatsoever of merchantability or fitness of the product
 *  for any particular purpose or use. In no event shall CSR be liable for
 *  any consequential, incidental or special damages whatsoever arising out
 *  of the use of or inability to use this software, even if the user has
 *  advised CSR of the possibility of such damages.
 *
 ******************************************************************************/
//

#import "ApplicationImage.h"

// #define FIRMWARE_TEST   1

/****************************************************************************/
/*								Constants                                   */
/****************************************************************************/
//size of the Firmware image
#define MAX_FIRMWARE_SIZE   0x20000 // 64 kBytes
#define MAX_BLOCKS          200

// Control Header offets
#define Header_CRC          0   // word - the CRC of the Header Block
#define version             2   // byte - Firmware version
#define Number_Of_Blocks    3   // byte - Number of Block Headers
#define SCL_Period          4   // word -

// Block Header offsets - defines the offset,size,crc and destination in RAM of data blocks
#define Source_Address      0   // word - Offset of data block from start (0)
#define Destination_Address 2   // word - Location in Device memory where this data block is copied to
#define Block_Length        4   // word - Length of the data block in bytes
#define Block_CRC           6   // word - The CRC of the data block

// Data Block 0 offsets
#define BT_MAC_Address_offset   2                           // Offset into data block for Mac address
#define XTAL_Trim_offset        8                           // Offset into data block for the crystal trim
#define IR_offset               60                          // Offset into data block for the identity root
#define ER_offset               IR_offset + Size_of_Root    // Offset into data block for the encryption root

// size of Control Header in bytes
#define Size_Of_Control_Header  6   //

// Size of each Block Header in bytes
#define Size_Of_Block_Header    8

// size of xTal Trim
#define Size_Of_XtalTrim        1

// size of BT Mac Address
#define Size_Of_BT_Mac_Address  6

#define Size_of_Root            16


/****************************************************************************/
/*								Private definitions                         */
/****************************************************************************/

@interface ApplicationImage ()

//-------[ import firmware image ]--------------------------------------------
- (NSMutableData *) convertFirmwareToBinary:(NSString *) filePath;
/*!
 @method readFirmwareFile
 @abstract Convert the image file from text to binary
 @discussion It is quicker to build code for bit manipulation on binary data than text strings.
 @updated 2013-11-27
 */

//-------[ Modify xtal trim and BT Address then generate new CRCs ]----------
- (void) setXtalTrim:(NSData *) xtalTrim :(uint8_t*) dest;
- (void) setBtMacAddr:(NSData *) btMacAddress :(uint8_t*) dest;
- (void) setRoot:(NSData *) rootKey :(uint8_t*) dest;
- (void) generateBlockCRC:(int) block :(NSMutableData *) binaryFirmware;
- (void) generateHeaderCRC :(NSMutableData *) binaryFirmware;


/****************************************************************/
/*                        CRC helper methods                    */
/****************************************************************/
- (void) copyBytes:(uint8_t *)src :(uint8_t *)dest :(int)n;
- (uint8_t) reflectByte:(uint8_t) byte;
- (uint16_t) addCRCByte:(uint16_t) crcRemainder :(uint8_t) byte;


/****************************************************************/
/* export binary firmware to original format as text file,      */
/****************************************************************/
#ifdef FIRMWARE_TEST
-(void) exportFirmware :(NSMutableData *) binaryFirmware;
- (void)writeStringToFile:(NSString*)aString :(NSString *)fileAtPath;
#endif

@end

/****************************************************************************/
/*								Firmware Class Implementation    			*/
/****************************************************************************/

@implementation ApplicationImage

/****************************************************************************/
/*									Init									*/
/****************************************************************************/

+ (id) sharedInstance {
	static ApplicationImage	*this	= nil;
    
	if (!this)
		this = [[ApplicationImage alloc] init];
    
	return this;
}


- (id) init {
    self = [super init];
    if (self) {
	}
    return self;
}


/****************************************************************************/
/*								 Actions                                    */
/****************************************************************************/

//===========================================================================
// Convert the given image file to cached Binary data
// 1. Buffer file as NSString
// 2. Create an NSString for each line and store as into NSArray
// 3. Scan for "@address data" and copy binary data into a holding byte buffer
// 4. Finally, copy the byte buffer to an NSMutableData array
//===========================================================================
- (NSMutableData *) convertFirmwareToBinary:(NSString *) filePath {
    if (filePath==nil)
        filePath = [[NSBundle mainBundle] pathForResource:@"remote" ofType:@"xuv"];
    if (filePath) {
        
        // 1. Read file into an NSString
        NSString *fileContents =
        [NSString stringWithContentsOfFile:filePath encoding:NSUTF8StringEncoding error:NULL];
        
        // 2. Create an NSString for each line and store as into NSArray
        NSArray* allLinedStrings =
        [fileContents componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
        
        // 3. Scan for "@address data" and copy binary data into a holding byte buffer, where
        //    address=a 6 digit hex string and data is a 4 digit word.
        
        uint32_t maxAddress=0;
        uint8_t rawData [MAX_FIRMWARE_SIZE];
        int32_t found=FALSE; // set to TRUE if at least one valid data byte found
        uint32_t address;    // storage hex string to binary conversion
        uint32_t data;
        // For all text lines in the file
        for (NSString *line in allLinedStrings) {
            // Make sure line begins with @, as it could begin with //
            // AND
            // Make sure 2 hex strings are decoded, address size is 6 chars and data size is 4 chars
            // Otherwise discard.
            if ([line UTF8String][0]=='@' &&
                
                sscanf ([line UTF8String], "@%6x %4x", &address, &data)==2) {
                
                found = TRUE;
                
                // QC added start
                
                address *= 2;
                
                // QC added end
                
                if (address>maxAddress)
                    
                    maxAddress = address;
                
                if (address<MAX_FIRMWARE_SIZE) {
                    
                    rawData [address] = data&0xff;
                    
                    rawData [address+1] = data>>8;
                    
                }
                
                //NSLog(@"%06x %04x", address, data);
                
            }
            
        }
        
        
        
        // 4. Finally, copy the byte buffer to an NSMutableData array for export
        if (found) {
            NSMutableData *binaryFirmware = [[NSMutableData alloc] initWithBytes:rawData length:maxAddress+2];
            return (binaryFirmware);
            
        }
    }
    
    return (nil);
}

//===========================================================================
// Save the given crystal trim
// 1. Copy the given 16-bit crystal trim to XTAL_Trim_offset in block 0
// 2. Generate Block CRC
// 3. Generate Header CRC
//===========================================================================
- (void) setXtalTrim:(NSData *) xtalTrim :(uint8_t*) dest {
    
    // safety check - proceed only if firmware file has been converted to Binary
    if (dest != nil) {
        uint8_t *src = (uint8_t *) [xtalTrim bytes];
        
        [self copyBytes:src :dest :(int)[xtalTrim length]];
        
        // NOTE: The CRC for the data & header block will be updated by the calling method
    }
}

//===========================================================================
// Save the given Bluetooth MAC address
// 1. Copy the given 24-bit BT Address to BT_MAC_Address_offset in block 0
// 2. Generate Block CRC
// 3. Generate Header CRC
//===========================================================================
- (void) setBtMacAddr:(NSData *) btMacAddress :(uint8_t*) dest {
    
    // safety check - proceed only if firmware file has been converted to Binary
    if (dest != nil) {
        // Create byte pointer so we can do byte by byte copy
        // we are only interested in the lower 6 bytes, so skip the top 2.
        uint8_t *src = (uint8_t *) [btMacAddress bytes];
        
        // Have to copy bytes in reverse
        for (int i=0, offset=5; i<[btMacAddress length]; i++, offset--) {
            *dest++ = *(src+offset);
        }
        
        // NOTE: The CRC for the data & header block will be updated by the calling method
    }
}

-(void) setRoot:(NSData *) rootKey :(uint8_t*) dest {
    // safety check - proceed only if firmware file has been converted to Binary
    if (dest != nil) {
        uint8_t *src = (uint8_t*) [rootKey bytes];
        memcpy(dest, src, Size_of_Root);
        // NOTE: The CRC for the data & header block will be updated by the calling method
    }
}


//===========================================================================
// Generate the data block CRC for the block number
// 1. Copy the given crystal trim to the raw firmware file
// 2. Generate Block CRC
// 3. Generate Header CRC
//===========================================================================
- (void) generateBlockCRC:(int) block :(NSMutableData *) binaryFirmware {
    
    // safety check - proceed only if firmware file has been converted to Binary
    if (binaryFirmware != nil) {
        
        uint16_t crcRemainder=0;
        
        uint8_t *base;
        base = [binaryFirmware mutableBytes];
        
        // - Compute the start address of the given block.
        uint16_t *blockHeader = (uint16_t *) (base+Size_Of_Control_Header+(Size_Of_Block_Header*block));
        
        uint16_t src = *(blockHeader);
        uint16_t length = *(blockHeader+2);
        
        while (length--) {
            crcRemainder = [self addCRCByte:crcRemainder :*(base + src++)];
        }
        
        // - Store CRC
        *(blockHeader+3) = crcRemainder;
        
        NSLog(@"%04x",crcRemainder);
    }
}


//===========================================================================
// Generate the data Header CRC
// 1. Copy the given crystal trim to the raw firmware file
// 2. Generate Block CRC
// 3. Generate Header CRC
//===========================================================================
- (void) generateHeaderCRC :(NSMutableData *) binaryFirmware {
    
    // safety check - proceed only if firmware file has been converted to Binary
    if (binaryFirmware != nil) {
        
        uint16_t crcRemainder=0;
        
        uint8_t *base;
        base = [binaryFirmware mutableBytes];
        
        // - Compute size of Header Block
        uint16_t sizeOfHeaderBlock =
        (Size_Of_Control_Header + (*(base + Number_Of_Blocks) * Size_Of_Block_Header));
        
        // - Skip the first two bytes for the start of crc computation as this is where
        //   the crc is stored.
        uint16_t src = 2;
        
        // - length of crc block is 2 less than the size of the Header as we omit the
        //   space occupied by the crc
        uint16_t length = sizeOfHeaderBlock-2;
        
        while (length--) {
            crcRemainder = [self addCRCByte:crcRemainder :*(base + src++)];
        }
        
        // The Header CRC is stored at the first word in memory therefore compute a
        // 16-bit pointer and save the crc there.
        uint16_t *controlHeader = (uint16_t *) base;
        *controlHeader = crcRemainder;
        
        NSLog(@"%04x",crcRemainder);
    }
}

//===========================================================================
// Generate the data block CRC for the block number
// 1. Copy the given crystal trim to the raw firmware file
// 2. Generate Block CRC
// 3. Generate Header CRC
//===========================================================================
- (void) copyBytes:(uint8_t *)src :(uint8_t *)dest :(int)n  {
    
    while (n--)
        *dest++ = *src++;
}


//===========================================================================
// Reflect byte across centre
// so that a byte with bits ABCDEFGH becomes HGFEDCBA
//===========================================================================
- (uint8_t) reflectByte:(uint8_t) byte  {
    
    uint8_t refelectedByte=0;
    
    for (int i=0; i<8; i++) {
        refelectedByte<<=1;
        if (byte&1)
            refelectedByte|=1;
        byte>>=1;
    }
    
    return (refelectedByte);
}


//===========================================================================
// Reflect byte across centre
// so that a byte with bits ABCDEFGH becomes HGFEDCBA
//===========================================================================
-(uint16_t) addCRCByte:(uint16_t) crcRemainder :(uint8_t) byte {
    
    /* The CRC lookup table */
    const uint16_t crcLookupTable[] =
    {
        0x0000U, 0x8005U, 0x800FU, 0x000AU, 0x801BU, 0x001EU, 0x0014U, 0x8011U,
        0x8033U, 0x0036U, 0x003CU, 0x8039U, 0x0028U, 0x802DU, 0x8027U, 0x0022U,
        0x8063U, 0x0066U, 0x006CU, 0x8069U, 0x0078U, 0x807DU, 0x8077U, 0x0072U,
        0x0050U, 0x8055U, 0x805FU, 0x005AU, 0x804BU, 0x004EU, 0x0044U, 0x8041U,
        0x80C3U, 0x00C6U, 0x00CCU, 0x80C9U, 0x00D8U, 0x80DDU, 0x80D7U, 0x00D2U,
        0x00F0U, 0x80F5U, 0x80FFU, 0x00FAU, 0x80EBU, 0x00EEU, 0x00E4U, 0x80E1U,
        0x00A0U, 0x80A5U, 0x80AFU, 0x00AAU, 0x80BBU, 0x00BEU, 0x00B4U, 0x80B1U,
        0x8093U, 0x0096U, 0x009CU, 0x8099U, 0x0088U, 0x808DU, 0x8087U, 0x0082U,
        0x8183U, 0x0186U, 0x018CU, 0x8189U, 0x0198U, 0x819DU, 0x8197U, 0x0192U,
        0x01B0U, 0x81B5U, 0x81BFU, 0x01BAU, 0x81ABU, 0x01AEU, 0x01A4U, 0x81A1U,
        0x01E0U, 0x81E5U, 0x81EFU, 0x01EAU, 0x81FBU, 0x01FEU, 0x01F4U, 0x81F1U,
        0x81D3U, 0x01D6U, 0x01DCU, 0x81D9U, 0x01C8U, 0x81CDU, 0x81C7U, 0x01C2U,
        0x0140U, 0x8145U, 0x814FU, 0x014AU, 0x815BU, 0x015EU, 0x0154U, 0x8151U,
        0x8173U, 0x0176U, 0x017CU, 0x8179U, 0x0168U, 0x816DU, 0x8167U, 0x0162U,
        0x8123U, 0x0126U, 0x012CU, 0x8129U, 0x0138U, 0x813DU, 0x8137U, 0x0132U,
        0x0110U, 0x8115U, 0x811FU, 0x011AU, 0x810BU, 0x010EU, 0x0104U, 0x8101U,
        0x8303U, 0x0306U, 0x030CU, 0x8309U, 0x0318U, 0x831DU, 0x8317U, 0x0312U,
        0x0330U, 0x8335U, 0x833FU, 0x033AU, 0x832BU, 0x032EU, 0x0324U, 0x8321U,
        0x0360U, 0x8365U, 0x836FU, 0x036AU, 0x837BU, 0x037EU, 0x0374U, 0x8371U,
        0x8353U, 0x0356U, 0x035CU, 0x8359U, 0x0348U, 0x834DU, 0x8347U, 0x0342U,
        0x03C0U, 0x83C5U, 0x83CFU, 0x03CAU, 0x83DBU, 0x03DEU, 0x03D4U, 0x83D1U,
        0x83F3U, 0x03F6U, 0x03FCU, 0x83F9U, 0x03E8U, 0x83EDU, 0x83E7U, 0x03E2U,
        0x83A3U, 0x03A6U, 0x03ACU, 0x83A9U, 0x03B8U, 0x83BDU, 0x83B7U, 0x03B2U,
        0x0390U, 0x8395U, 0x839FU, 0x039AU, 0x838BU, 0x038EU, 0x0384U, 0x8381U,
        0x0280U, 0x8285U, 0x828FU, 0x028AU, 0x829BU, 0x029EU, 0x0294U, 0x8291U,
        0x82B3U, 0x02B6U, 0x02BCU, 0x82B9U, 0x02A8U, 0x82ADU, 0x82A7U, 0x02A2U,
        0x82E3U, 0x02E6U, 0x02ECU, 0x82E9U, 0x02F8U, 0x82FDU, 0x82F7U, 0x02F2U,
        0x02D0U, 0x82D5U, 0x82DFU, 0x02DAU, 0x82CBU, 0x02CEU, 0x02C4U, 0x82C1U,
        0x8243U, 0x0246U, 0x024CU, 0x8249U, 0x0258U, 0x825DU, 0x8257U, 0x0252U,
        0x0270U, 0x8275U, 0x827FU, 0x027AU, 0x826BU, 0x026EU, 0x0264U, 0x8261U,
        0x0220U, 0x8225U, 0x822FU, 0x022AU, 0x823BU, 0x023EU, 0x0234U, 0x8231U,
        0x8213U, 0x0216U, 0x021CU, 0x8219U, 0x0208U, 0x820DU, 0x8207U, 0x0202U
    };
    
    uint8_t data;
    
    data = ([self reflectByte:byte]) ^ ((uint8_t)(crcRemainder >> 8));
    crcRemainder = crcLookupTable[data] ^ (crcRemainder << 8);
    return (crcRemainder);
}



//===========================================================================
// Prepare the Firmware image file for OTA upgrade upload to Bluetooth device
// If the file doesn't exist then first create it
//===========================================================================
-(NSData *) prepareFirmwareWith:(NSData *)crystalTrim
                            and:(NSData *) bluetoothMacAddress
                            and:(NSData*) iRoot
                            and:(NSData*) eRoot
                        forFile:(NSString *) filepath {

    NSMutableData *binaryFirmware = [self convertFirmwareToBinary:filepath];
    if (binaryFirmware != nil) {
        // Work out pointer to cs keys based on num blocks read from image.
        uint16_t *data = (uint16_t*)[binaryFirmware bytes];
        uint16_t numBlocks = CFSwapInt16BigToHost(data[1]);
        uint8_t *csKeys = (uint8_t*)[binaryFirmware mutableBytes] + Size_Of_Control_Header + (numBlocks * Size_Of_Block_Header);
        // Pointers into binary firmware for each key that needs to be updated.
        uint8_t *btAddrKey = csKeys + BT_MAC_Address_offset;
        uint8_t *xtalKey = csKeys + XTAL_Trim_offset;
        uint8_t *irKey = csKeys + IR_offset;
        uint8_t *erKey = csKeys + ER_offset;
        
        if (crystalTrim != nil) {
            [self setXtalTrim:crystalTrim :xtalKey];
        }
        if (bluetoothMacAddress != nil) {
            [self setBtMacAddr:bluetoothMacAddress :btAddrKey];
        }
        if (iRoot != nil) {
            [self setRoot: iRoot :irKey];
        }
        if (eRoot != nil) {
            [self setRoot: eRoot :erKey];
        }
        [self generateBlockCRC:0:binaryFirmware];
        [self generateHeaderCRC:binaryFirmware];
        
#ifdef FIRMWARE_TEST
        [self exportFirmware:binaryFirmware];
#endif
    }
    
    return (binaryFirmware);
}

#ifdef FIRMWARE_TEST
//===========================================================================
// Export Binary firmaware as a text file of type img
// This will be used to test features in this class
//===========================================================================

-(void) exportFirmware :(NSMutableData *) binaryFirmware {
    
    // safety check - proceed only if firmware file has been converted to Binary
    if (binaryFirmware != nil) {
        
        // Build the path, and create if needed.
        NSString* filePath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
        NSString* fileName = @"export.img";
        NSString* fileAtPath = [filePath stringByAppendingPathComponent:fileName];
        
        if (![[NSFileManager defaultManager] fileExistsAtPath:fileAtPath]) {
            [[NSFileManager defaultManager] createFileAtPath:fileAtPath contents:nil attributes:nil];
        }
        
        // pointer to the firmware binary image.
        uint8_t *base;
        base = [binaryFirmware mutableBytes];
        
        // pointer used to read 16ibt data from binary image for saving in Firemware
        uint16_t *read = (uint16_t *) base;
        
        // offset of word to be written
        uint16_t offset = 0;
        
        // a string that will hold the data to be written to file
        NSMutableString *fileWrite = [[NSMutableString alloc] init];
        // Write control Header
        //[fileWrite appendFormat:@"// Control Header\r\n"];
        [fileWrite appendFormat:@"@%06x   %04x\r\n",offset, *read++];
        [fileWrite appendFormat:@"@%06x   %04x\r\n",offset+=2, *read++];
        [fileWrite appendFormat:@"@%06x   %04x\r\n",offset+=2, *read++];
        
        // Write Header Blocks
        //[fileWrite appendFormat:@"// Block Headers\r\n"];
        
        // - offset is already at the correct place, we just need to know how many words to
        //   write. This will be header size in words minus size of the control_header.
        uint16_t sizeOfHeaderBlock =
        ((Size_Of_Control_Header + (*(base + Number_Of_Blocks) * Size_Of_Block_Header))/2)-3;
        
        while (sizeOfHeaderBlock--) {
            [fileWrite appendFormat:@"@%06x   %04x\r\n",offset+=2, *read++];
        }
        
        // Write Block data for all blocks
        //[fileWrite appendFormat:@"// Data Blocks\r\n"];
        uint8_t nBlocks = *(base+Number_Of_Blocks);
        uint16_t *blockHeader = (uint16_t *) (base+Size_Of_Control_Header);
        for (int i=0; i<nBlocks && i<MAX_BLOCKS; i++, blockHeader+=(Size_Of_Block_Header/2)) {
            uint16_t src = *blockHeader;
            read = (uint16_t *)(base + src);
            uint16_t length = (*(blockHeader+2))/2;
            while (length--) {
                [fileWrite appendFormat:@"@%06x   %04x\r\n",src, *read++];
                src += 2;
            }
        }
        
        NSLog(@"%@",fileWrite);
        [self writeStringToFile:fileWrite :fileAtPath];
    }
}


//===========================================================================
// Write the given string to the given text file at path
// If the file doesn't exist then first create it
//===========================================================================
- (void)writeStringToFile:(NSString*)aString :(NSString *)fileAtPath {
    
    if (![[NSFileManager defaultManager] fileExistsAtPath:fileAtPath]) {
        [[NSFileManager defaultManager] createFileAtPath:fileAtPath contents:nil attributes:nil];
    }
    
    [[aString dataUsingEncoding:NSUTF8StringEncoding] writeToFile:fileAtPath atomically:NO];
}
#endif


@end
