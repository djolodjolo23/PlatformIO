#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <Joystick.hpp>
#include <u8g2_logo_transparent_orange_oled_image_85x44.h>

class Display {
private:
    U8G2 &u8g2; 
    Joystick &joystick;
    String menuItems[5] = { "Item 1", "Item 2", "Item 3", "Item 4", "Item 5" };
    String subMenuItems[3] = { "Sub Item 1", "Sub Item 2", "Sub Item 3" };
    int currentMenuItem = 0;
    bool logoDisplayed = false;

public:
    Display(U8G2 &u8g2_instance, Joystick &joystick_instance) 
    : u8g2(u8g2_instance), joystick(joystick_instance) {}

    enum menuState {
        MAIN,
        SUB,
    };

    void start() {
        menuState menuState = MAIN; 
        showMenu(menuItems, 5, currentMenuItem); 

        while (true) {
            Joystick::State state = joystick.readState();

            switch (state) {
                case Joystick::UP:
                    if (!logoDisplayed) {
                        if (menuState == MAIN) {
                            currentMenuItem = (currentMenuItem == 0) ? 4 : currentMenuItem - 1; 
                            showMenu(menuItems, 5, currentMenuItem);
                        } else if (menuState == SUB) {
                            currentMenuItem = (currentMenuItem == 0) ? 2 : currentMenuItem - 1; 
                            showMenu(subMenuItems, 3, currentMenuItem);
                        }
                    }
                    break;

                case Joystick::DOWN:
                    if (!logoDisplayed) {
                        if (menuState == MAIN) {
                            currentMenuItem = (currentMenuItem == 4) ? 0 : currentMenuItem + 1; 
                            showMenu(menuItems, 5, currentMenuItem);
                        } else if (menuState == SUB) {
                            currentMenuItem = (currentMenuItem == 2) ? 0 : currentMenuItem + 1; 
                            showMenu(subMenuItems, 3, currentMenuItem);
                        }
                    }
                    break;

                case Joystick::RIGHT:
                case Joystick::CLICK:
                    if (!logoDisplayed) {
                        if (menuState == MAIN && currentMenuItem == 2) {
                            currentMenuItem = 0;
                            menuState = SUB;
                            showMenu(subMenuItems, 3, currentMenuItem);
                            Serial.println("Switched to Sub Menu");
                        } else {
                            displayLogo(); 
                            logoDisplayed = true;
                        }
                    }
                    break;

                case Joystick::LEFT:
                    if (logoDisplayed) {
                        logoDisplayed = false; 
                        if (menuState == MAIN) {
                            showMenu(menuItems, 5, currentMenuItem);
                        } else if (menuState == SUB) {
                            showMenu(subMenuItems, 3, currentMenuItem);
                        }
                    } else {
                        if (menuState == SUB) {
                            menuState = MAIN;
                            currentMenuItem = 2; 
                            showMenu(menuItems, 5, currentMenuItem);
                            Serial.println("Switched to Main Menu");
                        }
                    }
                    break;

                case Joystick::NONE:
                    break;
                default:
                    break;
            }

            delay(20);
        }
    }


    void showMenu(String items[], int itemsCount, int selectedItem) {
        int itemY = 14;
        u8g2.clearBuffer();
        u8g2.setFont(u8g2_font_ncenB12_tr);
        u8g2.setFontMode(1); 

        for (int i = 0; i < itemsCount; i++) {
            if (i == selectedItem) {
                u8g2.setDrawColor(1); 
                u8g2.drawBox(0, itemY - 13, 128, 15);

                u8g2.setDrawColor(0); 
                u8g2.drawStr(0, itemY, items[i].c_str());
            } else {
                u8g2.setDrawColor(1); 
                u8g2.drawStr(0, itemY, items[i].c_str());
            }

            u8g2.setDrawColor(1);
            itemY += 16;
        }
        u8g2.sendBuffer();
    }

    void displayLogo() {
        u8g2.clearBuffer();
        u8g2.setDrawColor(1); 
        u8g2.drawXBM(25, 25, 85, 44, u8g2_logo_transparent_orange_oled_image_85x44);
        u8g2.sendBuffer();
    }
};
