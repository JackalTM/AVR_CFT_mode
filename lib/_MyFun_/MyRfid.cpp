#include "MyRfid.h"

/******************************************************************************************************************************************************************
 * @name    MyRfidMenage 
 * @brief   Class constructor
 * @param   RefRfidClass Reference to Adafruit_PN532 global object
 * @param   refRfidOledData Reference to RFID_OLED_interface_t structure
 * @return  void
 * @note    This class use global defined class object for better code maitnance
*/
MyRfidMenageClass::MyRfidMenageClass(Adafruit_PN532& RefRfidClass):
    RefRfidClass(RefRfidClass)
{;}
//================================================================================================================================================================

/******************************************************************************************************************************************************************
 * @name    MyRfidMenage 
 * @brief   Class deconstructor
 * @param   void
 * @return  void
 * @note    void
*/
MyRfidMenageClass::~MyRfidMenageClass(void)
{;}
//================================================================================================================================================================

/******************************************************************************************************************************************************************
 * @name    _PrintOnSerialMonitor 
 * @brief   Print on serial monitor 
 * @param   inPagenumber
 * @return  void
 * @note    Private method
*/
void MyRfidMenageClass::_PrintOnSerialMonitor_ISO14443A_card(uint8_t inPagenumber)
{
    Serial.println("Found an ISO14443A card");
    Serial.print("  UID Length: ");     Serial.print(myRFID_TAG.uidLength, DEC);   Serial.println(" bytes");
    Serial.print("  UID Value: ");

    RefRfidClass.PrintHex((uint8_t*)(myRFID_TAG.uidArray), myRFID_TAG.uidLength);
    Serial.println("");

    Serial.print("PAGE "); Serial.print(inPagenumber); 
    RefRfidClass.PrintHexChar((uint8_t*)(myRFID_TAG.pageData), 4);
}
//================================================================================================================================================================

/******************************************************************************************************************************************************************
 * @name    _PrintOnSerialMonitor_NTAG2xx_content 
 * @brief   Print on serial monitor 
 * @param   inPagenumber
 * @return  void
 * @note    Private method
*/
void MyRfidMenageClass::_PrintOnSerialMonitor_NTAG2xx_content(uint8_t inPagenumber)
{   bool tBool;
    uint8_t i;
    uint8_t pData[32];
    for ( i = 0; i < NFC_PN532_MAX_PAGE_NUMBER; i++)
    {
        Serial.print("PAGE ");
        if (i < 10)
        { Serial.print("0");  Serial.print(i);}
        else
        { Serial.print(i);}

        Serial.print(": ");

        // Display the results, depending on 'success'
        if (tBool)
        { // Dump the page data
          RefRfidClass.PrintHexChar(pData, 4);}
        else
        { Serial.println("Unable to read the requested page!");}
    }
}
//================================================================================================================================================================

/******************************************************************************************************************************************************************
 * @name    ReadData 
 * @brief   Read data from RFID TAG
 * @param   inPageNumber Certaion page to fread from tag
 * @return  bool State if data was read from TAG
 * @note    This class use global defined class object for better code maitnance
*/
bool MyRfidMenageClass::ReadData(uint8_t pageNumber)
{
    bool     tBool;
    uint8_t* pData;

    tBool = RefRfidClass.readPassiveTargetID(PN532_MIFARE_ISO14443A, (uint8_t*)(myRFID_TAG.uidArray), (uint8_t*)&(myRFID_TAG.uidLength));

    if(tBool)
    {   _PrintOnSerialMonitor_ISO14443A_card(pageNumber);}
    else
    {   return tBool;}

    if(myRFID_TAG.uidLength == NFC_PN532_NTAG203_TAG)
    {   if((pageNumber >= 0x00) && (pageNumber <= NFC_PN532_MAX_PAGE_NUMBER))
        {   pData  = (uint8_t*)(myRFID_TAG.pageData);
            tBool = RefRfidClass.ntag2xx_ReadPage(pageNumber, pData);
            tBool = true;}
        else{;}
    }
    else
    {   tBool = false;}

    return tBool;
}
//================================================================================================================================================================