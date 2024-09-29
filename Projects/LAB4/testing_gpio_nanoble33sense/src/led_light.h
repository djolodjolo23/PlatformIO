#ifndef LED_LIGHT_H
#define LED_LIGHT_H

#include <Arduino.h>

class LedLight {
  private:
    int redPin;
    int greenPin;
    int bluePin;

  public:
    // Constructor
    LedLight(int redPin, int greenPin, int bluePin);

    // Methods to turn on/off LEDs
    void turnOnRed();
    void turnOffRed();
    void turnOnGreen();
    void turnOffGreen();
    void turnOnBlue();
    void turnOffBlue();
};

#endif
