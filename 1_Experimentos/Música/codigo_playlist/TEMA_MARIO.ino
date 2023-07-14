/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: Tema Super Mario Bros
*/

#define rele 9

void marioTheme() {
  //  int c2 = 65, d2 = 73, e2 = 82, f2 = 87, g2 = 98, a2 = 110, aS2= 117, b2 = 123;

  int notas = 66;
  float bpm = 180.0;
  // notas na melodia:
  int melodia[66] = {
    e2, e2, 0, e2, 0, c2, e2,/*|*/g2, 0, g2/2, 0,/*|*/
    c2*2, 0, g2, 0, e2,/*|*/0, a2, b2, aS2, a2,/*|*/
    g2, e2*2, g2*2, a2*2, f2*2, g2*2,/*|*/0, e2*2, c2*2, d2*2, b2, 0,/*|*/
    c2*2, 0, g2, 0, e2,/*|*/0, a2, b2, aS2, a2,/*|*/
    g2, e2*2, g2*2, a2*2, f2*2, g2*2,/*|*/0, e2*2, c2*2, d2*2, b2, 0,/*|*/
    e2, e2, 0, e2, 0, c2, e2,/*|*/g2, 0, g2/2, 0
  };

  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  float duracaoNotas[66] = {
    8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 4.0,/*|*/4.0, 4.0, 4.0, 4.0,/*|*/
    4.0, 8.0, 4.0, 8.0, 4.0,/*|*/8.0, 4.0, 4.0, 8.0, 4.0,/*|*/
    6.0, 6.0, 6.0, 4.0, 8.0, 8.0,/*|*/8.0, 4.0, 8.0, 8.0, 4.0, 8.0,/*|*/
    4.0, 8.0, 4.0, 8.0, 4.0,/*|*/8.0, 4.0, 4.0, 8.0, 4.0,/*|*/
    6.0, 6.0, 6.0, 4.0, 8.0, 8.0,/*|*/8.0, 4.0, 8.0, 8.0, 4.0, 8.0,/*|*/
    8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 4.0,/*|*/4.0, 4.0, 4.0, 4.0
  };

  jukebox(rele, bpm, melodia, duracaoNotas, notas);
}
