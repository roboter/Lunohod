// UTouch_ButtonTest (C)2010-2014 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a quick demo of how create and use buttons.
//
// This program requires the UTFT library.
//
// It is assumed that the display module is connected to an
// appropriate shield or that you know how to change the pin 
// numbers in the setup.
//

#include <UTFT.h>
#include <UTouch.h>

// Initialize display
// ------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Uno/2009 Shield            : <display model>,19,18,17,16
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Due       : <display model>,25,26,27,28
// Teensy 3.x TFT Test Board                   : <display model>,23,22, 3, 4
// ElecHouse TFT LCD/SD Shield for Arduino Due : <display model>,22,23,31,33
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(ITDB32WC,38,39,40,41);

// Initialize touchscreen
// ----------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Uno/2009 Shield            : 15,10,14, 9, 8
// Standard Arduino Mega/Due shield            :  6, 5, 4, 3, 2
// CTE TFT LCD/SD Shield for Arduino Due       :  6, 5, 4, 3, 2
// Teensy 3.x TFT Test Board                   : 26,31,27,28,29
// ElecHouse TFT LCD/SD Shield for Arduino Due : 25,26,27,29,30
//
UTouch  myTouch( 6, 5, 4, 3, 2);

// Declare which fonts we will be using
extern uint8_t BigFont[];

int botton_h = 60;
int botton_w = 230;
int padding = 5;
int text_space_h=25;
int text_space_w=45;
 
 
void drawButton(char *text, unsigned int position_x, unsigned int position_y)
{
  myGLCD.setColor(0, 0, 255); // blue
  int x1 = padding * (position_x + 1) + position_x * botton_h;
  int y1 = 240 - botton_w * position_y;
  int x2 = padding * (position_x + 1) + botton_h * (position_x + 1);
  int y2 = 240 - (padding * (position_y + 1)) - botton_w * (position_y + 1);
  myGLCD.fillRoundRect (x1, y1, x2, y2);
   
  myGLCD.setColor(255, 255, 255); //white
   
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  myGLCD.setColor(126, 255, 126); //
   
  myGLCD.setColor(126, 0, 126); //
   
  myGLCD.print(text, text_space_h+x1, y1-text_space_h, 270);
}

//void updateStr(int val)
//{
//  if (stCurrentLen<20)
//  {
//    stCurrent[stCurrentLen]=val;
//    stCurrent[stCurrentLen+1]='\0';
//    stCurrentLen++;
//    myGLCD.setColor(0, 255, 0);
//    myGLCD.print(stCurrent, LEFT, 224);
//  }
//  else
//  {
//    myGLCD.setColor(255, 0, 0);
//    myGLCD.print("BUFFER FULL!", CENTER, 192);
//    delay(500);
//    myGLCD.print("            ", CENTER, 192);
//    delay(500);
//    myGLCD.print("BUFFER FULL!", CENTER, 192);
//    delay(500);
//    myGLCD.print("            ", CENTER, 192);
//    myGLCD.setColor(0, 255, 0);
//  }
//}
//
//// Draw a red frame while a button is touched
//void waitForIt(int x1, int y1, int x2, int y2)
//{
//  myGLCD.setColor(255, 0, 0);
//  myGLCD.drawRoundRect (x1, y1, x2, y2);
//  while (myTouch.dataAvailable())
//    myTouch.read();
//  myGLCD.setColor(255, 255, 255);
//  myGLCD.drawRoundRect (x1, y1, x2, y2);
//}

/*************************
**  Required functions  **
*************************/

void setup()
{
// Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  drawButton("1 MOVE",0,0);
  drawButton("2 ROTATE",1,0);
  drawButton("3 SHOOT",2,0);

}



void loop()
{
  while (true)
  {
  }
}

