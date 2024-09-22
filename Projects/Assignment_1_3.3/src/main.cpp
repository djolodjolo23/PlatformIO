#include <Arduino.h>
#include <WiFiNINA.h>

int buttonPin = A1;
int pinStatus;
int currentColor = 0;

void shiftColorOnButtonPress();
void allColorsOff();

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(buttonPin, INPUT);
  allColorsOff();
}

void loop() {
  shiftColorOnButtonPress();
}


void shiftColorOnButtonPress() {
  pinStatus = digitalRead(buttonPin);
  if (pinStatus == LOW) {
    if (currentColor == 0) { // red is 0
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, LOW);
      digitalWrite(LEDB, LOW);
    } else if (currentColor == 1) { // green is 1
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, LOW);
      digitalWrite(LEDR, LOW);
    } else if (currentColor == 2) { // blue is 2
      digitalWrite(LEDB, HIGH);
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDG, LOW);
    }
    currentColor == 0 ? currentColor = 1 : currentColor == 1 ? currentColor = 2 : currentColor = 0;
    while (digitalRead(buttonPin) == LOW) {
      delay(10);
    }
  }

}

void allColorsOff() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}
