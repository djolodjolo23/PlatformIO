#ifndef BUZZER_H
#define BUZZER_H

class buzzer {

    private:
        int pin;

    public:

        buzzer(int pin);

        void playTone(double tone, double duration);

        void playMelody(double melody[], double noteDurations[], int melodySize, int bpm);
};

#endif