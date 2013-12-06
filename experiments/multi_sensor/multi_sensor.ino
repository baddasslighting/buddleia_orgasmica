#include "BuddleiaMIDI.h"
#include "BuddleiaSensor.h"

BuddleiaMIDI midi[] = {
  BuddleiaMIDI(MIDI_CHANNEL_1, 0x30),
  BuddleiaMIDI(MIDI_CHANNEL_2, 0x40),
  BuddleiaMIDI(MIDI_CHANNEL_3, 0x50)
};

BuddleiaSensor sensor[] = {
  BuddleiaSensor(0),
  BuddleiaSensor(1),
  BuddleiaSensor(2)
};
  
void setup() {  
  // MIDI communicates at this baud rate. Do not change!
  Serial.begin(MIDI_BAUD_RATE);  
  
  for (int i = 0; i < sizeof(midi); i++) {
    midi[i].playNote();
  }
}

void loop() {  
  for (int i = 0; i < sizeof(midi); i++) {    
    byte pitchBendAmount = map(sensor[i].read(), SENSOR_MIN, SENSOR_MAX, MIDI_PITCH_BEND_MID_MSB, MIDI_PITCH_BEND_MAX_MSB);    
    midi[i].pitchBend(pitchBendAmount);
  }  
}
