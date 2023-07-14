/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: L's Theme  
   */

int c2 = 65, d2 = 73, e2 = 82, fS2 = 93, g2 = 98, a2 = 110, b2 = 247;

// COMPASSO: 4/4
float andamento = 72;
// tempo do compasso(s) = 240 / andamento
float tempo = (240 / andamento) * 1000;


// notas na melodia:
int melodia[] = {
  g2,e2,a2,e2,  fS2,g2,e2,b2, 
  a2,g2,fS2,e2, d2,g2,e2,a2, 
  e2,fS2,g2,e2, b2
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  8,8,8,8, 8,8,8,8, 
  8,8,8,8, 8,8,8,8,
  8,8,8,8, 8
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 21; nota++) {
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = tempo / (duracaoNotas[nota]*2);
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
