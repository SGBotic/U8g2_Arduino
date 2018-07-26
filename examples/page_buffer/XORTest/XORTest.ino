/*

  XORTest.ino
  
  Shows solid and transparent font modes with XOR draw.
  Conclusion: Only use transparent font modes with XOR draw.
  This example also demonstrates scrolling.

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


/*
  U8glib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
  This is a page buffer example.    
*/U8G2_SSD1327_EA_W128128_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void testXOR(uint8_t x)
{
  u8g2.setFont(u8g2_font_ncenB14_tr);
  //u8g2.setFont(u8g2_font_courB24_tn);
  
  u8g2.firstPage();
  do {
    /* Solid font mode with XOR drawing: Does not make much sense */
    u8g2.setFontMode(0);
    u8g2.setDrawColor(1);
    u8g2.drawBox(10, 8, 10, 10);
    u8g2.drawBox(40, 20, 30, 12);
    u8g2.drawBox(100, 8, 4, 22);
    
    u8g2.setDrawColor(2);
    u8g2.drawStr(x,26, "XOR Test");
    u8g2.drawHLine(0, 29, 128);
    
    /* Transparent font mode with XOR drawing: looks good */
    u8g2.setFontMode(1);
    u8g2.setDrawColor(1);
    u8g2.drawBox(10, 8+32, 10, 10);
    u8g2.drawBox(40, 20+32, 30, 12);
    u8g2.drawBox(100, 8+32, 4, 22);
    u8g2.setDrawColor(2);
    u8g2.drawStr(x,26+32, "XOR Test");
    u8g2.drawHLine(0, 29+32, 128);


  } while ( u8g2.nextPage() );
}


void setup(void) {

  /* U8g2 Project: SSD1306 Test Board */
  //pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);
  //digitalWrite(10, 0);
  //digitalWrite(9, 0);		

  /* U8g2 Project: T6963 Test Board */
  //pinMode(18, OUTPUT);
  //digitalWrite(18, 1);	
  
  u8g2.begin();  
}



void loop(void) {
  uint8_t i;
  i = 20;
  do
  {
    testXOR(20-i);
    delay(15);
    i--;
  } while( i != 0 );
  i = 20;
  delay(15);
  do
  {
    testXOR(i);
    delay(15);
    i--;
  } while( i != 0 );
  delay(15);
}

