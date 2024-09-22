#include <Arduino.h>
#include "buzzer.h"

buzzer myBuzzer(A2);


double notes[] = {
    329.63, 329.63, 349.23, 392.00, 392.00, 349.23, 329.63, 293.66, 261.63, 261.63, 293.66, 329.63, 329.63, 293.66, 293.66, 0.00, 
    329.63, 329.63, 349.23, 392.00, 392.00, 349.23, 329.63, 293.66, 261.63, 261.63, 293.66, 329.63, 293.66, 261.63, 261.63, 0.00, 
};

double noteDurations[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.5, 0.5, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.5, 0.5, 2, 2, 
};

int numNotes = sizeof(notes) / sizeof(notes[0]);
int numOfDurations = sizeof(noteDurations) / sizeof(noteDurations[0]);
int bpm = 125;

void setup() {
    Serial.begin(9600);
}

void loop() {
    myBuzzer.playMelody(notes, noteDurations, numNotes, bpm);
}