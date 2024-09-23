#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Arduino_LSM9DS1.h>
#include <Adafruit_SH1106.h>


// Function declarations
int myFunction(int, int);

int counter = 0;

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  // Print initial message to the serial monitor
  Serial.println("Hello World");
  // Set the built-in LED pin as an output
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize the IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {


  // Read data from the IMU and print it
  float x, y, z;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    Serial.print("Acceleration X: ");
    Serial.print(x);
    Serial.print(", Y: ");
    Serial.print(y);
    Serial.print(", Z: ");
    Serial.println(z);
  }
}

// Function definitions
int myFunction(int x, int y) {
  return x + y;
}
