/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: Game of Thrones Theme
*/

#define rele 9
void gameOfThrones() {
  //int c2 = 65, cS2 = 69, d2 = 73, dS2 = 78, e2 = 82, f2 = 87,
  //    fS2 = 93, g2 = 98, gS2 = 104, a2 = 110, aS2 = 117, b2 = 123;

  int notas = 76;
  float bpm = 168.0;
  // notas na melodia:
  // notas na melodia:
  int melodia[77] = {
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
  float duracaoNotas[77] = {
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

  jukebox(rele, bpm, melodia, duracaoNotas, notas);
}
