#ifndef Myoware_h
#define Myoware_h
#include "Arduino.h"
#include <Filters.h>

class Myoware {
public:
    Myoware(int thePin);
    float getFlex();
    float getRaw();
private:
    int pin;

    FilterOnePole filterHighpass;
    FilterTwoPole filterLowpass;
};

#endif
