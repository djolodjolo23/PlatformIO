#pragma once

#include "Display.hpp"

class Joystick {
    private:
        uint8_t VRx_pin;
        uint8_t VRy_pin;
        Display* myDisplay;
        
        const int joystick_x_upper_standing_limit = 530;
        const int joystick_x_lower_standing_limit = 500;
        const int joystick_y_upper_standing_limit = 520;
        const int joystick_y_lower_standing_limit = 490;
        const int upper_coordinate_limit = 625;
        const int lower_coordinate_limit = 375;

    public:

        Joystick(uint8_t VRx_pin, uint8_t VRy_pin, Display* disp)
         : VRx_pin(VRx_pin), VRy_pin(VRy_pin), myDisplay(disp) {
            pinMode(VRx_pin, INPUT);
            pinMode(VRy_pin, INPUT);
        }

        
        void readAndTurnOnRgb(int &value_x, int &value_y) {
            value_x = analogRead(VRx_pin);
            value_y = analogRead(VRy_pin);

            if (value_x > joystick_x_upper_standing_limit && (value_y > lower_coordinate_limit || value_y < upper_coordinate_limit)) {
                myDisplay->rightArrow();
            } else if (value_x < joystick_x_lower_standing_limit && (value_y > lower_coordinate_limit || value_y < upper_coordinate_limit)) {
                myDisplay->leftArrow();
            } else if (value_y > joystick_y_upper_standing_limit && (value_x > lower_coordinate_limit || value_x < upper_coordinate_limit)) {
                myDisplay->upArrow();
            } else if (value_y < joystick_y_lower_standing_limit && (value_x > lower_coordinate_limit || value_x < upper_coordinate_limit)) {
                myDisplay->downArrow();
            } else {
                myDisplay->clearArrowArea();
            }
        }
        
};
