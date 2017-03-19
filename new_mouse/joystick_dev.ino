#include "Mouse.h"
#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();
int responseDelay = 5;
int x, y;
int click_delay = 500;
int left_count = 501;
int left_clicked = 0;
int right_count = 501;
int right_clicked = 0;

int drag_count = 501;
int drag_clicked = 0;

void setup() {
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

//  DRAG CLICK FOR STOMACH BUTTON SIGNAL
//  ANALOG VERSION
  if (analogRead(A2) > 420) {
    if (drag_clicked == 0 && drag_count > click_delay) {
      Mouse.press();
      drag_clicked = 1;
      drag_count = 0;
    } else if (drag_clicked == 1 && drag_count > click_delay) {
      Mouse.release();
      drag_clicked = 0;
      drag_count = 0; 
    }
    drag_count = drag_count + 1;
  } else {
    drag_count = click_delay + 1;
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
//    drag_count = drag_clicked + 1;
//  }

// RIGHT CLICK
  if (analogRead(A3) > 420) {
    if (right_count > click_delay) {
      Mouse.click(MOUSE_RIGHT);
      right_count = 0;
    }
    right_count = right_count + 1;
  } else {
    right_count = click_delay + 1;
  }

// LEFT CLICK
//  if (analogRead(A1) > 420) {
//    if (left_count > click_delay) {
//      Mouse.click();
//      left_count = 0;
//    }
//    left_count = left_count + 1;
//  } else {
//    left_count = click_delay + 1;
//  }
  
  delay(responseDelay);
}
