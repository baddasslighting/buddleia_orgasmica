#include "BuddleiaActivity.h"

BuddleiaActivity::BuddleiaActivity(byte sensorPin, byte midiChannel, byte midiNote) {
  _sensor = BuddleiaSensor(sensorPin);
  _midiNote = BuddleiaMIDINote(midiChannel, midiNote);
}

void BuddleiaActivity::setup() {
  _midiNote.playNote();
}

void BuddleiaActivity::pitchBend() {
   _midiNote.pitchBend(determinePitchBendAmount(_sensor.read()));
}

unsigned short BuddleiaActivity::determinePitchBendAmount(unsigned short reading) {
  return map(reading, SENSOR_MIN, SENSOR_MAX, MIDI_PITCH_BEND_MID_MSB, MIDI_PITCH_BEND_MAX_MSB);      
}
