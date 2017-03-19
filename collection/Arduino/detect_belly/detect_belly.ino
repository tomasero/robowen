/**************************************************************************/
/*!
  @file     Adafruit_MMA8451.h
  @author   K. Townsend (Adafruit Industries)
  @license  BSD (see license.txt)

  This is an example for the Adafruit MMA8451 Accel breakout board
  ----> https://www.adafruit.com/products/2019

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  @section  HISTORY

  v1.0  - First release
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

unsigned long time = 0;

// for detecting belly
float bellyArr[] = {-0.00975748,  0.05898267,  0.1972877 ,  0.33030744,  0.3870562 ,
                    0.2513518 , -0.02796029, -0.29437157, -0.27595468, -0.22089617,
                    -0.18336062, -0.09912632, -0.07430951, -0.07695034, -0.10330439,
                    -0.12752518, -0.12655274, -0.14258588, -0.11670343, -0.06548762,
                    0.02337672,  0.09663732,  0.141857  ,  0.21992208,  0.244688  ,
                    0.21309261,  0.14909269,  0.05097994, -0.02538929, -0.08695627,
                    -0.14038497, -0.15308613, -0.12130851, -0.06310996, -0.01760602,
                    0.01591391,  0.05002665,  0.05437263,  0.04097063,  0.02677141};

#define NFILT 40
float history[NFILT];

void updateHistory(float latest) {
        for(int i=0; i<NFILT-1; i++) {
                history[i] = history[i+1];
        }
        history[NFILT-1] = latest;
}

int count = 0;
float meanBelly = 0;

float calcBelly() {
        float out = 0;
        for(int i=0; i<NFILT; i++) {
                out += history[i] * bellyArr[i];
        }
        meanBelly = meanBelly*0.99 + out*0.01;
        out -= meanBelly;
        count++;
        if(count < 100) {
                return 0;
        } else {
                return out;
        }
}

void setup(void) {
        Serial.begin(115200);

//        Serial.println("Adafruit MMA8451 test!");


        if (! mma.begin()) {
                Serial.println("Couldnt start");
                while (1);
        }
//        Serial.println("MMA8451 found!");

        mma.setRange(MMA8451_RANGE_2_G);

//        Serial.print("Range = "); Serial.print(2 << mma.getRange());
//        Serial.println("G");

}

void loop() {
        // Read the 'raw' data in 14-bit counts
        mma.read();
//  Serial.print("X:\t"); Serial.print(mma.x);
//  Serial.print("\tY:\t"); Serial.print(mma.y);
//  Serial.print("\tZ:\t"); Serial.print(mma.z);
//  Serial.println();

        /* Get a new sensor event */
        sensors_event_t event;
        mma.getEvent(&event);

        /* Display the results (acceleration is measured in m/s^2) */
        /* Serial.print(event.acceleration.x); Serial.print(","); */
        /* Serial.print(event.acceleration.y); Serial.print(","); */
        /* Serial.print(event.acceleration.z); */

        float norm = sqrt(sq(event.acceleration.x) + sq(event.acceleration.y) + sq(event.acceleration.z));

        updateHistory(norm);
        float belly = calcBelly();

        if((belly > 5) && ((millis() - time) > 2000)) {
          Serial.println(1);
          time = millis();
        }
//        else {
//          Serial.println(0);
//        }


        /* Get the orientation of the sensor */
        /* uint8_t o = mma.getOrientation(); */


        /* Serial.println(); */
        delay(10);

}
