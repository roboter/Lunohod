/*
Blink
Turns on an LED on for one second, then off for one second, repeatedly.
This example code is in the public domain.
*/
#define D1 3 // Направление вращение двигателя 1
#define M1 4 // ШИМ вывод для управления двигателем 1
#define D2 6 // Направление вращение двигателя 2
#define M2 5 // ШИМ вывод для управления двигателем 2
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
#define LED 2
#define PIN1 8
#define PIN2 9
int pin1 = 8;
int pin2 = 9;
 
// the setup routine runs once when you press reset:
void setup() {
Serial.begin(9600);
// initialize the digital pin as an output.
pinMode(LED, OUTPUT);
pinMode(pin1, INPUT); // set pin to input
digitalWrite(pin1, HIGH); // turn on pullup resistors
pinMode(pin2, INPUT); // set pin to input
digitalWrite(pin2, HIGH); // turn on pullup resistors
 
pinMode(D1, OUTPUT);
pinMode(M1, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(M2, OUTPUT);
}
char command = 'S';
int i = 255;
// the loop routine runs over and over again forever:
void loop() {
//

if(Serial.available() > 0){
    command = Serial.read(); 
    Serial.println(command);
    switch(command)
    {
      case 'F': 
        digitalWrite(D1, HIGH);
        analogWrite(M1, 0);
        digitalWrite(D2, HIGH);
        analogWrite(M2, 0);
      //yellowCar.Forward_4W(velocity);
      break;
    case 'B': 
        digitalWrite(D1, LOW);
        analogWrite(M1, 255);
        digitalWrite(D2, LOW);
        analogWrite(M2, 255);
//      yellowCar.Back_4W(velocity);
      break;
    case 'L': 
        digitalWrite(D1, HIGH);
        analogWrite(M1, 0);
        digitalWrite(D2, LOW);
        analogWrite(M2, 255);
  //    yellowCar.Left_4W();
      break;
    case 'R':
        digitalWrite(D2, HIGH);
        analogWrite(M2, 0);
        digitalWrite(D2, LOW);
        analogWrite(M2, 255);
    //  yellowCar.Right_4W(); 
      break;
    case 'S': 
        digitalWrite(D2, LOW);
        analogWrite(M2, 0);
        digitalWrite(D2, LOW);
        analogWrite(M2, 0);
//      yellowCar.Stopped_4W();
      break; 
    }
    
}
//delay(100); // wait for a second
//
// delay(1000); // wait for a second
if(digitalRead(PIN1) == 1)
{
//Serial.println(i);
//digitalWrite(D1, HIGH);
//analogWrite(M1, 255 - i);
//digitalWrite(D2, HIGH);
//analogWrite(M2, 255 - i);
//i++;
}
if(digitalRead(PIN2) == 1)
{
Serial.println(i);
//digitalWrite(D1, LOW);
//analogWrite(M1, i);
//digitalWrite(D2, LOW);
//analogWrite(M2, i);
//i--;
}
//if(i>255) i =255;
//if(i<0) i=0;
//analogWrite(LED, i); // turn the LED on (HIGH is the voltage level)
}
