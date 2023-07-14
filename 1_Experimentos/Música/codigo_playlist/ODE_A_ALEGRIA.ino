/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: 9 SINFONIA: ODE A ALEGRIA - L. V. Beethoven
*/

#define rele 9

void odeAlegria() {
  //  int c2 = 65, d2 = 73, e2 = 82, f2 = 87, g2 = 98;

  int notas = 62;
  float bpm = 120.0;
  // notas na melodia:
  int melodia[62] = {
    e2, e2, f2, g2,/*|*/g2, f2, e2, d2,/*|*/
    c2, c2, d2, e2,/*|*/e2, d2, d2,/*|*/
    e2, e2, f2, g2,/*|*/g2, f2, e2, d2,/*|*/
    c2, c2, d2, e2,/*|*/d2, c2, c2,/*|*/
    d2, d2, e2, c2,/*|*/d2, e2, f2, e2, c2,/*|*/
    d2, e2, f2, e2, d2,/*|*/c2, d2, g2,/*|*/
    e2, e2, f2, g2,/*|*/g2, f2, e2, d2,/*|*/
    c2, c2, d2, e2,/*|*/d2, c2, c2
  };

  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  float duracaoNotas[62] = {
    4.0, 4.0, 4.0, 4.0,/*|*/4.0, 4.0, 4.0, 4.0,/*|*/
    4.0, 4.0, 4.0, 4.0,/*|*/8.0 / 3, 8.0, 2.0, /*|*/
    4.0, 4.0, 4.0, 4.0,/*|*/4.0, 4.0, 4.0, 4.0,/*|*/
    4.0, 4.0, 4.0, 4.0,/*|*/8.0 / 3, 8.0, 2.0, /*|*/
    4.0, 4.0, 4.0, 4.0,/*|*/4.0, 8.0, 8.0, 4.0, 4.0,/*|*/
    4.0, 8.0, 8.0, 4.0, 4.0,/*|*/4.0, 4.0, 2.0,/*|*/
    4.0, 4.0, 4.0, 4.0,/*|*/4.0, 4.0, 4.0, 4.0,/*|*/
    4.0, 4.0, 4.0, 4.0,/*|*/8.0 / 3, 8.0, 2.0
  };

  jukebox(rele, bpm, melodia, duracaoNotas, notas);
}
