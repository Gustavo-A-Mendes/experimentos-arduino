#include "pitches.h"

// notes in the melody:

int melody[] = {
  NOTE_E3, NOTE_DS3,
   NOTE_E3, NOTE_DS3,NOTE_E3, NOTE_B2, NOTE_D3, NOTE_C3,
    NOTE_A2, NOTE_C2, NOTE_E2, NOTE_A2,
     NOTE_B2, NOTE_E2, NOTE_GS2,NOTE_B2, NOTE_C3,
  NOTE_E3, NOTE_DS3,
   NOTE_E3, NOTE_DS3,NOTE_E3, NOTE_B2, NOTE_D3, NOTE_C3,
    NOTE_A2, NOTE_C2, NOTE_E2, NOTE_A2,
     NOTE_B2, NOTE_E2, NOTE_C3, NOTE_B2, NOTE_A2
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4,4,
   4,4,4,4,4,4,
    2,4,4,4,
     2,4,4,4,4,
  4,4,
   4,4,4,4,4,4,
    2,4,4,4,
     2,4,4,4,1
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 35; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(9, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration + 50;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(9);
  }
}

void loop() {
  // no need to repeat the melody.
}
