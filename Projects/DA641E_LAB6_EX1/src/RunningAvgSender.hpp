#pragma once
#include <Arduino.h>

class RunningAvgSender {

    private:
        static constexpr int avgSize = 10; 
        float avgBufferX[avgSize];
        float avgBufferY[avgSize];
        int avgIndex = 0;

        float avgX = 0;
        float avgY = 0;
        float rawX = 0;
        float rawY = 0;

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

            avgBufferX[avgIndex] = analogRead(A0);
            avgBufferY[avgIndex] = analogRead(A1);
            avgIndex = (avgIndex + 1) % avgSize;

            for (int i = 0; i < avgSize; i++) {
                avgX += avgBufferX[i];
                avgY += avgBufferY[i];
                if (i == 5) {
                    rawX = avgBufferX[i];
                    rawY = avgBufferY[i];
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