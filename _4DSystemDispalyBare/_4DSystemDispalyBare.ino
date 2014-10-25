//  Display.gfx_RectangleFilled(100,100, 200, 200, BLUE) ; 
//  gfx_Button(state, x, y, buttonColour, txtColour, font, txtWidth txtHeight, text)
//  Display.gfx_Slider(SLIDER_RAISED, 210, 100, 250,10, BLUE, 100, 50) ; // coordinates are different because we are in landscape mode
//  Display.gfx_ScreenMode(LANDSCAPE) ;
//  Display.touch_DetectRegion(100,100, 200, 200) ;
 //Display.gfx_MoveTo(30, 30);


#define DisplaySerial Serial1 
#define HWLOGGING Serial // Serial port for debugging
#define RESETLINE 4
#define TEXTWIDTH 3
#define TEXTHEIGHT 2
#define BUTTON_H 44
#define BUTTON_W 160
#define BUTTON_SMALL_W 36
#define PADDING 10

#include "Picaso_Serial_4DLib.h"
#include "Picaso_Const4D.h"

Picaso_Serial_4DLib Display(&DisplaySerial);

int x;
int y;
char cstr[20];
String str;
int rowadd = 3;
int coladd = 1;
unsigned int num = 0;

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
  Display.gfx_Cls();
  Display.gfx_ScreenMode(PORTRAIT) ;
  Display.putstr("Lunakhod loading...") ;
  HWLOGGING.begin(9600);
//  delay(5000); - uncomment in final
}

#define INIT_STATE 0
#define MOVE_STATE 1

int state = INIT_STATE;
void loop()
{
  Display.touch_Set(TOUCH_ENABLE) ;
  Display.touch_Set(TOUCH_REGIONDEFAULT) ;
  drawInitialScreen();



  while(1)
  {
    do {} while (Display.touch_Get(TOUCH_STATUS) != TOUCH_PRESSED);
    x = Display.touch_Get(TOUCH_GETX);                          // so we can get the first point
    y = Display.touch_Get(TOUCH_GETY);
    debugCoordinates();
    HWLOGGING.print("X="); 
    HWLOGGING.print(x);  
    HWLOGGING.print("; Y=");
    HWLOGGING.println(y);
    
    switch(state)
    { 
      case INIT_STATE:
        
        if(insideRegion(0, 1, x, y, BUTTON_W)) // MOVE
        {
          HWLOGGING.print("MOVE");       
          drawButton("MOVE", 0, 1,BUTTON_DOWN);
          state = MOVE_STATE;
          drawMoveScreen();
        }else if (insideRegion(0, 2, x, y, BUTTON_W)) // ROTATE
        {
           HWLOGGING.print("ROTATE");       
           drawButton("ROTATE", 0, 2, BUTTON_DOWN);
        }else if (insideRegion(0, 3, x, y, BUTTON_W)) // SHOOT
        {
           HWLOGGING.print("SHOOT");       
          drawButton("SHOOT", 0, 3, BUTTON_DOWN);
        }else if (insideRegion(0, 5, x, y, BUTTON_W)) // ERACE
        {
           HWLOGGING.print("ERACE");       
          drawButton("ERACE", 0, 5, BUTTON_DOWN);
        }
        break;
    
      case MOVE_STATE:
        if(insideRegion(0+coladd, 1+rowadd, x, y, BUTTON_SMALL_W)) // 1
        {
          add(1);
        }else if(insideRegion(1+coladd, 1+rowadd, x, y, BUTTON_SMALL_W)) // 2
        {
          add(2);
        }else if(insideRegion(2+coladd, 1+rowadd, x, y, BUTTON_SMALL_W)) // 3
        {
          add(3);
        }else if(insideRegion(0+coladd, 2+rowadd, x, y, BUTTON_SMALL_W)) // 4
        {
          add(4);
        }else if(insideRegion(1+coladd, 2+rowadd, x, y, BUTTON_SMALL_W)) // 5
        {
          add(5);
        }else if(insideRegion(2+coladd, 2+rowadd, x, y, BUTTON_SMALL_W)) // 6
        {
          add(6);
        }else if(insideRegion(0+coladd, 3+rowadd, x, y, BUTTON_SMALL_W)) // 7
        {
          add(7);
        }else if(insideRegion(1+coladd, 3+rowadd, x, y, BUTTON_SMALL_W)) // 8
        {
          add(8);
        }else if(insideRegion(2+coladd, 3+rowadd, x, y, BUTTON_SMALL_W)) // 9
        {
          add(9);
        }
        else if(insideRegion(1+coladd, 4+rowadd, x, y, BUTTON_SMALL_W)) // 0
        {
          add(0);
        }
        else if(insideRegion(0, 10, x, y, BUTTON_W)) // BACK
        {
          state = INIT_STATE;
          drawInitialScreen();
        } else if(insideRegion(1, 10, x, y, BUTTON_W)) // OK
        {
          //TODO: Save
          state = INIT_STATE;
          drawInitialScreen();
        }
        
      break;
    }
    
    
    
  }
//    Display.touch_Set(TOUCH_REGIONDEFAULT) ;
}

