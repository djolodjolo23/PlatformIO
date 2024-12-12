#include <Arduino.h>
#include "RP2040_PWM.h"

RP2040_PWM* IR_PWM = NULL;

const int IR_LED_PIN = 9;

void setup() {
  pinMode(IR_LED_PIN, OUTPUT);
  // Set up a 38kHz PWM with 50% duty cycle
  IR_PWM = new RP2040_PWM(IR_LED_PIN, 38000, 50.0); // Pin, Frequency, DutyCycle%
}

void loop() {
  // Turn on the PWM for 3 seconds
  IR_PWM->setPWM(IR_LED_PIN, 38000, 50.0);
  delay(1000);

  // Turn off the PWM for 3 seconds by setting duty cycle to 0
  IR_PWM->setPWM(IR_LED_PIN, 38000, 0.0);
  delay(1000);
}
