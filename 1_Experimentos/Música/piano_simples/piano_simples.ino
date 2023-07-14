const int botoes[7] = {
  12, 11, 8, 6, 5, 3, 2
};
const int pinoMais = A5;
const int pinoMenos = A4;

bool botoesEstado[7] = {
  1, 1, 1, 1, 1, 1, 1
};
bool mais, menos;

// ------------ C - D - E - F - G - A -- B -
int notas[7] = {65, 73, 82, 87, 98, 110, 123
};

// limite: 0.5(minimo) até 64 -> 2^6 (maximo);
float multi = 1.0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 7; i++) {
    pinMode(botoes[i], INPUT);
  }
}

void loop() {
  /*
    for (int i = 0; i < 7; i++) {
    Serial.print(digitalRead(botoes[i]));
    Serial.print(" ");
    }
    Serial.println("");
  */
//  mudarOitava(pinoMais, pinoMenos);
    aumentarOitava(pinoMais);
    diminuirOitava(pinoMenos);
  //  Serial.println(multi);

  for (int i = 0; i < 7; i++) {
    botoesEstado[i] = digitalRead(botoes[i]);

    if (botoesEstado[i] == LOW) {
      tone(9, notas[i] * multi);
    }
    if (pararNota(botoesEstado)) {
      noTone(9);
    }
  }
}

bool pararNota (bool pinos[7]) {
  for (int i = 0; i < 7; i++) {
    if (pinos[i] == LOW) {
      return LOW;
    }
  }
  return HIGH;
}

void mudarOitava (int pino1, int pino2) {
  static int estado1Atu, estado1Ant, estado2Atu, estado2Ant;
  estado1Atu = digitalRead(pino1);
  estado2Atu = digitalRead(pino2);
//  Serial.println(estadoAtu);
  if (estado1Atu != estado1Ant || estado2Atu != estado2Ant) {
    if (multi > 0.5 && multi < 64.0) {
      if (estado1Atu == LOW) {
        multi *= 2.0;
      }
      else if (estado2Atu == LOW) {
        multi *= 0.5;
      }
    }
    estado1Ant = estado1Atu;
    estado2Ant = estado2Atu;
  }
}

void aumentarOitava (int pino) {
  static int estadoAtu, estadoAnt;
  estadoAtu = digitalRead(pino);
  if (estadoAtu != estadoAnt) {
    if (estadoAtu == LOW) {
      if (multi < 64) {
        multi *= 2.0;
      }
    }
    estadoAnt = estadoAtu;
  }
}

void diminuirOitava (int pino) {
  static int estadoAtu, estadoAnt;
  estadoAtu = digitalRead(pino);
  if (estadoAtu != estadoAnt) {
    if (estadoAtu == LOW) {
      if (multi > 0.5) {
        multi *= 0.5;
      }
    }
    estadoAnt = estadoAtu;
  }
}
