#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <math.h>

class Display {
private:
    U8G2 &u8g2; 
    int max_x_y_joystick = 750;
    int min_x_y_joystick = 250;
    int max_x_y_display = 128;
    int min_x_y_display = 0;
    int center_x_y_display = 64;
    int maxRadius = 80;

public:
    Display(U8G2 &u8g2_instance) : u8g2(u8g2_instance) {}

    void clearArrowArea() {
        u8g2.setDrawColor(0);
        u8g2.drawBox(30, 30, 98, 98); 
        u8g2.setDrawColor(1);
    }

    void rightArrow() {
        clearArrowArea();
        u8g2.drawLine(32, 64, 96, 64);
        u8g2.drawLine(96, 64, 86, 54);
        u8g2.drawLine(96, 64, 86, 74);
        u8g2.sendBuffer();
    }

    void leftArrow() {
        clearArrowArea();
        u8g2.drawLine(96, 64, 32, 64);
        u8g2.drawLine(32, 64, 42, 54);
        u8g2.drawLine(32, 64, 42, 74);
        u8g2.sendBuffer();
    }

    void upArrow() {
        clearArrowArea();
        u8g2.drawLine(64, 32, 64, 96);
        u8g2.drawLine(64, 32, 54, 42);
        u8g2.drawLine(64, 32, 74, 42);
        u8g2.sendBuffer();
    }

    void downArrow() {
        clearArrowArea();
        u8g2.drawLine(64, 96, 64, 32);
        u8g2.drawLine(64, 96, 54, 86);
        u8g2.drawLine(64, 96, 74, 86);
        u8g2.sendBuffer();
    }

    void drawArrowBasedOnCoordinate(const String &text1, const String &text2){
        // convert string to integer
        clearArrowArea();
        int rawX =  text1.toInt();
        int rawY = text2.toInt();
        int x = scaleValue(rawX);
        int y = scaleValue(rawY);
        x = constrain(x, min_x_y_display, max_x_y_display);
        y = constrain(y, min_x_y_display, max_x_y_display);
        //scaleToRadius(x, y);
        Serial.println("X: " + String(x) + " Y: " + String(y));
        u8g2.drawLine(64, 64, x, y);
        u8g2.sendBuffer();
    }

    int scaleValue(int originalValue) {
        return min_x_y_display + ((originalValue - min_x_y_joystick) * (max_x_y_display - min_x_y_display)) / (max_x_y_joystick - min_x_y_joystick);
    }

    void scaleToRadius(int &x, int &y) {
        // Calculate the distance from the center
        float dx = x - center_x_y_display;
        float dy = y - center_x_y_display;
        float distance = sqrt(dx * dx + dy * dy);

        // Prevent division by zero when the joystick is at the center
        if (distance == 0) {
            return; // The point is already at the center
        }

        // Calculate the scaling factor
        float scaleFactor = min(1.0, (float)maxRadius / distance);

        // Scale the coordinates toward the center
        x = center_x_y_display + dx * scaleFactor;
        y = center_x_y_display + dy * scaleFactor;

        // Debugging: Print the scaled values
        Serial.println("Scaled X: " + String(x) + " Y: " + String(y));
    }

    void showCoordinates(const String &text1, const String &text2) {
        u8g2.setFont(u8g2_font_ncenB08_tr);

        u8g2.setDrawColor(0);
        u8g2.drawBox(0, 0, 128, 16);
        u8g2.setDrawColor(1);
        u8g2.drawStr(0, 10, text1.c_str());

        u8g2.setDrawColor(0);
        u8g2.drawBox(0, 112, 128, 16);
        u8g2.setDrawColor(1);
        u8g2.drawStr(0, 126, text2.c_str());

        u8g2.sendBuffer();
    }
};
