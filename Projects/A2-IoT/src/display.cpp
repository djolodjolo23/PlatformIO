#include "display.h"
#include "burger_oled_image_76x76.h"
#include "biryani_oled_image_76x76.h"
#include "spaghetti_oled_image_76x76.h"
#include "unknown_oled_image_76x76.h"

display::display(U8G2 &u8g2_instance) : u8g2(u8g2_instance) {
}



void display::drawCenteredText(const char* str, int y) {
    int strWidth = u8g2.getStrWidth(str);  
    int x = (124 - strWidth) / 2;  
    u8g2.drawStr(x, y, str); 
}

void display::drawWrappedText(const char* str, int y, int maxWidth) {
    std::string message = str;
    int lineHeight = 10; 
    int startX = 5;
    int availableWidth = maxWidth - startX * 2;
    
    while (message.length() > 0) {
        int splitIndex = u8g2.getUTF8Width(message.c_str()) <= availableWidth ? message.length() : availableWidth / u8g2.getMaxCharWidth();
        
        if (splitIndex < message.length()) {
            int spacePos = message.rfind(' ', splitIndex);
            if (spacePos != -1) {
                splitIndex = spacePos;
            }
        }

        std::string line = message.substr(0, splitIndex);
        drawCenteredText(line.c_str(), y);
        message = message.substr(splitIndex);  // Move to the next part of the string
        message.erase(0, message.find_first_not_of(" \t\n\r\f\v"));  // Trim leading whitespace
        message.erase(message.find_last_not_of(" \t\n\r\f\v") + 1);  // Trim trailing whitespace
        y += lineHeight;
    }
}


void display::clearArea() {
    u8g2.setDrawColor(0);  
    u8g2.drawBox(24, 24, 68, 68); 
    u8g2.setDrawColor(1);
}

void display::clearScreen() {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

void display::inferenceStartInfo(int sec) {
    clearScreen();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    String message = "Starting inferencing in " + String(sec) + " seconds...";
    drawWrappedText(message.c_str(), 64, 124);
    u8g2.sendBuffer();
}

void display::recordInfo() {
    clearScreen();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    drawWrappedText("Recording...", 64, 124);
    u8g2.sendBuffer();
}

void display::recordingDone() {
    clearScreen();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    drawWrappedText("Recording done!", 64, 124);
    u8g2.sendBuffer();
}

void display::spaghetti() {
    clearScreen();
    u8g2.drawXBM(24, 0, 76, 76, spaghetti_oled_image_76x76);
    //draw text
    u8g2.setFont(u8g2_font_ncenB08_tr);
    drawWrappedText("You ordered Spaghetti! Comming soon!", 90, 124);
    u8g2.sendBuffer();

}

void display::unknown() {
    clearScreen();
    u8g2.drawXBM(24, 0, 76, 76, unknown_oled_image_76x76);
    u8g2.setFont(u8g2_font_ncenB08_tr);
    drawWrappedText("Unknown food! Please try again.", 90, 124);

    u8g2.sendBuffer();
    
}

void display::hamburger() {
    clearScreen();
    u8g2.drawXBM(24, 0, 76, 76, burger_oled_image_76x76);
    u8g2.setFont(u8g2_font_ncenB08_tr);
    drawWrappedText("You ordered Hamburger! Comming soon!", 90, 124);
    u8g2.sendBuffer();
}

void display::biryani() {
    clearScreen();
    u8g2.drawXBM(24, 0, 76, 76, biryani_oled_image_76x76);
    u8g2.setFont(u8g2_font_ncenB08_tr);
    drawWrappedText("You ordered Biryani! Comming soon!", 90, 124);
    u8g2.sendBuffer();
}

void display::drawImage(String imageName) {
    clearScreen();
    if (imageName == "hamburger") {
        hamburger();
    } else if (imageName == "biryani") {
        biryani();
    } else if (imageName == "spaghetti") {
        spaghetti();
    } else {
        unknown();
    }
}
