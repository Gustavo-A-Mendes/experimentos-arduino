/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: STAR WARS - Marcha Imperial
   */

int c2 = 65, cS2 = 69, d2 = 73, dS2 = 78, e2 = 82, f2 = 87,
    fS2 = 93, g2 = 98, gS2 = 104, a2 = 110, aS2 = 117, b2 = 123;

// COMPASSO: 3/4
float andamento = 120.0;
// tempo do compasso(s) = 180 / andamento
float tempo = (180 / andamento) * 1000;

// notas na melodia:
int melodia[] = {
  g2, c2, dS2, f2,/*|*/g2, c2, dS2, f2,/*|*/
  g2, c2, dS2, f2,/*|*/g2, c2, dS2, f2,/*|*/
  g2, c2, e2, f2,/*|*/g2, c2, e2, f2,/*|*/
  g2, c2, e2, f2,/*|*/g2, c2, e2, f2,/*|*/
  g2,/*|*/c2,/*|*/dS2, f2, g2,/*|*/c2, dS2, f2,/*|*/
  d2, g2/2, aS2, c2,/*|*/d2, g2/2, aS2, c2,/*|*/
  d2, g2/2, aS2, c2,/*|*/d2, g2/2, aS2,/*|*/
  f2,/*|*/aS2,/*|*/dS2, d2, f2,/*|*/aS2, dS2, d2,/*|*/
  c2, f2/2, a2, aS2,/*|*/c2, f2/2, a2, aS2,/*|*/
  c2, f2/2, a2, aS2,/*|*/d2, f2/2
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
float duracaoNotas[] = {
  4.0, 4.0, 8.0, 8.0,/*|*/4.0, 4.0, 8.0, 8.0,/*|*/
  4.0, 4.0, 8.0, 8.0,/*|*/4.0, 4.0, 8.0, 8.0,/*|*/
  4.0, 4.0, 8.0, 8.0,/*|*/4.0, 4.0, 8.0, 8.0,/*|*/
  4.0, 4.0, 8.0, 8.0,/*|*/4.0, 4.0, 8.0, 8.0,/*|*/
  4.0/3,/*|*/4.0/3,/*|*/8.0, 8.0, 2.0,/*|*/2.0, 8.0, 8.0,/*|*/
  4.0, 4.0, 8.0, 8.0,/*|*/4.0, 4.0, 8.0, 8.0,/*|*/
  4.0, 4.0, 8.0, 8.0,/*|*/4.0, 4.0, 4.0,/*|*/
  4.0/3,/*|*/4.0/3,/*|*/8.0, 8.0, 2.0,/*|*/2.0, 8.0, 8.0,/*|*/
  4.0, 4.0, 8.0, 8.0,/*|*/4.0, 4.0, 8.0, 8.0,/*|*/
  4.0, 4.0, 8.0, 8.0,/*|*/4.0, 2.0
  
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 77; nota++) {
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    float duracaoNota = tempo / (duracaoNotas[nota]);
    tone(9, melodia[nota]*2, duracaoNota - 50);
    
    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo até o próxima nota se manterá.
    float pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}
void loop() {
  // nao precisa repetir a melodia.
}
