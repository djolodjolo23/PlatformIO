#include <Arduino.h>
#include <WiFiNINA.h>
#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN 5
#define LED_PIN 25
#define LED_COUNT 24


int counter = 0;

uint8_t arr[3] = {0, 1, 2};
static bool lastButtonState = HIGH;


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setCurrentColour(int col);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  strip.setBrightness(30);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50); 
    counter = (counter + 1) % 3;      
    setCurrentColour(arr[counter]);   
  }

  lastButtonState = buttonState;      
  Serial.println(lastButtonState);
}


void setCurrentColour(int col) {
    int red = (col == 0) ? 255 : 0;
    int green = (col == 2) ? 255 : 0;
    int blue = (col == 1) ? 255 : 0;

    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    strip.show();
}
