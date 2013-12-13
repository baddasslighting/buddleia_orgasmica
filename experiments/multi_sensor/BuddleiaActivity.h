#include "BuddleiaSensor.h"
#include "BuddleiaMIDINote.h"

#ifndef BuddleiaActivity_h
#define BuddleiaActivity_h

#include <Arduino.h>

// TODO Rename this class. It's designed to "glue" a MIDI Note to a Sensor.
class BuddleiaActivity {
  public:
    BuddleiaActivity(byte sensorPin, byte midiChannel, byte midiNote);
    void setup();    
    void pitchBend();
  private:
     BuddleiaSensor _sensor;
     BuddleiaMIDINote _midiNote;
     unsigned short determinePitchBendAmount(unsigned short reading);
};

#endif
