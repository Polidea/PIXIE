#include "Led.h"

Led::Led(int pin) : pin_(pin){
    fakeServo_.attach(pin, 0, 65535);
}

void Led::show(float power) {
    currentPower_ = power;
    fakeServo_.writeMicroseconds(0.32 * (currentPower_)*65535);
}

void Led::blink(float frequency) {
    if (increasing_) {
        float power = currentPower_ + (0.020 * frequency);
        if (power > 1) {
            show(1);
            increasing_ = false;
        }
        else {
            show(power); 
        }
    }
    else {
        float power = currentPower_ - (0.020 * frequency);
        if (power < 0) {
            show(0);
            increasing_ = true;
        }
        else {
            show(power);
        }
    }
}
