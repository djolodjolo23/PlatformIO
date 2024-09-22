#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Initialize for SH1107 Seeed 96x96 OLED display using Software I2C
U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R1, /* clock=*/ I2C_SCL, /* data=*/ I2C_SDA, /* reset=*/ U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();  // Initialize the display
}

void loop(void) {
  u8g2.clearBuffer();                    // Clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);    // Choose a suitable font
  u8g2.drawLine(32, 64, 96, 64);         // Horizontal line for the shaft

  // draw the upper diagonal line of the arrowhead
  u8g2.drawLine(96, 64, 86, 54);         // Longer upper diagonal line of the arrowhead
  u8g2.drawLine(96, 64, 86, 74);         // Longer lower diagonal line of the arrowhead

  u8g2.sendBuffer();                     // Transfer internal memory to the display
  delay(1000);                           // Wait for 1 second
  u8g2.clearBuffer();                    // Clear the internal memory
  u8g2.clearDisplay();    
  delay(1000);               // Clear the display
}