/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: 9 SINFONIA: ODE A ALEGRIA - L. V. Beethoven
   */

int c2 = 65, d2 = 73, e2 = 82, f2 = 87, g2 = 98;

// COMPASSO: 4/4
float andamento = 120;
// tempo do compasso(s) = 240 / andamento
float tempo = (240 / andamento) * 1000;

// notas na melodia:
int melodia[] = {
  e2,e2,f2,g2,    g2,f2,e2,d2,
  c2,c2,d2,e2,    e2,d2,d2,
  e2,e2,f2,g2,    g2,f2,e2,d2,
  c2,c2,d2,e2,    d2,c2,c2
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
float duracaoNotas[] = {
  4.0, 4.0, 4.0, 4.0,       4.0,   4.0, 4.0, 4.0,
  4.0, 4.0, 4.0, 4.0,       8.0/3, 8.0, 2.0,
  4.0, 4.0, 4.0, 4.0,       4.0,   4.0, 4.0, 4.0,
  4.0, 4.0, 4.0, 4.0,       8.0/3, 8.0, 2.0
};

void setup() {

  Serial.begin(9600);
  // itera as notas das melodias:
  for (int nota = 0; nota < 30; nota++) {
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    float duracaoNota = tempo / duracaoNotas[nota];
    Serial.println(duracaoNota);
    tone(9, melodia[nota], duracaoNota - 50);
    
    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo até o próxima nota se manterá.
    float pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(9);
  }
}
void loop() {
  // nao precisa repetir a melodia.
}
