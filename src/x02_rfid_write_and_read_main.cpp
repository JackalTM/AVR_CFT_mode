/**************************************************************************/
/*!
    @file     readntag203.pde
    @author   KTOWN (Adafruit Industries)
    @license  BSD (see license.txt)

    This example will wait for any NTAG203 or NTAG213 card or tag,
    and will attempt to read from it.

    This is an example sketch for the Adafruit PN532 NFC/RFID breakout boards
    This library works with the Adafruit NFC breakout
      ----> https://www.adafruit.com/products/364

    Check out the links above for our tutorials and wiring diagrams
    These chips use SPI or I2C to communicate.

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!
*/
/**************************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include "MyInterface.h"
#include "MyRfid.h"
#include "MyDisplay.h"
#include "ISRConfig.h"

// Use this line for a breakout with a hardware SPI connection.  Note that
// the PN532 SCK, MOSI, and MISO pins need to be connected to the Arduino's
// hardware SPI SCK, MOSI, and MISO pins.  On an Arduino Uno these are
// SCK = 13, MISO = 12,  MOSI = 11, 10 = SS.  The SS line can be any digital IO pin.
#define PN532_SCK   13
#define PN532_MISO  12
#define PN532_MOSI  11
#define PN532_SS    10
Adafruit_PN532 NfcPn532(PN532_SS);

// Global interface for display and reading data
RFID_OLED_interface_t rfidOledInterface;
interruptControl_t    irqControl;

// Interface structure between Adafruit_PN532 and Adafruit_SH1106
MyRfidMenageClass MyRfidMenage(NfcPn532, rfidOledInterface);    

uint8_t i;

void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) { delay(100);} // for Leonardo/Micro/Zero

  Serial.println("Setup started...");

  NfcPn532.begin();

  uint32_t versiondata = NfcPn532.getFirmwareVersion();
  if (versiondata == 0x0) 
  { // RFID board not found
    Serial.print("Didn't find PN53x board");
    Serial.print("Error during initialization");
    while(true) {;} // halt
  }
  else
  { // Module PN532 is working correctly!
    Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
    Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
    Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

    Serial.println("Setup sucessfull!");
    Serial.println("Waiting for an ISO14443A Card ...");
  }

  SetupTimerT2(0x00, MYCFG_TIMER_MODE_NORMAL, MYCFG_TIMER_PRESCALER_1024x);

  i=0;
}

void loop(void) 
{
  MyRfidMenage.ReadData( i );
  i++;

  // Wait a bit before trying again
  Serial.println("\n\nSend a character to scan another tag!");
  Serial.flush();
  while (!Serial.available());
  while (Serial.available())  { Serial.read();}
  Serial.flush();
}


ISR(TIMER2_OVF_vect)
{
  ;
}
