/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

/*********************************************************************
I change the adafruit SSD1306 to SH1106

SH1106 driver don't provide several functions such as scroll commands.

*********************************************************************/

#include "stdint.h"
#include "MyInterface.h"
#include "ISRConfig.h"
#include "MyDisplay.h"
#include "MyRfid.h"
#include "UniversalFuns.h"

#define OLED_RESET 4
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

/***************************************************************************************************
 * Library objects inicialization
*/
Adafruit_SH1106         Display(OLED_RESET); // Adafrut object initialization and its inheritances

/***************************************************************************************************
 * Myc custom objects initialization
*/
CLK_interface_t         time;
My_OLED_DisplayClass    OledDisplay(Display); // Class wraper for Adafruit_SH1106

uint8_t counter;
bool printData;
uint8_t intdata;

void IncreaseTimeAmountBy(CLK_interface_t* pTime)
{
    pTime.second++;
    if(pTime.second >= 60)
    {
      pTime.second = 0;
      pTime.minute++;
    }else{;}

    if(pTime.minute >= 60)
    {
      pTime.minute = 0;
      pTime.hour++;
    }else{;}

    if(pTime.hour >= 12)
    {
      pTime.hour = 0;
    }else{;}
}

void setup()   
{       
  Serial.begin(9600);
  ///while (!Serial) delay(10); // for Leonardo/Micro/Zero
  //Serial.println("Hello!");

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  Display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  Display.clearDisplay();

  printData = false;
  time.hour = 0;
  time.minute = 0;
  time.second = 0;

  SetupTimerT2(0x00, MYCFG_TIMER_MODE_NORMAL, MYCFG_TIMER_PRESCALER_1024x);
}

void loop() 
{
  if(printData == true)
  {
    IncreaseTimeAmountBy(&time);

    OledDisplay.DisplayDataCall(&time);
    //Serial.print("DEBUG PRINT: ");
    //Serial.println(time.second);
  }
  else{;}
}

ISR(TIMER2_OVF_vect)
{ 
  if(counter <= 0xFE)
  { counter++;}
  else
  { counter  = 0x00;
    printData = true;}
}