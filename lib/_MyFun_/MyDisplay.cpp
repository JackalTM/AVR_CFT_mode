#include "MyDisplay.h"

/********************************************************************************************************************************************
   @brief   Class constructor
   @param   RefAdafruit_SH1106 Reference to OLED display class
   @param   refRfidOledData Reference to RFID => OLED interface 
   @note    This class is conected to intialized Adafruit_SH1106 object
*/
//My_OLED_DisplayClass::My_OLED_DisplayClass(Adafruit_SH1106& inRefAdafruit_SH1106, RFID_OLED_interface_t& inRefRfidOledData):
//RefAdafruit_SH1106(inRefAdafruit_SH1106),
//RefRfidOledData(inRefRfidOledData)
My_OLED_DisplayClass::My_OLED_DisplayClass(Adafruit_SH1106&  RefAdafruit_SH1106):
   RefAdafruit_SH1106(RefAdafruit_SH1106)
{
   i = 0;
}
//===========================================================================================================================================

/********************************************************************************************************************************************
   @brief   Class deconstructor
   @param   void
   @note    This class is conected to intialized Adafruit_SH1106 object
*/
My_OLED_DisplayClass::~My_OLED_DisplayClass(void)
{;}
//===========================================================================================================================================

/********************************************************************************************************************************************
 * @name    _DisplayString(const String &pSTR, uint8_t sectorX, uint8_t sectorY)
   @brief   Display certain string data in certain data sector
   @param   pSTR String constant
   @param   sectorX Sector for x cordinate
   @param   sectorY Sector for y cordinate
   @note    This class is conected to intialized Adafruit_SH1106 object
   @return  void
*/
void My_OLED_DisplayClass::_DisplayString(const String &pSTR, uint8_t sectorX, uint8_t sectorY)
{
   sectorX = MY_DISPLAY_MAX_CHARS_IN_X(sectorX) + 1;
   sectorY = MY_DISPLAY_MAX_CHARS_IN_Y(sectorY) + 1;

   RefAdafruit_SH1106.setCursor(sectorX, sectorY) ;
   RefAdafruit_SH1106.print(pSTR);
}
//===========================================================================================================================================

/********************************************************************************************************************************************
 * @name    _DisplayIneger(uint8_t data)
   @brief   Display certain string data
   @param   pSTR String constant
   @note    This class is conected to intialized Adafruit_SH1106 object
   @return
*/
void My_OLED_DisplayClass::_DisplayIneger(uint8_t data, uint8_t sectorX, uint8_t sectorY)
{
   sectorX = MY_DISPLAY_MAX_CHARS_IN_X(sectorX) + 1;
   sectorY = MY_DISPLAY_MAX_CHARS_IN_Y(sectorY) + 1;

   RefAdafruit_SH1106.setCursor(sectorX, sectorY) ;
   RefAdafruit_SH1106.print(data);
}
//===========================================================================================================================================

/********************************************************************************************************************************************
 * @name    _DisplayTime(void)
   @brief   Display time 
   @param   void
   @note    This class is conected to intialized Adafruit_SH1106 object
   @return
*/
void My_OLED_DisplayClass::_NumberToString(uint8_t number, char* pSTR)
{
   if(number <= 9)
   {
      *(pSTR + 0x00) = '0';
      *(pSTR + 0x01) = number + 0x30;
   }
   else if((number >= 10) && (number <= 99))
   {
      *(pSTR + 0x00) = (number / 10) + 0x30;
      *(pSTR + 0x01) = (number % 10) + 0x30;
   }
   else
   {
      *(pSTR + 0x00) = 0x30;
      *(pSTR + 0x01) = 0x30;
   }
}
void My_OLED_DisplayClass::_DisplayTimeShort(CLK_interface_t* pTime, uint8_t sectorX, uint8_t sectorY)
{
   char tSTR[6];

   _NumberToString(pTime->minute, &(tSTR[0]));
   tSTR[2] = ':';
   _NumberToString(pTime->second, &(tSTR[3]));
   tSTR[5] = '\0';

   sectorX = MY_DISPLAY_MAX_CHARS_IN_X(sectorX) + 1;
   sectorY = MY_DISPLAY_MAX_CHARS_IN_Y(sectorY) + 1;

   //RefAdafruit_SH1106.setCursor(sectorX, sectorY) ;
   RefAdafruit_SH1106.println(tSTR);
}
void My_OLED_DisplayClass::_DisplayTimeFULL(CLK_interface_t* pTime, uint8_t sectorX, uint8_t sectorY)
{
   char tSTR[9];

   _NumberToString(pTime->hour, &(tSTR[0]));
   tSTR[2] = ':';
   _NumberToString(pTime->minute, &(tSTR[3]));
   tSTR[5] = ':';
   _NumberToString(pTime->second, &(tSTR[6]));
   tSTR[8] = '\0';

   sectorX = MY_DISPLAY_MAX_CHARS_IN_X(sectorX) + 1;
   sectorY = MY_DISPLAY_MAX_CHARS_IN_Y(sectorY) + 1;

   //RefAdafruit_SH1106.setCursor(sectorX, sectorY) ;
   RefAdafruit_SH1106.println(tSTR);
}

/********************************************************************************************************************************************
 * @name    DisplayData
   @brief   Display certain data
   @param   inData Data to display
   @note    This class is conected to intialized Adafruit_SH1106 object
   @return
*/
void My_OLED_DisplayClass::DisplayDataCall(CLK_interface_t* pTime)
{
   RefAdafruit_SH1106.clearDisplay();
   RefAdafruit_SH1106.setTextSize(2);
   RefAdafruit_SH1106.setTextColor(WHITE);
   RefAdafruit_SH1106.setCursor(0,0);

   _DisplayString(MY_DISPLAY_STR_TICKETS, 0, 0);

   _DisplayString(MY_DISPLAY_STR_RED, 0, 2);    _DisplayTimeShort(pTime, 0, 2);
   _DisplayString(MY_DISPLAY_STR_BLU, 0, 4);    _DisplayTimeShort(pTime, 0, 4);  

   RefAdafruit_SH1106.display();
}
//===========================================================================================================================================