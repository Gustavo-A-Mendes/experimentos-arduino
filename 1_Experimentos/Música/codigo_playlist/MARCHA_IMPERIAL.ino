/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: STAR WARS - Marcha Imperial
*/

#define rele 9

void marchaImperial() {
  //  int c2 = 65, cS2 = 69, d2 = 73, dS2 = 78, e2 = 82, f2 = 87,
  //      fS2 = 93, g2 = 98, gS2 = 104, a2 = 110, aS2 = 117, b2 = 123;

  int notas = 70;
  float bpm = 108.0;
  // notas na melodia:
  int melodia[] = {
    g2, g2, g2, dS2, aS2,/*|*/g2, dS2, aS2, g2,/*|*/
    d2*2, d2*2, d2*2, dS2*2, aS2,/*|*/fS2, dS2, aS2, g2,/*|*/
    g2*2, g2, g2, g2*2, fS2*2, f2*2,/*|*/
    e2*2, dS2*2, e2*2, 0, gS2, cS2*2, c2*2, b2,/*|*/
    aS2, a2, aS2, 0, dS2, fS2, dS2, fS2,/*|*/aS2, g2, aS2, d2*2,/*|*/
    g2*2, g2, g2, g2*2, fS2*2, f2*2,/*|*/
    e2*2, dS2*2, e2*2, 0, gS2, cS2*2, c2*2, b2,/*|*/
    aS2, a2, aS2, 0, dS2, fS2, dS2, aS2,/*|*/g2, dS2, aS2, g2
  };
  
  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  float duracaoNotas[70] = {
    4.0, 4.0, 4.0, 16.0/3, 16.0,/*|*/4.0, 16.0/3, 16.0, 2.0,/*|*/
    4.0, 4.0, 4.0, 16.0/3, 16.0,/*|*/4.0, 16.0/3, 16.0, 2.0,/*|*/
    4.0, 16.0/3, 16.0, 4.0, 16.0/3, 16.0,/*|*/
    16.0, 16.0, 8.0, 8.0, 8.0, 4.0, 16.0/3, 16.0,/*|*/
    16.0, 16.0, 8.0, 8.0, 8.0, 4.0, 16.0/3, 16.0,/*|*/4.0, 16.0/3, 16.0, 2.0,/*|*/
    4.0, 16.0/3, 16.0, 4.0, 16.0/3, 16.0,/*|*/
    16.0, 16.0, 8.0, 8.0, 8.0, 4.0, 16.0/3, 16.0,/*|*/
    16.0, 16.0, 8.0, 8.0, 8.0, 4.0, 16.0/3, 16.0,/*|*/4.0, 16.0/3, 16.0, 2.0
  };

  jukebox(rele, bpm, melodia, duracaoNotas, notas);
}
