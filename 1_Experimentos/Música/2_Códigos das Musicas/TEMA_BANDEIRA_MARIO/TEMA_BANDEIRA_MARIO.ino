// faixa com som alto = C1 ao GS3
// faixa com som baixo = A3 ao D8

#define NOTA_C3  131
#define NOTA_CS3 139
#define NOTA_D3  147
#define NOTA_DS3 156
#define NOTA_E3  165
#define NOTA_F3  175
#define NOTA_FS3 185
#define NOTA_G3  196
#define NOTA_GS3 208
#define NOTA_A3  220
#define NOTA_AS3 233
#define NOTA_B3  247

// COMPASSO: 4/4
// notas na melodia:
int melodia[] = {
  NOTA_G3/2,NOTA_C3,NOTA_E3,NOTA_G3,NOTA_C3*2,NOTA_E3*2,NOTA_G3*2,NOTA_E3*2,
   NOTA_GS3/2,NOTA_C3,NOTA_DS3,NOTA_GS3,NOTA_C3*2,NOTA_DS3*2,NOTA_GS3*2,NOTA_DS3*2,
    NOTA_AS3/2,NOTA_D3,NOTA_F3,NOTA_AS3,NOTA_D3*2,NOTA_F3*2,NOTA_AS3*2,NOTA_AS3*2,NOTA_AS3*2,NOTA_AS3*2,
     NOTA_C3*4
  
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  12,12,12,12,12,12,4,4,
   12,12,12,12,12,12,4,4,
    12,12,12,12,12,12,4,12,12,12,
     1
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 27; nota++) {

    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = 1000 / duracaoNotas[nota];
    tone(9, 2*melodia[nota], duracaoNota);

    // para distinguir as notas, adicione um tempo minimo entre elas.
    // duracao da nota + 30% parece funcionar bem:
    int pausaEntreNotas = duracaoNota + 50;
    //delay(40);
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}

void loop() {
  // nao precisa repetir a melodia.
}
