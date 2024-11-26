#pragma once
#include <Arduino.h>


class FlatVibrationMotor
{
private:
    int m_pin;
    int m_num_vibrations = 0;
public:
    FlatVibrationMotor(int pin) : m_pin(pin) {
        pinMode(m_pin, OUTPUT);
    }

    void vibrate() {
        digitalWrite(m_pin, HIGH);
        delay(100);
        digitalWrite(m_pin, LOW);
        m_num_vibrations++;
    }

    int getNumberOfVibrations() {
        return m_num_vibrations;
    }

    void setNumberOfVibrations(int num) {
        m_num_vibrations = num;
    }

    
};

