
#include "joystick.h"

const int joystick::joystick_x_upper_standing_limit = 530;
const int joystick::joystick_x_lower_standing_limit = 500;
const int joystick::joystick_y_upper_standing_limit = 520;
const int joystick::joystick_y_lower_standing_limit = 490;
const int joystick::upper_coordinate_limit = 625;
const int joystick::lower_coordinate_limit = 375;

joystick::joystick(uint8_t VRx_pin, uint8_t VRy_pin, display* disp) : VRx_pin(VRx_pin), VRy_pin(VRy_pin), myDisplay(disp) {
    pinMode(VRx_pin, INPUT);
    pinMode(VRy_pin, INPUT);
    
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);

    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
}


void joystick::readAndTurnOnRgb(int &value_x, int &value_y) {
    value_x = analogRead(VRx_pin);
    value_y = analogRead(VRy_pin);

    if (value_x > joystick_x_upper_standing_limit && (value_y > lower_coordinate_limit || value_y < upper_coordinate_limit)) {
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDB, LOW);
        myDisplay->rightArrow();
    } else if (value_x < joystick_x_lower_standing_limit && (value_y > lower_coordinate_limit || value_y < upper_coordinate_limit)) {
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, LOW);
        myDisplay->leftArrow();
    } else if (value_y > joystick_y_upper_standing_limit && (value_x > lower_coordinate_limit || value_x < upper_coordinate_limit)) {
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDB, HIGH);
        myDisplay->upArrow();
    } else if (value_y < joystick_y_lower_standing_limit && (value_x > lower_coordinate_limit || value_x < upper_coordinate_limit)) {
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, HIGH);
        digitalWrite(LEDB, LOW);
        myDisplay->downArrow();
    } else {
        digitalWrite(LEDR, LOW);
        digitalWrite(LEDG, LOW);
        digitalWrite(LEDB, LOW);
        myDisplay->clearArrowArea();
    }
}