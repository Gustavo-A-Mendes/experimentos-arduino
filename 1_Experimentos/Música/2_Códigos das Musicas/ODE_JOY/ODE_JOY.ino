// faixa com som alto = C1 ao GS3
// faixa com som baixo = A3 ao D8

int C2 = 65, D2 = 73, E2 = 82, F2 = 87, G2 = 98;

// COMPASSO: 4/4
float andamento = 112;
// tempo do compasso(s) = 240 / andamento
float tempo = (240 / andamento) * 1000;

// notas na melodia:
int melodia[] = {
  C2,E2,F2,G2, G2,F2,E2,D2,
  C2,C2,D2,E2, E2,D2,D2
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  4,4,4,4, 4,4,4,4,
  4,4,4,4, 8/3,8,2
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 15; nota++) {

    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = tempo / (duracaoNotas[nota]);
    tone(9, 8*melodia[nota], duracaoNota - 50);
    
    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo até o próxima nota se manterá.
    int pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}

void loop() {
  // nao precisa repetir a melodia.
}
