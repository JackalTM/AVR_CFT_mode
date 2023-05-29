#include "MyInterface.h"
#include <Adafruit_SH1106.h>
#include <Adafruit_GFX.h>

// It is wraper for Adafruit_SH1106 class

#ifndef _MY_DISPLAY_H
#define _MY_DISPLAY_H

#define MY_DISPLAY_MAX_PIXEL_X  64
#define MY_DISPLAY_MAX_PIXEL_Y  128

#define MY_DISPLAY_FACTOR_X  6
#define MY_DISPLAY_FACTOR_Y  12

#define MY_DISPLAY_MAX_CHARS_IN_X(sectorX)  (MY_DISPLAY_MAX_PIXEL_X / MY_DISPLAY_FACTOR_X) * (sectorX)
#define MY_DISPLAY_MAX_CHARS_IN_Y(sectorY)  (MY_DISPLAY_MAX_PIXEL_Y / MY_DISPLAY_FACTOR_Y) * (sectorY)

#define MY_DISPLAY_STR_TICKETS  ">TICKETS<"
#define MY_DISPLAY_STR_BLU      "BU:"
#define MY_DISPLAY_STR_RED      "RD:"

class My_OLED_DisplayClass
{
private:
    // Referance to global data
    Adafruit_SH1106&        RefAdafruit_SH1106;

    uint8_t i;
    void _DisplayString(const String &pSTR, uint8_t sectorX, uint8_t sectorY);
    void _DisplayIneger(uint8_t data, uint8_t sectorX, uint8_t sectorY);
    void _NumberToString(uint8_t number, char* pSTR);
    void _DisplayTimeShort(CLK_interface_t* pTime, uint8_t sectorX, uint8_t sectorY);
    void _DisplayTimeFULL(CLK_interface_t* pTime, uint8_t sectorX, uint8_t sectorY);

public:
    // My_OLED_DisplayClass::My_OLED_DisplayClass(Adafruit_SH1106& inRefAdafruit_SH1106, RFID_OLED_interface_t& inRefRfidOledData);    
    My_OLED_DisplayClass(Adafruit_SH1106&  RefAdafruit_SH1106);    
    ~My_OLED_DisplayClass(void);

    // Display screens
    void DisplayDataCall(CLK_interface_t* pTime);
};

#endif //_MY_DISPLAY_H