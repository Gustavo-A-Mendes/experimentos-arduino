#include "pitches.h"

// faixa alto = C1 ao GS3
// faixa baixa = A3 ao D8

// notes in the melody:
/*
int melody[] = {
  NOTE_C1, NOTE_D1, NOTE_E1, NOTE_F1, NOTE_G1, NOTE_A1, NOTE_B1,
  NOTE_C2, NOTE_D2, NOTE_E2, NOTE_F2, NOTE_G2, NOTE_A2, NOTE_B2,
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5,
  NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A6, NOTE_B6,
  NOTE_C7, NOTE_D7, NOTE_E7, NOTE_F7, NOTE_G7, NOTE_A7, NOTE_B7,
  NOTE_C8, NOTE_D8, 
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 1,
  4, 4, 4, 4, 4, 4, 1,
  4, 4, 4, 4, 4, 4, 1,
  4, 4, 4, 4, 4, 4, 1,
  4, 4, 4, 4, 4, 4, 1,
  4, 4, 4, 4, 4, 4, 1,
  4, 4, 4, 4, 4, 4, 1,
  4, 1
};
*/
void setup() {
  /*
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 32; thisNote++) {
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
    
    tone(10);
    
    noTone(10);
    
    tone(11);
    
    noTone(11);
    
  
  }
  */
}

void loop() {
  // no need to repeat the melody.
  tone(9, NOTE_A4);
  
}
