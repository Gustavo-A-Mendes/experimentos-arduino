/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: NEVER GONNA GIVE YOU UP - Rick Roll
*/

#include <Jukebox.h>
#define rele 9

void rickRoll() {
  //  int c2 = 65, cS2 = 69, d2 = 73, dS2 = 78, e2 = 82, f2 = 87,
  //      fS2 = 93, g2 = 98, gS2 = 104, a2 = 110, aS2 = 117, b2 = 123;

  int notas = 66;
  float bpm = 114.0;
  // notas na melodia:
  int melodia[67] = {
    f2, g2, c2,/*|*/g2, a2, c2*2, aS2, a2,/*|*/f2, g2, c2, 0, c2, c2, d2, f2, f2,/*|*/
    f2, g2, c2,/*|*/g2, a2, c2*2, aS2, a2,/*|*/f2, g2, c2, 0, d2, e2, f2, d2,/*|*/
    0, f2, a2, g2, c2, d2, f2, d2,/*|*/a2, a2, g2, c2, d2, f2, d2,/*|*/
    g2, g2, f2, e2, d2, c2, d2, f2, d2,/*|*/f2, g2, e2, d2, c2, c2, c2,/*|*/g2, f2
  };
  
  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  int duracaoNotas[67] = {
    -4, -4, 4,/*|*/-4, -4, 16, 16, 8,/*|*/-4, -4, 2, -4, 16, 16, 16, 8, 16,/*|*/
    -4, -4, 4,/*|*/-4, -4, 16, 16, 8,/*|*/-4, -4, 2, 2, 8, 8, 8, 8,/*|*/
    8, 8, 8, -4, 16, 16, 16, 16,/*|*/-8, -8, -4, 16, 16, 16, 16,/*|*/
    -8, -8, -8, 16, 8, 16, 16, 16, 16,/*|*/4, 8, -8, 16, 8, 8, 8,/*|*/4, 2
  };

  Jukebox msc6(rele, bpm, melodia, duracaoNotas, notas);
  msc6.Update();
}
