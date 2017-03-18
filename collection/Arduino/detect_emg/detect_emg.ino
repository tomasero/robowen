
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}


int sensorValue = 0;
float sensorBack = 0;

// high passed signal (>150Hz)
float hpval = 0;
float hpback1 = 0;
float hpback2 = 0;

// low passed value
float lowval = 0;
float lowback1 = 0;
float lowback2 = 0;

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorBack = sensorValue;
  sensorValue = analogRead(A0);

  // high pass filter
  hpback2 = hpback1;
  hpback1 = hpval;

  hpval = 0.4625973*sensorValue - 0.4625973*sensorBack - 0.07480541*hpval;

  // low pass filter on absolute value
  lowback2 = lowback1;
  lowback1 = lowval;
  lowval = 3.26112508e-05*(abs(hpval) + 2*abs(hpback1) + abs(hpback2)) + 1.98378282*lowback1 - 0.98391326*lowback2;

  // print out the value you read:
  Serial.println(lowval*100);
  delay(3);        // delay in between reads for stability
}
