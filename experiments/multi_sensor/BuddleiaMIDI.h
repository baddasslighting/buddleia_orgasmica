#include "BuddleiaMIDIChannels.h"
#include "BuddleiaMIDICommands.h"

#define MIDI_BAUD_RATE 31250

#ifndef BuddleiaMIDI_h
#define BuddleiaMIDI_h

#include <Arduino.h>

class BuddleiaMIDI {
  public:
    BuddleiaMIDI(byte channel);
    BuddleiaMIDI(byte channel, byte note);    
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
