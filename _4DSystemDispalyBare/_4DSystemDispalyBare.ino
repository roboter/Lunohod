#define DisplaySerial Serial
#define RESETLINE 4

#include "Picaso_Serial_4DLib.h"

#include "Picaso_Const4D.h"

Picaso_Serial_4DLib Display(&DisplaySerial);

void setup()
{
  
  pinMode(13,OUTPUT);
  pinMode(RESETLINE, OUTPUT);  // Set D4 on Arduino to Output (4D Arduino Adaptor V2 - Display Reset)
  digitalWrite(RESETLINE, 1);  // Reset the Display via D4
  delay(100);
  digitalWrite(RESETLINE, 0);  // unReset the Display via D4
  delay(5000);
  DisplaySerial.begin(9600) ;
  Display.TimeLimit4D   = 5000 ; // 5 second timeout on all commands
  Display.gfx_Cls() ;
  Display.gfx_ScreenMode(LANDSCAPE) ;
  Display.putstr("Lunakhod loading...") ;
//  Serial.begin(9600);
}

int x;
int y;
char cstr[20] ;
String str;
void loop()
{
  Display.touch_Set(TOUCH_ENABLE) ;
 // Display.touch_DetectRegion(100,100, 200, 200) ;
  Display.touch_Set(TOUCH_REGIONDEFAULT) ;
 // Display.gfx_RectangleFilled(100,100, 200, 200, BLUE) ; 
   //-------------Draw some buttons-------------------------
//  Display.gfx_RectangleFilled(0,0,19,19,RED);           //
//  Display.gfx_RectangleFilled(20,0,39,19,ORANGE);       //
//  Display.gfx_RectangleFilled(40,0,59,19,YELLOW);       //
//  Display.gfx_RectangleFilled(60,0,79,19,GREEN);        //
//  Display.gfx_RectangleFilled(80,0,99,19,BLUE);         //
//  Display.gfx_RectangleFilled(100,0,119,19,INDIGO);     //
//  Display.gfx_RectangleFilled(120,0,139,19,PINK);       //
//  Display.gfx_RectangleFilled(140,0,159,19,BROWN);      //
//  Display.gfx_RectangleFilled(180,0,199,19,BLACK);      //
//  Display.gfx_RectangleFilled(200,0,219,19,WHITE);      //
//  Display.gfx_RectangleFilled(220,0,239,19,BLUE);    // display area for current color selection
//  Display.gfx_Rectangle(260,0,279,19,RED);              //
  //Display.gfx_Button(OFF,290,0,WHITE,RED,1,1,1,"Clear");   // I wish I how to use these buttons
  //-------------------------------------------------------
  
  do {} while (Display.touch_Get(TOUCH_STATUS) != TOUCH_PRESSED);
  x = Display.touch_Get(TOUCH_GETX);                          // so we can get the first point
  y = Display.touch_Get(TOUCH_GETY);
  Display.txt_MoveCursor(1,0);
  printint(x);
  Display.txt_MoveCursor(2,0);
  printint(y);
//  Display.putstr(cstr) ;
//  Display.println(cstr) ;
//  Serial.print("X="); 
//  Serial.print(x);  
//  Serial.print("; Y=");
//  Serial.println(y);
  Display.touch_Set(TOUCH_REGIONDEFAULT) ;
}
void printint(int val)
{
  str = String(val);
  str.toCharArray(cstr,16);
  
  Display.putstr(cstr) ;
}
