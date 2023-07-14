/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: Asa Branca
   */

int c2 = 65, d2 = 73, e2 = 82, f2 = 87, g2 = 98;

// COMPASSO: 4/4
float andamento = 210;
// tempo do compasso(s) = 240 / andamento
float tempo = (240 / andamento) * 1000;

// notas na melodia:
int melodia[] = {
  0,c2,d2,    e2,g2,  g2,e2,      f2,f2,
  0,c2,d2,    e2,g2,  g2,f2,      e2,
  0,c2,c2,d2, e2,g2,  0,g2,f2,e2, c2,f2,
  0,f2,e2,d2, d2,e2,  0,d2,d2,c2, c2,0,
  0,c2,c2,d2, e2,g2,  0,g2,f2,e2, c2,f2,
  0,f2,e2,d2, d2,e2,  0,d2,d2,c2, c2,0
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  2,4,4,   2,2, 2,2,     2,2, 
  2,4,4,   2,2, 2,2,     1,
  4,4,4,4, 2,2, 4,4,4,4, 2,2,
  4,4,4,4, 2,2, 4,4,4,4, 1,4,
  4,4,4,4, 2,2, 4,4,4,4, 2,2,
  4,4,4,4, 2,2, 4,4,4,4, 1,4
  
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 65; nota++) {
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = tempo / (duracaoNotas[nota]);
    tone(9, melodia[nota], duracaoNota - 50);
    
    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo ate o proxima nota se mantera.
    int pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}

void loop() {
  // nao precisa repetir a melodia.
}
