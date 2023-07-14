/* 
UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
BACHARELADO EM CIENCIAS E TECNOLOGIA - BCT
=====:TECLADO MUSICAL:=====
*/

// define os pinos
#define rele 9
#define teclas A0
#define pinoMais A5
#define pinoMenos A4

// frequencia das notas base
int c2 = 65, d2 = 73, e2 = 82, f2 = 87, g2 = 98, a2 = 110, b2 = 123;

// sinais para indicar a escala
int nota;
float multiplicador[] = {
  0.5, 1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0
};

// sinais para mudar a frequência da escala
bool mais, menos;

void setup() {
  Serial.begin(9600);

  pinMode(rele, OUTPUT);
  pinMode(teclas, INPUT);
  pinMode(pinoMais, INPUT);
  pinMode(pinoMenos, INPUT);
}

void loop() {
  // define a escala em que o programa inicia
  static int n = 3;
  float multi = multiplicador[n];

  // monitora a mudanca de estado dos botoes
  static bool maisAtu, maisAnt, menosAtu, menosAnt;
  
  maisAtu = digitalRead(pinoMais);
  if (maisAtu != maisAnt) {
    if (maisAtu == HIGH) {
      mais = HIGH;
    }
    maisAnt = maisAtu;
  } else {
    mais = LOW;
  }
  menosAtu = digitalRead(pinoMenos);
  if (menosAtu != menosAnt) {
    if (menosAtu == HIGH) {
      menos = HIGH;
    }
    menosAnt = menosAtu;
  } else {
    menos = LOW;
  }
  
  // aumenta a frequencia
  if (mais == HIGH) {
    if (n < 7) {
      n++;
    }
  }
  // diminui a frequencia
  else if (menos == HIGH) {
    if (n > 0) {
      n--;
    }
  }

  nota = analogRead(teclas);
  Serial.println(nota);
  if ((nota >= 30) and (nota < 210)) {
    tone(rele, c2 * multi);
  }
  else if ((nota >= 210) and (nota < 410)) {
    tone(rele, d2 * multi);
  }
  else if ((nota >= 410) and (nota < 525)) {
    tone(rele, e2 * multi);
  }
  else if ((nota >= 525) and (nota < 610)) {
    tone(rele, f2 * multi);
  }
  else if ((nota >= 610) and (nota < 730)) {
    tone(rele, g2 * multi);
  }
  else if ((nota >= 730) and (nota < 915)) {
    tone(rele, a2 * multi);
  }
  else if (nota >= 915) {
    tone(rele, b2 * multi);
    }
  else {
    noTone(rele);
  }
}
