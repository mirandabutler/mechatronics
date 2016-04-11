#ifndef MBED_robotDS_H
#define MBED_robotDS_H

#include "mbed.h"

class motor1 {
public:
    motor1(PinName direction, PinName sleep, PinName pwm);
    void run1(pin1, pin2, pin3);

private:
    DigitalOut _direction; //direction
    DigitalOut _sleep; //sleep
    PwmOut _pwm; //PWM

};

// class motor2 {
// public:
//     motor2(PinName pin1, PinName pin2);
//     void run2(pin1, pin2);
//
// private:
//     DigitalOut _pin1; //direction
//     PwmOut _pin2; //PWM
//
// };

#endif
