/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: Asa Branca
*/

#include <Jukebox.h>
#define rele 9
void asaBranca() {
  //  int c2 = 65, d2 = 73, e2 = 82, f2 = 87, g2 = 98;

  int notas = 65;
  float bpm = 210.0;
  // notas na melodia:
  int melodia[66] = {
    0, c2, d2,/*|*/e2, g2,/*|*/g2, e2,/*|*/f2, f2,
    0, c2, d2,/*|*/e2, g2,/*|*/g2, f2,/*|*/e2,
    0, c2, c2, d2,/*|*/e2, g2,/*|*/0, g2, f2, e2,/*|*/c2, f2,
    0, f2, e2, d2,/*|*/d2, e2,/*|*/0, d2, d2, c2,/*|*/c2, 0,
    0, c2, c2, d2,/*|*/e2, g2,/*|*/0, g2, f2, e2,/*|*/c2, f2,
    0, f2, e2, d2,/*|*/d2, e2,/*|*/0, d2, d2, c2,/*|*/c2, 0
  };

  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  int duracaoNotas[66] = {
    2, 4, 4,/*|*/2, 2,/*|*/2, 2,/*|*/2, 2,
    2, 4, 4,/*|*/2, 2,/*|*/2, 2,/*|*/1,
    4, 4, 4, 4,/*|*/2, 2,/*|*/4, 4, 4, 4,/*|*/2, 2,
    4, 4, 4, 4,/*|*/2, 2,/*|*/4, 4, 4, 4,/*|*/1, 4,
    4, 4, 4, 4,/*|*/2, 2,/*|*/4, 4, 4, 4,/*|*/2, 2,
    4, 4, 4, 4,/*|*/2, 2,/*|*/4, 4, 4, 4,/*|*/1, 4
  };

  Jukebox msc3(rele, bpm, melodia, duracaoNotas, notas);
  msc3.Update();
}
