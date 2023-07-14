/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: Viva La Vida - Coldplay
   */

#define NOTA_C2  65
#define NOTA_D2  73
#define NOTA_E2  82
#define NOTA_F2  87
#define NOTA_G2  98
#define NOTA_A2  110
#define NOTA_B2  123

// COMPASSO: 4/4
// notas na melodia:
int melodia[] = {
  0,NOTA_C2*2,NOTA_E2*2,NOTA_A2*2,NOTA_G2*2, NOTA_F2*2,
   NOTA_E2*2,NOTA_C2*2,NOTA_E2*2,NOTA_A2*2,NOTA_G2*2, NOTA_F2*2,
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  8,8,8,8/3,8, 1,
   4,8,8,8,8/3,8, 1,
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 14; nota++) {

    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = 2000 / (duracaoNotas[nota]);
    tone(9, 4*melodia[nota], duracaoNota);

    // para distinguir as notas, adicione um tempo minimo entre elas.
    // duracao da nota parece funcionar bem:
    int pausaEntreNotas = duracaoNota+10;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}

void loop() {
  // nao precisa repetir a melodia.
}
