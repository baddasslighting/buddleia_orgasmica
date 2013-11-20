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
#define MIDI_PITCH_BEND_MID_MSB  0x40  // MSB for no pitch bend
#define MIDI_PITCH_BEND_MID_LSB  0x00  // LSB for no pitch bend
#define MIDI_PITCH_BEND_MAX_MSB  0x7f  // MSB for max pitch bend
#define MIDI_PITCH_BEND_MAX_LSB  0x7f  // LSB for nax pitch bend

#define MIDI_COMMAND_PITCH_BEND_MSB_POS 0 // Position within the MIDI pitch bend command of the MSB
#define MIDI_COMMAND_PITCH_BEND_LSB_POS 1 // Position within the MIDI pitch bend command of the MSB

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

void convertNormalizedPitchToBytes(float normalizedPitch, byte dataBytes[]) {
  byte mostSigByte = MIDI_PITCH_BEND_MID_MSB;
  //byte mostSigByte = (byte)(((float)(MIDI_PITCH_BEND_MAX_MSB - MIDI_PITCH_BEND_MID_MSB)) * normalizedPitch) + MIDI_PITCH_BEND_MID_MSB;
  byte leastSigByte = (byte)((float)MIDI_PITCH_BEND_MAX_LSB * normalizedPitch);
  
  dataBytes[MIDI_COMMAND_PITCH_BEND_MSB_POS] = mostSigByte;
  dataBytes[MIDI_COMMAND_PITCH_BEND_LSB_POS] = leastSigByte;
}

float calculateNormalizedPitchFromProximity(int proximity) {
  return (float)proximity / 1023.0;
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

