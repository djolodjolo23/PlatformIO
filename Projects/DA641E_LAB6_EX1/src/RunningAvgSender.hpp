#pragma once
#include <Arduino.h>

class RunningAvgSender {

    private:
        static constexpr int avgSize = 10; 
        float avgBuffer1[avgSize];
        float avgBuffer2[avgSize];

        float avgX = 0;
        float avgY = 0;
        float rawX = 0;
        float rawY = 0;

        int avgSize = 10; 
        float* xRaw;
        float* yRaw;
        float* xFiltered;
        float* yFiltered;

        int samples;
        int intervalMs;
        
    public:
        RunningAvgSender(float* xRaw, float* yRaw, float* xFiltered, float* yFiltered, int samples, int intervalMs)
        : xRaw(xRaw), yRaw(yRaw), xFiltered(xFiltered), yFiltered(yFiltered), samples(samples) {
            this->intervalMs = intervalMs;
        }

        void calculateRawAndAvg() {
            avgX = 0;
            avgY = 0;
            for (int i = 0; i < avgSize; i++) {
                float val1 = analogRead(A0);
                float val2 = analogRead(A1);
                avgX += val1;
                avgY += val2;
                delay(1); 
                if (i == 5) {
                    rawX = val1;
                    rawY = val2;
                }
            }
            avgX /= avgSize;
            avgY /= avgSize;
        }

        void fillUpBuffers() {
            for (int i =0; i < samples; i++) {
                calculateRawAndAvg();
                xRaw[i] = rawX;
                yRaw[i] = rawY;
                xFiltered[i] = avgX;
                yFiltered[i] = avgY;
                delay(intervalMs);
            }
        }

        void print() {
            Serial.println("xRaw, yRaw, xFiltered, yFiltered");
            for (int i = 0; i < samples; i++) {
                Serial.print(xRaw[i]);
                Serial.print(", ");
                Serial.print(yRaw[i]);
                Serial.print(", ");
                Serial.print(xFiltered[i]);
                Serial.print(", ");
                Serial.println(yFiltered[i]);
            }
        }
};