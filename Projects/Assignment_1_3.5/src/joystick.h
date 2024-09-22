#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "display.h"

class joystick {
    private:
        uint8_t VRx_pin;
        uint8_t VRy_pin;
        display* myDisplay;
        
        static const int joystick_x_upper_standing_limit;
        static const int joystick_x_lower_standing_limit;
        static const int joystick_y_upper_standing_limit;
        static const int joystick_y_lower_standing_limit;
        static const int upper_coordinate_limit;
        static const int lower_coordinate_limit;

    public:
        joystick(uint8_t VRx_pin, uint8_t VRy_pin, display* myDisplay);
        
        void readAndTurnOnRgb(int &value_x, int &value_y);
        
};

#endif