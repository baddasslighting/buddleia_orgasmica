/*
  Experiment to change the volume of a MIDI note proportionally to the proximity to the sensor. i.e. Closer means louder.
*/

#include <math.h>

#define MIDI_COMMAND_NOTE_OFF    0x80 // MIDI command to stop playing a note
#define MIDI_COMMAND_NOTE_ON     0x90 // MIDI command to begin playing a note
#define MIDI_CHANNEL_1           0x00 // MIDI has 16 channels. They go from 0x00 to 0x0F
#define MIDI_MAX_VELOCITY        0x7f // MIDI velocity, which is how hard you hit the key. Goes from 0x00 to 0x7f
#define SENSOR_MIN               0    // Lowest value the sensor can return (in theory)
#define SENSOR_MAX               1023 // Highest value the sensor can return (in theory)

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
  Note played when something is far away from the sensor.
*/
int farthestNote = 69;

/*
  Note played when something is close to the sensor.
*/
int closestNote = 103;

/*
  Distance between low and high notes.
*/
int noteRange = (closestNote - farthestNote);

/*
  I believe we need to keep track of the previous note so we can stop playing it.
*/
int previousNote = farthestNote;

/*
  Interpolate the note, using farthestNote and closestNote as our low and high anchors.
*/
int interpolateNoteFromProximity(int proximity) {
  // Convert the proximity to a float ranging from 0 to 1.0 ( known as a "normalized" value )
  float normalizedProximity = proximity / SENSOR_MAX;
  
  // Calculate the increase in pitch from the proximity.
  int noteDifference = normalizedProximity * noteRange;

  // The new note will be the base note with the appropriate amount of increase in pitch given a trigger's distance from the sensor.
  return farthestNote + noteDifference;
}

void setup() {
  // MIDI communicates at this baud rate. Do not change!
  Serial.begin(31250);
}

void loop() {
  // Read proximity from sensor
  int proximity = analogRead(SENSOR_PIN);
    
  // Stop playing the previous note
  Serial.write(MIDI_COMMAND_NOTE_OFF | MIDI_CHANNEL_1); // 1st Byte: The command. In this case, stop playing a note on channel 1.
  Serial.write(previousNote);                           // 2nd Byte: The note from the last loop.
  Serial.write(MIDI_MAX_VELOCITY);                      // 3rd Byte: Velocity ( key press hardness ).             
  
  // If we have enough signal from the proximity sensor
  if (proximity > proximityThreshold) {
    int note = interpolateNoteFromProximity(proximity);

    // Save the current note for the next loop in order to stop playing it. Otherwise we'll end up with the "cat falling on a keyboard" problem.
    previousNote = note;
    
    // Play a Note
    Serial.write(MIDI_COMMAND_NOTE_ON | MIDI_CHANNEL_1); // 1st Byte: The command. In this case, play note on channel 1.
    Serial.write(note);                                  // 2nd Byte: The note. 
    Serial.write(MIDI_MAX_VELOCITY);                     // 3rd Byte: Velocity ( key press hardness ).  
  }

  // Wait for a bit before reading the sensor again.
  delay(sensorReadInterval);  
}


