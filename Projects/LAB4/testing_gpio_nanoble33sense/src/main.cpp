#include <Arduino.h>
#include "led_light.h"

// Define the pins
#define LED_PIN_RED A0
#define LED_PIN_GREEN A1
#define LED_PIN_BLUE A2

// Create an instance of the LedLight class
LedLight myLed(LED_PIN_RED, LED_PIN_GREEN, LED_PIN_BLUE);

// Function declarations
int myFunction(int, int);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Call a sample function and print its result
  int result = myFunction(2, 3);
  Serial.println(result);
}

void loop() {
  // Use the methods of the LedLight class to control the LEDs
  myLed.turnOnRed();
  delay(500);
  myLed.turnOffRed();
  delay(500);

  myLed.turnOnGreen();
  delay(500);
  myLed.turnOffGreen();
  delay(500);

  myLed.turnOnBlue();
  delay(500);
  myLed.turnOffBlue();
  delay(500);
}

// Function definitions
int myFunction(int x, int y) {
  return x + y;
}
