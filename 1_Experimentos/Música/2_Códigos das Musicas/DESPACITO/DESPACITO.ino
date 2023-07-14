/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: Despacito
   */

#define NOTA_C2  65
#define NOTA_CS2 69
#define NOTA_D2  73
#define NOTA_E2  82
#define NOTA_F2  87
#define NOTA_FS2 93
#define NOTA_G2  98
#define NOTA_A2  110
#define NOTA_AS2 117
#define NOTA_B2  123

// COMPASSO: 4/4
float andamento = 89;
// tempo do compasso(s) = 240 / andamento
float tempo = (240 / andamento) * 1000;

// Oitavas: C3 -> C2*2
//          C1 -> C2/2
// notas na melodia:
int melodia[] = {
  NOTA_B2,0,NOTA_FS2,NOTA_B2,NOTA_CS2*2,NOTA_D2*2,NOTA_E2*2,NOTA_D2*2,NOTA_CS2*2,NOTA_B2,NOTA_A2, 
   NOTA_G2,NOTA_D2*2,NOTA_D2*2,0,0, NOTA_D2*2,NOTA_A2,NOTA_D2*2,NOTA_A2,NOTA_D2*2,NOTA_A2,NOTA_D2*2,NOTA_E2*2,
    NOTA_CS2*2,0,0, NOTA_B2,NOTA_B2,NOTA_B2,NOTA_B2,NOTA_CS2*2,NOTA_D2*2,NOTA_CS2*2,NOTA_D2*2,NOTA_CS2*2,NOTA_D2*2,NOTA_CS2*2,
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  4,16,16,16,16,12,12,12,12,12,12, 
   5,5,4,8,4, 8,8,8,8,8,8,8,16,
    3,4,2, 4,16,16,16,16,16,16,8,12,12,12,
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 38; nota++) {

    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = tempo / (duracaoNotas[nota]);
    tone(9, 4*melodia[nota], duracaoNota - 50);
    
    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo total utilizado pela nota se manterá.
    int pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}

void loop() {
  // nao precisa repetir a melodia.
}
