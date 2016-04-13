#ifndef MBED_robotDS_H
#define MBED_robotDS_H

#include "mbed.h"

class motor1 {
    public:
        motor1(PinName direction, PinName sleep, PinName pwm);
        void run1(int DIR, int SLP, float per, float speed);

    private:
        DigitalOut _direction; //direction
        DigitalOut _sleep; //sleep
        PwmOut _pwm; //PWM
};

class motor2 {
    public:
        motor2(PinName direction, PinName pwm);
        void run2(int DIR, float per, float speed);

    private:
        DigitalOut _direction; //direction
        PwmOut _pwm; //PWM
};

class max4617 {
    public:
        max4617(PinName pinA, PinName pinB, PinName pinC);
        void maxSwitch(int A, int B, int C);

    private:
        DigitalOut _pinA;
        DigitalOut _pinB;
        DigitalOut _pinC;

};

#endif
