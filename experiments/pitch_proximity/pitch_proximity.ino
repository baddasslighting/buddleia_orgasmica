/*
  Experiment to change the pitch of a MIDI note proportionally to the proximity to the sensor. i.e. Closer means higher pitch.
*/

/*
  MSB - Most Significant Byte is "coarse" tuning.
  LSB - Least Significant Byte is "fine" tuning.
*/

#define MIDI_COMMAND_NOTE_OFF   0x80 // MIDI command to stop playing a note
#define MIDI_COMMAND_NOTE_ON    0x90 // MIDI command to begin playing a note
#define MIDI_CHANNEL_1          0x00 // MIDI has 16 channels. They go from 0x00 to 0x0F
#define MIDI_MAX_VELOCITY       0x7f // MIDI velocity, which is how hard you hit the key. Goes from 0x00 to 0x7f
#define MIDI_COMMAND_PITCH_BEND 0xe0 // MIDI pitch bend command.
#define MIDI_PITCH_BEND_MID_MSB 64   // Coarse stepping "most significant byte" middle amount - no pitch bend
#define MIDI_PITCH_BEND_MAX_MSB 127  // Coarse stepping "most significant byte" maximum amount - full high pitch bend
#define MIDI_PITCH_BEND_MIN_LSB 0    // Fine stepping "least significant byte" minimum amount - no pitch bend
#define MIDI_PITCH_BEND_MAX_LSB 127  // Fine stepping "least significant byte" maximum amount - full high pitch bend
#define MIDI_PITCH_BEND_MSB_POS 0    // Position within the MIDI pitch bend command of the MSB
#define MIDI_PITCH_BEND_LSB_POS 1    // Position within the MIDI pitch bend command of the MSB
#define SENSOR_PIN              0    // Which analog pin is this sensor connected to?
#define SENSOR_MAX              676  // Maximum amount the IR sensor will read
#define RUNNING_AVG_SAMPLE_LEN  8    // Number of readings to take from the sensor for each pitch bend
/*
  Number of miliseconds between sensor reaadings. For example, 250ms is 4 times per second.
*/
int sensorReadInterval = 50;

/*
  MIDI notes range from 0x00 ( 0 in decimal ) to 0x7f ( 127 in decimal ). Check the wiki for a link
  to a table of notes. We'll use F#, represented by 0x30 ( 48 in decimal ).
*/
byte note = 0x30;

void convertNormalizedPitchToBytes(float normalizedPitch, byte dataBytes[]) {
  // Calculate the MSB: 64 * (value from 0.0 to 1.0, basically a percentage) + 64
  // This means if the sensor is reading 0, we're at a pitch bend of 64, which is "no change in pitch"
  // If the sensor is reading 1.0, we're at a pitch bend of 127, which is "max change in pitch"
  byte mostSigByte  = (byte)(MIDI_PITCH_BEND_MID_MSB * normalizedPitch + MIDI_PITCH_BEND_MID_MSB);

  // Ignore the LSB for now by passing in the value of 0
  byte leastSigByte = (byte)MIDI_PITCH_BEND_MIN_LSB;
  
  dataBytes[MIDI_PITCH_BEND_MSB_POS] = mostSigByte;
  dataBytes[MIDI_PITCH_BEND_LSB_POS] = leastSigByte;
}

/*
  Convert the proximity sensor reading into a value from 0.0 to 1.0. Think of this as a percentage of how close
  the raver's hand is to the sensor. 0.0 being "no one in front" and 1.0 being someone getting allll up in the sensor's business!
*/
float calculateNormalizedPitchFromProximity(int proximity) {
  return (float)proximity / (float)SENSOR_MAX;
}

/*
  Append a new value to the array and remove the oldest value.
*/
void appendValueToArray(byte array[], byte value) {
  // Move each value over by one
  for (int i = 0; i < (RUNNING_AVG_SAMPLE_LEN - 1); i++) {
    array[i] = array[i + 1];
  }
  
  // Place our new value into the last array index
  array[RUNNING_AVG_SAMPLE_LEN - 1] = value;
}

/*
  We're keeping track of the last 8 calculated pitch bends value, then averaging them to create a smoother
  pitch bend as the sensor is triggered. We'll also initialize the array with 0s.
*/
byte lastFewPitchBends[RUNNING_AVG_SAMPLE_LEN];

/*
  Calculate the running average of all the calculated pitch bends. This is to smooth out the value coming out of the sensor.
*/
byte calculateRunningAverage(byte values[]) {
  int runningAverage = 0;
  
  for (int i = 0; i < RUNNING_AVG_SAMPLE_LEN; i++) {
    runningAverage = runningAverage + values[i];
  } 
 
  return (byte)(runningAverage / RUNNING_AVG_SAMPLE_LEN);
}

void setup() {
  // MIDI communicates at this baud rate. Do not change!
  Serial.begin(31250);
 
  // Initialize our last few pitch bend array to all 0s 
  memset(lastFewPitchBends, 0x00, RUNNING_AVG_SAMPLE_LEN); 
  
  // Play a Note
  Serial.write(MIDI_COMMAND_NOTE_ON | MIDI_CHANNEL_1); // 1st Byte: The command. In this case, play note on channel 1.
  Serial.write(note);                                  // 2nd Byte: The note. 
  Serial.write(MIDI_MAX_VELOCITY);                     // 3rd Byte: Velocity ( key press hardness ).    
}

void loop() {
  // Read proximity from IR sensor
  int proximity = analogRead(SENSOR_PIN);  
  
  // Normalize, that is to say convert the sensor reading into a value from 0.0 to 1.0. This of this as a percentage.
  float normalizedProximity = calculateNormalizedPitchFromProximity(proximity);
    
  byte dataBytes[2];
  
  // Calculate what the pitch bend should be given the proximity
  convertNormalizedPitchToBytes(normalizedProximity, dataBytes);
  
  // Add the new calculated pitch to the last few pitches
  appendValueToArray(lastFewPitchBends, dataBytes[MIDI_PITCH_BEND_MSB_POS]);
  
  // Calculate the average pitch bend. This is what we actually use. This makes it smoooooooth and continous sounding.
  byte pitchBend = calculateRunningAverage(lastFewPitchBends);

  // Alter the pitch bend
  Serial.write(MIDI_COMMAND_PITCH_BEND | MIDI_CHANNEL_1); // 1st Byte: The command. In this case, alter pitch bend on channel 1.
  Serial.write(MIDI_PITCH_BEND_MIN_LSB);                  // 2nd Byte: Pitch bend's least significant byte. We're igoring this for now, so we're passing in 0.
  Serial.write(pitchBend);                                // 3nd Byte: Pitch bend's most significant byte. This is actually the average of the last 8 calculated pitch bends.
      
  // Wait for a bit before reading the sensor again.
  delay(sensorReadInterval);  
}

