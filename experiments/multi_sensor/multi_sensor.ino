#include "BuddleiaActivity.h"
#include "BuddleiaMIDINote.h"
#include "BuddleiaSensor.h"

BuddleiaActivity activites[] = {
  BuddleiaActivity(SENSOR_PIN_1, MIDI_CHANNEL_1, 0x30),
  BuddleiaActivity(SENSOR_PIN_2, MIDI_CHANNEL_2, 0x40),
  BuddleiaActivity(SENSOR_PIN_3, MIDI_CHANNEL_3, 0x50),
  BuddleiaActivity(SENSOR_PIN_4, MIDI_CHANNEL_4, 0x60),
  BuddleiaActivity(SENSOR_PIN_5, MIDI_CHANNEL_5, 0x70)
};

void setup() {  
  // MIDI communicates at this baud rate. Do not change!
  Serial.begin(MIDI_BAUD_RATE);  
  
  for (int i = 0; i < sizeof(activites); i++) {
    activites[i].setup();
  }
}

void loop() {  
  for (int i = 0; i < sizeof(activites); i++) {    
    activites[i].pitchBend();
  }  
}
