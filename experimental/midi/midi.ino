/*
  Example MIDI Arduino Code
  
  DO NOT MODIFY THIS CODE. Use this as a way to play around with making some noise!
*/

#define MIDI_COMMAND_NOTE_ON  0x80  // MIDI command to stop playing a note
#define MIDI_COMMAND_NOTE_OFF 0x90  // MIDI command to begin playing a note

#define MIDI_CHANNEL_1 0x00         // MIDI has 16 channels. They go from 0x00 to 0x0F

#define MIDI_MAX_VELOCITY 0x7f      // MIDI velocity, which is how hard you hit the key. Goes from 0x00 to 0x7f

#define MIDI_CONTROL_MODE_CHANGE 0xB0  // MIDI command for controlling modes on a channel.
#define MIDI_CHANNEL_VOLUME      0x07  // MIDI channel volume. Does what you think. Goes from 0x00 to 0x7f.

/*
  Number of miliseconds to play this note.
*/
int duration = 500;

/*
  Combine the command for turning a note on with the channel number to arrive at the full
  MIDI command. We will specify which not to play later. This is just for turning any
  old note on.
*/
byte onChannelOneTurnNoteOn = MIDI_COMMAND_NOTE_ON | MIDI_CHANNEL_1;

/*
  MIDI notes range from 0x00 ( or in decimal, 0 ) to 0x7f ( in decimal, 127 ). Check the wiki for a link
  to a table of notes. We'll use A440 / A4, which is 440 Hz, which is represented by 0x45 ( in decimal, 69 ).
*/
byte note = 0x45;

/*
  Combine the command for turning a note off with the channel number to arrive at the full
  MIDI command. We will specify which not to play later. This is just for turning any
  old note off.
*/
byte onChannelOneTurnNoteOff = MIDI_COMMAND_NOTE_OFF | MIDI_CHANNEL_1;

/*
  Combine the command for changing some aspect or mode of the channel with the channel number to
  arrive at the full MIDI command. We will specify what we which to change about the channel later.
*/
byte onChannelOneChangeMode = MIDI_CONTROL_MODE_CHANGE | MIDI_CHANNEL_1;

/*
  Value for the volume. Ranges from 0x00 ( in decimal, 0 ) to 0x7f ( in decimal, 127 ).
*/
byte volume = 0x7f;

void setup() {
  // MIDI communicates at this baud rate. Do not change!
  Serial.begin(31250);
}

void loop() {

  // Set the Volume to Max
  Serial.write(onChannelOneChangeMode); // 1st Byte: The command. In this case, change something about channel 1.
  Serial.write(MIDI_CHANNEL_VOLUME);    // 2nd Byte: What we want to change, namely the volume. 
  Serial.write(volume);                 // 3rd Byte: Volume amount.
  
  // Play a Note
  Serial.write(onChannelOneTurnNoteOn); // 1st Byte: The command. In this case, play note on channel 1.
  Serial.write(note);                   // 2nd Byte: The note. 
  Serial.write(MIDI_MAX_VELOCITY);      // 3rd Byte: Velocity ( key press hardness ).
  
  // Wait
  delay(duration);
  
  // Stop Playing a Note
  Serial.write(onChannelOneTurnNoteOff); // 1st Byte: The command. In this case, stop paying note on channel 1.
  Serial.write(note);                    // 2nd Byte: The note. 
  Serial.write(MIDI_MAX_VELOCITY);       // 3rd Byte: Velocity ( key press hardness ).
  
  // Wait
  delay(duration);
}


