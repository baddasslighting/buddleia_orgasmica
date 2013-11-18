/*
  Experiment to change the pitch of a MIDI note proportionally to the proximity to the sensor. i.e. Closer means higher pitch.
*/

#define MIDI_COMMAND_NOTE_OFF    0x80  // MIDI command to stop playing a note
#define MIDI_COMMAND_NOTE_ON     0x90  // MIDI command to begin playing a note
#define MIDI_CHANNEL_1           0x00  // MIDI has 16 channels. They go from 0x00 to 0x0F
#define MIDI_MAX_VELOCITY        0x7f  // MIDI velocity, which is how hard you hit the key. Goes from 0x00 to 0x7f
#define MIDI_COMMAND_PITCH_BEND  0xe0  // MIDI pitch bend command.
#define MIDI_PITCH_BEND_NORMAL   8192  // No pitch bend
#define MIDI_PITCH_BEND_MAX      16383 // Max pitch bend

#define SENSOR_PIN 0 // Which analog pin is this sensor connected to?

/*
  Number of miliseconds between sensor reaadings. For example, 250ms is 4 times per second.
*/
int sensorReadInterval = 250;

/*
  MIDI notes range from 0x00 ( 0 in decimal ) to 0x7f ( 127 in decimal ). Check the wiki for a link
  to a table of notes. We'll use A440 / A4, which is 440 Hz, represented by 0x45 ( 69 in decimal ).
*/
byte note = 0x45;

/*
  MIDI requires the pitch be in two bytes, whereas the first bit in each byte is unused, so as two 7-bit bytes.
*/

byte[] convertPitchDecimalToPitchBytes(int pitch) {
  byte firstByte, secondByte;
  
  int difference = pitch - MIDI_PITCH_BEND_NORMAL;
  
  // Pitch value uses both bytes
  if (difference >= 8192) {
    firstByte  = (byte)(difference / 64 - 1); // First byte ranges from 0 to 0x7f ( 127 in decimal )
    secondByte = 0x7f;                        // Second byte is 0x7f ( 127 in decimal )
  }
  // Pitch value only uses the second byte
  else {
    firstByte  = 0x00;                        // First byte is 0x00 ( 0 in decimal )
    secondByte = (byte)(difference / 64 - 1); // Second byte ranges from 0 to 0x7f ( 127 in decimal )
  }
}

/*
  Determine the change in pitch given the proximity

  Expected Ranges:
    Input: 0 to 1023
    Output: Array of two bytes ranging from 0x00 to 0x7f
*/
byte[] calculatePitchFromProximity(int proximity) {
  return (proximity / 1023 * MIDI_PITCH_BEND_NORMAL) + MIDI_PITCH_BEND_NORMAL
}

