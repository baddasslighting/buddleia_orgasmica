#include "BuddleiaSensor.h"

/**
 * Constructor
 */
BuddleiaSensor::BuddleiaSensor(byte analogPin) {
  _pin = analogPin;
  memset(_buffer, 0, SENSOR_BUFFER_LEN); // Fill sensor buffer with all zeros
}

/**
 * Read a value from the sensor, map it over the expected range, average it with the N previous readings and return the average.
 */
unsigned short BuddleiaSensor::read() {
  // The raw sensor reading is mapped from the actual range to the expected range.
  unsigned short reading = expand(analogRead(_pin));

  // Average the last N sensor readings to create a smoother effect.
  updateBuffer(reading);
  
  return bufferAverage();
}

/**
 * Shift each element of a fixed size array then append the new value to the last position.
 */
void BuddleiaSensor::updateBuffer(unsigned short reading) {  
  // Shift the entire buffer by one to make room for the new reading
  for (byte i = 0; i < (SENSOR_BUFFER_LEN - 1); i++) {
    _buffer[i] = _buffer[i + 1];
  }
  
  // Place our new reading into the last index of the buffer
  _buffer[SENSOR_BUFFER_LEN - 1] = reading;  
}

/**
 * Average all the values in the sensor buffer.
 */
unsigned short BuddleiaSensor::bufferAverage() {
  unsigned short average = 0;
  
  for (byte i = 0; i < SENSOR_BUFFER_LEN; i++) {
    average += _buffer[i];
  } 
 
  return average / SENSOR_BUFFER_LEN;  
}

/**
 * Map the sensor values from the actual range to the idealized range.
 */
unsigned short BuddleiaSensor::expand(unsigned short rawReading) {
  // Take the raw sensor reading, which ranges from SENSOR_ACTUAL_MIN to SENSOR_ACTUAL_MAX
  // and linearly expand the value to go from SENSOR_MIN to SENSOR_MAX.
  return map(rawReading, SENSOR_ACTUAL_MIN, SENSOR_ACTUAL_MAX, SENSOR_MIN, SENSOR_MAX);   
}
