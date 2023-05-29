#include <stdint.h>

#ifndef _MY_INTERFACE_H
#define _MY_INTERFACE_H

#define MY_INTERFACE_CURRENT_CLOCK_RED  0x11
#define MY_INTERFACE_CURRENT_CLOCK_BLU  0x22
#define MY_INTERFACE_CURRENT_CLOCK_BOTH 0x33

#define MY_INTERFACE_MODE_OPER 0x11
#define MY_INTERFACE_MODE_EDIT 0x22

typedef struct 
{
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t modeactive;
}CLK_interface_t;

#define NFC_PN532_NTAG203_TAG       7
#define NFC_PN532_UID_MAX_SIZE      NFC_PN532_NTAG203_TAG
#define NFC_PN532_PAGE_SIZE         32
#define NFC_PN532_MAX_PAGE_NUMBER   42
typedef struct 
{
    uint8_t uidLength;  // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    uint8_t uidArray[NFC_PN532_UID_MAX_SIZE];   // Buffer to store the returned UID
    uint8_t pageData[NFC_PN532_PAGE_SIZE];
}RFID_interface_t;

#endif // _MY_INTERFACE_H