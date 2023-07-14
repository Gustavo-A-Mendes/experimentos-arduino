/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: TRENZINHO CAIPIRA - Heitor Villa-Lobos
   */

int c2 = 65, d2 = 73, e2 = 82, f2 = 87, g2 = 98, a2 = 110;

// COMPASSO: 4/4
float andamento = 120;
// tempo do compasso(s) = 240 / andamento
float tempo = (240 / andamento) * 1000;

// notas na melodia:
int melodia[] = {
  e2,e2,e2,d2,c2,     e2,e2,
  g2,g2,g2,f2,e2,     f2,
  f2,f2,f2,e2,d2,     f2,f2,
  a2,a2,a2,g2,f2,     g2
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  8/3,8,16/3,16/3,8,  8/7,8,
  8/3,8,16/3,16/3,8,  1,
  8/3,8,16/3,16/3,8,  4/3,4,
  8/3,8,16/3,16/3,8,  1
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 26; nota++) {
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = tempo / (duracaoNotas[nota]);
    tone(9, melodia[nota], duracaoNota - 50);
    
    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo até o próxima nota se manterá.
    int pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}
void loop() {
  // nao precisa repetir a melodia.
}
