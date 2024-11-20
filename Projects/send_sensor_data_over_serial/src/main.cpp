#include <Arduino.h>

#include <Arduino_LSM6DSOX.h>

// Define sampling rate and duration
const int intervalMs = 10; // Capture data every 10ms
const int durationSeconds = 10;
const int samples = (durationSeconds * 1000) / intervalMs;

// Arrays to store accelerometer and gyroscope data
float accX[samples], accY[samples], accZ[samples];
float gyroX[samples], gyroY[samples], gyroZ[samples];

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize the IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.println("IMU initialized.");
}

void loop() {
  // Capture data for 10 seconds
  Serial.println("Starting data capture in 2 sec...");
  delay(2000);
  for (int i = 0; i < samples; i++) {
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // Read accelerometer data
      IMU.readAcceleration(accX[i], accY[i], accZ[i]);

      // Read gyroscope data
      IMU.readGyroscope(gyroX[i], gyroY[i], gyroZ[i]);
    }

    delay(intervalMs);
  }

  Serial.println("Sending data...");
  for (int i = 0; i < samples; i++) {
    Serial.print(accX[i], 6); Serial.print(", ");
    Serial.print(accY[i], 6); Serial.print(", ");
    Serial.print(accZ[i], 6); Serial.print(", ");
    Serial.print(gyroX[i], 6); Serial.print(", ");
    Serial.print(gyroY[i], 6); Serial.print(", ");
    Serial.println(gyroZ[i], 6);
  }
  Serial.println("Capture complete");
  }
