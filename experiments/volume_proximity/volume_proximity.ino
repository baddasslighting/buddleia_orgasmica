/*
  Experiment to change the volume of a MIDI note proportionally to the proximity to the sensor. i.e. Closer means louder.
*/

#include <math.h>

#define MIDI_COMMAND_NOTE_OFF    0x80 // MIDI command to stop playing a note
#define MIDI_COMMAND_NOTE_ON     0x90 // MIDI command to begin playing a note
#define MIDI_CHANNEL_1           0x00 // MIDI has 16 channels. They go from 0x00 to 0x0F
#define MIDI_MAX_VELOCITY        0x7f // MIDI velocity, which is how hard you hit the key. Goes from 0x00 to 0x7f
#define MIDI_CONTROL_MODE_CHANGE 0xB0 // MIDI command for controlling modes on a channel.
#define MIDI_CHANNEL_VOLUME      0x07 // MIDI channel volume. Does what you think. Goes from 0x00 to 0x7f.

#define SENSOR_PIN 0 // Which analog pin is this sensor connected to?

/*
  Number of miliseconds between sensor reaadings. For example, 250ms is 4 times per second.
*/
int sensorReadInterval = 250;

/*
  Below this level, no notes will be played. Adjust as needed.
*/
int proximityThreshold = 10;

/*
  MIDI notes range from 0x00 ( 0 in decimal ) to 0x7f ( 127 in decimal ). Check the wiki for a link
  to a table of notes. We'll use A440 / A4, which is 440 Hz, represented by 0x45 ( 69 in decimal ).
*/
byte note = 0x45;

/*
  Attempt to weight the input values such that low levels are worth more than they should be
  and higher levels are still worth a lot.
  
  Expected Ranges:
    Input: 0 to 1024
    Output: 0 to 127
*/
int calculateVolumeIntensityFromProximity(int proximity) {
  // log10(1..1025) is 0.0 to 3.0, multiplied by 42 is 0 to ~127
  return (int)(log10(proximity + 1) * 42.0);
}

void setup() {
  // MIDI communicates at this baud rate. Do not change!
  Serial.begin(31250);
}

void loop() {
  int proximity = analogRead(SENSOR_PIN);
  
  // If we have enough signal from the proximity sensor, 
  if (proximity > proximityThreshold) {
    int volume = calculateVolumeIntensityFromProximity(proximity);
    
    // Change the volume of the note
    Serial.write(MIDI_CONTROL_MODE_CHANGE | MIDI_CHANNEL_1); // 1st Byte: The command. In this case, change something about channel 1.
    Serial.write(MIDI_CHANNEL_VOLUME);                       // 2nd Byte: What we want to change, namely the volume. 
    Serial.write(volume);                                    // 3rd Byte: Volume amount.  
    
    // Play a Note
    Serial.write(MIDI_COMMAND_NOTE_ON | MIDI_CHANNEL_1); // 1st Byte: The command. In this case, play note on channel 1.
    Serial.write(note);                                  // 2nd Byte: The note. 
    Serial.write(MIDI_MAX_VELOCITY);                     // 3rd Byte: Velocity ( key press hardness ).  
  }
  else {
    // Stop playing the note
    Serial.write(MIDI_COMMAND_NOTE_OFF | MIDI_CHANNEL_1); // 1st Byte: The command. In this case, stop playing a note on channel 1.
    Serial.write(note);                                   // 2nd Byte: The note. 
    Serial.write(MIDI_MAX_VELOCITY);                      // 3rd Byte: Velocity ( key press hardness ).      
  }
      
  // Wait for a bit before reading the sensor again.
  delay(sensorReadInterval);  
}


