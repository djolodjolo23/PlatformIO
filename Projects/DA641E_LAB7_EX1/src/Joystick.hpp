#pragma once

class Joystick {
    private:
        uint8_t VRx_pin;
        uint8_t VRy_pin;

    public:

        enum State {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            CLICK,
            NONE
        };

        Joystick(uint8_t VRx_pin, uint8_t VRy_pin)
         : VRx_pin(VRx_pin), VRy_pin(VRy_pin) {
            pinMode(VRx_pin, INPUT);
            pinMode(VRy_pin, INPUT);
        }


        State readState() {
            int value_x = analogRead(VRx_pin);
            int value_y = analogRead(VRy_pin);
            Serial.println("X: " + String(value_x) + " Y: " + String(value_y));
            if (value_x < 300) {
                return LEFT;
            } else if (value_x > 700 && value_x < 900) {
                return RIGHT;
            } else if (value_y < 300) {
                return DOWN;
            } else if (value_y > 700) {
                return UP;
            } else if (value_x > 900) {
                return CLICK;
            } else {
                return NONE;
            }
        }
        
};
