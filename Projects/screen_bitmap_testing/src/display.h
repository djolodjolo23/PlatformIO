#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <U8g2lib.h> 


class display {
    private:

        U8G2 &u8g2;   

    public:
        display(U8G2 &u8g2_instance);

        void clearArea();
        void hamburger();
        void biryani();
        void spaghetti();
        void unknown();
};

#endif