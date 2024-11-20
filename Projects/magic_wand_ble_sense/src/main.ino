/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include <Arduino.h>

#include "magic_wand_model_data.h"
#include "rasterize_stroke.h"
#include "imu_provider.h"

namespace {

  const int VERSION = 0x00000000;

  // Constants for image rasterization
  constexpr int raster_width = 32;
  constexpr int raster_height = 32;
  constexpr int raster_channels = 3;
  constexpr int raster_byte_count = raster_height * raster_width * raster_channels;
  int8_t raster_buffer[raster_byte_count];
  

}  // namespace

void setup() {
  Serial.begin(9600);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialized IMU!");
    while (1);
  }
  SetupIMU();
  }

void loop() {

  // make sure IMU data is available then read in data
  const bool data_available = IMU.accelerationAvailable() || IMU.gyroscopeAvailable();
  if (!data_available) {
    return;
  }
  int accelerometer_samples_read;
  int gyroscope_samples_read;
  ReadAccelerometerAndGyroscope(&accelerometer_samples_read, &gyroscope_samples_read);

  // Parse and process IMU data
  bool done_just_triggered = false;
  if (gyroscope_samples_read > 0) {
    EstimateGyroscopeDrift(current_gyroscope_drift);
    UpdateOrientation(gyroscope_samples_read, current_gravity, current_gyroscope_drift);
    UpdateStroke(gyroscope_samples_read, &done_just_triggered);
  }
  if (accelerometer_samples_read > 0) {
    EstimateGravityDirection(current_gravity);
    UpdateVelocity(accelerometer_samples_read, current_gravity);
  }

  // Wait for a gesture to be done
  if (done_just_triggered) {
    // Rasterize the gesture
    RasterizeStroke(stroke_points, *stroke_transmit_length, 0.6f, 0.6f, raster_width, raster_height, raster_buffer);
    for (int y = 0; y < raster_height; ++y) {
      char line[raster_width + 1];
      for (int x = 0; x < raster_width; ++x) {
        const int8_t* pixel = &raster_buffer[(y * raster_width * raster_channels) + (x * raster_channels)];
        const int8_t red = pixel[0];
        const int8_t green = pixel[1];
        const int8_t blue = pixel[2];
        char output;
        if ((red > -128) || (green > -128) || (blue > -128)) {
          output = '#';
        } else {
          output = '.';
        }
        line[x] = output;
      }
      line[raster_width] = 0;
      Serial.println(line);
    }

  }
}
