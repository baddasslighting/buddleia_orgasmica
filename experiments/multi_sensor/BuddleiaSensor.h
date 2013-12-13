#ifndef BuddleiaSensor_h
#define BuddleiaSensor_h

#include <Arduino.h>

#define SENSOR_PIN_1 0x01
#define SENSOR_PIN_2 0x02
#define SENSOR_PIN_3 0x03
#define SENSOR_PIN_4 0x04
#define SENSOR_PIN_5 0x05
#define SENSOR_PIN_6 0x06
#define SENSOR_PIN_7 0x07
#define SENSOR_PIN_8 0x08
#define SENSOR_PIN_9 0x09

#define SENSOR_MIN 0
#define SENSOR_MAX 1024

#define SENSOR_ACTUAL_MIN 0
#define SENSOR_ACTUAL_MAX 676

#define SENSOR_BUFFER_LEN 8

class BuddleiaSensor {
  public:
    BuddleiaSensor();
    BuddleiaSensor(byte sensorPin);
    void setPin(byte sensorPin);
    unsigned short read();
  private:
    byte _pin;    
    unsigned short _buffer[SENSOR_BUFFER_LEN];
    void initBuffer();
    void updateBuffer(unsigned short reading);
    unsigned short bufferAverage();
    unsigned short expand(unsigned short rawReading);
};

#endif
