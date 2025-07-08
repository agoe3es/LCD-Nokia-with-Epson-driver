/****************************************************/
/* Example Program For LCD6610                      */
/* MCU      : Arduino Nano                          */
/* By       : Gravitech                             */
/* Function : Demo Interface LCD6610 (Epson driver) */ 
/****************************************************/
/* Interface LCD6610 to Arduino Nano                */
/*    Nano  --> LCD6610                             */
/*    D2    --> BL                                  */
/*    D3    --> #CS                                 */
/*    D4    --> SCLK                                */
/*    D5    --> SDATA                               */
/*    D6    --> #RESEET                             */
/*    +5V   --> VCC,VBL                             */
/*    GND   --> GND                                 */
/****************************************************/

#include <Arduino.h>
#include <NokiaLCD.h>

// Define Software SPI Pin Signal

#define BL 2          // Digital 2 --> BL
#define CS 3          // Digital 3 --> #CS
#define CLK 4         // Digital 4 --> SCLK
#define SDA 5         // Digital 5 --> SDATA
#define RESET 6       // Digital 6 --> #RESET


// Epson S1D15G10 Command Set 
#define DISON       0xaf
#define DISOFF      0xae
#define DISNOR      0xa6
#define DISINV      0xa7
#define COMSCN      0xbb
#define DISCTL      0xca
#define SLPIN       0x95
#define SLPOUT      0x94
#define PASET       0x75
#define CASET       0x15
#define DATCTL      0xbc
#define RGBSET8     0xce
#define RAMWR       0x5c
#define RAMRD       0x5d
#define PTLIN       0xa8
#define PTLOUT      0xa9
#define RMWIN       0xe0
#define RMWOUT      0xee
#define ASCSET      0xaa
#define SCSTART     0xab
#define OSCON       0xd1
#define OSCOFF      0xd2
#define PWRCTR      0x20
#define VOLCTR      0x81
#define VOLUP       0xd6
#define VOLDOWN     0xd7
#define TMPGRD      0x82
#define EPCTIN      0xcd
#define EPCOUT      0xcc
#define EPMWR       0xfc
#define EPMRD       0xfd
#define EPSRRD1     0x7c
#define EPSRRD2     0x7d
#define NOP         0x25

#define cbi(reg, bit) (reg&=~(1<<bit))
#define sbi(reg, bit) (reg|= (1<<bit))

#define CS0 cbi(PORTD,CS);
#define CS1 sbi(PORTD,CS);
#define CLK0 cbi(PORTD,CLK);
#define CLK1 sbi(PORTD,CLK);
#define SDA0 cbi(PORTD,SDA);
#define SDA1 sbi(PORTD,SDA);
#define RESET0 cbi(PORTD,RESET);
#define RESET1 sbi(PORTD,RESET);
#define BL0 cbi(PORTD,BL);
#define BL1 sbi(PORTD,BL);

