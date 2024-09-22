#include <Arduino.h>
#include "buzzer.h"

buzzer::buzzer(int pin) : pin(pin) {
    pinMode(pin, OUTPUT);
}

void buzzer::playTone(double frequency, double duration) {
    tone(pin, frequency);
    delay(duration);
    noTone(pin);
}

void buzzer::playMelody(double notes[], double noteDurations[], int melodySize, int bpm) {
    Serial.println("Playing melody");
    int durationMultiplier = 60000 / bpm;
    for (int i = 0; i < melodySize; i++) {

        double currentNote = notes[i];
        double currentDuration = noteDurations[i];
        int durationMs = durationMultiplier * currentDuration;

        Serial.println(currentNote);
        Serial.println(durationMs);
        // silence 
        if (currentNote == 0.00) {
            Serial.println("Rest");
            noTone(pin);
            delay(durationMs);
        } else {
            playTone(currentNote, durationMs);
        }
    }
}