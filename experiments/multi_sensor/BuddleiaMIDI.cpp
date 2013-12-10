#include "BuddleiaMIDI.h"

/**
 * Channel constructor.
 */
BuddleiaMIDI::BuddleiaMIDI(byte channel) {
  _channel = channel;
}

/**
 * Channel and note constructor.
 */
BuddleiaMIDI::BuddleiaMIDI(byte channel, byte note) {
  _channel = channel;
  _note = note;
}

/**
 * Set the note for this MIDI channel.
 */
void BuddleiaMIDI::setNote(byte note) {
  _note = note;
}

/**
 * Issue a note command, which type is specified by the method argument.
 */
void BuddleiaMIDI::noteCommand(byte command) {
  Serial.write(command | _channel);
  Serial.write(_note);
  Serial.write(MIDI_MAX_VELOCITY);  
}

/**
 * Issue play note MIDI command.
 */
void BuddleiaMIDI::playNote() {
  noteCommand(MIDI_COMMAND_NOTE_ON);
}

/**
 * Issue stop note MIDI command.
 */
void BuddleiaMIDI::stopNote() {
  noteCommand(MIDI_COMMAND_NOTE_OFF);
}

/**
 * Issue pitch bend MIDI command using *only* the Most Significant Byte.
 */
void BuddleiaMIDI::pitchBend(byte amount) {
  Serial.write(MIDI_COMMAND_PITCH_BEND | _channel);
  Serial.write(MIDI_PITCH_BEND_MIN_LSB);
  Serial.write(amount);  
}


