#include "Mouse.h"
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include "Myoware.h"

Adafruit_MMA8451 mma = Adafruit_MMA8451();

Myoware leftEMG(A2);
Myoware rightEMG(A3);

float myo_threshold = 0.25;

int click_delay = 1300; // in ms

int x, y;

int left_clicked = 0;
int right_clicked = 0;
int drag_clicked = 0;

unsigned long left_start = 0;
unsigned long right_start = 0;
unsigned long drag_start = 0;

void setup() {
  Serial.begin(115200);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  Mouse.begin();
}

void loop() {
  // Mouse Control
  x = map(analogRead(A4), 374, 628, 1023, 0);
  y = map(analogRead(A5), 380, 644, 0, 1023);

  // Range of deviation from center when idle
  if (y < 562  && y > 484) {
    y = 512;
  } else if (y > 561) {
    y = map(y, 562, 1023, 512, 548);
  } else if (y < 485) {
    y = map(y, 0, 484, 476, 512);
  }

  // Range of deviation from center when idle
  if (x < 511 && x > 498) {
    x = 512;
  } else if (x > 510) {
    x = map(x, 511, 1023, 512, 548);
  } else if (x < 499) {
    x = map(x, 0, 498, 476, 512);
  }
  Mouse.move(x, y, 0);

  float rightFlex = rightEMG.getFlex();
  Serial.print(rightFlex * 100);
  Serial.print(" ");
  float leftFlex = leftEMG.getFlex();
  Serial.println(leftFlex * 100);
  
  boolean leftDetect = leftFlex > myo_threshold;
  boolean rightDetect = rightFlex > myo_threshold;

  unsigned long currTime = millis();

  //  DRAG CLICK
  //  ANALOG VERSION
  if (leftDetect) {
    if (drag_clicked == 0) { //&& (currTime - drag_start) > click_delay) {
      Mouse.press();
      drag_clicked = 1;
    }
  } else {
    Mouse.release();
    drag_clicked = 0;
  }

  //  DIGITAL VERSION
  //  if ( "stomach button event" ) {
  //    if (drag_clicked == 0) {
  //      Mouse.press();
  //      drag_clicked = 1;
  //    } else if (drag_clicked == 1) {
  //      Mouse.release();
  //      drag_clicked = 0;
  //    }
  //    drag_start = drag_clicked + 1;
  //  }

  // RIGHT CLICK
  if (rightDetect) {
    if ((currTime - right_start) > click_delay) {
      Mouse.click(MOUSE_RIGHT);
      right_start = millis();
    }
  }

  // LEFT CLICK
  //  if (leftDetect) {
  //    if ((currTime-left_start) > click_delay) {
  //      Mouse.press();
  //      left_start = millis();
  //    }
  //  } else {
  //    Mouse.release();
  //  }
}
