// include the library code:
#include <LiquidCrystal.h>

//LCD////////////////////////////////////
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//////////////////////////////////////////////


//LDR/////////////////////
int sensorPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
//////////////////////////


void setup() {
  //LCD//////////////////////////
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  //////////////////////////////////
  
  //LDR//////////////////////////
  Serial.begin(9600); //sets serial port for communication
  //////////////////////////////

}

void loop() {
  //LDR//////////////////////////
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  delay(100);
  //////////////////////////////
  
  //LCD//////////////////////////
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  ////////////////////////////////



}
