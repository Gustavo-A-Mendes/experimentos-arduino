// faixa com som alto = C1 ao GS3
// faixa com som baixo = A3 ao D8

#define NOTA_B1  62
#define NOTA_C2  65
#define NOTA_CS2 69
#define NOTA_D2  73
#define NOTA_DS2 78
#define NOTA_E2  82
#define NOTA_G2  98

// COMPASSO: 4/4
// notas na melodia:
int melodia[] = {
  NOTA_E2,0,NOTA_C2,NOTA_G2/2, NOTA_D2,NOTA_E2,NOTA_D2, 
   NOTA_CS2,NOTA_DS2,NOTA_CS2, NOTA_C2
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  4,8,2.67,4, 6,6,6,
   6,6,6, 1
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 11; nota++) {

    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = 1000 / duracaoNotas[nota];
    tone(9, 4*melodia[nota], duracaoNota);

    // para distinguir as notas, adicione um tempo minimo entre elas.
    // duracao da nota + 30% parece funcionar bem:
    int pausaEntreNotas = duracaoNota + 50;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}

void loop() {
  // nao precisa repetir a melodia.
}
