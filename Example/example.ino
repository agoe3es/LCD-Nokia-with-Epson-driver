#include <NokiaLCD.h>
NokiaLCD lcd;

void setup() 
{ 
  DDRD |= B01111100;   // Set SPI pins as output 
  PORTD |= B01111100;  // Set SPI pins HIGH
  lcd.init();
  delay(500);
} 
 
void loop() 
{
 char text [50];

 lcd.draw_color_bar();
 
 delay(2000);
 lcd.clear(BLACK);
   
 strcpy(text," LCD6610");
 lcd.draw_text(YELLOW, BLACK, 35, 5, text);
 strcpy(text," 132X132");
 lcd.draw_text(CYAN, BLACK, 35, 15, text);
 strcpy(text," Color Graphic LCD");
 lcd.draw_text(CYAN, BLACK, 3, 23, text);
 strcpy(text,"WWW.GRAVITECH.US");
 lcd.draw_text(RED, WHITE, 12, 33, text);
 strcpy(text," TEST GREEN COLOR ");
 lcd.draw_text(GREEN, BLACK, 7, 45, text);
 strcpy(text," TEST BLUE COLOR ");
 lcd.draw_text(BLUE, BLACK, 7, 60, text);
 strcpy(text," TEST WHITE COLOR ");
 lcd.draw_text(WHITE, BLACK, 7, 75, text);
 strcpy(text," TEST MAGENTA COLOR ");
 lcd.draw_text(MAGENTA, BLACK, 7, 90, text);
 strcpy(text," TEST CYAN COLOR ");
 lcd.draw_text(CYAN, BLACK, 7, 105, text);
 strcpy(text," TEST YELLOW COLOR ");
 lcd.draw_text(YELLOW, BLACK, 7, 120, text);
 
 delay(2000);
 lcd.clear(BLACK);
} 
