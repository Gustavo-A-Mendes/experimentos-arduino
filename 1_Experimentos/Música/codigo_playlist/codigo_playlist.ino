/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Playlist de Musicas
*/

// Oitavas: C3 -> C2*2
//          C1 -> C2/2
int c2 = 65, cS2 = 69, d2 = 73, dS2 = 78, e2 = 82, f2 = 87,
    fS2 = 93, g2 = 98, gS2 = 104, a2 = 110, aS2 = 117, b2 = 123;

const int pinoSeletor = 8;
const int pinoPlay = 7;
//    int pinoLED[4] = {2, 3, 4, 5};

int trilha = 0;
int play;

void setup() {
  Serial.begin(9600);
  pinMode(pinoPlay, INPUT);
  pinMode(pinoSeletor, INPUT);
  /*
    for (int i = 0; i < 4; i++) {
    pinMode(pinoLED[i], OUTPUT);
    }
  */
  //  Serial.println(trilha);
}

void loop() {
  //  Serial.println(analogRead(A0));
  play = digitalRead(pinoPlay);
  while (play == LOW) {
    botaoSeletor(pinoSeletor, 6);
    play = digitalRead(pinoPlay);
  }

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
      marchaImperial();
      trilha = 0;
      break;
    case 3:
      //  indicacaoTrilha(trilha, pinoLED);
      odeAlegria();
      trilha = 0;
      break;
    case 4:
      //  indicacaoTrilha(trilha, pinoLED);
      marioTheme();
      trilha = 0;
      break;
    case 5:
      //  indicacaoTrilha(trilha, pinoLED);
      secrets();
      trilha = 0;
      break;
    case 6:
      //  indicacaoTrilha(trilha, pinoLED);
      gameOfThrones();
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
    if (estadoAtu == HIGH) {
      trilha++;
      if (trilha > n) {
        trilha = 1;
      }

    }
    estadoAnt = estadoAtu;
  }
}
