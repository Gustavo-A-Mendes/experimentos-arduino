/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: GRAVITY FALLS - Tema de Abertura
*/

#include <Jukebox.h>
#define rele 9

void gravityFalls() {
  //  int c2 = 65, cS2 = 69, d2 = 73, dS2 = 78, e2 = 82, f2 = 87,
  //      fS2 = 93, g2 = 98, gS2 = 104, a2 = 110, aS2 = 117, b2 = 123;

  int notas = 99;
  float bpm = 160.0;
  // notas na melodia:
  int melodia[100] = {
    f2, d2, a2/2, d2, f2, d2, a2/2, d2,/*|*/f2, c2, a2/2, c2, f2, c2, a2/2, c2,/*|*/
    e2, cS2, a2/2, cS2, e2, cS2, a2/2, cS2,/*|*/e2, cS2, a2/2, cS2, e2, a2,/*|*/
    d2, e2,/*|*/f2,/*|*/a2, g2, a2,/*|*/c2,/*|*/
    d2, 0, e2,/*|*/f2, e2,/*|*/g2, a2,/*|*/g2, f2,/*|*/
    0, f2, f2, f2,/*|*/a2, a2, g2, f2,/*|*/0, a2, a2, a2,/*|*/g2, a2, g2, f2,/*|*/
    0, f2, f2, f2,/*|*/a2, a2, g2, f2,/*|*/0, a2, a2, a2,/*|*/0, cS2*2, cS2*2, cS2*2,/*|*/
    0, f2, f2, f2,/*|*/a2, a2, g2, f2,/*|*/0, aS2, aS2, aS2,/*|*/g2, 0, c2*2, 0,/*|*/
    a2, 0, cS2*2, 0,/*|*/d2*2
  };
  
  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  int duracaoNotas[100] = {
    8, 8, 8, 8, 8, 8, 8, 8,/*|*/8, 8, 8, 8, 8, 8, 8, 8,/*|*/
    8, 8, 8, 8, 8, 8, 8, 8,/*|*/8, 8, 8, 8, 4, 4,/*|*/
    -2, 4,/*|*/1,/*|*/-4, -4, 4,/*|*/1,/*|*/
    2, 4, 4,/*|*/2, 2,/*|*/2, 2,/*|*/2, 2,/*|*/
    4, 4, 4, 4,/*|*/4, 4, 4, 4,/*|*/4, 4, 4, 4,/*|*/4, 4, 4, 4,/*|*/
    4, 4, 4, 4,/*|*/4, 4, 4, 4,/*|*/4, 4, 4, 4,/*|*/4, 4, 4, 4,/*|*/
    4, 4, 4, 4,/*|*/4, 4, 4, 4,/*|*/4, 4, 4, 4,/*|*/4, 4, 4, 4,/*|*/
    4, 4, 4, 4,/*|*/2
  };

  Jukebox msc2(rele, bpm, melodia, duracaoNotas, notas);
  msc2.Update();
}
