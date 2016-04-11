#ifndef MBED_robotDS_H
#define MBED_robotDS_H

#include "mbed.h"

class motor1 {
public:
    motor1(PinName pin1, PinName pin2, PinName pin3);
    void run1(pin1, pin2, pin3);

private:
    DigitalOut _pin1; //direction
    DigitalOut _pin2; //sleep
    PwmOut _pin3; //PWM

};

class motor2 {
public:
    motor2(PinName pin1, PinName pin2);
    void run2(pin1, pin2);

private:
    DigitalOut _pin1; //direction
    PwmOut _pin2; //PWM

};

#endif
