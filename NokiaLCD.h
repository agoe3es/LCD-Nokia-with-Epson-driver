/*
  NokiaLCD.h - Library for a Nokia LCD with the epson driver.
  Created by Thomas Jespersen, July 2009 (Originally Arduino Sketch by Gravitech.us)
*/

#ifndef NokiaLCD_h
#define NokiaLCD_h

//a few basic colors
#define RED			0xE0
#define GREEN			0x1C
#define BLUE			0x03
#define YELLOW			0xFC
#define MAGENTA			0xE3
#define CYAN			0x1F
#define BLACK			0x00
#define WHITE			0xFF

#include "Arduino.h"

class NokiaLCD
{
  public:
    void init();
    void draw_color_bar();
	
    void clear(byte color);
    void draw_text_line(byte fcolor, byte bcolor,byte x, byte y,char c);
    void rect(byte color, byte x1, byte y1, byte x2, byte y2);
	void draw_text(byte fcolor, byte bcolor, byte x, byte y,char *text);
	void put_pixel(byte color, byte x, byte y);
	void set_box(byte x1, byte y1, byte x2, byte y2);
	
  private:
    void shiftBits(byte b);
    void sendData(byte data);
    void sendCMD(byte data);
	
};

#endif
