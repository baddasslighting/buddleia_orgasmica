#include "BuddleiaMIDINote.h"

/**
 * Zero arg constructor.
 */
BuddleiaMIDINote::BuddleiaMIDINote() {

}

/**
 * Channel constructor.
 */
BuddleiaMIDINote::BuddleiaMIDINote(byte channel) {
  _channel = channel;
}

/**
 * Channel and note constructor.
 */
BuddleiaMIDINote::BuddleiaMIDINote(byte channel, byte note) {
  _channel = channel;
  _note = note;
}

/**
 * Set the channel.
 */
void BuddleiaMIDINote::setChannel(byte channel) {
  _channel = channel;
}

/**
 * Set the note for this MIDI channel.
 */
void BuddleiaMIDINote::setNote(byte note) {
  _note = note;
}

/**
 * Issue a note command, which type is specified by the method argument.
 */
void BuddleiaMIDINote::noteCommand(byte command) {
  Serial.write(command | _channel);
  Serial.write(_note);
  Serial.write(MIDI_MAX_VELOCITY);  
}

/**
 * Issue play note MIDI command.
 */
void BuddleiaMIDINote::playNote() {
  noteCommand(MIDI_COMMAND_NOTE_ON);
}

/**
 * Issue stop note MIDI command.
 */
void BuddleiaMIDINote::stopNote() {
  noteCommand(MIDI_COMMAND_NOTE_OFF);
}

/**
 * Issue pitch bend MIDI command using *only* the Most Significant Byte.
 */
void BuddleiaMIDINote::pitchBend(byte amount) {
  Serial.write(MIDI_COMMAND_PITCH_BEND | _channel);
  Serial.write(MIDI_PITCH_BEND_MIN_LSB);
  Serial.write(amount);  
}


