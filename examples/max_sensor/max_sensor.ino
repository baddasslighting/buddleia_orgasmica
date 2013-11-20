/*
  Determine the highest reading from a sensor
*/

#define SENSOR_PIN 0 // Which analog pin is this sensor connected to?

/*
  Number of miliseconds between sensor reaadings. For example,100ms is 10 times per second.
*/
int sensorReadInterval = 100;

void setup() {
  // TODO Determine if this is important or just used for the Serial Monitor.
  Serial.begin(9600);
}

int maxValue = 0;

void loop() {
  /*
    Read the value from the IR proximity sensor. Values returned will range from 0 to 1024.
  */
  int value = analogRead(SENSOR_PIN);

  /*
    New max value has been found. Record and display it.
  */  
  if (value > maxValue) {
    maxValue = value;
    Serial.println(maxValue);    
  }

  /*
    Wait before reading the sensor again. Think of this as the "resolution" or "sampling rate" of the sensor.
    Longer means sampling less often, shorter means sampling more often.
  */
  delay(sensorReadInterval);
}