void add(int n)
{
  HWLOGGING.print(num);       
  num = num * 10 + n;
  drawNumber(); 
}

boolean insideRegion(int position_x, int position_y, int x, int y, int button_width)
{
  int x1 = PADDING * (position_x + 1) + position_x * button_width;
  int y1 = BUTTON_H * position_y;
  int x2 = PADDING * (position_x + 1) + button_width * (position_x + 1);
  int y2 = PADDING * (position_y + 1) + (BUTTON_H - 12) * (position_y + 1);
  Display.gfx_Rectangle(x1, y1, x2, y2, RED);
  Display.gfx_Rectangle(x1, y1,x1+5,y1+5, WHITE);
  
  Display.gfx_PutPixel(x, y, PINK);

  if(x < x1 || x > x2) return false;
  if(y < y1 || y > y2) return false;
  return true;
}

void drawNumber()
{
    str = String(num);
  str.toCharArray(cstr,16);  
 Display.gfx_MoveTo(50,100);
  
//  Display.txt_MoveCursor(1, 0);
//  Display.txt_FontID(FONT1);
//    Display.putstr(cstr) ;
//  Display.txt_MoveCursor(2, 0);
//  Display.txt_FontID(FONT2);
//    Display.putstr(cstr) ;
//  Display.txt_MoveCursor(3, 0);
  Display.txt_FontID(FONT3);

  Display.putstr(cstr) ;
//   Display.gfx_MoveTo(0,0);
}

void printint(int val)
{
  str = String(val);
  str.toCharArray(cstr,16);  
  Display.putstr(cstr) ;
}


void drawInitialScreen()
{
  Display.gfx_Cls();
  drawButton("MOVE",   0, 1, BUTTON_UP);
  drawButton("ROTATE", 0, 2, BUTTON_UP);
  drawButton("SHOOT",  0, 3, BUTTON_UP);
  drawButton("ERACE",  0, 5, BUTTON_UP);
}

void drawMoveScreen()
{
  Display.gfx_Cls();
  drawSmallButton("1", 0+coladd, 1+rowadd, BUTTON_UP);
  drawSmallButton("2", 1+coladd, 1+rowadd, BUTTON_UP);
  drawSmallButton("3", 2+coladd, 1+rowadd, BUTTON_UP);

  drawSmallButton("4", 0+coladd, 2+rowadd, BUTTON_UP);
  drawSmallButton("5", 1+coladd, 2+rowadd, BUTTON_UP);
  drawSmallButton("6", 2+coladd, 2+rowadd, BUTTON_UP);
  
  drawSmallButton("7", 0+coladd, 3+rowadd, BUTTON_UP);
  drawSmallButton("8", 1+coladd, 3+rowadd, BUTTON_UP);
  drawSmallButton("9", 2+coladd, 3+rowadd, BUTTON_UP);

  drawSmallButton("0", 1+coladd, 4+rowadd, BUTTON_UP);  
  drawButton("BACK", 0, 10, BUTTON_UP);
  drawButton("OK", 1, 10, BUTTON_UP);
}


void drawButton(char *text, unsigned int position_x, unsigned int position_y, int state)
{
  int x1 = PADDING * (position_x + 1) + position_x * BUTTON_W;
  int y1 = BUTTON_H * position_y;
  Display.gfx_Button(BUTTON_UP, x1, y1, ORANGE, WHITE, FONT3, TEXTWIDTH, TEXTHEIGHT, text);
}

void drawSmallButton(char *text, unsigned int position_x, unsigned int position_y, int state)
{
  int x1 = PADDING * (position_x + 1) + position_x * BUTTON_SMALL_W;
  int y1 = BUTTON_H * position_y;
  Display.gfx_Button(BUTTON_UP, x1, y1, ORANGE, WHITE, FONT3, TEXTWIDTH, TEXTHEIGHT, text);
}

void displayColors()
{
     //-------------Draw some buttons-------------------------
  Display.gfx_RectangleFilled(0,0,19,19,RED);           //
  Display.gfx_RectangleFilled(20,0,39,19,ORANGE);       //
  Display.gfx_RectangleFilled(40,0,59,19,YELLOW);       //
  Display.gfx_RectangleFilled(60,0,79,19,GREEN);        //
  Display.gfx_RectangleFilled(80,0,99,19,BLUE);         //
  Display.gfx_RectangleFilled(100,0,119,19,INDIGO);     //
  Display.gfx_RectangleFilled(120,0,139,19,PINK);       //
  Display.gfx_RectangleFilled(140,0,159,19,BROWN);      //
  Display.gfx_RectangleFilled(180,0,199,19,BLACK);      //
  Display.gfx_RectangleFilled(200,0,219,19,WHITE);      //
  Display.gfx_RectangleFilled(220,0,239,19,BLUE);    // display area for current color selection
  Display.gfx_Rectangle(260,0,279,19,RED);              //
  Display.gfx_Button(OFF,0,290,WHITE,RED,1,1,1,"Clear");   // I wish I how to use these buttons
}

void debugCoordinates()
{
  Display.txt_MoveCursor(1,0);
  printint(x);
  Display.txt_MoveCursor(2,0);
  printint(y);
}
