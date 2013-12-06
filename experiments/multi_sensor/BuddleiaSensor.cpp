#include "BuddleiaSensor.h"

BuddleiaSensor::BuddleiaSensor(byte analogPin) {
  _pin = analogPin;
  memset(_buffer, 0, SENSOR_BUFFER_LEN);
}

unsigned short BuddleiaSensor::read() {
  unsigned short reading = map(analogRead(_pin), SENSOR_ACTUAL_MIN, SENSOR_ACTUAL_MAX, SENSOR_MIN, SENSOR_MAX);  
  updateBuffer(reading);
  return bufferAverage();
}

void BuddleiaSensor::updateBuffer(unsigned short reading) {  
  // Shift the entire buffer by one to make room for the new reading
  for (byte i = 0; i < (SENSOR_BUFFER_LEN - 1); i++) {
    _buffer[i] = _buffer[i + 1];
  }
  
  // Place our new reading into the last index of the buffer
  _buffer[SENSOR_BUFFER_LEN - 1] = reading;  
}

unsigned short BuddleiaSensor::bufferAverage() {
  unsigned short average = 0;
  
  for (byte i = 0; i < SENSOR_BUFFER_LEN; i++) {
    average += _buffer[i];
  } 
 
  return average / SENSOR_BUFFER_LEN;  
}
