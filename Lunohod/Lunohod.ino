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

#include <Keypad.h>
#include <UTFT.h>
//#include <UTouch.h>
#include "pitches.h"

#define ASCII_KEY 0x30

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

int tonePin =8;
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'A','3','2','1',},
  {'B','6','5','4'},
  {'C','9','8','7'},
  {'D','*','0','#'}
};


// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 14, 15, 16, 17 };
// Connect keypad COL0, COL2, COL3 and COL4 to these Arduino pins.
byte colPins[COLS] = { 18, 19, 20, 21 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const int analogInPinX = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPinY = A1;  // Analog input pin that the potentiometer is attached to

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
//UTouch  myTouch( 6, 5, 4, 3, 2);

// Declare which fonts we will be using
extern uint8_t BigFont[];

#define BIGBUTTON 230
#define SMALLBUTTON 65
int botton_h = 65;
//int botton_w = 230;
int padding = 5;
int text_space_h=25;
int text_space_w=45;
 
 
void drawButton(char *text, unsigned int position_x, unsigned int position_y,unsigned int botton_w)
{
  myGLCD.setColor(0, 0, 255); // blue
  int x1 = padding * (position_x + 1) + position_x * botton_h;
  int y1 = 240 - padding * (position_y + 1) - botton_w * position_y;
  int x2 = padding * (position_x + 1) + botton_h * (position_x + 1);
  int y2 = 240 - (padding * (position_y + 1)) - botton_w * (position_y + 1);
  myGLCD.fillRoundRect (x1, y1, x2, y2);
   
  myGLCD.setColor(255, 255, 255); //white
   
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  myGLCD.setColor(126, 255, 126); //
   
  myGLCD.setColor(126, 0, 126); //
   
  myGLCD.print(text, text_space_h+x1, y1-text_space_h, 270);
}
const int PinSW = 9;  // Analog input pin that the potentiometer is attached to


/*************************
**  Required functions  **
*************************/

void setup()
{
  Serial.begin(9600);
  pinMode(PinSW, INPUT_PULLUP);       // turn on pullup resistors
// Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();

//  myTouch.InitTouch();
//  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  drawButton("1 MOVE", 0, 0, BIGBUTTON);
  drawButton("2 ROTATE",1, 0, BIGBUTTON);
  drawButton("3 SHOOT", 2, 0, BIGBUTTON);

}



//states
#define INIT 0
#define MOVE 1

int state = INIT;


int cursorX = 0;
int cursorY = 0;

int X;
int Y;
int SW;
char cstr[16];
String str;
unsigned int steps = 0;
void loop()
{
    // print the results to the serial monitor:
//  Serial.print("X = " );                       
//  Serial.print(X);      
//  Serial.print("\t Y = ");      
//  Serial.print(Y);   
//  Serial.print("\t SW = ");      
//  Serial.println(SW);   


  X = 517-analogRead(analogInPinX);  
  Y = 507-analogRead(analogInPinY);  
  SW =digitalRead(PinSW);
  if(X <-5)
    cursorX= cursorX + 1;
  if(X >5)
    cursorX= cursorX - 1;
  if(Y <-5)
    cursorY= cursorY + 1;
  if(Y >5)
    cursorY= cursorY - 1;
  myGLCD.drawPixel(cursorX, cursorY);
  char key = kpd.getKey();
  
  switch (state)
  {
//    case
    case INIT:
    {
      if(key)  // Check for a valid key.
      {
        switch (key)
        {
          case '1': 
            state = MOVE;
              printKeyboard();
              break;
          case '*':
              playMelody();
            break;
          default:
            Serial.println(key);
        }
      }    
    }
    break;
    case MOVE:
      if(key)  // Check for a valid key.
      {
        switch(key)
        {
          default:
            if(steps < 999)
            {
              steps = steps * 10 + key-ASCII_KEY;
            
            }
          break;
          case '#':
            steps = 0;
          break;
        }
          Serial.print("steps: ");
          Serial.println(steps);
          str = String(steps);
          str.toCharArray(cstr,16);
          drawButton(cstr, 4, 0, BIGBUTTON);
      }
    break;

  }
}

void printKeyboard()
{
  myGLCD.clrScr();  
  drawButton("1", 0, 0, SMALLBUTTON);
  drawButton("2", 0, 1, SMALLBUTTON);
  drawButton("3", 0, 2, SMALLBUTTON);
  drawButton("4", 1, 0, SMALLBUTTON);
  drawButton("5", 1, 1, SMALLBUTTON);
  drawButton("6", 1, 2, SMALLBUTTON);
  drawButton("7", 2, 0, SMALLBUTTON);
  drawButton("8", 2, 1, SMALLBUTTON);
  drawButton("9", 2, 2, SMALLBUTTON);
  drawButton("#", 3, 0, SMALLBUTTON);
  drawButton("0", 3, 1, SMALLBUTTON);
  drawButton("*", 3, 2, SMALLBUTTON);
}

void playMelody()
{
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(tonePin, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(tonePin);
  }
}
