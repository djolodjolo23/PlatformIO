#include <Arduino.h>
#include <WiFiNINA.h>
#include <Adafruit_NeoPixel.h>

/*

#include <WiFiNINA.h> 

void setup() { 
  // Set LED Pins as Outputs 
  pinMode(LEDR, OUTPUT); 
  pinMode(LEDG, OUTPUT); 
  pinMode(LEDB, OUTPUT); 
} 

void loop() { 
  // Cycle Colour Blinking 
  digitalWrite(LEDR,HIGH); // Turn On RED LED 
  delay(250); 
  digitalWrite(LEDR,LOW);  // Turn Off RED LED 

  digitalWrite(LEDG,HIGH); // Turn On GREEN LED 
  delay(250); 
  digitalWrite(LEDG,LOW);  // Turn Off GREEN LED 

  digitalWrite(LEDB,HIGH); // Turn On BLUE LED 
  delay(250); 
  digitalWrite(LEDB,LOW);  // Turn Off BLUE LED 
}
*/



#define motorPin 2

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  digitalWrite(motorPin, HIGH);  // turn the motor on 
  delay(1000);                   // wait for a second
  digitalWrite(motorPin, LOW);   // turn the motor off
  delay(1000);                   // wait for a second
}



/*
// LED_PIN refers to the pin where the LED ring is connected to, D2 corresponds to 25
#define LED_PIN 25

// LED_COUNT indicates how many LEDs there are in the ring, if you had a different NeoPixel
// configuration, like a strip, you should simply add the total amount of LEDs and put it here
#define LED_COUNT 24

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setRingRed(bool off);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(50);
}

void loop() {
  setRingRed(false);
  delay(1000);
  setRingRed(true);
  delay(1000);
}

void setRingRed(bool off) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(off ? 0 : 255, 0, 0));
  }
  strip.show();
}
*/


// EXERCISE 1
//Using the button as input, make a system that changes between different modes of light using the LED ring.
//Make use of functions to help yourself for future uses of similar code.
