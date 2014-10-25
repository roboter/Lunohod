#define DisplaySerial Serial

#include "Picaso_Serial_4DLib.h"
#include "BigDemo.h" 
#include "Picaso_Const4D.h"

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
    Display.putstr("Lunokhod loading...") ;
}

void loop()
{
 

}
