/*
  Experiment to change the pitch of a MIDI note proportionally to the proximity to the sensor. i.e. Closer means higher pitch.
*/

/*
  MSB - Most Significant Byte is "coarse" tuning.
  LSB - Least Significant Byte is "fine" tuning.
*/

#define MIDI_COMMAND_NOTE_OFF    0x80  // MIDI command to stop playing a note
#define MIDI_COMMAND_NOTE_ON     0x90  // MIDI command to begin playing a note
#define MIDI_CHANNEL_1           0x00  // MIDI has 16 channels. They go from 0x00 to 0x0F
#define MIDI_MAX_VELOCITY        0x7f  // MIDI velocity, which is how hard you hit the key. Goes from 0x00 to 0x7f
#define MIDI_COMMAND_PITCH_BEND  0xe0  // MIDI pitch bend command.

#define MIDI_PITCH_BEND_MID_MSB  64  // Coarse stepping "most significant byte" middle amount - no pitch bend
#define MIDI_PITCH_BEND_MAX_MSB  127 // Coarse stepping "most significant byte" maximum amount - full high pitch bend

#define MIDI_PITCH_BEND_MIN_LSB  0   // Fine stepping "least significant byte" minimum amount - no pitch bend
#define MIDI_PITCH_BEND_MAX_LSB  127 // Fine stepping "least significant byte" maximum amount - full high pitch bend

#define MIDI_COMMAND_PITCH_BEND_MSB_POS 0 // Position within the MIDI pitch bend command of the MSB
#define MIDI_COMMAND_PITCH_BEND_LSB_POS 1 // Position within the MIDI pitch bend command of the MSB

#define SENSOR_PIN 0   // Which analog pin is this sensor connected to?
#define SENSOR_MAX 676 // Maximum amount the IR sensor will read

/*
  Number of miliseconds between sensor reaadings. For example, 250ms is 4 times per second.
*/
int sensorReadInterval = 100;

/*
  MIDI notes range from 0x00 ( 0 in decimal ) to 0x7f ( 127 in decimal ). Check the wiki for a link
  to a table of notes. We'll use A440 / A4, which is 440 Hz, represented by 0x45 ( 69 in decimal ).
*/
byte note = 0x45;

void convertNormalizedPitchToBytes(float normalizedPitch, byte dataBytes[]) {
  // Calculate the MSB: 64 * (value from 0.0 to 1.0, basically a percentage) + 64
  // This means if the sensor is reading 0, we're at a pitch bend of 64, which is "no change in pitch"
  // If the sensor is reading 1.0, we're at a pitch bend of 127, which is "max change in pitch"
  byte mostSigByte  = MIDI_PITCH_BEND_MID_MSB * normalizedPitch + MIDI_PITCH_BEND_MID_MSB;
  byte leastSigByte = MIDI_PITCH_BEND_MIN_LSB;
  
  dataBytes[MIDI_COMMAND_PITCH_BEND_MSB_POS] = mostSigByte;
  dataBytes[MIDI_COMMAND_PITCH_BEND_LSB_POS] = leastSigByte;
}

/*
  Convert the proximity sensor reading into a value from 0.0 to 1.0. Think of this as a percentage of how close
  the raver's hand is to the sensor. 0.0 being "no one in front" and 1.0 being someone getting allll up in the sensor's business!
*/
float calculateNormalizedPitchFromProximity(int proximity) {
  return (float)proximity / (float)SENSOR_MAX;
}

void setup() {
  // MIDI communicates at this baud rate. Do not change!
  Serial.begin(31250);
  
  // Play a Note
  Serial.write(MIDI_COMMAND_NOTE_ON | MIDI_CHANNEL_1); // 1st Byte: The command. In this case, play note on channel 1.
  Serial.write(note);                                  // 2nd Byte: The note. 
  Serial.write(MIDI_MAX_VELOCITY);                     // 3rd Byte: Velocity ( key press hardness ).    
}

void loop() {
  int proximity = analogRead(SENSOR_PIN);  
  float normalizedProximity = calculateNormalizedPitchFromProximity(proximity);
  
  byte dataBytes[2];
  
  convertNormalizedPitchToBytes(normalizedProximity, dataBytes);

  // Alter the pitch bend
  Serial.write(MIDI_COMMAND_PITCH_BEND | MIDI_CHANNEL_1);   // 1st Byte: The command. In this case, alter pitch bend on channel 1.
  Serial.write(dataBytes[MIDI_COMMAND_PITCH_BEND_LSB_POS]); // 2nd Byte: Pitch bend's least significant byte
  Serial.write(dataBytes[MIDI_COMMAND_PITCH_BEND_MSB_POS]); // 3nd Byte: Pitch bend's most significant byte
      
  // Wait for a bit before reading the sensor again.
  delay(sensorReadInterval);  
}

