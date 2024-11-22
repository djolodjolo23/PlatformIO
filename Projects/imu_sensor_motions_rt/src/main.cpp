#include <Arduino_LSM9DS1.h>
#include "Streaming.h"
#include "SensorFusion.h"

SF fusion;

float gx, gy, gz, ax, ay, az, mx, my, mz;

float gx_filt = 0, gy_filt = 0, gz_filt = 0;
float ax_filt = 0, ay_filt = 0, az_filt = 0;

float pitch, roll, yaw;
float deltat;

const float alpha = 0.1f;  

const float ROLL_THRESHOLD = 5.0f;          
const float PITCH_SPIKE_THRESHOLD = 17.0f;  
const float YAW_SPIKE_THRESHOLD = 17.0f;   

const int BUFFER_SIZE = 10;
float pitchBuffer[BUFFER_SIZE] = {0};
float yawBuffer[BUFFER_SIZE] = {0};
int bufferIndex = 0;

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

  for (int i = 0; i < BUFFER_SIZE; i++) {
    pitchBuffer[i] = 0.0f;
    yawBuffer[i] = 0.0f;
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

    ax_filt = alpha * ax + (1.0f - alpha) * ax_filt;
    ay_filt = alpha * ay + (1.0f - alpha) * ay_filt;
    az_filt = alpha * az + (1.0f - alpha) * az_filt;

    gx_filt = alpha * gx + (1.0f - alpha) * gx_filt;
    gy_filt = alpha * gy + (1.0f - alpha) * gy_filt;
    gz_filt = alpha * gz + (1.0f - alpha) * gz_filt;

    deltat = fusion.deltatUpdate();
    //fusion.MadgwickUpdate(gx_filt, gy_filt, gz_filt, ax_filt, ay_filt, az_filt, mx, my, mz, deltat);
    fusion.MahonyUpdate(gx_filt, gy_filt, gz_filt, ax_filt, ay_filt, az_filt, mx, my, mz, deltat);

    roll = fusion.getRoll();
    pitch = fusion.getPitch();
    yaw = fusion.getYaw();

    pitchBuffer[bufferIndex] = pitch;
    yawBuffer[bufferIndex] = yaw;

    static float previousRoll = 0.0f;
    float rollDifference = roll - previousRoll;

    if (abs(rollDifference) > ROLL_THRESHOLD) {
      if (rollDifference > 0) {
        Serial.println("Increasing Brightness");
      } else {
        Serial.println("Decreasing Brightness");
      }
    }
    previousRoll = roll;
    float pitchChange = pitch - pitchBuffer[(bufferIndex + 1) % BUFFER_SIZE];
    if (abs(pitchChange) > PITCH_SPIKE_THRESHOLD) {
      if (pitchChange > 0) {
        Serial.println("Pitch Spike Up - Disconnecting");
      } else {
        Serial.println("Pitch Spike Down - Connected");
      }
    }
    float yawChange = yaw - yawBuffer[(bufferIndex + 1) % BUFFER_SIZE];
    if (abs(yawChange) > YAW_SPIKE_THRESHOLD) {
      if (yawChange > 0) {
        Serial.println("Yaw Spike Left - Switching to Previous Color");
      } else {
        Serial.println("Yaw Spike Right - Switching to Next Color");
      }
    }

    bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;

    // Debug
    //Serial << "Pitch:\t" << pitch << "\tRoll:\t" << roll << "\tYaw:\t" << yaw << endl;

    delay(50); 
  }
}