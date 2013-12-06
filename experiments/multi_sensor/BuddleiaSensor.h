#ifndef BuddleiaSensor_h
#define BuddleiaSensor_h

#include <Arduino.h>

#define SENSOR_MIN 0
#define SENSOR_MAX 1024

#define SENSOR_ACTUAL_MIN 0
#define SENSOR_ACTUAL_MAX 676

#define SENSOR_BUFFER_LEN 8

class BuddleiaSensor {
  public:
    BuddleiaSensor(byte sensorPin);
    unsigned short read();
  private:
    byte _pin;    
    unsigned short _buffer[SENSOR_BUFFER_LEN];
    void updateBuffer(unsigned short reading);
    unsigned short bufferAverage();
};

#endif
