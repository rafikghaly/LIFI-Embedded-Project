// include the library code:
#include <LiquidCrystal.h>
const int pulseThreshold = 100;  // Adjust this threshold according to your ambient light conditions
const int pulseDuration = 10000;  // Duration of the message reception in milliseconds
//LCD////////////////////////////////////
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//////////////////////////////////////////////


//LDR/////////////////////
int ldrPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
//////////////////////////

////E7na/////
int counter =0;


void setup() {
  //////////LASERTEST////////////
  pinMode(8,OUTPUT);
  //LCD//////////////////////////
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  //////////////////////////////////
  
  //LDR//////////////////////////
  Serial.begin(9600); //sets serial port for communication
  //////////////////////////////

}

void loop() {
  //LDR//////////////////////////
  sensorValue = analogRead(ldrPin); // read the value from the sensor
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen

  //////////////////////////////
  unsigned long startTime = millis();  // Record the start time of the message reception
  
  while (millis() - startTime < pulseDuration) {

    int previousValue = analogRead(ldrPin);  // Read the LDR value
    delay(100);  // Delay between readings for stability
    digitalWrite(8,HIGH);
    delay(200);
    int currentValue = analogRead(ldrPin);  // Read the LDR value again
    delay(200);
    digitalWrite(8,LOW);
    int diff = currentValue - previousValue;  // Calculate the difference
    Serial.println(diff);
    if (diff > pulseThreshold) {
      // Pulse detected
      delay(100);  // Wait for 100ms to ensure the pulse has ended
      
      // Start receiving the message combinations
      String message = receiveMessage(currentValue);
      
      // Process the received message
      if (message == "000") {
        // Do something for combination ABC
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("I LOVE U");
        Serial.println("Received message: ABC");
      } else if (message == "010") {
        // Do something for combination DEF
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Received: DEF");
        Serial.println("Received message: DEF");
      } else if (message == "111") {
        // Do something for combination GHI
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Received: GHI");
        Serial.println("Received message: GHI");
      } else {
        // Invalid combination
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Invalid message");
        Serial.println(message);
      }
      
      delay(2000);  // Display the received message for 2 seconds
      lcd.clear();  // Clear the LCD display
      
      break;  // Exit the while loop
    }
  }
}



String receiveMessage(int value) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Recieving message");
        Serial.println("Recieving");
  String message = "";
  unsigned long startTime = millis();  // Record the start time of the message reception
  
  while (millis() - startTime < pulseDuration) {
    int previousValue = analogRead(ldrPin);  // Read the LDR value
    delay(100);  // Delay between readings for stability
    if(counter ==1)
    {
     digitalWrite(8,LOW);
    }
    else{digitalWrite(8,HIGH);}
    int currentValue = analogRead(ldrPin);  // Read the LDR value again
    delay(100);
    digitalWrite(8,LOW);
    int diff = abs(currentValue - value);  // Calculate the difference
    
    if (diff < pulseThreshold) {
//      // Pulse detected
        delay(100);  // Wait for 100ms to ensure the pulse has ended
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Next Bit"+counter);
        Serial.println("ENTER NEXT BIT BSOR3AAAAA");
//      
//      // Check if it's a short pulse or a long pulse
//      int pulseDuration = analogRead(ldrPin);
//      
        message += "1";
        counter++;
      } 
      else {
        // Short pulse received
        delay(100);  // Wait for 100ms to ensure the pulse has ended
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Next Bit"+counter);
        Serial.println("ENTER NEXT BIT BSOR3AAAAA");
        message += "0";
        counter++;
      }
      
      if (message.length() == 3) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Recieved");
        Serial.println(message);
        counter=0;
        break;
      }
    }
  
  
  return message;
}
