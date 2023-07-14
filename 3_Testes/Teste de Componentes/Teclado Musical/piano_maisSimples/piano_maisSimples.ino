#define rele 9
#define teclaC 12
#define teclaD 11
#define teclaE 8
#define teclaF 6
#define teclaG 5
#define teclaA 3
#define teclaB 2
#define pinoMais A5
#define pinoMenos A4

int c = 65, d = 73, e = 82, f = 87, g = 98, a = 110, b = 123;
float multiplicador[] = {
  0.5, 1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0
};

bool mais, menos;

void setup() {
  Serial.begin(9600);

  pinMode(rele, OUTPUT);
  pinMode(teclaC, INPUT);
  pinMode(teclaD, INPUT);
  pinMode(teclaE, INPUT);
  pinMode(teclaF, INPUT);
  pinMode(teclaG, INPUT);
  pinMode(teclaA, INPUT);
  pinMode(teclaB, INPUT);
  pinMode(pinoMais, INPUT);
  pinMode(pinoMenos, INPUT);
}

void loop() {
  static bool maisAtu, maisAnt, menosAtu, menosAnt;
  static int n = 1;
  float multi = multiplicador[n];

  maisAtu = digitalRead(pinoMais);
  if (maisAtu != maisAnt) {
    if (maisAtu == LOW) {
      mais = LOW;
    }
    maisAnt = maisAtu;
  } else {
    mais = HIGH;
  }

  menosAtu = digitalRead(pinoMenos);
  if (menosAtu != menosAnt) {
    if (menosAtu == LOW) {
      menos = LOW;
    }
    menosAnt = menosAtu;
  } else {
    menos = HIGH;
  }

  if (mais == LOW) {
    if (n < 7) {
      n++;
    }
  }
  else if (menos == LOW) {
    if (n > 0) {
      n--;
    }
  }

  if (digitalRead(teclaC) == LOW) {
    tone(rele, c * multi);
  }
  /*
  else if (digitalRead(teclaD) == LOW) {
    tone(rele, d * multi);
  }
  else if (digitalRead(teclaE) == LOW) {
    tone(rele, e * multi);
  }
  else if (digitalRead(teclaF) == LOW) {
    tone(rele, f * multi);
  }
  else if (digitalRead(teclaG) == LOW) {
    tone(rele, g * multi);
  }
  else if (digitalRead(teclaA) == LOW) {
    tone(rele, a * multi);
  }
  else if (digitalRead(teclaB) == LOW) {
    tone(rele, b * multi);
  }*/
  else {
    noTone(rele);
  }
}
