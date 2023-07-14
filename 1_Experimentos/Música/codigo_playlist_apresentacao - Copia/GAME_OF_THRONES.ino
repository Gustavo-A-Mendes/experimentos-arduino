/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: Game of Thrones Theme
*/

#include <Jukebox.h>
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
    f2,/*|*/aS2,/*|*/dS2, d2, f2,/*|*/aS2/2, dS2, d2,/*|*/
    c2, f2/2, a2/2, aS2/2,/*|*/c2, f2/2, a2/2, aS2/2,/*|*/
    c2, f2/2, a2/2, aS2/2,/*|*/c2
  };
  
  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  int duracaoNotas[77] = {
    4, 4, 8, 8,/*|*/4, 4, 8, 8,/*|*/
    4, 4, 8, 8,/*|*/4, 4, 8, 8,/*|*/
    4, 4, 8, 8,/*|*/4, 4, 8, 8,/*|*/
    4, 4, 8, 8,/*|*/4, 4, 8, 8,/*|*/
    -2,/*|*/-2,/*|*/8, 8, 2,/*|*/2, 8, 8,/*|*/
    4, 4, 8, 8,/*|*/4, 4, 8, 8,/*|*/
    4, 4, 8, 8,/*|*/4, 4, 4,/*|*/
    -2,/*|*/-2,/*|*/8, 8, 2,/*|*/2, 8, 8,/*|*/
    4, 4, 8, 8,/*|*/4, 4, 8, 8,/*|*/
    4, 4, 8, 8,/*|*/2
  };

  Jukebox msc1(rele, bpm, melodia, duracaoNotas, notas);
  msc1.Update();
}
