#include <Arduino.h>

/*
void setup() {
  Serial.begin(115200);
}

void loop() {
    int val1 = analogRead( A0 );
    int val2 = analogRead( A1 );

    Serial.print( "X-Y coordinate:" );
    Serial.print( val1, DEC );
    Serial.print( "," );
    Serial.println( val2, DEC );
    Serial.println( " " );
    delay( 200 );
}
*/

/*
float avg1 = 0;
float avg2 = 0;
int avgSize = 10;  // determines the amount of samples to use to make the average

void setup() {
  Serial.begin(115200);
}

void loop() {

  for (int i = 0; i < avgSize; i++) {
    avg1 += analogRead(A0);
    avg2 += analogRead(A1);
    delay(1);  // note that this delay is needed to stabilise the ADC
  }
  avg1 /= avgSize;
  avg2 /= avgSize;


  Serial.print("X-Y coordinate:");
  Serial.print(int(avg1));
  Serial.print(",");
  Serial.println(int(avg2));
  Serial.println(" ");
  delay(200);
}
*/

/*

const int avgSize = 10;  // determines the amount of samples to use to make the average
float avgBuffer1[avgSize];
float avgBuffer2[avgSize];
int avgIndex = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // read current data, and
  // store readings in array
  avgBuffer1[avgIndex] = analogRead(A0);
  avgBuffer2[avgIndex] = analogRead(A1);
  avgIndex++;

  // reset the index
  if (avgIndex >= avgSize) avgIndex = 0;

  // create variables to calculate the average
  float avg1 = 0;
  float avg2 = 0;

  for (int i = 0; i < avgSize; i++) {

    avg1 += avgBuffer1[i];
    avg2 += avgBuffer2[i];
  }
  avg1 /= avgSize;
  avg2 /= avgSize;


  Serial.print("X-Y coordinate:");
  Serial.print(int(avg1));
  Serial.print(",");
  Serial.println(int(avg2));
  Serial.println(" ");
  delay(200);
}

*/

int val1 = 0;
int threshold = 320;

float smoothedVal1 = 0.0;
float prevSmoothedVal1 = 0.0;

// weight is the smoothing factor, in range [0,1].
// Higher the value - less smoothing (higher the latest reading impact)
float weight = 0.1;

float filter(float rawVal, float w, float prevVal);

void setup() {
  Serial.begin(115200);
}

void loop() {
  val1 = analogRead(A0);
  smoothedVal1 = filter(val1, weight, prevSmoothedVal1);
  prevSmoothedVal1 = smoothedVal1;

  Serial.print("X coordinate:");
  Serial.print(val1, DEC);
  Serial.print(", smoothed: ");
  Serial.println(int(smoothedVal1));
  delay(10);
}

float filter(float rawVal, float w, float prevVal) {
  float result = w * rawVal + (1.0 - w) * prevVal;
  return result;
}

/*
#include <MadgwickAHRS.h>
#include <Arduino_LSM6DS3.h>

Madgwick filter;

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
    Serial.print("Orientation: ");
    Serial.print(heading);
    Serial.print(" ");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.println(roll);
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
*/

