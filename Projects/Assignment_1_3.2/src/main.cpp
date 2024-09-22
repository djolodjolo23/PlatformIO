#include <Arduino.h>
#include <WiFiNINA.h>


void showYellow();
void showMagenta();
void showCyan();

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void loop() {
  showYellow();
  delay(2000);
  showMagenta();
  delay(2000);
  showCyan();
  delay(2000);
}

void showYellow() {
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);
}

void showMagenta() {
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, HIGH);
}

void showCyan() {
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}