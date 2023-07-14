#define rele 9
#define teclas A0
#define pinoMais A5
#define pinoMenos A4

int nota = 0;
int c = 65, d = 73, e = 82, f = 87, g = 98, a = 110, b = 123;
float multiplicador[] = {
  0.5, 1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0
};

bool mais, menos;

void setup() {
  Serial.begin(9600);

  pinMode(rele, OUTPUT);
  pinMode(teclas, INPUT);
  pinMode(pinoMais, INPUT);
  pinMode(pinoMenos, INPUT);
}

void loop() {
  static bool maisAtu, maisAnt, menosAtu, menosAnt;
  static int n = 3;
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

  nota = analogRead(teclas);
  Serial.println(nota);
  if ((nota >= 30) and (nota < 210)) {
    tone(rele, c * multi);
  }
  else if ((nota >= 210) and (nota < 410)) {
    tone(rele, d * multi);
  }
  else if ((nota >= 410) and (nota < 525)) {
    tone(rele, e * multi);
  }
  else if ((nota >= 525) and (nota < 610)) {
    tone(rele, f * multi);
  }
  else if ((nota >= 610) and (nota < 730)) {
    tone(rele, g * multi);
  }
  else if ((nota >= 730) and (nota < 915)) {
    tone(rele, a * multi);
  }
  else if (nota >= 915) {
    tone(rele, b * multi);
    }
  else {
    noTone(rele);
  }
}
