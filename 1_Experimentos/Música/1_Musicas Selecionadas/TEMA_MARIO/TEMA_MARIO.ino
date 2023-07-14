/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: Tema Super Mario Bros
   */

int c2 = 65, d2 = 73, e2 = 82, f2 = 87, g2 = 98, a2 = 110, aS2= 117, b2 = 123;

// COMPASSO: 4/4
int andamento = 180;
// tempo do compasso(s) = 240 / andamento
float tempo = (240 / andamento) * 1000;

// Oitavas: C3 -> C2*2
//          C1 -> C2/2
// notas na melodia:
int melodia[] = {
  e2,e2,0,e2,0,c2,e2,          g2,0,g2/2,0,
  c2*2,0,g2,0,e2,              0,a2,b2,aS2,a2,
  g2,e2*2,g2*2,a2*2,f2*2,g2*2, 0,e2*2,c2*2,d2*2,b2,0,
  c2*2,0,g2,0,e2,              0,a2,b2,aS2,a2,
  g2,e2*2,g2*2,a2*2,f2*2,g2*2, 0,e2*2,c2*2,d2*2,b2,0,
  e2,e2,0,e2,0,c2,e2,          g2,0,g2/2,0
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  8,8,8,8,8,8,4, 4,4,4,4,
  4,8,4,8,4,     8,4,4,8,4,
  6,6,6,4,8,8,   8,4,8,8,4,8,
  4,8,4,8,4,     8,4,4,8,4,
  6,6,6,4,8,8,   8,4,8,8,4,8,
  8,8,8,8,8,8,4, 4,4,4,4
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 66; nota++) {
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = tempo / (duracaoNotas[nota]);
    tone(9, melodia[nota], duracaoNota - 50);
    
    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo total utilizado pela nota se manterá.
    int pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}

void loop() {
  // nao precisa repetir a melodia.
}