byte const font[475] = {
0x00 , 0x00 , 0x00 , 0x00 , 0x00 ,
0x00 , 0x06 , 0x5F , 0x06 , 0x00 ,                      // !
0x07 , 0x03 , 0x00 , 0x07 , 0x03 ,                      // ,
0x24 , 0x7E , 0x24 , 0x7E , 0x24 ,                      // #
0x24 , 0x2B , 0x6A , 0x12 , 0x00 ,                      // $
0x63 , 0x13 , 0x08 , 0x64 , 0x63 ,                      // %
0x36 , 0x49 , 0x56 , 0x20 , 0x50 ,                      // &
0x00 , 0x07 , 0x03 , 0x00 , 0x00 ,                      // //
0x00 , 0x3E , 0x41 , 0x00 , 0x00 ,                      // (
0x00 , 0x41 , 0x3E , 0x00 , 0x00 ,                      // )
0x08 , 0x3E , 0x1C , 0x3E , 0x08 ,                      // *
0x08 , 0x08 , 0x3E , 0x08 , 0x08 ,                      // +
0x00 , 0xE0 , 0x60 , 0x00 , 0x00 ,                      // ,
0x08 , 0x08 , 0x08 , 0x08 , 0x08 ,                      // -
0x00 , 0x60 , 0x60 , 0x00 , 0x00 ,                      // .
0x20 , 0x10 , 0x08 , 0x04 , 0x02 ,                      // /
0x3E , 0x51 , 0x49 , 0x45 , 0x3E ,                      // 0
0x00 , 0x42 , 0x7F , 0x40 , 0x00 ,                      // 1
0x62 , 0x51 , 0x49 , 0x49 , 0x46 ,                      // 2
0x22 , 0x49 , 0x49 , 0x49 , 0x36 ,                      // 3
0x18 , 0x14 , 0x12 , 0x7F , 0x10 ,                      // 4
0x2F , 0x49 , 0x49 , 0x49 , 0x31 ,                      // 5
0x3C , 0x4A , 0x49 , 0x49 , 0x30 ,                      // 6
0x01 , 0x71 , 0x09 , 0x05 , 0x03 ,                      // 7
0x36 , 0x49 , 0x49 , 0x49 , 0x36 ,                      // 8
0x06 , 0x49 , 0x49 , 0x29 , 0x1E ,                      // 9
0x00 , 0x6C , 0x6C , 0x00 , 0x00 ,                      // :
0x00 , 0xEC , 0x6C , 0x00 , 0x00 ,                      // ;
0x08 , 0x14 , 0x22 , 0x41 , 0x00 ,                      // <
0x24 , 0x24 , 0x24 , 0x24 , 0x24 ,                      // =
0x00 , 0x41 , 0x22 , 0x14 , 0x08 ,                      // >
0x02 , 0x01 , 0x59 , 0x09 , 0x06 ,                      // ?
0x3E , 0x41 , 0x5D , 0x55 , 0x1E ,                      // @
0x7E , 0x09 , 0x09 , 0x09 , 0x7E ,                      // A
0x7F , 0x49 , 0x49 , 0x49 , 0x36 ,                      // B
0x3E , 0x41 , 0x41 , 0x41 , 0x22 ,                      // C
0x7F , 0x41 , 0x41 , 0x41 , 0x3E ,                      // D
0x7F , 0x49 , 0x49 , 0x49 , 0x41 ,                      // E
0x7F , 0x09 , 0x09 , 0x09 , 0x01 ,                      // F
0x3E , 0x41 , 0x49 , 0x49 , 0x7A ,                      // G
0x7F , 0x08 , 0x08 , 0x08 , 0x7F ,                      // H
0x00 , 0x41 , 0x7F , 0x41 , 0x00 ,                      // I
0x30 , 0x40 , 0x40 , 0x40 , 0x3F ,                      // J
0x7F , 0x08 , 0x14 , 0x22 , 0x41 ,                      // K
0x7F , 0x40 , 0x40 , 0x40 , 0x40 ,                      // L
0x7F , 0x02 , 0x04 , 0x02 , 0x7F ,                      // M
0x7F , 0x02 , 0x04 , 0x08 , 0x7F ,                      // N
0x3E , 0x41 , 0x41 , 0x41 , 0x3E ,                      // O
0x7F , 0x09 , 0x09 , 0x09 , 0x06 ,                      // P
0x3E , 0x41 , 0x51 , 0x21 , 0x5E ,                      // Q
0x7F , 0x09 , 0x09 , 0x19 , 0x66 ,                      // R
0x26 , 0x49 , 0x49 , 0x49 , 0x32 ,                      // S
0x01 , 0x01 , 0x7F , 0x01 , 0x01 ,                      // T
0x3F , 0x40 , 0x40 , 0x40 , 0x3F ,                      // U
0x1F , 0x20 , 0x40 , 0x20 , 0x1F ,                      // V
0x3F , 0x40 , 0x3C , 0x40 , 0x3F ,                      // W
0x63 , 0x14 , 0x08 , 0x14 , 0x63 ,                      // X
0x07 , 0x08 , 0x70 , 0x08 , 0x07 ,                      // Y
0x71 , 0x49 , 0x45 , 0x43 , 0x00 ,                      // Z
0x00 , 0x7F , 0x41 , 0x41 , 0x00 ,                      // [
0x02 , 0x04 , 0x08 , 0x10 , 0x20 ,                      // Back slash
0x00 , 0x41 , 0x41 , 0x7F , 0x00 ,                      // ]
0x04 , 0x02 , 0x01 , 0x02 , 0x04 ,                      // ^
0x80 , 0x80 , 0x80 , 0x80 , 0x80 ,                      // _
0x00 , 0x03 , 0x07 , 0x00 , 0x00 ,                      // `
0x20 , 0x54 , 0x54 , 0x54 , 0x78 ,                      // a
0x7F , 0x44 , 0x44 , 0x44 , 0x38 ,                      // b
0x38 , 0x44 , 0x44 , 0x44 , 0x28 ,                      // c
0x38 , 0x44 , 0x44 , 0x44 , 0x7F ,                      // d
0x38 , 0x54 , 0x54 , 0x54 , 0x18 ,                      // e
0x08 , 0x7E , 0x09 , 0x09 , 0x00 ,                      // f
0x18 , 0xA4 , 0xA4 , 0xA4 , 0x7C ,                      // g
0x7F , 0x04 , 0x04 , 0x78 , 0x00 ,                      // h
0x00 , 0x00 , 0x7D , 0x00 , 0x00 ,                      // i
0x40 , 0x80 , 0x84 , 0x7D , 0x00 ,                      // j
0x7F , 0x10 , 0x28 , 0x44 , 0x00 ,                      // k
0x00 , 0x00 , 0x7F , 0x40 , 0x00 ,                      // l
0x7C , 0x04 , 0x18 , 0x04 , 0x78 ,                      // m
0x7C , 0x04 , 0x04 , 0x78 , 0x00 ,                      // n
0x38 , 0x44 , 0x44 , 0x44 , 0x38 ,                      // o
0xFC , 0x44 , 0x44 , 0x44 , 0x38 ,                      // p
0x38 , 0x44 , 0x44 , 0x44 , 0xFC ,                      // q
0x44 , 0x78 , 0x44 , 0x04 , 0x08 ,                      // r
0x08 , 0x54 , 0x54 , 0x54 , 0x20 ,                      // s
0x04 , 0x3E , 0x44 , 0x24 , 0x00 ,                      // t
0x3C , 0x40 , 0x20 , 0x7C , 0x00 ,                      // u
0x1C , 0x20 , 0x40 , 0x20 , 0x1C ,                      // v
0x3C , 0x60 , 0x30 , 0x60 , 0x3C ,                      // w
0x6C , 0x10 , 0x10 , 0x6C , 0x00 ,                      // x
0x9C , 0xA0 , 0x60 , 0x3C , 0x00 ,                      // y
0x64 , 0x54 , 0x54 , 0x4C , 0x00 ,                      // z
0x08 , 0x3E , 0x41 , 0x41 , 0x00 ,                      // {
0x00 , 0x00 , 0x7F , 0x00 , 0x00 ,                      // |
0x00 , 0x41 , 0x41 , 0x3E , 0x08 ,                      // }
0x02 , 0x01 , 0x02 , 0x01 , 0x00                        // ~
};

