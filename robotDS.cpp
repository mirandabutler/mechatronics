#include "robotDS.h"
#include "mbed.h"


//Running Motor (3 pins)
motor1::motor1(PinName direction, PinName sleep, PinName pwm) : _direction(direction), _sleep(sleep), _pwm(pwm) {
    //init
    // _direction = 0;
    // _sleep = 0;
    // _pwm.period = 0;
}

void motor1::run1(int DIR, int SLP, float speed) {
    _direction = DIR;
    _sleep = SLP;
    _pwm.period(speed);
    wait(.01);
}


// //Running Motor (2 pins)
// motor1::run1(PinName pin1, PinName pin2, PinName pin3) : _pin(pin) {
//     // (finish)
// }
//
// void motor2::run2(int DIR, int speed) {
//     pin1 = DIR;
//     pin2.period(speed);
//     wait(.01);
// }
