#include "Arduino.h"
#ifndef Myoware_h
#define Myoware_h

class Myoware {
public:
    Myoware(int thePin);
    float getValue();
    float processSignal();
private:
    int pin;

    int sensorValue;
    float sensorBack;

// high passed signal (>150Hz)
    float hpval;
    float hpback1;
    float hpback2;

// low passed value
    float lowval;
    float lowback1;
    float lowback2;
}

#endif
