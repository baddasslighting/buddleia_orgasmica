/*
  Example IR Proximity Sensor Arduino Code
  
  DO NOT MODIFY THIS CODE. Use this as a way to play around with making it detect stuff!
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

void loop() {
  /*
    Read the value from the IR proximity sensor. Values returned will range from 0 to 1024.
  */
  int value = analogRead(SENSOR_PIN);

  /*
    Display the value on the Serial Monitor ( under Tool > Serial Monitor ) within the Arduino IDE.
    This is for demonstration purposes.
  */
  Serial.println(value);
  
  /*
    Wait before reading the sensor again. Think of this as the "resolution" or "sampling rate" of the sensor.
    Longer means sampling less often, shorter means sampling more often.
  */
  delay(sensorReadInterval);
}
