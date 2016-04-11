#ifndef MBED_robotDS_H
#define MBED_robotDS_H

#include "mbed.h"

class Flasher {
public:
    Flasher(PinName pin);
    void flash(int n);

private:
    DigitalOut _pin;
};

#endif
