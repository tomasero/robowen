#include "Arduino.h"
#include "Myoware.h"
#include <Filters.h>

Myoware::Myoware(int thePin) {
    pinMode(thePin, INPUT);
    pin = thePin;

    // highpass 90Hz filter first to get the signal
    filterHighpass.setFilter(HIGHPASS, 90, 0);
    // follow up with a lowpass 0.5 Hz filter on the absolute value
    filterLowpass.setAsFilter(LOWPASS_BUTTERWORTH, 1.0);
}

float Myoware::getFlex() {
    float sensorValue = analogRead(pin);
    filterHighpass.input(sensorValue);
    filterLowpass.input(abs(filterHighpass.output()));
    return filterLowpass.output();
}

float Myoware::getRaw() {
  return analogRead(pin);
}

