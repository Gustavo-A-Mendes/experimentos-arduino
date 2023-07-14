/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: Asa Branca
*/

#define rele 9
void secrets() {
//  int c2 = 65, cS2 = 69, d2 = 73, dS2 = 78, e2 = 82, f2 = 87,
//      fS2 = 93, g2 = 98, gS2 = 104, a2 = 110, aS2 = 117, b2 = 123;

  int notas = 48;
  float bpm = 133.0;
  // notas na melodia:
  int melodia[48] = {
    d2, fS2, a2, fS2, a2, fS2, d2, fS2,/*|*/d2, fS2, a2, fS2, a2, fS2, d2, fS2,/*|*/
    cS2, fS2, a2, fS2, a2, fS2, cS2, fS2,/*|*/cS2, fS2, a2, fS2, a2, fS2, cS2, fS2,/*|*/
    b2/2, d2, b2, d2, b2, d2, b2/2, d2
  };

  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  float duracaoNotas[64] = {
    8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,/*|*/8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,/*|*/
    8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,/*|*/8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,/*|*/
    8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0
  };

  jukebox(rele, bpm, melodia, duracaoNotas, notas);
}
