/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   ===== FISICA, MUSICA E ROBÓTICA =====
   Musica: STAR WARS - Marcha Imperial
   */

int c2 = 65, cS2 = 69, d2 = 73, dS2 = 78, e2 = 82, f2 = 87,
    fS2 = 93, g2 = 98, gS2 = 104, a2 = 110, aS2 = 117, b2 = 123;

// COMPASSO: 4/4
float andamento = 108;
// tempo do compasso(s) = 240 / andamento
float tempo = (240 / andamento) * 1000;

// notas na melodia:
int melodia[] = {
  g2,g2,g2,dS2,aS2,             g2,dS2,aS2,g2,
  d2*2,d2*2,d2*2,dS2*2,aS2,     fS2,dS2,aS2,g2,
  g2*2,g2,g2,g2*2,fS2*2,f2*2,   e2*2,dS2*2,e2*2,0,gS2,cS2*2,c2*2,b2,
  aS2,a2,aS2,0,dS2,fS2,dS2,fS2, aS2,g2,aS2,d2*2,
  g2*2,g2,g2,g2*2,fS2*2,f2*2,   e2*2,dS2*2,e2*2,0,gS2,cS2*2,c2*2,b2,
  aS2,a2,aS2,0,dS2,fS2,dS2,aS2, g2,dS2,aS2,g2  
};

// duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
int duracaoNotas[] = {
  4,4,4,16/3,16,         4,16/3,16,2,
  4,4,4,16/3,16,         4,16/3,16,2,
  4,16/3,16,4,16/3,16,   16,16,8,8,8,4,16/3,16,
  16,16,8,8,8,4,16/3,16, 4,16/3,16,2,
  4,16/3,16,4,16/3,16,   16,16,8,8,8,4,16/3,16,
  16,16,8,8,8,4,16/3,16, 4,16/3,16,2
};

void setup() {
  // itera as notas das melodias:
  for (int nota = 0; nota < 71; nota++) {
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = tempo / (duracaoNotas[nota]);
    tone(9, melodia[nota], duracaoNota - 50);
    
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
