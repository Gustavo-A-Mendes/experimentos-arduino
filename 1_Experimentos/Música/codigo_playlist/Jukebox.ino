int relePino;

int notas, *melodia[100];
float andamento, tempo, *duracaoNotas[100];


void jukebox (int pino, float bpm, int mel[100], float duracao[100], int n) {
  relePino = pino;
  pinMode(relePino, OUTPUT);

  notas = n;
  // COMPASSO: 4/4
  andamento = bpm;
  // tempo do compasso(s) = 240 / andamento
  tempo = (240 / andamento) * 1000;
  for (int i = 0; i < notas; i++) {
    melodia[i] = &mel[i];
    duracaoNotas[i] = &duracao[i];
  }

  
  for (int nota = 0; nota < notas; nota++) {

    // float novoAndamento = map(analogRead(A0), 0, 1023, andamento/3, andamento*3);
    // tempo = (240 / novoAndamento) * 1000;
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    float duracaoNota = tempo / (*duracaoNotas[nota]);
    tone(relePino, *melodia[nota], duracaoNota - 50);

    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo até o próxima nota se manterá.
    float pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(relePino);
  }
}
