#include <Arduino.h>
#include <WiFiNINA.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "Display.hpp"
#include "Joystick.hpp"


#define VRx_pin A0
#define VRy_pin A1


U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R1, /* clock=*/ I2C_SCL, /* data=*/ I2C_SDA, /* reset=*/ U8X8_PIN_NONE);
Joystick myJoystick(VRx_pin, VRy_pin);
Display myDisplay(u8g2, myJoystick);

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  myDisplay.start();
}

void loop() {
  //myDisplay->drawArrowBasedOnCoordinate(String(position_x), String(position_y));
  //myDisplay->showCoordinates("X: " + String(position_x), "Y: " + String(position_y));
  //Serial.println("X: " + String(position_x) + " Y: " + String(position_y));
}