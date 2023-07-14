/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Playlist de Musicas
*/

// Oitavas: C3 -> C2*2
//          C1 -> C2/2
int c2 = 65, cS2 = 69, d2 = 73, dS2 = 78, e2 = 82, f2 = 87,
    fS2 = 93, g2 = 98, gS2 = 104, a2 = 110, aS2 = 117, b2 = 123;

const int pinoSeletor = 7;
const int pinoPlay = 6;
//const int ledUM = 12, ledDOIS = 11, ledTRES = 10, ledQUATRO = 8;
const int pinoLED[4] = {12, 11, 10, 8};
int trilha = 0;
int play;

void setup() {
  Serial.begin(9600);
  pinMode(pinoPlay, INPUT);
  pinMode(pinoSeletor, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(pinoLED[i], OUTPUT);
  }
  //  pinMode(ledUM, OUTPUT);
  //  pinMode(ledDOIS, OUTPUT);
  //  pinMode(ledTRES, OUTPUT);
  //  pinMode(ledQUATRO, OUTPUT);

  //  Serial.println(trilha);
}

void loop() {
  //  Serial.println(analogRead(A0));
  //  play = digitalRead(pinoPlay);
    do {
    botaoSeletor(pinoSeletor, 4);
    acendeLED();
    play = digitalRead(pinoPlay);
    } while (play == HIGH);

    switch (trilha) {
    case 0:
      //  indicacaoTrilha(trilha, pinoLED);
      break;
    case 1:
      //  indicacaoTrilha(trilha, pinoLED);
      asaBranca();
      trilha = 0;
      break;
    case 2:
      //  indicacaoTrilha(trilha, pinoLED);
      gameOfThrones();
      trilha = 0;
      break;
    case 3:
      //  indicacaoTrilha(trilha, pinoLED);
      marioTheme();
      trilha = 0;
      break;
    case 4:
      //  indicacaoTrilha(trilha, pinoLED);
      marchaImperial();
      trilha = 0;
      break;
    default:
      trilha = 0;
      break;
    }
}


void botaoSeletor (int pino, int n) {
  static int estadoAtu, estadoAnt;
  estadoAtu = digitalRead(pino);
  Serial.println(trilha);
  if (estadoAtu != estadoAnt) {
    if (estadoAtu == LOW) {
      trilha++;
      if (trilha > n) {
        trilha = 1;
      }

    }
    estadoAnt = estadoAtu;
  }
}


void acendeLED() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pinoLED[i], LOW);
  }
  if (trilha > 0) {
    digitalWrite(pinoLED[trilha - 1], HIGH);
  }
}
