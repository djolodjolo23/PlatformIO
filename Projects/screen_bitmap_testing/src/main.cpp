#include <Arduino.h>
#include <PDM.h>
#include "display.h"


display* myDisplay; // pointer
U8G2_SH1107_SEEED_128X128_F_HW_I2C u8g2(U8G2_R1, /* clock=*/ I2C_SCL, /* data=*/ I2C_SDA, /* reset=*/ U8X8_PIN_NONE);


/**
 * @brief      Arduino setup function
 */
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);

    u8g2.begin();
    myDisplay = new display(u8g2);
}

void loop()
{
    myDisplay->biryani();
    delay(2000);
    myDisplay->spaghetti();
    delay(2000);
    myDisplay->unknown();
    delay(2000);
    myDisplay->hamburger();
    delay(2000);
}