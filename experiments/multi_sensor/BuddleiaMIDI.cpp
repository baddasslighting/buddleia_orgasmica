#include "BuddleiaMIDI.h"

BuddleiaMIDI::BuddleiaMIDI(byte channel) {
  _channel = channel;
}

BuddleiaMIDI::BuddleiaMIDI(byte channel, byte note) {
  _channel = channel;
  _note = note;
}

void BuddleiaMIDI::setNote(byte note) {
  _note = note;
}

void BuddleiaMIDI::noteCommand(byte command) {
  Serial.write(command | _channel);
  Serial.write(_note);
  Serial.write(MIDI_MAX_VELOCITY);  
}

void BuddleiaMIDI::playNote() {
  noteCommand(MIDI_COMMAND_NOTE_ON);
}

void BuddleiaMIDI::stopNote() {
  noteCommand(MIDI_COMMAND_NOTE_OFF);
}

void BuddleiaMIDI::pitchBend(byte amount) {
  Serial.write(MIDI_COMMAND_PITCH_BEND | _channel);
  Serial.write(MIDI_PITCH_BEND_MIN_LSB);
  Serial.write(amount);  
}


