#include "robotDS.h"
#include "mbed.h"


//Motor (3 pins)
motor1::motor1(PinName direction, PinName sleep, PinName pwm) : _direction(direction), _sleep(sleep), _pwm(pwm) {
    //init
}

void motor1::run1(int SLP, int DIR, float per, float speed) {
    _direction = DIR;
    _sleep = SLP;
    _pwm.period(per);
    _pwm.write(speed);
    wait(.01);
}


//Motor (2 pins)
motor2::motor2(PinName direction, PinName pwm) : _direction(direction), _pwm(pwm) {
    // (init)
}

void motor2::run2(int DIR, float per, float speed) {
    _direction = DIR;
    _pwm.period(per);
    _pwm.write(speed);
    wait(.01);
}

//Max4617 switch
max4617::max4617(PinName pinA, PinName pinB, PinName pinC) : _pinA(pinA), _pinB(pinB), _pinC(pinC) {
    //
}

void max4617::maxSwitch(int A, int B, int C) {
    _pinA = A;
    _pinB = B;
    _pinC = C;
}