/*************************************************************/
/*            Function prototypes                            */
/*************************************************************/

//void shiftBits(byte);
//void LCD_put_pixel(byte, byte, byte);
//void sendData(byte);
//void sendCMD(byte);

/*************************************************************/
/*            Function definitions                           */
/*************************************************************/

/**************************************/
/*        Shifting SPI bit out        */
/**************************************/
void NokiaLCD::shiftBits(byte b) 
{
  CLK0
  if ((b&128)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&64)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&32)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&16)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&8)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&4)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&2)!=0) SDA1 else SDA0
  CLK1

  CLK0
  if ((b&1)!=0) SDA1 else SDA0
  CLK1
}

/**************************************/
/*        Put pixel to LCD            */
/**************************************/

void NokiaLCD::put_pixel(byte color, byte x, byte y)
{
  sendCMD(CASET);   // page start/end ram
  sendData(x);      // for some reason starts at 2
  sendData(x+1);

  sendCMD(PASET);   // column start/end ram
  sendData(y);
  sendData(y+1);
  sendCMD(RAMWR);
  sendData(color);
}

/**************************************/
/*        Sending data                */
/**************************************/
void NokiaLCD::sendData(byte data) {
  CLK1
  CS1
  CS0

  CLK0
  SDA1                  
  CLK1

  shiftBits(data);
}

