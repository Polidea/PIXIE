#ifndef LED_H
#define LED_H

#include "application.h"

class Led {
    public:
        explicit Led(int pin);
        void show(float power);
        void blink(float frequency);
    private:
        float currentPower_;
        bool increasing_;
        int pin_;
        Servo fakeServo_;
};

#endif
