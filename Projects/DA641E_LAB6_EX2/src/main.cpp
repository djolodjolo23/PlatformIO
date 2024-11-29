#include <Arduino.h>
#include <MadgwickAHRS.h>
#include <Arduino_LSM6DS3.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 25
#define LED_COUNT 24
Madgwick filter;
Adafruit_NeoPixel ring(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

float convertRawAcceleration(float aRaw);
float convertRawGyro(float gRaw);


void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  // start the filter at 104Hz as it is the IMU's freq.
  filter.begin(104);

  // the accelerometer range is 4G
  // the gyroscope range is 2000 degrees/second
  ring.begin();
  ring.show();
}

void loop() {
  float aix, aiy, aiz;
  float gix, giy, giz;
  float ax, ay, az;
  float gx, gy, gz;
  float roll, pitch, heading;
 
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
    IMU.readAcceleration(aix, aiy, aiz);
    IMU.readGyroscope(gix, giy, giz);

    // convert from raw data to gravity and degrees/second units
    ax = convertRawAcceleration(aix);
    ay = convertRawAcceleration(aiy);
    az = convertRawAcceleration(aiz);
    gx = convertRawGyro(gix);
    gy = convertRawGyro(giy);
    gz = convertRawGyro(giz);

    // update the filter, which computes orientation
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();

    int roll_led = map(roll, -180, 180, 0, LED_COUNT - 1);
    int pitch_led = map(pitch, -90, 90, 0, LED_COUNT - 1);
    int heading_led = map(heading, 165, 195, 0, LED_COUNT - 1);

    ring.clear();
    ring.setPixelColor(roll_led, ring.Color(255, 0, 0));    
    ring.setPixelColor(pitch_led, ring.Color(0, 255, 0));   
    ring.setPixelColor(heading_led, ring.Color(0, 0, 255)); 
    ring.show();

    Serial.print("Orientation: ");
    Serial.print(heading);
    Serial.print(" ");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.println(roll);

    delay(10);
    

  }
}

float convertRawAcceleration(float aRaw) {
  // since we are using 4G range
  // -4g maps to a raw value of -32768
  // +4g maps to a raw value of 32767

  float a = (aRaw * 4.0) / 32768.0;
  return a;
}

float convertRawGyro(float gRaw) {
  // since we are using 2000 degrees/seconds range
  // -2000 maps to a raw value of -32768
  // +2000 maps to a raw value of 32767

  float g = (gRaw * 2000.0) / 32768.0;
  return g;
}