/**************************************/
/*        Sending command             */
/**************************************/
void NokiaLCD::sendCMD(byte data) {

  CLK1
  CS1
  CS0

  CLK0
  SDA0
  CLK1

  shiftBits(data);

}

void NokiaLCD::set_box(byte x1, byte y1, byte x2, byte y2)
{
  sendCMD(CASET);   // page start/end ram
  sendData(x1);     // for some reason starts at 2
  sendData(x2);

  sendCMD(PASET);   // column start/end ram
  sendData(y1);
  sendData(y2);
}

void NokiaLCD::rect(byte color, byte x1, byte y1, byte x2, byte y2)
{
  uint16_t i;
  uint16_t total_bytes1;
  uint16_t total_bytes2;
  uint16_t total_bytes;

  lcd_set_box(x1, y1, x2, y2);

  sendCMD(RAMWR);
  total_bytes1 = (x2 - x1 + 1); 
  total_bytes2 = (y2 - y1 + 1);
  total_bytes = total_bytes1 * total_bytes2;
  for (i = 0; i < total_bytes; i++){
    sendData(color);
  }
}

void NokiaLCD::init()
{
  // Hardware Reset LCD
  RESET0
  delay(10);
  RESET1

  // Initial state
  CS1
  SDA1
  CLK1

  // Display control
  sendCMD(DISCTL);
  sendData(0x03); 		// 2 divisions, Field swithcing period
  sendData(32);   		// 132 lines to be display
  sendData(12);   		// Inversely hightlighted lines - 1
  sendData(0);

  sendCMD(COMSCN);  	// comscn
  sendData(0x01);

  sendCMD(OSCON);  		// oscon

  sendCMD(SLPOUT);  	// sleep out

  sendCMD(VOLCTR);  	// electronic volume, this is kinda contrast/brightness
  sendData(0x24);       // this might be different for individual LCDs
  sendData(0x03);    

  sendCMD(PWRCTR);  	// power ctrl
  sendData(0x0f);      	// everything on, no external reference resistors
  delay(100);

  sendCMD(DISINV);  	// display mode

  sendCMD(DATCTL);  	// datctl
  sendData(0x00);
  sendData(0);
  sendData(0x01);
  sendData(0);

  sendCMD(RGBSET8);   	// setup color lookup table
    // color table

	sendData(0);
    sendData(2);
    sendData(4);
    sendData(6);
    sendData(8);
    sendData(10);
    sendData(12);
    sendData(15);
    // GREEN
    sendData(0);
    sendData(2);
    sendData(4);
    sendData(6);
    sendData(8);
    sendData(10);
    sendData(12);
    sendData(15);
    //BLUE
    sendData(0);
    sendData(4);
    sendData(9);
    sendData(15);

    sendCMD(NOP);
    clear(0xff);
    sendCMD(DISON);    // display on

   //for (i = 0; i < 150; i++){   // this loop adjusts the contrast, change the number of iterations to get
   //   sendCMD(VOLUP);           // desired contrast.  This might be different for individual LCDs
   //   delay_ms(2);
   //}
}

void NokiaLCD::draw_color_bar()
{
  rect(RED,0,0,131,33);
  rect(GREEN,0,34,131,66);
  rect(BLUE,0,67,131,99);
  rect(WHITE,0,100,131,131);
}

void NokiaLCD::draw_text_line(byte fcolor, byte bcolor,byte x, byte y,char c)
{
  unsigned int i;
  lcd_set_box(x,y,x,y+7);
  sendCMD(RAMWR);
  for(i=0;i<8;i++)
  {
    if (1<<i & c)
      sendData(fcolor);
    else
      sendData(bcolor);
  }
}

void NokiaLCD::draw_text(byte fcolor, byte bcolor, byte x, byte y,char *text)
{
  byte c;
  byte t;
  unsigned int i;
  unsigned int j;
  while(*text != 0)
   {
     t = *text;
     i = t - 32;
     i = i * 5;
     for(j = i; j < i+5; j++)
     {
       c = font[j];
       draw_text_line(fcolor, bcolor, x++, y, c);
     }
     draw_text_line(fcolor, bcolor, x++, y, 0);
     text++;
   }
}

void NokiaLCD::clear(byte color)
{
 rect(color,0,0,131,131)
}
