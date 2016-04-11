#include "robotDS.h"
#include "mbed.h"

Flasher::Flasher(PinName pin) : _pin(pin) {
    _pin = 0;
}

void Flasher::flash(int n) {
    for(int i=0; i<n*2; i++) {
        _pin = !_pin;
        wait(0.2);
    }
}
