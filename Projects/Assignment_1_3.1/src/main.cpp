#include <Arduino.h>

void mimickHarddrive();
void flicker();

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  mimickHarddrive();
}

void mimickHarddrive() {
  digitalWrite(PIN_LED, LOW);
  delay(3000);
  digitalWrite(PIN_LED, HIGH);
  delay(1000);
  flicker();
  digitalWrite(PIN_LED, HIGH);
  // end
  delay(10000);
}

void flicker() {
  for (int i = 0; i <= 2; i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(300);
    digitalWrite(PIN_LED, LOW);
    delay(300);
  }
}