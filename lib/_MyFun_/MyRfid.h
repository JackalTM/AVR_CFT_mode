/**************************************************************************/
/*!
    @file     readntag203.pde
    @author   WZ    KTOWN (Adafruit Industries)
    @license  BSD (see license.txt)

    This application is using Adafruit libraries for educational purpose
*/
/**************************************************************************/

  // NTAG2x3 cards have 39*4 bytes of user pages (156 user bytes),
      // starting at page 4 ... larger cards just add pages to the end of
      // this range:

      // See: http://www.nxp.com/documents/short_data_sheet/NTAG203_SDS.pdf

      // TAG Type       PAGES   USER START    USER STOP
      // --------       -----   ----------    ---------
      // NTAG 203       42      4             39
      // NTAG 213       45      4             39k

      // NTAG 215       135     4             129
      // NTAG 216       231     4             225

#include "stdint.h"
#include "Arduino.h"
#include "MyInterface.h"
#include <Adafruit_PN532.h>

#ifndef _MY_RFID_H
#define _MY_RFID_H

#define MYRFID_DISPALY_DATA_SERIAL
class MyRfidMenageClass
{
private:
    // References for global object
    Adafruit_PN532&         RefRfidClass;
    RFID_interface_t        myRFID_TAG;

    void _PrintOnSerialMonitor_ISO14443A_card(uint8_t inPagenumber);
    void _PrintOnSerialMonitor_NTAG2xx_content(uint8_t inPagenumber);

    bool CheckTagType(void);
public:
    MyRfidMenageClass(Adafruit_PN532& RefRfidClass);
    ~MyRfidMenageClass(void);

    bool ReadData(uint8_t pageNumber);
    void WriteData(uint8_t pageNumber);
};

#endif // _MY_RFID_H