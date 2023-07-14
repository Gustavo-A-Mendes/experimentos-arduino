#define NOTE_C2  65
#define NOTE_D2  73
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_G2  98

// faixa alto = C1 ao GS3
// faixa baixa = A3 ao D8

// notes in the melody:
int melody[] = {
  0,0,0,0,NOTE_C2,
   NOTE_D2,NOTE_F2,NOTE_D2,NOTE_E2,NOTE_G2,NOTE_E2,
    NOTE_F2,0,0,0,
  NOTE_C2,
   NOTE_D2, NOTE_F2, NOTE_D2, NOTE_E2, NOTE_G2, NOTE_E2,
    NOTE_F2,0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  2,2,2,4,4, 
   2,4,4,2,4,4,
    2,4,4,4,
  4,
   2,4,4,2,4,4,
    2,1
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 24; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(9, 4*melody[thisNote], noteDuration);

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
