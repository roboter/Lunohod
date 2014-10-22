/*  http://playground.arduino.cc/Code/Keypad#Download
 */
#include <Keypad.h>
 #include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

int tonePin =8;

int X;
int Y;
int SW;
const int analogInPinX = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPinY = A1;  // Analog input pin that the potentiometer is attached to
const int PinSW = 9;  // Analog input pin that the potentiometer is attached to
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



void setup()
{
  Serial.begin(9600);
  pinMode(PinSW, INPUT_PULLUP);       // turn on pullup resistors
}

void loop()
{
  // read the analog in value:
  X = analogRead(analogInPinX);  
  Y = analogRead(analogInPinY);  
  SW =digitalRead(PinSW);
  // map it to the range of the analog out:
//  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
//  analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
  Serial.print("X = " );                       
  Serial.print(X);      
  Serial.print("\t Y = ");      
  Serial.print(Y);   
  Serial.print("\t SW = ");      
  Serial.println(SW);   
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      default:
        Serial.println(key);
    }
  }
}
