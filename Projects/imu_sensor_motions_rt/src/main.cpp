#include <Arduino_LSM9DS1.h>
#include "Streaming.h"
#include "SensorFusion.h"

SF fusion;

// Raw sensor data
float gx, gy, gz, ax, ay, az, mx, my, mz;

// Filtered sensor data variables
float gx_filt = 0, gy_filt = 0, gz_filt = 0;
float ax_filt = 0, ay_filt = 0, az_filt = 0;

// Orientation angles
float pitch, roll, yaw;
float deltat;

// Smoothing factor for low-pass filter
const float alpha = 0.5f;  // Adjust between 0 (more smoothing) and 1 (less smoothing)

// Thresholds for detecting movements
const float ROLL_NEUTRAL_ZONE = 2.0f;      // Degrees, adjust as needed
const float PITCH_SPIKE_THRESHOLD = 15.0f; // Adjust as needed for pitch spikes
const float YAW_SPIKE_THRESHOLD = 15.0f;   // Adjust as needed for yaw spikes

// Buffers for storing recent orientation data
const int BUFFER_SIZE = 8;
float pitchBuffer[BUFFER_SIZE] = {0};
float yawBuffer[BUFFER_SIZE] = {0};
int bufferIndex = 0;

// Volume control state
enum VolumeState {
  VOLUME_NEUTRAL,
  VOLUME_INCREASING,
  VOLUME_DECREASING
};

static VolumeState volumeState = VOLUME_NEUTRAL;

// Stabilization delay variables
unsigned long lastActionTime = 0;
const unsigned long STABILIZATION_DELAY = 1000; // milliseconds

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

  // Initialize buffers
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

    // Convert gyroscope data from degrees/s to radians/s
    gx *= DEG_TO_RAD;
    gy *= DEG_TO_RAD;
    gz *= DEG_TO_RAD;

    // Apply low-pass filter to accelerometer data
    ax_filt = alpha * ax + (1.0f - alpha) * ax_filt;
    ay_filt = alpha * ay + (1.0f - alpha) * ay_filt;
    az_filt = alpha * az + (1.0f - alpha) * az_filt;

    // Apply low-pass filter to gyroscope data
    gx_filt = alpha * gx + (1.0f - alpha) * gx_filt;
    gy_filt = alpha * gy + (1.0f - alpha) * gy_filt;
    gz_filt = alpha * gz + (1.0f - alpha) * gz_filt;

    deltat = fusion.deltatUpdate();
    //fusion.MadgwickUpdate(gx_filt, gy_filt, gz_filt, ax_filt, ay_filt, az_filt, mx, my, mz, deltat);
    fusion.MahonyUpdate(gx_filt, gy_filt, gz_filt, ax_filt, ay_filt, az_filt, mx, my, mz, deltat);

    // Get orientation angles
    roll = fusion.getRoll();
    pitch = fusion.getPitch();
    yaw = fusion.getYaw();

    // Update buffers with new data
    pitchBuffer[bufferIndex] = pitch;
    yawBuffer[bufferIndex] = yaw;

    unsigned long currentTime = millis();

    // Roll detection for volume control with stabilization delay
    if (roll > ROLL_NEUTRAL_ZONE) {
      if (volumeState != VOLUME_INCREASING && (currentTime - lastActionTime > STABILIZATION_DELAY)) {
        Serial.println("Start Increasing Volume");
        volumeState = VOLUME_INCREASING;
        lastActionTime = currentTime;
        // Implement your volume increase logic here
      }
    } else if (roll < -ROLL_NEUTRAL_ZONE) {
      if (volumeState != VOLUME_DECREASING && (currentTime - lastActionTime > STABILIZATION_DELAY)) {
        Serial.println("Start Decreasing Volume");
        volumeState = VOLUME_DECREASING;
        lastActionTime = currentTime;
        // Implement your volume decrease logic here
      }
    } else {
      if (volumeState != VOLUME_NEUTRAL) {
        Serial.println("Volume Control Neutral");
        volumeState = VOLUME_NEUTRAL;
        lastActionTime = currentTime;
        // Optionally, implement logic when returning to neutral
      }
    }

    // Pitch spike detection
    float pitchChange = pitch - pitchBuffer[(bufferIndex + 1) % BUFFER_SIZE];
    if (abs(pitchChange) > PITCH_SPIKE_THRESHOLD ) {
      // Implement a debounce mechanism if needed
      Serial.println("Pitch Spike Detected");
      // Implement your connection logic here
    }

    // Yaw spike detection
    float yawChange = yaw - yawBuffer[(bufferIndex + 1) % BUFFER_SIZE];
    if (abs(yawChange) > YAW_SPIKE_THRESHOLD) {
      // Implement a debounce mechanism if needed
      Serial.println("Yaw Spike Detected");
      // Implement your color switching logic here
    }

    // Increment buffer index
    bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;

    // Debug output (optional)
    // Serial << "Pitch:\t" << pitch << "\tRoll:\t" << roll << "\tYaw:\t" << yaw << endl;

    delay(50); 
  }
}
