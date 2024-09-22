#include "display.h"

display::display(U8G2 &u8g2_instance) : u8g2(u8g2_instance) {
}

void display::clearArrowArea() {
    u8g2.setDrawColor(0);  
    u8g2.drawBox(30, 30, 68, 68); 
    u8g2.setDrawColor(1);
}

void display::rightArrow() {
    clearArrowArea();
    u8g2.drawLine(32, 64, 96, 64);  
    u8g2.drawLine(96, 64, 86, 54); 
    u8g2.drawLine(96, 64, 86, 74);  
    u8g2.sendBuffer();
}

void display::leftArrow() {
    clearArrowArea();
    u8g2.drawLine(96, 64, 32, 64);  
    u8g2.drawLine(32, 64, 42, 54);  
    u8g2.drawLine(32, 64, 42, 74);  
    u8g2.sendBuffer();
}

void display::upArrow() {
    clearArrowArea();
    u8g2.drawLine(64, 32, 64, 96);  
    u8g2.drawLine(64, 32, 54, 42);  
    u8g2.drawLine(64, 32, 74, 42);  
    u8g2.sendBuffer();
}

void display::downArrow() {
    clearArrowArea();
    u8g2.drawLine(64, 96, 64, 32);  
    u8g2.drawLine(64, 96, 54, 86);  
    u8g2.drawLine(64, 96, 74, 86); 
    u8g2.sendBuffer();
}

void display::showCoordinates(String text1, String text2) {
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