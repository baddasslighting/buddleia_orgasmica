#include "BuddleiaMIDIChannels.h"
#include "BuddleiaMIDICommands.h"

#define MIDI_BAUD_RATE 31250

#ifndef BuddleiaMIDINote_h
#define BuddleiaMIDINote_h

#include <Arduino.h>

class BuddleiaMIDINote {
  public:
    BuddleiaMIDINote(byte channel);
    BuddleiaMIDINote(byte channel, byte note);    
    void setNote(byte note);
    void noteCommand(byte command);
    void playNote();
    void stopNote();
    void pitchBend(byte amount);
  private:
    byte _channel;
    byte _note;
};

#endif
