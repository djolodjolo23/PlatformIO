#include <Arduino.h>
#include <Arduino.h>
#include <MadgwickAHRS.h>
#include <Arduino_LSM6DS3.h>


Madgwick filter;

int threshold = 320;
int rollVal = 0;
int pitchVal = 0;
int yawVal = 0;

float smoothRoll = 0;
float smoothPitch = 0;
float smoothHeading = 0;

float prevSmoothRoll = 0;
float prevSmoothPitch = 0;
float prevSmoothHeading = 0;

float weight = 0.1;

float convertRawAcceleration(float aRaw);
float convertRawGyro(float gRaw);
float filterVal(float rawVal, float w, float prevVal);

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

    smoothRoll = filterVal(roll, weight, prevSmoothRoll);
    smoothPitch = filterVal(pitch, weight, prevSmoothPitch);
    smoothHeading = filterVal(heading, weight, prevSmoothHeading);

    prevSmoothRoll = smoothRoll;
    prevSmoothPitch = smoothPitch;
    prevSmoothHeading = smoothHeading;


    if (smoothRoll > 15) {
      Serial.println("Rolling too much to the left");
    } else if (smoothRoll < -15) {
      Serial.println("Rolling too much to the right");
    } 

    if (smoothPitch > 15) {
      Serial.println("Pitching too high upwards");
    } else if (smoothPitch < -15) {
      Serial.println("Pitching too low downwards");
    } 

    if (smoothHeading > 185) {
      Serial.println("Heading too far to the left");
    } else if (smoothHeading < 175) {
      Serial.println("Heading too far to the right");
    } 

    if ((smoothRoll <= 15 && smoothRoll >= -15) && 
        (smoothPitch <= 15 && smoothPitch >= -15) && 
        (smoothHeading <= 190 && smoothHeading >= 170)) {
      Serial.println("All good");
    }

    delay(20);
    

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


float filterVal(float rawVal, float w, float prevVal) {
  float result = w * rawVal + (1.0 - w) * prevVal;
  return result;
}