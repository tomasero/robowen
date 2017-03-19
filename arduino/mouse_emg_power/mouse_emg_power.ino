#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include "Myoware.h"
#include <Mouse.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

Myoware leftEMG(A0);
Myoware rightEMG(A2);

float myo_threshold = 0.28;

int click_delay = 1300; // in ms
int emg_power_delay = 5000; // in ms, how long EMG must be held to turn chair on and off

int prev_x, raw_x, x, raw_y, y;

int left_clicked = 0;
int right_clicked = 0;
int drag_clicked = 0;

unsigned long left_start = 0;
unsigned long right_start = 0;
unsigned long drag_start = 0;
unsigned long nudge_start = 0;
unsigned long timer = 0;

boolean chair_state = true;
boolean chair_on_off = false;

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
  if (millis() - nudge_start > 3) {
    raw_x = analogRead(A3);
    nudge_start = millis();
  }
  raw_y = analogRead(A5);
  x = map(raw_x, 374, 628, 1023, 0);
  y = map(raw_y, 380, 644, 0, 1023);

  // Range of deviation from center when idle
  if (y < 562  && y > 484) {
    y = 512;
  } else if (y > 561) {
    y = map(y, 562, 1023, 512, 534);
  } else if (y < 485) {
    y = map(y, 0, 484, 490, 512);
  }

  // Range of deviation from center when idle
  if (x < 511 && x > 498) {
    x = 512;
  } else if (x > 510) {
    x = map(x, 511, 1023, 512, 534);
  } else if (x < 499) {
    x = map(x, 0, 498, 490, 512);
  }
  // Comment this out if using the NUDGE CLICK
  Mouse.move(x, y, 0);

  float rightFlex = rightEMG.getFlex();
  float leftFlex = leftEMG.getFlex();
  Serial.print(rightFlex * 100);
  Serial.print(" ");
  Serial.println(leftFlex * 100);
  
  boolean leftDetect = leftFlex > myo_threshold;
  boolean rightDetect = rightFlex > myo_threshold;

  unsigned long currTime = millis();

  // Chair on/off detection
  if (leftDetect && rightDetect) {
    if (chair_on_off) {
      if (currTime - timer > emg_power_delay){
        chair_state = !chair_state;
        chair_on_off = false;
      }
    }
    else {
      timer = millis();
      chair_on_off = true;
    }
  }


  if (!chair_state) {
    return;
  }

  //  DRAG CLICK
  if (leftDetect) {
    if (drag_clicked == 0) { 
      Mouse.press();
      drag_clicked = 1;
    }
  } else {
    Mouse.release();
    drag_clicked = 0;
  }

  // RIGHT CLICK
  if (rightDetect) {
    if ((currTime - right_start) > click_delay) {
      Mouse.click(MOUSE_RIGHT);
      right_start = millis();
    }
  }

//  NUDGE CLICK
//  (works only in the absence of EMG clicks)
//
//  delay(4);
//  new_x = analogRead(A3) - raw_x;
//  Serial.println(prev_x);
//  if (abs(prev_x) > 5) {
//    Mouse.click();
//  } else {
//    Mouse.move(x, y, 0);
//  }
}
