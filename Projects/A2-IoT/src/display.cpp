#include "display.h"
#include "burger_oled_image_76x76.h"
#include "biryani_oled_image_76x76.h"
#include "spaghetti_oled_image_76x76.h"
#include "unknown_oled_image_76x76.h"

display::display(U8G2 &u8g2_instance) : u8g2(u8g2_instance) {
}

void display::clearArea() {
    u8g2.setDrawColor(0);  
    u8g2.drawBox(30, 30, 68, 68); 
    u8g2.setDrawColor(1);
}

void display::spaghetti() {
    clearArea();
    u8g2.drawXBM(35, 10, 76, 76, spaghetti_oled_image_76x76);
    u8g2.sendBuffer();
}

void display::unknown() {
    clearArea();
    u8g2.drawXBM(35, 10, 76, 76, unknown_oled_image_76x76);
    u8g2.sendBuffer();
    
}


void display::hamburger() {
    clearArea();
    u8g2.drawXBM(35, 10, 76, 76, burger_oled_image_76x76);
    u8g2.sendBuffer();
}



void display::biryani() {
    clearArea();
    u8g2.drawXBM(35, 10, 76, 76, biryani_oled_image_76x76);
    u8g2.sendBuffer();
}
