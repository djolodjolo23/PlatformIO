#include <Arduino.h>
#include "FlatVibrationMotor.hpp"
#define BUTTON_PIN 5
#define VIRBATION_MOTOR_PIN 2

FlatVibrationMotor* vibrationMotor;
static bool lastButtonState = HIGH;
static int seconds = 5;
static int highScore = 0;

void playGame(int &seconds);

void setup() {
  Serial.begin(9600);
  vibrationMotor = new FlatVibrationMotor(VIRBATION_MOTOR_PIN);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  delay(3000);
}

void loop() {
  playGame(seconds);
}

void playGame(int &seconds) {
  Serial.print("Lets see how many times you can press the button in ");
  Serial.print(seconds);
  Serial.println(" seconds");
  delay(1000);
  unsigned long startCountdown = millis();
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("Go!");
  unsigned long startTime = millis();
  while (millis() - startTime < seconds * 1000) {
    bool buttonState = digitalRead(BUTTON_PIN);
    if (buttonState == LOW && lastButtonState == HIGH) {
      vibrationMotor->vibrate();
      Serial.print("\rNumber of vibrations: ");
      Serial.print(vibrationMotor->getNumberOfVibrations());
    }
    lastButtonState = buttonState;
  }
  Serial.println("\nTime's up!");
  Serial.print("You pressed the button ");
  Serial.print(vibrationMotor->getNumberOfVibrations());
  Serial.println(" times");
  delay(2000);
  Serial.println("Current High Score: ");
  Serial.println(highScore);
  delay(2000);
  Serial.println("Press the button to play again");
  if (vibrationMotor->getNumberOfVibrations() > highScore) {
    highScore = vibrationMotor->getNumberOfVibrations();
  }
  while (digitalRead(BUTTON_PIN) == HIGH) {
    delay(10);
  }
  vibrationMotor->setNumberOfVibrations(0);
}

