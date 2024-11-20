#include <Arduino_LSM9DS1.h>    
#include "Streaming.h"          
#include "SensorFusion.h"

#define BUFFER_SIZE 5

SF fusion;

float gx, gy, gz, ax, ay, az, mx, my, mz;
float pitch, roll, yaw;
float deltat;

float pitchBuffer[BUFFER_SIZE]; 
float rollBuffer[BUFFER_SIZE];
float yawBuffer[BUFFER_SIZE];

int pitchIndex = 0;
int rollIndex = 0;
int yawIndex = 0;

void addToBuffer(float value, float* buffer, int& index) {
  buffer[index] = value;
  index = (index + 1) % BUFFER_SIZE;
}

void addValuesToBuffer(float pitch, float roll, float yaw) {
  addToBuffer(pitch, pitchBuffer, pitchIndex);
  addToBuffer(roll, rollBuffer, rollIndex);
  addToBuffer(yaw, yawBuffer, yawIndex);
}

int checkControl() {
  float highestDifference = 0;
  uint8_t controlling_num;
  float pitchDifference = abs(pitchBuffer[0] - pitchBuffer[4]);
  float rollDifference = abs(rollBuffer[0] - rollBuffer[4]);
  float yawDifference = abs(yawBuffer[0] - yawBuffer[4]) ;
  if (pitchDifference > highestDifference) {
    highestDifference = pitchDifference;
    controlling_num = 1;  
  }
  if (rollDifference > highestDifference) {
    highestDifference = rollDifference;
    controlling_num = 2;
  }
  if (yawDifference > highestDifference) {
    highestDifference = yawDifference;
    controlling_num = 3;
  }
  return controlling_num;
}

#define EULER_DATA

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;  
  }

  if (!IMU.begin()) {
    Serial.println("IMU initialization unsuccessful");
    while (1) {
      ;  
    }
  } else {
    Serial.println("IMU initialized successfully");
  }
}

void loop() {
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() && IMU.magneticFieldAvailable()) {
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);
    IMU.readMagneticField(mx, my, mz);

    gx *= DEG_TO_RAD;
    gy *= DEG_TO_RAD;
    gz *= DEG_TO_RAD;

    deltat = fusion.deltatUpdate();
    //fusion.MadgwickUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, deltat);
    fusion.MahonyUpdate(gx, gy, gz, ax, ay, az, mx, my, mz, deltat);

    // Get orientation angles
    roll = fusion.getRoll();
    pitch = fusion.getPitch();
    yaw = fusion.getYaw();

    addValuesToBuffer(pitch, roll, yaw);

    if (checkControl() == 1) {
      Serial << "Pitch is controlling" << endl;
    } else if (checkControl() == 2) {
      Serial << "Roll is controlling" << endl;
    } else if (checkControl() == 3) {
      Serial << "Yaw is controlling" << endl;
    }

    //#ifdef EULER_DATA
      //Serial << "Pitch:\t" << pitch << "\t\tRoll:\t" << roll << "\t\tYaw:\t" << yaw << endl << endl;
    //#endif
    delay(50); 
  }
}
