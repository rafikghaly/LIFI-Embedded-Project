// include the library code:
#include <LiquidCrystal.h>
const int pulseThreshold = 20;  // Adjust this threshold according to your ambient light conditions
const int pulseDuration = 5000;  // Duration of the message reception in milliseconds
//LCD////////////////////////////////////
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//////////////////////////////////////////////


//LDR/////////////////////
int ldrPin = A0; // select the input pin for LDR
int sensorValue = 0; // variable to store the value coming from the sensor
//////////////////////////

//Buzzer/////////////////////
const int buzzer = 9;
const int buttonPin = 7;
int buttonState = 0;  // variable for reading the pushbutton status

//LED///////////////////////
const int ledPin = 13;

////counter/////
int counter =0;
void setup() {
  //LCD//////////////////////////
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("hello, world!");
  //////////////////////////////////
  
  //LDR//////////////////////////
  Serial.begin(9600); //sets serial port for communication
  //////////////////////////////

  //Buzzer/////////////////////
   pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
   pinMode(buttonPin, INPUT);

  //LED/////////////////////////
   pinMode(ledPin, OUTPUT);

}

void loop() {
  //Button///////////////////////
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  //LDR//////////////////////////
  sensorValue = analogRead(ldrPin); // read the value from the sensor
  Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  delay(100);
  //////////////////////////////
  unsigned long startTime = millis();  // Record the start time of the message reception
  
  while (millis() - startTime < pulseDuration) {
    int previousValue = analogRead(ldrPin);  // Read the LDR value
    delay(100);  // Delay between readings for stability
    int currentValue = analogRead(ldrPin);  // Read the LDR value again
    
    int diff = currentValue - previousValue;  // Calculate the difference
    
    if (diff > pulseThreshold) {
      // Pulse detected
      delay(100);  // Wait for 100ms to ensure the pulse has ended
      
      // Start receiving the message combinations
      String message = receiveMessage(currentValue);
      
      // Process the received message
      if (message == "100") {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("FIRE !!!!!");
        tone(buzzer, 1000); // Send 1KHz sound signal...
        digitalWrite(ledPin, HIGH);
        Serial.println("FIRE !!!!!");
      } else if (message == "111") {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Door is Opened!");
        tone(buzzer, 1500);
        digitalWrite(ledPin, HIGH);
        Serial.println("Door is Opened!");
      } else if (message == "110") {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Object Detected!");
        tone(buzzer, 2000);
        digitalWrite(ledPin, HIGH);
        Serial.println("Object Detected!");
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
  if (buttonState == HIGH) {
    Serial.println("MUTE!!");
    digitalWrite(ledPin, LOW);
    noTone(buzzer);     // Stop sound...
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
    delay(200);  // Delay between readings for stability
    int currentValue = analogRead(ldrPin);  // Read the LDR value again

    int diff = abs(currentValue - value);  // Calculate the difference
    
    if (diff < pulseThreshold) {
//      // Pulse detected
        delay(200);  // Wait for 100ms to ensure the pulse has ended
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
        delay(200);  // Wait for 100ms to ensure the pulse has ended
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
