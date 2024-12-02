#include <Arduino.h>
#include <Arduino_LSM6DSOX.h>

const int motorPin = 2;
const int numSamples = 4; 
float Ax, Ay, Az;
float accelerationMagnitude;
float magnitudeSamples[numSamples];
int sampleIndex = 0;
float movingAverage = 0.0;
float total = 0.0;
unsigned long previousMillis = 0;
const long interval = 100; 
const float movementThreshold = 0.04; 

unsigned long lastMovementTime = 0; 
const unsigned long stationaryInterval = 10000; 

int vibrationStep = 0; 

void vibrate(unsigned long currentMillis);


void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  for (int i = 0; i < numSamples; i++) {
    magnitudeSamples[i] = 0.0;
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(Ax, Ay, Az);

      accelerationMagnitude = sqrt(Ax * Ax + Ay * Ay + Az * Az);

      total -= magnitudeSamples[sampleIndex];
      magnitudeSamples[sampleIndex] = accelerationMagnitude;
      total += magnitudeSamples[sampleIndex];
      sampleIndex = (sampleIndex + 1) % numSamples;

      movingAverage = total / numSamples;

      if (abs(movingAverage - 1.0) > movementThreshold) {
        Serial.println("Movement detected");
        lastMovementTime = currentMillis;
        analogWrite(motorPin, 0);
      } else {
        if (currentMillis - lastMovementTime >= stationaryInterval) {
          Serial.println("Stationary and vibrating");
          vibrate(currentMillis);
        } else {
          analogWrite(motorPin, 0);
        }

      }

    }
  }
}

void vibrate(unsigned long currentMillis) {
  static unsigned long vibrationMillis = 0;
  if (vibrationStep == 0) { 
    vibrationMillis = currentMillis;
    vibrationStep = 1;
  }
  if (vibrationStep == 1) { 
    int intensity = (currentMillis - vibrationMillis) / 10 * 5; 
    Serial.println(currentMillis);
    if (intensity >= 255) {
      intensity = 255;
      vibrationStep = 2; 
      vibrationMillis = currentMillis;
    }
    analogWrite(motorPin, intensity);
  }
  if (vibrationStep == 2) { 
    int intensity = 255 - (currentMillis - vibrationMillis) / 10 * 5; 
    Serial.println(currentMillis);
    if (intensity <= 40) {
      intensity = 40;
      vibrationStep = 0; 
    analogWrite(motorPin, intensity);
  }
  }
}