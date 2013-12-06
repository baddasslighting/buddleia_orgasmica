/*
  MIDI Commands
*/

#define MIDI_COMMAND_NOTE_OFF   0x80 // MIDI command to stop playing a note
#define MIDI_COMMAND_NOTE_ON    0x90 // MIDI command to begin playing a note
#define MIDI_MAX_VELOCITY       0x7F // MIDI velocity, which is how hard you hit the key. Goes from 0x00 to 0x7F
#define MIDI_COMMAND_PITCH_BEND 0xe0 // MIDI pitch bend command.
#define MIDI_PITCH_BEND_MID_MSB 64   // Coarse stepping "most significant byte" middle amount - no pitch bend
#define MIDI_PITCH_BEND_MAX_MSB 127  // Coarse stepping "most significant byte" maximum amount - full high pitch bend
#define MIDI_PITCH_BEND_MIN_LSB 0    // Fine stepping "least significant byte" minimum amount - no pitch bend
#define MIDI_PITCH_BEND_MAX_LSB 127  // Fine stepping "least significant byte" maximum amount - full high pitch bend
#define MIDI_PITCH_BEND_MSB_POS 0    // Position within the MIDI pitch bend command of the MSB
#define MIDI_PITCH_BEND_LSB_POS 1    // Position within the MIDI pitch bend command of the MSB

