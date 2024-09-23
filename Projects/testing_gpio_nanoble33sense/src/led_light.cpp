#include "led_light.h"

// Constructor
LedLight::LedLight(int redPin, int greenPin, int bluePin) {
  this->redPin = redPin;
  this->greenPin = greenPin;
  this->bluePin = bluePin;

  // Initialize the pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

// Methods to control the red LED
void LedLight::turnOnRed() {
  digitalWrite(redPin, HIGH);
}

void LedLight::turnOffRed() {
  digitalWrite(redPin, LOW);
}

// Methods to control the green LED
void LedLight::turnOnGreen() {
  digitalWrite(greenPin, HIGH);
}

void LedLight::turnOffGreen() {
  digitalWrite(greenPin, LOW);
}

// Methods to control the blue LED
void LedLight::turnOnBlue() {
  digitalWrite(bluePin, HIGH);
}

void LedLight::turnOffBlue() {
  digitalWrite(bluePin, LOW);
}
