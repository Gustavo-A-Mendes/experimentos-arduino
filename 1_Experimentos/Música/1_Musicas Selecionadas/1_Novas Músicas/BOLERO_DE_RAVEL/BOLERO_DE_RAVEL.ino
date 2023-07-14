/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: BOLERO DE RAVEL - Maurice Ravel
   */

int c2 = 65, d2 = 73, e2 = 82, f2 = 87, g2 = 98,
    a2 = 110, b2 = 123, c3 = 131, d3 = 147;

// COMPASSO: 3/4
float andamento = 66;
// tempo do compasso(s) = 180 / andamento
float tempo = (180 / andamento) * 1000;

// notas na melodia:
int melodia[] = {
  c3,b2,c3,d3,c3,b2,a2,   c3,c3,a2,c3,b2,c3,
  a2,g2,e2,f2,g2,         f2,e2,d2,e2,f2,g2,a2,g2,
  a2,b2,a2,g2,f2,e2,d2,   e2,d2,c2,c2,c2,d2,e2,f2,
  d2,g2
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  2,12,12,12,12,12,12,    6,12,12,2,12,12,
  12,12,12,12,4/3,        12,12,12,12,12,12,12,4/3,
  12,12,12,12,12,12,12,   12,12,6,6,12,12,6,6,
  3,3/5
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 43; nota++) {
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
