#pragma once
#include <Arduino.h>

class ExpMovAvgSender {

    private:

        int rawX = 0;
        int rawY = 0;
        int threshold = 320;

        float smoothedX = 0.0;
        float prevSmoothedX = 0.0;
        float smoothedY = 0.0;
        float prevSmoothedY = 0.0;

        float weight = 0.1;

        float* xRaw;
        float* yRaw;
        float* xFiltered;
        float* yFiltered;

        int samples;
        int intervalMs;
        
    public:
        ExpMovAvgSender(float* xRaw, float* yRaw, float* xFiltered, float* yFiltered, int samples, int intervalMs)
        : xRaw(xRaw), yRaw(yRaw), xFiltered(xFiltered), yFiltered(yFiltered), samples(samples) {
            this->intervalMs = intervalMs;
        }

        void calculateRawAndAvg() {
            rawX = analogRead(A0);
            rawY = analogRead(A1);
            //smoothedX = filter(rawX, weight, prevSmoothedX);
            //smoothedY = filter(rawY, weight, prevSmoothedY);
            //prevSmoothedX = smoothedX;
            //prevSmoothedY = smoothedY;
            if (prevSmoothedX == 0.0) {
                smoothedX = rawX;
                prevSmoothedX = rawX;
            } else {
                smoothedX = filter(rawX, weight, prevSmoothedX);
            }
            if (prevSmoothedY == 0.0) {
                smoothedY = rawY;
                prevSmoothedY = rawY;
            } else {
                smoothedY = filter(rawY, weight, prevSmoothedY);
            }

            prevSmoothedX = smoothedX;
            prevSmoothedY = smoothedY;
            
        }

        void fillUpBuffers() {
            for (int i =0; i < samples; i++) {
                calculateRawAndAvg();
                xRaw[i] = rawX;
                yRaw[i] = rawY;
                xFiltered[i] = smoothedX;
                yFiltered[i] = smoothedY;
                delay(intervalMs);
            }
        }

        float filter(float rawVal, float w, float prevVal) {
            float result = w * rawVal + (1.0 - w) * prevVal;
            return result;
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