#include "Myoware.h"

Myoware left(A0);
Myoware right(A2);

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  Serial.print(left.getFlex()*50);
  Serial.print(" ");
  Serial.print(right.getFlex()*50);
  Serial.println();
  delay(5);
}
