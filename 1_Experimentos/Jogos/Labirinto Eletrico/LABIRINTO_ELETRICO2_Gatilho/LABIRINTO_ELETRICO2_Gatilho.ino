/* Copie 100% deste documento e cole na área de programação do Arduino IDE */
/* *********************** Nervo Teste do Manual do Mundo ***********************
   Criado por: Anderson Harayashiki Moreira
   Rev.: 02
   Data: 25.02.2018
   Guia de conexão:o
   LED indicativo: Pino 2
   Labirinto: Pino 3
   Botão: Pino 7
   Buzzer: Pino 9
   Módulo Relé (Sirene): Pino 10
 ***************************************************************************** */
#include "pitches.h"

// Declaração dos pinos utilizados do Arduino
#define ledVERDE 2
#define ledAMARELO 3
#define ledVERMELHO 4
#define pinoBuzzer 5
#define pinoLabirinto 11
#define pinoEspera 7
#define pinoLED A0
#define pinoVitoria A5

// Declaração das variáveis auxiliares
int nivel = 0;
int deltaT;
int tomBuzzer;
int estadoLabirinto = HIGH;
int estadoEspera = HIGH;
int estadoVitoria = HIGH;
int estadoBuzzer = HIGH;

// A função setup é apenas executada uma vez ao se iniciar o Arduino, aqui configuramos nossa placa Arduino
void setup() {
  Serial.begin(9600);
  // Pinos configurados como entrada:
  pinMode(pinoLabirinto, INPUT_PULLUP); // Configurando a entrada como INPUT_PULLUP, utilizamos o resistor interno pull-up do Arduino
  pinMode(pinoEspera, INPUT_PULLUP); // Configurando a entrada como INPUT_PULLUP, utilizamos o resistor interno pull-up do Arduino
  pinMode(pinoVitoria, INPUT_PULLUP); // Configurando a entrada como INPUT_PULLUP, utilizamos o resistor interno pull-up do Arduino
  //=======  pinMode(pinoBotao, INPUT);
  // Pinos configurados como saída:
  pinMode(pinoBuzzer, OUTPUT);
  pinMode(ledVERDE, OUTPUT);
  pinMode(ledAMARELO, OUTPUT);
  pinMode(ledVERMELHO, OUTPUT);
  digitalWrite(pinoLED, LOW);

  digitalWrite(ledVERDE, HIGH);
  digitalWrite(ledAMARELO, HIGH);
  digitalWrite(ledVERMELHO, HIGH);
}
// A função loop é executada repetitivamente até se desligar o Arduino
void loop() {
  estadoLabirinto = digitalRead(pinoLabirinto);
  if (estadoLabirinto == LOW) {
    nivel++;
    // estabelece um comportamento para cada estado de nivel
    switch (nivel) {
      case 0:
        tentativas();
        break;
      case 1:
        deltaT = 150;
        tomBuzzer = 3500;
        tentativas();
        break;
      case 2:
        deltaT = 100;
        tomBuzzer = 4000;
        tentativas();
        break;
      case 3:
        deltaT = 1000;
        tomBuzzer = 500;
        tentativas();
        break;
        /*
          case 4:
          deltaT = 1000;
          tomBuzzer = 500;
          tentativas();
          break;
        */
    }
  }
  
  estadoVitoria = digitalRead(pinoVitoria);
  if (estadoVitoria == LOW) {
      digitalWrite(ledVERDE, HIGH);
      digitalWrite(ledAMARELO, HIGH);
      digitalWrite(ledVERMELHO, HIGH);
      
      vitoria();
      esperar();
      nivel = 0;
  }

}

// funcao que contabiliza as tentativas e emite um sinal caracteristico
void tentativas() {
  if (nivel >= 1) {
    if (nivel < 3) {
      for (int i = 0; i < 5; i++) {
        tone(pinoBuzzer, tomBuzzer, deltaT / 2);
        pisca();
        delay(deltaT);
      }
      noTone(pinoBuzzer);
    }
    else {
      tone(pinoBuzzer, tomBuzzer);
      pisca();
      noTone(pinoBuzzer);
      nivel = 0;
    }
  }
  esperar();
}


void pisca() {
  // Serial.println("cheguei!");
  bool estadoPisca = LOW;
  if (nivel == 1) {
    digitalWrite(ledVERDE, LOW);
    digitalWrite(ledAMARELO, HIGH);
    digitalWrite(ledVERMELHO, HIGH);
  }
  else if (nivel == 2) {
    digitalWrite(ledVERDE, LOW);
    digitalWrite(ledAMARELO, LOW);
    digitalWrite(ledVERMELHO, HIGH);
  }
  else if (nivel == 3) {
    for (int i = 0; i < 10; i++) {
      if (estadoPisca) {
        digitalWrite(ledVERDE, HIGH);
        digitalWrite(ledAMARELO, HIGH);
        digitalWrite(ledVERMELHO, HIGH);
      }
      else {
        digitalWrite(ledVERDE, LOW);
        digitalWrite(ledAMARELO, LOW);
        digitalWrite(ledVERMELHO, LOW);
      }
      estadoPisca = !estadoPisca;
      delay(250);

    }
  }
  else {
    digitalWrite(ledVERDE, HIGH);
    digitalWrite(ledAMARELO, HIGH);
    digitalWrite(ledVERMELHO, HIGH);
  }
}


void esperar() {
  while (true) {
    estadoEspera = digitalRead(pinoEspera);
    // Serial.println(estadoEspera);
    if (estadoEspera == LOW) {
      break;
    }
  }
  tone(pinoBuzzer, 2000, 100);
  delay(100);
  noTone(pinoBuzzer);
}


void vitoria() {
  int melodia[] = {
    NOTE_G3/2,NOTE_C3,NOTE_E3,NOTE_G3,NOTE_C3*2,NOTE_E3*2,NOTE_G3*2,NOTE_E3*2,
    NOTE_GS3/2,NOTE_C3,NOTE_DS3,NOTE_GS3,NOTE_C3*2,NOTE_DS3*2,NOTE_GS3*2,NOTE_DS3*2,
    NOTE_AS3/2,NOTE_D3,NOTE_F3,NOTE_AS3,NOTE_D3*2,NOTE_F3*2,NOTE_AS3*2,NOTE_AS3*2,NOTE_AS3*2,NOTE_AS3*2,
    NOTE_C3*4
  };
  
  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  int duracaoNotas[] = {
    12,12,12,12,12,12,4,4,
    12,12,12,12,12,12,4,4,
    12,12,12,12,12,12,4,12,12,12,
    1
  };

  for (int nota = 0; nota < 27; nota++) {
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    int duracaoNota = 1000 / duracaoNotas[nota];
    tone(5, 2*melodia[nota], duracaoNota);
    // para distinguir as notas, adicione um tempo minimo entre elas.
    // duracao da nota + 30% parece funcionar bem:
    int pausaEntreNotas = duracaoNota + 50;
    //delay(40);
    delay(pausaEntreNotas);    
    // parar a funcao tone:
    noTone(5);
  }
}
